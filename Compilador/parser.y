%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "ast.h"
#include "tabela.h"

NoAST* raiz_ast = NULL;  // Raiz da AST global

int yylex(void);                     // Função gerada pelo flex para o analisador léxico
void yyerror(const char *s);         // Função para reportar erros de sintaxe
void type_error(const char* expected, const char* got, const char* var_name);  // Função para erros de tipo
int linha_atual = 1;                 // Variável global para rastrear número da linha atual

// Variáveis para geração de código C
FILE* output_file = NULL;            // Arquivo de saída para código C (ou stdout)
int indent_level = 0;                // Nível de indentação atual para código C
%}

%union {
    int intValue;    // Para números inteiros
    char* id;        // Para identificadores
    char* str;       // Para strings
    float floatValue; // Para números de ponto flutuante
    char charValue;   // Para caracteres
    NoAST* ast;       // Para nós da AST
}

// Tokens para operadores
%token <str> operador_mais
%token <str> operador_menos
%token <str> operador_multiplicacao
%token <str> operador_divisao

// Token para atribuição
%token <str> atribuicao_igual

// Tokens para comandos
%token comando_print
%token comando_if
%token comando_else
%token comando_while
%token comando_for
%token comando_in
%token comando_range

// Tokens para comparadores
%token <str> comparador_igual
%token <str> comparador_diferente
%token <str> comparador_maior_que
%token <str> comparador_menor_que
%token <str> comparador_maior_igual
%token <str> comparador_menor_igual

// Tokens para variáveis e valores
%token <intValue> NUM
%token <id> ID
%token caracter_abreParentese
%token caracter_fechaParentese
%token caracter_doispontos
%token <str> FRASE

// Tokens para caracteres especiais
%token caracter_pontoEVirgula
%token caracter_abreChave
%token caracter_fechaChave

// Associação de tipos para as regras gramaticais
%type <str> expressao
%type <str> comparador
%type <str> comparacao
%type <str> stmt statement print condicional loop_while loop_for
%type <ast> expr          // Expressões retornam um nó AST
%type <ast> stmt          // Comandos retornam um nó AST
%type <ast> stmt_list     // Lista de comandos retorna um nó AST
%type <ast> block         // Blocos de código retornam um nó AST
%type <ast> assign        // Atribuições retornam um nó AST
%type <ast> print         // Comandos print retornam um nó AST
%type <ast> if_stmt       // Comandos if retornam um nó AST
%type <ast> program       // Programa retorna um nó AST
%type <ast> decl          // Declarações retornam um nó AST
%type <ast> cond          // Condições retornam um nó AST
%type <str> comp          // Comparadores retornam uma string
%type <ast> if_cond       // Condição do if retorna um nó AST

// Definição de precedência e associatividade
%left OR
%left AND
%nonassoc comparador_igual comparador_diferente comparador_maior_que comparador_menor_que comparador_maior_igual comparador_menor_igual // Operadores de comparação não são associativos
%left operador_mais operador_menos      // + e - têm mesma precedência, associativos à esquerda
%left operador_multiplicacao operador_divisao    // * e / têm precedência maior que + e -, associativos à esquerda

// Resolução do conflito do dangling else
%nonassoc LOWER_THAN_ELSE  // Precedência mais baixa para if sem else
%nonassoc comando_else             // Precedência mais alta para else

// Definição do símbolo inicial da gramática
%start program

%%

// Início da gramática

// Um programa é uma sequência de declarações
program:
    stmt_list
    {
        $$ = criarNoPrograma($1);
        raiz_ast = $$; // Guarda a raiz da AST
        
        // Adiciona os includes padrão do C
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n\n");
        printf("int main() {\n");
    }
    | /* vazio */
    { 
        $$ = criarNoPrograma(NULL); 
        raiz_ast = $$; // Guarda a raiz da AST
        
        // Adiciona os includes padrão do C mesmo para programa vazio
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n\n");
        printf("int main() {\n");
        printf("    return 0;\n}");
    }
    ;

// Lista de instruções (stmts)
stmt_list:
    stmt
    {
        // Cria um nó de lista de comandos com um único comando
        $$ = criarNoListaCmd($1, NULL);
    }
    | stmt_list stmt
    {
        // Adiciona um comando à lista existente
        NoAST *ultimo = $1;
        while (ultimo->proximo) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = criarNoListaCmd($2, NULL);
        $$ = $1;
    }
    ;

// Tipos de declarações suportadas
stmt:
    decl caracter_pontoEVirgula     { $$ = $1; }
    | assign caracter_pontoEVirgula { $$ = $1; }
    | print caracter_pontoEVirgula  { $$ = $1; }
    | if_stmt          { $$ = $1; }
    ;

// Bloco de código (múltiplas declarações)
block:
    caracter_doispontos stmt
    {
        // Cria um bloco com um único comando
        $$ = criarNoBloco($2);
    }
    | caracter_doispontos caracter_abreChave stmt_list caracter_fechaChave
    {
        // Cria um bloco com múltiplos comandos
        $$ = criarNoBloco($3);
    }
    ;

// Declaração de variável
decl:
    INT ID
    {
        // Verifica se a variável já foi declarada
        if (buscarSimbolo($2)) {
            fprintf(stderr, "Aviso: Variável '%s' já foi declarada\n", $2);
            // Não causamos erro, apenas aviso - em Python, redeclaração é permitida
        }
        
        // Adiciona variável à tabela de símbolos
        inserirSimboloCompleto($2, "int", SIM_VARIAVEL, @1.first_line);
        
        // Cria nó de declaração na AST
        $$ = criarNoDecl("int", $2);
        
        // Gera código C para a declaração
        printf("    int %s;\n", $2);
        
        free($2);
    }
    ;

// Atribuição de valor
assign:
    ID ASSIGN expr
    {
        Simbolo *s = buscarSimbolo($1);
        if (!s) {
            // Em Python, todas as variáveis são declaradas implicitamente
            fprintf(stderr, "[AVISO] Linha %d: Implicitamente declarando variável '%s' como int\n", linha_atual, $1);
            inserirSimboloCompleto($1, "int", SIM_VARIAVEL, linha_atual);
            s = buscarSimbolo($1);
            
            // Gera a declaração em C
            printf("    int %s;\n", $1);
        }
        
        // Verificação simples de tipo para demonstração
        if (strcmp(s->tipo, "int") == 0) {
            if ($3->tipo == AST_NUM && $3->valor < 0) {
                type_error("int", "int negativo", $1);
                fprintf(stderr, "[AVISO] Linha %d: Valor negativo (%d) atribuído à variável '%s'\n",
                        linha_atual, $3->valor, $1);
                // Não vai gerar YYERROR, apenas aviso
            }
        }
        
        // Marca como inicializada e utilizada
        marcarInicializado($1);
        
        // Cria nó de atribuição na AST
        NoAST *id_node = criarNoId($1);
        $$ = criarNoAtrib(id_node, $3);
        
        // Gera código C para a atribuição
        printf("    %s = ", $1);
        imprimirAST($3);  // Imprime a expressão
        printf(";\n");
        
        // Se a expressão for um número constante, podemos atribuir o valor na tabela
        if ($3->tipo == AST_NUM) {
            atribuirValorInt($1, $3->valor);
        }
        
        free($1);  // Libera apenas o ID, a AST continua na memória
    }
    | ID ASSIGN error
    {
        // Tratamento de erro sintático em atribuição
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Expressão inválida na atribuição para a variável '%s'. Deve ser uma expressão válida\n", 
                linha_atual, $1);
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
        free($1);   // Libera memória do identificador
        $$ = NULL;  // Não há nó AST para retornar
    }
    | error ASSIGN expr 
    {
        // Tratamento de erro sintático em atribuição (lado esquerdo inválido)
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Identificador inválido no lado esquerdo da atribuição\n", linha_atual);
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
        liberarAST($3);  // Libera memória da AST
        $$ = NULL;  // Não há nó AST para retornar
    }
    ;

// Comando print
print:
    comando_print caracter_abreParentese expr caracter_fechaParentese
    {
        // Cria nó de impressão na AST
        $$ = criarNoPrint($3);
        
        // Gera código C para o printf
        printf("    printf(\"%%d\\n\", ");
        imprimirAST($3);  // Imprime a expressão em notação normal
        printf(");\n");
    }
    | comando_print caracter_abreParentese error caracter_fechaParentese 
    {
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Expressão inválida no print. Comando print deve receber uma expressão válida\n", linha_atual);
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
        $$ = NULL;  // Não há nó AST para retornar
    }
    | comando_print error
    {
        // Tratamento de erro sintático no print (formato)
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Comando print mal formatado. Sintaxe correta: print(expressão);\n", linha_atual);
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
        $$ = NULL;  // Não há nó AST para retornar
    }
    ;

// Nova regra auxiliar para condição do if para reduzir ambiguidade
if_cond:
    LPAREN cond RPAREN
    {
        $$ = $2;
    }
    | LPAREN error RPAREN
    {
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Condição inválida no if. Deve ser uma expressão booleana válida ou comparação\n", linha_atual);
        yyerrok;
        yyclearin;
        $$ = NULL;
    }
    ;

// Comando condicional if
if_stmt:
    comando_if if_cond block %prec LOWER_THAN_ELSE
    {
        // Cria nó if na AST
        $$ = criarNoIf($2, $3);
        
        // Gera código C para o if
        printf("    if (");
        imprimirAST($2);  // Imprime a condição
        printf(") {\n");
        imprimirAST($3);  // Imprime o bloco
        printf("    }\n");
    }
    | comando_if if_cond block comando_else block
    {
        // Cria nó if-else na AST
        $$ = criarNoIfElse($2, $3, $5);
        
        // Gera código C para if-else
        printf("    if (");
        imprimirAST($2);  // Imprime a condição
        printf(") {\n");
        imprimirAST($3);  // Imprime o bloco if
        printf("    } else {\n");
        imprimirAST($5);  // Imprime o bloco else
        printf("    }\n");
    }
    | comando_if error 
    {
        // Tratamento de erro sintático no formato do if
        fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: Estrutura if mal formatada. Sintaxe correta: if (condição) : comando;\n", linha_atual);
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
        $$ = NULL;  // Não há nó AST para retornar
    }
    ;

// Condição para comando if
cond:
    expr comparador expr
    {
        // Determina o tipo de comparação
        TipoComparacao tipo_comp;
        if (strcmp($2, "==") == 0) tipo_comp = COMP_IGUAL;
        else if (strcmp($2, "!=") == 0) tipo_comp = COMP_DIFERENTE;
        else if (strcmp($2, ">") == 0) tipo_comp = COMP_MAIOR;
        else if (strcmp($2, "<") == 0) tipo_comp = COMP_MENOR;
        else if (strcmp($2, ">=") == 0) tipo_comp = COMP_MAIOR_IGUAL;
        else if (strcmp($2, "<=") == 0) tipo_comp = COMP_MENOR_IGUAL;
        
        // Cria nó de comparação na AST
        $$ = criarNoComp(tipo_comp, $1, $3);
        
        free($2);  // Libera a string do comparador
    }
    | expr
    {
        // Qualquer expressão pode ser usada como condição
        $$ = $1;
    }
    ;

// Operadores de comparação
comp:
    comparador_maior_que { $$ = strdup(">"); }
    | comparador_menor_que { $$ = strdup("<"); }
    | comparador_maior_igual { $$ = strdup(">="); }
    | comparador_menor_igual { $$ = strdup("<="); }
    | comparador_igual { $$ = strdup("=="); }
    | comparador_diferente { $$ = strdup("!="); }
    ;

// Regras para expressões
expr:
    NUM { $$ = criarNoNum($1); }  // Expressão numérica
    | ID {
        // Verificação de declaração de variável
        Simbolo *s = buscarSimbolo($1);
        if (!s) {
            // Em Python, variáveis são declaradas implicitamente na primeira utilização
            fprintf(stderr, "[AVISO] Linha %d: Implicitamente declarando variável '%s' como int\n", linha_atual, $1);
            inserirSimboloCompleto($1, "int", SIM_VARIAVEL, linha_atual);
            s = buscarSimbolo($1);
            
            // Gera código C para declaração
            printf("    int %s;\n", $1);
        }
        
        // Verifica se a variável foi inicializada
        if (s && !s->inicializado) {
            fprintf(stderr, "[AVISO] Linha %d: Variável '%s' está sendo usada antes de receber um valor\n", linha_atual, $1);
        }
        
        // Marca a variável como utilizada
        if (s) marcarUtilizado($1);
        
        $$ = criarNoId($1);  // Cria nó para variável
        free($1);           // Libera memória do identificador
    }
    | caracter_abreParentese expr caracter_fechaParentese { $$ = $2; }
    | expr operador_mais expr { $$ = criarNoOp('+', $1, $3); }
    | expr operador_menos expr { $$ = criarNoOp('-', $1, $3); }
    | expr operador_multiplicacao expr { $$ = criarNoOp('*', $1, $3); }
    | expr operador_divisao expr {
        if ($3->tipo == AST_NUM && $3->valor == 0) {
            fprintf(stderr, "[ERRO ARITMÉTICO] Linha %d: Divisão por zero detectada em tempo de compilação\n", linha_atual);
            // CORREÇÃO: Usar YYABORT em vez de YYERROR para garantir que o parsing seja completamente interrompido
            YYABORT;  // Aborta completamente o parsing para o teste 10
        }
        
        // Cria o nó de operação de divisão
        $$ = criarNoOp('/', $1, $3);
        
        // Se não for constante, adiciona verificação em tempo de execução
        if ($3->tipo != AST_NUM) {
            printf("    // Verificação de divisão por zero adicionada\n");
            printf("    if (");
            // Imprime o divisor conforme seu tipo
            if ($3->tipo == AST_ID) {
                printf("%s", $3->nome);
            } else {
                // Para expressões mais complexas, imprime a expressão
                printf("(");
                imprimirAST($3);
                printf(")");
            }
            printf(" == 0) {\n");
            printf("        fprintf(stderr, \"[ERRO EM TEMPO DE EXECUÇÃO] Divisão por zero na expressão: ");
            
            // Imprime a expressão completa para fins de diagnóstico
            imprimirAST($1);
            printf(" / ");
            imprimirAST($3);
            
            printf("\\n\");\n");
            printf("        exit(1);\n");
            printf("    }\n");
        }
    }
    ;

%%

// Função chamada pelo Bison para reportar erros de sintaxe
void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTÁTICO] Linha %d: ", linha_atual);
    
    switch(yychar) {
        case comando_print:
            fprintf(stderr, "Comando print mal formatado. Sintaxe correta: print(expressão)\n");
            break;
            
        case atribuicao_igual:
            fprintf(stderr, "Atribuição inválida. Formato correto: identificador = expressão\n");
            break;
            
        case ID:
            fprintf(stderr, "Uso incorreto do identificador '%s'. Verifique se ele está sendo utilizado no contexto correto\n", yylval.id);
            break;
            
        case NUM:
            fprintf(stderr, "Uso incorreto do número '%d'. Os números devem ser usados em expressões ou atribuições\n", yylval.intValue);
            break;
            
        case comando_if:
            fprintf(stderr, "Estrutura if mal formatada. Sintaxe correta: if (condição) : comando\n");
            break;
            
        case comando_else:
            fprintf(stderr, "Erro no comando 'else': deve ser precedido por um 'if' e seguido por um bloco de código\n");
            break;
            
        case caracter_doispontos:
            fprintf(stderr, "Dois pontos ':' usado incorretamente. O ':' deve seguir uma condição ou preceder um bloco\n");
            break;
            
        case caracter_abreParentese:
            fprintf(stderr, "Parêntese de abertura '(' sem o correspondente parêntese de fechamento ')'\n");
            break;
            
        case caracter_fechaParentese:
            fprintf(stderr, "Parêntese de fechamento ')' sem o correspondente parêntese de abertura '('\n");
            break;
            
        case caracter_pontoEVirgula:
            fprintf(stderr, "Ponto e vírgula ';' usado incorretamente ou desnecessário\n");
            break;
            
        case operador_mais:
        case operador_menos:
        case operador_multiplicacao:
        case operador_divisao:
            fprintf(stderr, "Operador aritmético usado incorretamente. Deve estar entre duas expressões válidas\n");
            break;
            
        case comparador_igual:
        case comparador_diferente:
        case comparador_maior_que:
        case comparador_menor_que:
        case comparador_maior_igual:
        case comparador_menor_igual:
            fprintf(stderr, "Operador de comparação usado incorretamente. Deve estar entre duas expressões válidas\n");
            break;
            
        case caracter_abreChave:
            fprintf(stderr, "Chave de abertura '{' sem a correspondente chave de fechamento '}'\n");
            break;
            
        case caracter_fechaChave:
            fprintf(stderr, "Chave de fechamento '}' sem a correspondente chave de abertura '{'\n");
            break;
            
        default:
            if (strstr(s, "syntax error") != NULL) {
                fprintf(stderr, "Sintaxe inválida. Verifique a estrutura do seu código\n");
            } else if (strstr(s, "unexpected") != NULL) {
                fprintf(stderr, "Token inesperado. Verifique se não há símbolos fora de lugar\n");
            } else {
                fprintf(stderr, "%s\n", s);
            }
    }
}

// Função para reportar erros de tipo
void type_error(const char* expected, const char* got, const char* var_name) {
    fprintf(stderr, "[ERRO DE TIPO] Linha %d: Variável '%s' é do tipo '%s', mas recebeu valor do tipo '%s'\n",
            linha_atual, var_name, expected, got);
}

// Função adicional para verificar variáveis não utilizadas e imprimir a AST
int yyparse_and_check() {
    int result = yyparse();
    
    // Se o parsing foi bem-sucedido, adiciona o return 0; ao final do main()
    if (result == 0) {
        printf("    return 0;\n}\n");
        
        // Imprime a AST se solicitado
        if (raiz_ast != NULL) {
            fprintf(stderr, "\n[ÁRVORE DE SINTAXE ABSTRATA] Estrutura detalhada:\n");
            fprintf(stderr, "================================================\n");
            imprimirASTDetalhada(raiz_ast, 0);
            fprintf(stderr, "================================================\n");
            
            // Libera a memória da AST
            liberarAST(raiz_ast);
            raiz_ast = NULL;
        }
    }
    
    // Verifica variáveis não utilizadas
    verificarVariaveisNaoUtilizadas();
    
    return result;
}