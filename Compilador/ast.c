#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include <stdbool.h>
#include "tabela.h"


// Função base para criar qualquer tipo de nó na AST
// Aloca memória e inicializa os campos do nó
No *criar_no(enum TipoNo tipo, No *esquerda, No *direita) {
    No *no = malloc(sizeof(No));
    no->tipo = tipo;
    no->esquerda = esquerda;
    no->direita = direita;
    no->meio = NULL;
    return no;
}

// Cria um nó que representa uma definição de função
// nome: identificador da função
// params: lista de parâmetros (não implementado completamente)
// corpo: comandos dentro da função
No *criar_funcao(char *nome, No *params, No *corpo) {
    No *no = criar_no(NO_DEF_FUNCAO, params, corpo);
    no->valor.sval = strdup(nome);  // Duplica a string para evitar problemas de memória
    return no;
}

// Cria um nó para estrutura condicional if-else
// condicao: expressão a ser avaliada
// corpo_if: comandos executados se condição for verdadeira
// corpo_else: comandos executados se condição for falsa (pode ser NULL)
No *criar_if(No *condicao, No *corpo_if, No *corpo_else) {
    No *no = criar_no(NO_IF, condicao, corpo_else);
    no->meio = corpo_if;  // O nó if tem 3 filhos: condição, corpo_if e corpo_else
    return no;
}

// Cria um nó para loop for no estilo Python
// var: variável de iteração
// alcance: limite do loop (ex: range(10))
// corpo: comandos dentro do loop
No *criar_for(char *var, No *alcance, No *corpo) {
    No *no = criar_no(NO_FOR, alcance, corpo);
    no->valor.sval = strdup(var);  // Guarda o nome da variável de iteração
    return no;
}

// Cria um nó para loop while
// cond: condição para continuar o loop
// body: comandos dentro do loop
No *criar_while(No *cond, No *body) {
    No *no = criar_no(NO_WHILE, cond, body);
    return no;
}

// Cria um nó para comando de impressão
// expr: expressão a ser impressa
No *criar_print(No *expr) {
    return criar_no(NO_PRINT, expr, NULL);
}

// Cria um nó para atribuição de variável
// var: nome da variável 
// expr: expressão cujo valor será atribuído
No *criar_atribuicao(char *var, No *expr) {
    No *no = criar_no(NO_ATRIBUICAO, NULL, expr);
    no->valor.sval = strdup(var);  // Guarda o nome da variável
    return no;
}

// Cria um nó para operações de comparação (==, !=, <, >, <=, >=)
// op: tipo de operação de comparação
// esquerda/direita: operandos da comparação
No *criar_comparacao(enum TipoOp op, No *esquerda, No *direita) {
    No *no = criar_no(NO_COMPARACAO, esquerda, direita);
    no->op = op;  // Guarda o tipo de operação
    return no;
}

// Cria um nó para operações aritméticas (+, -, *, /)
// op: tipo de operação aritmética
// esquerda/direita: operandos da operação
No *criar_aritmetico(enum TipoOp op, No *esquerda, No *direita) {
    No *no = criar_no(NO_ARITMETICO, esquerda, direita);
    no->op = op;  // Guarda o tipo de operação
    return no;
}

// Cria um nó para representar um número inteiro literal
// valor: o valor do inteiro
No *criar_numero(int valor) {
    No *no = criar_no(NO_NUMERO, NULL, NULL);
    no->valor.ival = valor;  // Guarda o valor inteiro
    return no;
}

// Cria um nó para representar um número de ponto flutuante
// valor: o valor do float
No *criar_flutuante(float valor) {
    No *no = criar_no(NO_FLUTUANTE, NULL, NULL);
    no->valor.fval = valor;  // Guarda o valor float
    return no;
}

// Cria um nó para representar um identificador (nome de variável)
// nome: o nome do identificador
No *criar_identificador(char *nome) {
    No *no = criar_no(NO_IDENTIFICADOR, NULL, NULL);
    no->valor.sval = strdup(nome);  // Guarda o nome do identificador
    return no;
}

// Cria um nó para chamada de função
// nome: nome da função chamada
// args: argumentos para a função (pode ser NULL)
No *criar_chamada_funcao(char *nome, No *args) {
    No *no = criar_no(NO_CHAMADA_FUNCAO, args, NULL);
    no->valor.sval = strdup(nome);  // Guarda o nome da função
    return no;
}

// Cria um nó para representar uma string literal
// valor: conteúdo da string
No *criar_string(char *valor) {
    No *no = criar_no(NO_STRING, NULL, NULL);
    no->valor.sval = strdup(valor);  // Guarda o conteúdo da string
    return no;
}

// Converte o tipo de operação interno para sua representação em texto
// Útil para geração de código e depuração
const char *obter_string_op(enum TipoOp op) {
    switch (op) {
        case OP_MAIS: return "+";
        case OP_MENOS: return "-";
        case OP_VEZES: return "*";
        case OP_DIVIDE: return "/";
        case OP_IGUAL: return "==";
        case OP_DIFERENTE: return "!=";
        case OP_MENOR: return "<";
        case OP_MAIOR: return ">";
        case OP_MENOR_IGUAL: return "<=";
        case OP_MAIOR_IGUAL: return ">=";
        default: return "?";
    }
}

// Estrutura para manter uma lista de variáveis encontradas durante a geração de código
struct ListaVar {
    char nome[64];  // Nome da variável
    bool eh_flutuante;  // Tipo da variável (int ou float)
    struct ListaVar *prox;  // Ponteiro para próxima variável na lista
};

// Busca uma variável na lista pelo nome
// Retorna ponteiro para nó da lista se encontrado, NULL caso contrário
static struct ListaVar *buscar_var(struct ListaVar *vars, const char *nome) {
    while (vars) {
        if (strcmp(vars->nome, nome) == 0) return vars;
        vars = vars->prox;
    }
    return NULL;
}

// Verifica se uma expressão vai resultar em um valor de ponto flutuante
// Importante para determinar o tipo correto ao declarar variáveis
static bool eh_no_flutuante(No *no) {
    if (!no) return false;
    if (no->tipo == NO_FLUTUANTE) return true;
    if (no->tipo == NO_STRING) return false;  // String não é float
    if (no->tipo == NO_ARITMETICO) {
        // Se qualquer operando for float, o resultado é float
        return eh_no_flutuante(no->esquerda) || eh_no_flutuante(no->direita);
    }
    if (no->tipo == NO_IDENTIFICADOR) {
        // Se for variável, consulta a tabela de símbolos
        Simbolo *s = buscarSimbolo(no->valor.sval, 0);
        return s && s->tipo == TIPO_FLOAT;
    }
    return false;
}


// Adiciona uma variável à lista de variáveis
// Se a variável já existe e o novo tipo é float, promove a variável para float
void adicionar_var(struct ListaVar **vars, const char *nome, bool eh_flutuante) {
    struct ListaVar *v = buscar_var(*vars, nome);
    if (v) {
        // Variável já existe: se o novo é float, promove para float
        if (eh_flutuante) v->eh_flutuante = true;
        return;
    }
    // Criar nova variável na lista
    struct ListaVar *nova_var = malloc(sizeof(struct ListaVar));
    strncpy(nova_var->nome, nome, 63);
    nova_var->nome[63] = '\0';  // Garante terminação da string
    nova_var->eh_flutuante = eh_flutuante;
    nova_var->prox = *vars;
    *vars = nova_var;  // Insere no início da lista
}

// Percorre a AST coletando todas as variáveis usadas no programa
// Adiciona-as à lista de variáveis para posterior declaração em C
void coletar_vars(No *no, struct ListaVar **vars) {
    if (!no) return;
    switch (no->tipo) {
        case NO_ATRIBUICAO:
            // Quando encontra atribuição, adiciona a variável à lista
            adicionar_var(vars, no->valor.sval, eh_no_flutuante(no->direita));
            coletar_vars(no->direita, vars);
            break;
        case NO_LISTA_COMANDOS:
            // Percorre recursivamente a lista de comandos
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_IF:
            // Percorre todos os componentes do if-else
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->meio, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_FOR:
            // Percorre o range e corpo do loop
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_PRINT:
            // Verifica a expressão a ser impressa
            coletar_vars(no->esquerda, vars);
            break;
        case NO_COMPARACAO:
        case NO_ARITMETICO:
            // Verifica ambos os operandos
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        default:
            break;
    }
}

// Gera as declarações de variáveis no código C
// Imprime cada variável com seu tipo apropriado
void imprimir_decl_vars(struct ListaVar *vars, FILE *saida) {
    struct ListaVar *atual = vars;
    while (atual) {
        fprintf(saida, "    %s %s;\n", atual->eh_flutuante ? "float" : "int", atual->nome);
        atual = atual->prox;
    }
}

// Extrai comandos globais e definições de funções da AST
// Separa o que deve estar no escopo global do que deve estar dentro de funções
void extrair_comandos_globais(No *no, No **comandos_globais, No **definicoes_funcoes) {
    if (!no) return;
    
    if (no->tipo == NO_LISTA_COMANDOS) {
        // Percorre recursivamente a lista de comandos
        extrair_comandos_globais(no->esquerda, comandos_globais, definicoes_funcoes);
        extrair_comandos_globais(no->direita, comandos_globais, definicoes_funcoes);
    } else if (no->tipo == NO_DEF_FUNCAO) {
        // Encontrou definição de função - adiciona à lista específica
        No *novo_def = malloc(sizeof(No));
        *novo_def = *no;
        novo_def->esquerda = NULL;
        novo_def->direita = NULL;
        
        // Extrai apenas o corpo da função
        extrair_corpo_funcao(no->direita, &(novo_def->direita));
        
        // Adiciona à lista de definições de funções
        if (!*definicoes_funcoes) {
            *definicoes_funcoes = criar_no(NO_LISTA_COMANDOS, novo_def, NULL);
        } else {
            No *temp = *definicoes_funcoes;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, novo_def, NULL);
        }
        
        // CORREÇÃO: Extrai funções aninhadas incorretamente e outras definições globais
        extrair_funcoes_aninhadas(no->direita, comandos_globais, definicoes_funcoes);
    } else {
        // Comando global (não é função) - adiciona à lista de comandos globais
        if (!*comandos_globais) {
            *comandos_globais = criar_no(NO_LISTA_COMANDOS, no, NULL);
        } else {
            No *temp = *comandos_globais;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, no, NULL);
        }
    }
}

// Extrai apenas os comandos que formam o corpo de uma função
// Filtra comandos que deveriam estar no escopo global
void extrair_corpo_funcao(No *no, No **corpo) {
    if (!no) return;
    
    if (no->tipo == NO_LISTA_COMANDOS) {
        extrair_corpo_funcao(no->esquerda, corpo);
        // Para o corpo da função, só incluímos comandos que não são funções ou chamadas de função
        if (no->direita && no->direita->tipo != NO_CHAMADA_FUNCAO && no->direita->tipo != NO_DEF_FUNCAO) {
            extrair_corpo_funcao(no->direita, corpo);
        }
    } else if (no->tipo != NO_CHAMADA_FUNCAO && no->tipo != NO_DEF_FUNCAO) {
        // Adicionar comando ao corpo da função (exceto chamadas e definições de função)
        if (!*corpo) {
            *corpo = criar_no(NO_LISTA_COMANDOS, no, NULL);
        } else {
            No *temp = *corpo;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, no, NULL);
        }
    }
}

// Extrai comandos globais que foram incorretamente colocados dentro de funções
void extrair_comandos_globais_do_corpo(No *no, No **comandos_globais) {
    if (!no) return;
    
    if (no->tipo == NO_LISTA_COMANDOS) {
        extrair_comandos_globais_do_corpo(no->esquerda, comandos_globais);
        extrair_comandos_globais_do_corpo(no->direita, comandos_globais);
    } else if (no->tipo == NO_CHAMADA_FUNCAO) {
        // Esta é uma chamada de função que deveria estar no main
        if (!*comandos_globais) {
            *comandos_globais = criar_no(NO_LISTA_COMANDOS, no, NULL);
        } else {
            No *temp = *comandos_globais;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, no, NULL);
        }
    }
}

// Extrai funções que foram aninhadas incorretamente (dentro de outras funções)
// Em C, funções não podem ser aninhadas, então precisamos movê-las para o nível global
void extrair_funcoes_aninhadas(No *no, No **comandos_globais, No **definicoes_funcoes) {
    if (!no) return;
    
    if (no->tipo == NO_LISTA_COMANDOS) {
        extrair_funcoes_aninhadas(no->esquerda, comandos_globais, definicoes_funcoes);
        extrair_funcoes_aninhadas(no->direita, comandos_globais, definicoes_funcoes);
    } else if (no->tipo == NO_DEF_FUNCAO) {
        // Esta é uma função aninhada incorretamente - mover para o nível global
        No *novo_def = malloc(sizeof(No));
        *novo_def = *no;
        novo_def->esquerda = NULL;
        novo_def->direita = NULL;
        
        // Extrai apenas o corpo da função
        extrair_corpo_funcao(no->direita, &(novo_def->direita));
        
        // Adiciona à lista de definições globais
        if (!*definicoes_funcoes) {
            *definicoes_funcoes = criar_no(NO_LISTA_COMANDOS, novo_def, NULL);
        } else {
            No *temp = *definicoes_funcoes;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, novo_def, NULL);
        }
        
        // Recursivamente processa o corpo desta função também
        extrair_funcoes_aninhadas(no->direita, comandos_globais, definicoes_funcoes);
    } else if (no->tipo == NO_CHAMADA_FUNCAO) {
        // Esta é uma chamada de função que deveria estar no main
        if (!*comandos_globais) {
            *comandos_globais = criar_no(NO_LISTA_COMANDOS, no, NULL);
        } else {
            No *temp = *comandos_globais;
            while (temp->direita) temp = temp->direita;
            temp->direita = criar_no(NO_LISTA_COMANDOS, no, NULL);
        }
    }
}

// Gera o código C para todas as funções definidas no programa
// Para cada função, declara suas variáveis locais e traduz seus comandos
void gerar_funcoes(No *no, FILE *saida) {
    if (!no) return;

    if (no->tipo == NO_LISTA_COMANDOS) {
        gerar_funcoes(no->esquerda, saida);
        gerar_funcoes(no->direita, saida);
    } else if (no->tipo == NO_DEF_FUNCAO) {
        // Cabeçalho da função
        fprintf(saida, "void %s() {\n", no->valor.sval);

        // 1) Coletar e declarar variáveis locais, com indentação de 4 espaços
        struct ListaVar *vars = NULL;
        coletar_vars(no->direita, &vars);
        for (struct ListaVar *cur = vars; cur; cur = cur->prox) {
            fprintf(saida, "    %s %s;\n",
                    cur->eh_flutuante ? "float" : "int",
                    cur->nome);
        }

        // 2) Gerar o corpo da função, também com indentação
        gerar_codigo_c_interno(no->direita, saida, 1);

        // 3) Liberar a lista de variáveis
        while (vars) {
            struct ListaVar *tmp = vars;
            vars = vars->prox;
            free(tmp);
        }

        // Fecha a função
        fprintf(saida, "}\n\n");
    }
}

// Função principal que coordena a geração completa do código C
// Gera cabeçalhos, funções e o main()
void gerar_codigo_c(No *no, FILE *saida) {
    static bool header_printed = false;
    struct ListaVar *vars = NULL;
    No *comandos_globais = NULL;
    No *definicoes_funcoes = NULL;

    // Imprime o include apenas na primeira chamada
    if (!header_printed) {
        fprintf(saida, "#include <stdio.h>\n\n");
        header_printed = true;
    }

    // Separar comandos globais das definições de função
    extrair_comandos_globais(no, &comandos_globais, &definicoes_funcoes);

    // Primeiro: gerar as funções
    if (definicoes_funcoes) {
        gerar_funcoes(definicoes_funcoes, saida);
    }

    // Agora gera o main() - coletar variáveis apenas dos comandos globais
    coletar_vars(comandos_globais, &vars);
    fprintf(saida, "int main() {\n");
    imprimir_decl_vars(vars, saida);  // Declara as variáveis no início da função
    gerar_codigo_c_interno(comandos_globais, saida, 1);
    fprintf(saida, "    return 0;\n}\n");

    // Libera a memória da lista de variáveis
    while (vars) {
        struct ListaVar *tmp = vars;
        vars = vars->prox;
        free(tmp);
    }
}


// Função recursiva que traduz cada nó da AST para código C
// indent: nível de indentação para formatar o código gerado
void gerar_codigo_c_interno(No *no, FILE *saida, int indent) {
    if (!no) return;
    
    // Cria a string de indentação com espaços
    char ind[32];
    memset(ind, ' ', indent * 4);
    ind[indent * 4] = '\0';
    
    switch (no->tipo) {
        case NO_DEF_FUNCAO:
            // Ignorar: as funções já foram geradas antes do main
            break;
        case NO_LISTA_COMANDOS:
            // Processa cada comando na lista
            gerar_codigo_c_interno(no->esquerda, saida, indent);
            if (no->direita) gerar_codigo_c_interno(no->direita, saida, indent);
            break;
        case NO_IF:
            // Gera estrutura if-else em C
            fprintf(saida, "%sif ", ind);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, " {\n");
            gerar_codigo_c_interno(no->meio, saida, indent + 1);
            fprintf(saida, "%s}", ind);
            if (no->direita) {
                // Se tiver bloco else
                fprintf(saida, " else {\n");
                gerar_codigo_c_interno(no->direita, saida, indent + 1);
                fprintf(saida, "%s}", ind);
            }
            fprintf(saida, "\n");
            break;
        case NO_FOR:
            // Traduz for do Python para for em C
            fprintf(saida, "%sfor (int %s = 0; %s < ", ind, no->valor.sval, no->valor.sval);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, "; %s++) {\n", no->valor.sval);
            gerar_codigo_c_interno(no->direita, saida, indent + 1);
            fprintf(saida, "%s}\n", ind);
            break;
            
        case NO_WHILE:
            // Traduz while para C
            fprintf(saida, "%swhile (", ind);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, ") {\n");
            gerar_codigo_c_interno(no->direita, saida, indent + 1);
            fprintf(saida, "%s}\n", ind);
            break;
            
        case NO_PRINT: {
            // Traduz print para printf
            if (no->esquerda->tipo == NO_STRING) {
                // Caso especial para string literal
                fprintf(saida, "%sprintf(\"%s\\n\");\n", ind, no->esquerda->valor.sval);
            } else {
                // Para expressões numéricas, usa formato adequado
                bool is_float = eh_no_flutuante(no->esquerda);
                const char *fmt = is_float ? "%f" : "%d";
                fprintf(saida, "%sprintf(\"%s\\n\", ", ind, fmt);
                gerar_codigo_c_interno(no->esquerda, saida, 0);
                fprintf(saida, ");\n");
            }
            break;
        }
        case NO_ATRIBUICAO:
            // Traduz atribuição de variável
            fprintf(saida, "%s%s = ", ind, no->valor.sval);
            gerar_codigo_c_interno(no->direita, saida, 0);
            fprintf(saida, ";\n");
            break;
        case NO_COMPARACAO:
        case NO_ARITMETICO:
            // Traduz expressões aritméticas e comparações
            fprintf(saida, "(");
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, " %s ", obter_string_op(no->op));
            gerar_codigo_c_interno(no->direita, saida, 0);
            fprintf(saida, ")");
            break;
        case NO_NUMERO:
            // Número inteiro literal
            fprintf(saida, "%d", no->valor.ival);
            break;
        case NO_FLUTUANTE:
            // Número de ponto flutuante literal
            fprintf(saida, "%f", no->valor.fval);
            break;
        case NO_IDENTIFICADOR:
            // Nome de variável
            fprintf(saida, "%s", no->valor.sval);
            break;
        case NO_CHAMADA_FUNCAO:
            // Chamada de função
            fprintf(saida, "%s%s(", ind, no->valor.sval);
            // Por enquanto, assume que não há argumentos
            fprintf(saida, ");\n");
            break;
        case NO_STRING:
            // String literal
            fprintf(saida, "\"%s\"", no->valor.sval);
            break;
        default:
            break;
    }
}

// Função auxiliar que imprime a AST em formato legível para humanos
// Útil para depuração da estrutura gerada pelo parser
void imprimirAST(No *no, int nivel) {
    if (!no) return;
    
    // Indentação para visualização da hierarquia
    for (int i = 0; i < nivel; i++) printf("  ");
    
    switch (no->tipo) {
        case NO_LISTA_COMANDOS:
            // Lista de comandos sequenciais
            printf("LISTA_COMANDOS\n");
            imprimirAST(no->esquerda, nivel + 1);
            imprimirAST(no->direita, nivel + 1);
            break;
        case NO_IF:
            // Comando condicional if-else
            printf("IF\n");
            imprimirAST(no->esquerda, nivel + 1);    // condição
            for (int i = 0; i < nivel; i++) printf("  ");
            printf("ENTAO:\n");
            imprimirAST(no->meio, nivel + 1);  // então
            if (no->direita) {
                for (int i = 0; i < nivel; i++) printf("  ");
                printf("SENAO:\n");
                imprimirAST(no->direita, nivel + 1); // senão
            }
            break;
        case NO_FOR:
            // Loop for com variável e alcance
            printf("FOR var=%s\n", no->valor.sval);
            imprimirAST(no->esquerda, nivel + 1);    // alcance
            imprimirAST(no->direita, nivel + 1);   // corpo
            break;
        case NO_DEF_FUNCAO:
            // Definição de função
            printf("DEF %s\n", no->valor.sval);
            imprimirAST(no->esquerda, nivel + 1);    // parâmetros
            imprimirAST(no->direita, nivel + 1);     // corpo
            break;
        case NO_PRINT:
            // Comando de impressão
            printf("PRINT\n");
            imprimirAST(no->esquerda, nivel + 1);    // expressão a imprimir
            break;
        case NO_ATRIBUICAO:
            // Atribuição de variável
            printf("ATRIBUIR %s\n", no->valor.sval);
            imprimirAST(no->direita, nivel + 1);     // valor atribuído
            break;
        case NO_COMPARACAO:
            // Operação de comparação
            printf("COMPARACAO %s\n", obter_string_op(no->op));
            imprimirAST(no->esquerda, nivel + 1);    // operando esquerdo
            imprimirAST(no->direita, nivel + 1);     // operando direito
            break;
        case NO_ARITMETICO:
            // Operação aritmética
            printf("ARITMETICO %s\n", obter_string_op(no->op));
            imprimirAST(no->esquerda, nivel + 1);    // operando esquerdo
            imprimirAST(no->direita, nivel + 1);     // operando direito
            break;
        case NO_NUMERO:
            // Número inteiro literal
            printf("NUMERO %d\n", no->valor.ival);
            break;
        case NO_FLUTUANTE:
            // Número flutuante literal
            printf("FLUTUANTE %f\n", no->valor.fval);
            break;
        case NO_IDENTIFICADOR:
            // Nome de variável
            printf("IDENTIFICADOR %s\n", no->valor.sval);
            break;
        case NO_STRING:
            // String literal
            printf("STRING \"%s\"\n", no->valor.sval);
            break;
        default:
            // Nó de tipo desconhecido/não implementado
            printf("NO tipo %d\n", no->tipo);
            break;
    }
}