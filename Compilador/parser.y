%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "ast.h"
#include "tabela.h"

int yylex(void);                     // Função gerada pelo flex para o analisador léxico
void yyerror(const char *s);         // Função para reportar erros de sintaxe
void type_error(const char* expected, const char* got, const char* var_name);  // Função para erros de tipo
%}

%union {
    int intValue;    // Para números inteiros
    char* id;        // Para identificadores
    char* str;       // Para strings
    float floatValue; // Para números de ponto flutuante
    char charValue;   // Para caracteres
    NoAST* ast;       // Para nós da AST
}

%code requires {
    #include "tipos.h"  // Inclui tipo NoAST no Bison
}

// Declaração de tokens para operadores relacionais
%token EQ NEQ GE LE GT LT
// Tokens para estruturas de controle
%token IF ELSE COLON
// Tokens para variáveis e valores
%token <id> ID
%token <intValue> NUM
// Tokens para outros elementos da linguagem
%token PRINT INT 
%token ASSIGN SEMICOLON LPAREN RPAREN
%token PLUS MINUS TIMES DIVIDE
%token FLOAT CHAR RETURN WHILE FOR
%token BREAK CONTINUE TRUE FALSE NONE
%token NOT AND OR IS LAMBDA
%token DEL GLOBAL NONLOCAL ASSERT
%token RAISE TRY EXCEPT FINALLY WITH
%token YIELD DEF CLASS
%token ASYNC AWAIT MATCH CASE TYPE
%token LBRACE RBRACE  // Tokens para chaves

// Associação de tipos para as regras gramaticais
%type <ast> expr      // Expressões retornam um nó AST
%type <str> comp      // Comparadores retornam uma string
%type <id> cond       // Condições retornam um id (string)

// Definição de precedência e associatividade
%left PLUS MINUS      // + e - têm mesma precedência, associativos à esquerda
%left TIMES DIVIDE    // * e / têm precedência maior que + e -, associativos à esquerda
%nonassoc COLON       // : não é associativo
%nonassoc ELSE        // else não é associativo

%%

// Inicio da gramática

// Um programa é uma sequência de declarações
program:
    program stmt     // Um programa pode ter várias declarações
    |                // Ou pode ser vazio
    ;

// Tipos de declarações suportadas
stmt:
    decl             // Declaração de variável
    | assign         // Atribuição de valor
    | print          // Comando de impressão
    | if_stmt        // Comando condicional
    | block          // Blocos de código
    ;

// Bloco de código (múltiplas declarações)
block:
    COLON
    stmt 
    | COLON LBRACE 
    stmt_list RBRACE
    ;

// Lista de instruções dentro de um bloco
stmt_list:
    stmt                       // Uma única instrução
    | stmt_list stmt           // Múltiplas instruções
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
        
        // Adiciona variável à tabela de símbolos com informações mais completas
        // Usando o número da linha atual do parser
        inserirSimboloCompleto($2, "int", SIM_VARIAVEL, @1.first_line);
        printf("int %s;\n", $2);    // Gera código C para a declaração
        free($2);                   // Libera a memória alocada para o identificador
    }
    ;

// Atribuição de valor
assign:
    ID ASSIGN expr
    {
        // Busca variável na tabela de símbolos
        Simbolo *s = buscarSimbolo($1);
        if (!s) {
            // No Python, podemos usar variáveis antes de declará-las (convertemos para C)
            fprintf(stderr, "Aviso: Implicitamente declarando variável '%s' como int\n", $1);
            inserirSimboloCompleto($1, "int", SIM_VARIAVEL, @1.first_line);
            s = buscarSimbolo($1);
        }
        
        // Verificação simples de tipo para demonstração
        if (strcmp(s->tipo, "int") == 0) {
            if ($3->tipo == AST_NUM && $3->valor < 0) {
                type_error("int", "int negativo", $1);
                // Não vai gerar YYERROR, apenas aviso
            }
        }
        
        // Marca como inicializada e utilizada
        marcarInicializado($1);
        
        // Gera código C para a atribuição
        printf("%s = ", $1);
        imprimirAST($3);  // Imprime a expressão
        printf(";\n");
        
        // Se a expressão for um número constante, podemos atribuir o valor na tabela
        if ($3->tipo == AST_NUM) {
            atribuirValorInt($1, $3->valor);
        }
        
        liberarAST($3);   // Libera memória da AST
        free($1);         // Libera memória do identificador
    }
    | ID ASSIGN error SEMICOLON {
        // Tratamento de erro sintático em atribuição
        fprintf(stderr, "[ERRO SINTATICO] Expressão inválida na atribuição. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    | error SEMICOLON {
        // Tratamento de erro sintático genérico
        fprintf(stderr, "[ERRO SINTATICO] Atribuição mal formatada. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    ;

// Comando print
print:
    PRINT LPAREN ID RPAREN
    {
        // Verifica se a variável existe na tabela de símbolos
        Simbolo *s = buscarSimbolo($3);
        if (!s) {
            fprintf(stderr, "Erro: Variável '%s' não foi declarada\n", $3);
            YYERROR;  // Reporta erro ao Bison
        }
        
        // Marca a variável como utilizada
        marcarUtilizado($3);
        
        // Gera código C para o printf
        printf("printf(\"%%d\\n\", %s);\n", $3);
        free($3);  // Libera memória do identificador
    }
    | PRINT LPAREN NUM RPAREN
    {
        // Gera código C para imprimir uma constante
        printf("printf(\"%%d\\n\", %d);\n", $3);
    }
    | PRINT LPAREN expr RPAREN
    {
        // Gera código C para imprimir uma expressão
        printf("printf(\"%%d\\n\", ");
        imprimirAST($3);  // Imprime a expressão em notação normal
        printf(");\n");
        // Imprime a AST em ordem (implementação da travessia em ordem)
        printf("Impressão em ordem da AST: ");
        imprimirASTEmOrdem($3);
        printf("\n");
        liberarAST($3);  // Libera memória da AST
    }
    | PRINT LPAREN error RPAREN SEMICOLON {
        // Tratamento de erro sintático no print
        fprintf(stderr, "[ERRO SINTATICO] Expressão inválida no print. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    | PRINT error SEMICOLON {
        // Tratamento de erro sintático no print (formato)
        fprintf(stderr, "[ERRO SINTATICO] Comando print mal formatado. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    ;

// Comando condicional if
if_stmt:
    IF LPAREN cond RPAREN block
    {
        // Gera código C para o if
        printf("if (%s) {\n    // Código do bloco if\n}\n", $3);
        free($3);  // Libera memória da condição
    }
    | IF LPAREN cond RPAREN block ELSE block
    {
        // Gera código C para if-else
        printf("if (%s) {\n    // Código do bloco if\n} else {\n    // Código do bloco else\n}\n", $3);
        free($3);  // Libera memória da condição
    }
    | IF LPAREN error RPAREN block SEMICOLON {
        // Tratamento de erro sintático na condição do if
        fprintf(stderr, "[ERRO SINTATICO] Condição inválida no if. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    | IF error SEMICOLON {
        // Tratamento de erro sintático no formato do if
        fprintf(stderr, "[ERRO SINTATICO] Estrutura if mal formatada. Pulando até ';'\n");
        yyerrok;    // Indica ao Bison que o erro foi recuperado
        yyclearin;  // Limpa token de erro no buffer
    }
    ;

// Condição para comando if
cond:
    expr comp expr
    {
        // Cria uma string representando a condição
        char buffer[256] = "";
        char temp[128] = "";
        
        strcat(buffer, "(");
        
        // Captura a representação da primeira expressão
        switch($1->tipo) {
            case AST_NUM:
                sprintf(temp, "%d", $1->valor);
                strcat(buffer, temp);
                break;
            case AST_ID:
                strcat(buffer, $1->nome);
                break;
            case AST_OP:
                // Para operações, usamos parênteses para preservar a precedência
                strcat(buffer, "(");
                
                // Recursivamente construir a representação para o lado esquerdo
                if ($1->esquerda) {
                    if ($1->esquerda->tipo == AST_NUM) {
                        sprintf(temp, "%d", $1->esquerda->valor);
                        strcat(buffer, temp);
                    } else if ($1->esquerda->tipo == AST_ID) {
                        strcat(buffer, $1->esquerda->nome);
                    }
                }
                
                // Adiciona o operador
                sprintf(temp, " %c ", $1->operador);
                strcat(buffer, temp);
                
                // Recursivamente construir a representação para o lado direito
                if ($1->direita) {
                    if ($1->direita->tipo == AST_NUM) {
                        sprintf(temp, "%d", $1->direita->valor);
                        strcat(buffer, temp);
                    } else if ($1->direita->tipo == AST_ID) {
                        strcat(buffer, $1->direita->nome);
                    }
                }
                
                strcat(buffer, ")");
                break;
        }
        
        // Adiciona o operador de comparação
        sprintf(temp, " %s ", $2);
        strcat(buffer, temp);
        
        // Captura a representação da segunda expressão
        switch($3->tipo) {
            case AST_NUM:
                sprintf(temp, "%d", $3->valor);
                strcat(buffer, temp);
                break;
            case AST_ID:
                strcat(buffer, $3->nome);
                break;
            case AST_OP:
                // Para operações, usamos parênteses para preservar a precedência
                strcat(buffer, "(");
                
                // Recursivamente construir a representação para o lado esquerdo
                if ($3->esquerda) {
                    if ($3->esquerda->tipo == AST_NUM) {
                        sprintf(temp, "%d", $3->esquerda->valor);
                        strcat(buffer, temp);
                    } else if ($3->esquerda->tipo == AST_ID) {
                        strcat(buffer, $3->esquerda->nome);
                    }
                }
                
                // Adiciona o operador
                sprintf(temp, " %c ", $3->operador);
                strcat(buffer, temp);
                
                // Recursivamente construir a representação para o lado direito
                if ($3->direita) {
                    if ($3->direita->tipo == AST_NUM) {
                        sprintf(temp, "%d", $3->direita->valor);
                        strcat(buffer, temp);
                    } else if ($3->direita->tipo == AST_ID) {
                        strcat(buffer, $3->direita->nome);
                    }
                }
                
                strcat(buffer, ")");
                break;
        }
        
        strcat(buffer, ")");
        $$ = strdup(buffer);  // Retorna a string criada
        free($2);           // Libera memória do comparador
        liberarAST($1);     // Libera árvore da primeira expressão
        liberarAST($3);     // Libera árvore da segunda expressão
    }
    | ID { $$ = strdup($1); }  // Condição simples (apenas um identificador)
    ;

// Operadores de comparação
comp:
    GT { $$ = strdup(">"); }   // Maior que
    | LT { $$ = strdup("<"); } // Menor que
    | GE { $$ = strdup(">="); } // Maior ou igual a
    | LE { $$ = strdup("<="); } // Menor ou igual a
    | EQ { $$ = strdup("=="); } // Igual a
    | NEQ { $$ = strdup("!="); } // Diferente de
    ;

// Regras para expressões
expr:
    NUM { $$ = criarNoNum($1); }  // Expressão numérica
    | ID {
        // Verificação de declaração de variável
        Simbolo *s = buscarSimbolo($1);
        if (!s) {
            // Em Python, variáveis podem ser usadas antes de declaradas
            fprintf(stderr, "Aviso: Implicitamente declarando variável '%s' como int\n", $1);
            inserirSimboloCompleto($1, "int", SIM_VARIAVEL, @1.first_line);
        } else {
            // Marca a variável como utilizada
            marcarUtilizado($1);
        }
        $$ = criarNoId($1);  // Cria nó para variável
        free($1);           // Libera memória do identificador
    }
    | LPAREN expr RPAREN { $$ = $2; }  // Expressão entre parênteses
    | expr PLUS expr { $$ = criarNoOp('+', $1, $3); }  // Adição
    | expr MINUS expr { $$ = criarNoOp('-', $1, $3); }  // Subtração
    | expr TIMES expr { $$ = criarNoOp('*', $1, $3); }  // Multiplicação
    | expr DIVIDE expr {
        // Verifica divisão por zero se o divisor for uma constante
        if ($3->tipo == AST_NUM && $3->valor == 0) {
            fprintf(stderr, "Erro: Divisão por zero detectada\n");
            YYERROR;  // Reporta erro ao Bison
        }
        
        // Cria o nó de operação de divisão
        $$ = criarNoOp('/', $1, $3);
        
        // Se não for constante, adiciona verificação em tempo de execução
        if ($3->tipo != AST_NUM) {
            printf("// Verificação de divisão por zero adicionada\n");
            printf("if (");
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
            printf("    fprintf(stderr, \"Erro em tempo de execução: Divisão por zero\\n\");\n");
            printf("    exit(1);\n");
            printf("}\n");
        }
    }
    ;

%%

// Função chamada pelo Bison para reportar erros de sintaxe
void yyerror(const char *s) {
    switch(yychar) {
        case INT:
            if (yylval.id == NULL)
                fprintf(stderr, "Erro: Declaração 'int' deve ser seguida de um identificador válido\n");
            break;
            
        case ASSIGN:
            fprintf(stderr, "Erro: Atribuição inválida. Formato correto: identificador = expressão\n");
            break;
            
        case ID:
            fprintf(stderr, "Erro: Uso incorreto de identificador '%s'\n", yylval.id);
            break;
            
        case NUM:
            fprintf(stderr, "Erro: Uso incorreto do número '%d'\n", yylval.intValue);
            break;
            
        case PRINT:
            fprintf(stderr, "Erro: Comando print mal formatado. Use: print(expressão)\n");
            break;
            
        case IF:
            fprintf(stderr, "Erro: Estrutura if mal formatada. Use: if (condição) : comando\n");
            break;
            
        case ELSE:
            fprintf(stderr, "Erro: else deve ser precedido por um if\n");
            break;
            
        case COLON:
            fprintf(stderr, "Erro: ':' usado incorretamente\n");
            break;
            
        case LPAREN:
        case RPAREN:
            fprintf(stderr, "Erro: Parênteses não balanceados\n");
            break;
            
        default:
            fprintf(stderr, "Erro sintático: %s\n", s);
    }
}

// Função para reportar erros de tipo
void type_error(const char* expected, const char* got, const char* var_name) {
    fprintf(stderr, "Erro de tipo: Variável '%s' é do tipo '%s', mas recebeu valor do tipo '%s'\n",
            var_name, expected, got);
}

// Função adicional para verificar variáveis não utilizadas no final do parsing
int yyparse_and_check() {
    int result = yyparse();
    
    // Depois de terminar o parsing, verifica variáveis não utilizadas
    verificarVariaveisNaoUtilizadas();
    
    return result;
}