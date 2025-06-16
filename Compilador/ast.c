#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include <stdbool.h>

// Funções de criação de nós da árvore sintática
No *criar_no(enum TipoNo tipo, No *esquerda, No *direita) {
    No *no = malloc(sizeof(No));
    no->tipo = tipo;
    no->esquerda = esquerda;
    no->direita = direita;
    no->meio = NULL;
    return no;
}

No *criar_funcao(char *nome, No *params, No *corpo) {
    No *no = criar_no(NO_DEF_FUNCAO, params, corpo);
    no->valor.sval = strdup(nome);
    return no;
}

No *criar_if(No *condicao, No *corpo_if, No *corpo_else) {
    No *no = criar_no(NO_IF, condicao, corpo_else);
    no->meio = corpo_if;
    return no;
}

No *criar_for(char *var, No *alcance, No *corpo) {
    No *no = criar_no(NO_FOR, alcance, corpo);
    no->valor.sval = strdup(var);
    return no;
}

No *criar_print(No *expr) {
    return criar_no(NO_PRINT, expr, NULL);
}

No *criar_atribuicao(char *var, No *expr) {
    No *no = criar_no(NO_ATRIBUICAO, NULL, expr);
    no->valor.sval = strdup(var);
    return no;
}

No *criar_comparacao(enum TipoOp op, No *esquerda, No *direita) {
    No *no = criar_no(NO_COMPARACAO, esquerda, direita);
    no->op = op;
    return no;
}

No *criar_aritmetico(enum TipoOp op, No *esquerda, No *direita) {
    No *no = criar_no(NO_ARITMETICO, esquerda, direita);
    no->op = op;
    return no;
}

No *criar_numero(int valor) {
    No *no = criar_no(NO_NUMERO, NULL, NULL);
    no->valor.ival = valor;
    return no;
}

No *criar_flutuante(float valor) {
    No *no = criar_no(NO_FLUTUANTE, NULL, NULL);
    no->valor.fval = valor;
    return no;
}

No *criar_identificador(char *nome) {
    No *no = criar_no(NO_IDENTIFICADOR, NULL, NULL);
    no->valor.sval = strdup(nome);
    return no;
}

// Função auxiliar para obter o símbolo da operação
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

// Estrutura para armazenar variáveis já declaradas
struct ListaVar {
    char nome[64];
    bool eh_flutuante;
    struct ListaVar *prox;
};

// Função auxiliar para checar se variável já foi declarada e seu tipo
static struct ListaVar *buscar_var(struct ListaVar *vars, const char *nome) {
    while (vars) {
        if (strcmp(vars->nome, nome) == 0) return vars;
        vars = vars->prox;
    }
    return NULL;
}

// Função para determinar se um nó é flutuante
static bool eh_no_flutuante(No *no) {
    if (!no) return false;
    if (no->tipo == NO_FLUTUANTE) return true;
    if (no->tipo == NO_ARITMETICO) {
        // Se qualquer lado for flutuante, resultado é flutuante
        return eh_no_flutuante(no->esquerda) || eh_no_flutuante(no->direita);
    }
    if (no->tipo == NO_IDENTIFICADOR) {
        // Não é possível saber aqui, assume inteiro
        return false;
    }
    return false;
}

// Função auxiliar para adicionar variável à lista
void adicionar_var(struct ListaVar **vars, const char *nome, bool eh_flutuante) {
    struct ListaVar *v = buscar_var(*vars, nome);
    if (v) {
        if (eh_flutuante) v->eh_flutuante = true;
        return;
    }
    struct ListaVar *nova_var = malloc(sizeof(struct ListaVar));
    strncpy(nova_var->nome, nome, 63);
    nova_var->nome[63] = '\0';
    nova_var->eh_flutuante = eh_flutuante;
    nova_var->prox = *vars;
    *vars = nova_var;
}

// Função para coletar variáveis
void coletar_vars(No *no, struct ListaVar **vars) {
    if (!no) return;
    switch (no->tipo) {
        case NO_ATRIBUICAO:
            adicionar_var(vars, no->valor.sval, eh_no_flutuante(no->direita));
            coletar_vars(no->direita, vars);
            break;
        case NO_LISTA_COMANDOS:
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_IF:
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->meio, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_FOR:
            adicionar_var(vars, no->valor.sval, false);
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        case NO_PRINT:
            coletar_vars(no->esquerda, vars);
            break;
        case NO_COMPARACAO:
        case NO_ARITMETICO:
            coletar_vars(no->esquerda, vars);
            coletar_vars(no->direita, vars);
            break;
        default:
            break;
    }
}

// Função para imprimir declarações de variáveis
void imprimir_decl_vars(struct ListaVar *vars, FILE *saida) {
    struct ListaVar *atual = vars;
    while (atual) {
        fprintf(saida, "%s %s;\n", atual->eh_flutuante ? "float" : "int", atual->nome);
        atual = atual->prox;
    }
}

// Função principal de geração de código C
void gerar_codigo_c(No *no, FILE *saida) {
    struct ListaVar *vars = NULL;
    coletar_vars(no, &vars);
    fprintf(saida, "int main() {\n");
    imprimir_decl_vars(vars, saida);
    gerar_codigo_c_interno(no, saida, 1);
    fprintf(saida, "    return 0;\n}\n");
    while (vars) {
        struct ListaVar *tmp = vars;
        vars = vars->prox;
        free(tmp);
    }
}

// Função recursiva auxiliar para geração de código C com indentação
void gerar_codigo_c_interno(No *no, FILE *saida, int indent) {
    if (!no) return;
    char ind[32];
    memset(ind, ' ', indent * 4);
    ind[indent * 4] = '\0';
    switch (no->tipo) {
        case NO_LISTA_COMANDOS:
            gerar_codigo_c_interno(no->esquerda, saida, indent);
            if (no->direita) gerar_codigo_c_interno(no->direita, saida, indent);
            break;
        case NO_IF:
            fprintf(saida, "%sif ", ind);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, " {\n");
            gerar_codigo_c_interno(no->meio, saida, indent + 1);
            fprintf(saida, "%s}", ind);
            if (no->direita) {
                fprintf(saida, " else {\n");
                gerar_codigo_c_interno(no->direita, saida, indent + 1);
                fprintf(saida, "%s}", ind);
            }
            fprintf(saida, "\n");
            break;
        case NO_FOR:
            fprintf(saida, "%sfor (int %s = 0; %s < ", ind, no->valor.sval, no->valor.sval);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, "; %s++) {\n", no->valor.sval);
            gerar_codigo_c_interno(no->direita, saida, indent + 1);
            fprintf(saida, "%s}\n", ind);
            break;
        case NO_PRINT: {
            const char *fmt = "%d";
            if (no->esquerda && no->esquerda->tipo == NO_FLUTUANTE) {
                fmt = "%f";
            }
            fprintf(saida, "%sprintf(\"%s\\n\", ", ind, fmt);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, ");\n");
            break;
        }
        case NO_ATRIBUICAO:
            fprintf(saida, "%s%s = ", ind, no->valor.sval);
            gerar_codigo_c_interno(no->direita, saida, 0);
            fprintf(saida, ";\n");
            break;
        case NO_COMPARACAO:
        case NO_ARITMETICO:
            fprintf(saida, "(");
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, " %s ", obter_string_op(no->op));
            gerar_codigo_c_interno(no->direita, saida, 0);
            fprintf(saida, ")");
            break;
        case NO_NUMERO:
            fprintf(saida, "%d", no->valor.ival);
            break;
        case NO_FLUTUANTE:
            fprintf(saida, "%f", no->valor.fval);
            break;
        case NO_IDENTIFICADOR:
            fprintf(saida, "%s", no->valor.sval);
            break;
        default:
            break;
    }
}

// Impressão textual da AST para debug
void imprimirAST(No *no, int nivel) {
    if (!no) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    switch (no->tipo) {
        case NO_LISTA_COMANDOS:
            printf("LISTA_COMANDOS\n");
            imprimirAST(no->esquerda, nivel + 1);
            imprimirAST(no->direita, nivel + 1);
            break;
        case NO_IF:
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
            printf("FOR var=%s\n", no->valor.sval);
            imprimirAST(no->esquerda, nivel + 1);    // alcance
            imprimirAST(no->direita, nivel + 1);   // corpo
            break;
        case NO_PRINT:
            printf("PRINT\n");
            imprimirAST(no->esquerda, nivel + 1);
            break;
        case NO_ATRIBUICAO:
            printf("ATRIBUIR %s\n", no->valor.sval);
            imprimirAST(no->direita, nivel + 1);
            break;
        case NO_COMPARACAO:
            printf("COMPARACAO %s\n", obter_string_op(no->op));
            imprimirAST(no->esquerda, nivel + 1);
            imprimirAST(no->direita, nivel + 1);
            break;
        case NO_ARITMETICO:
            printf("ARITMETICO %s\n", obter_string_op(no->op));
            imprimirAST(no->esquerda, nivel + 1);
            imprimirAST(no->direita, nivel + 1);
            break;
        case NO_NUMERO:
            printf("NUMERO %d\n", no->valor.ival);
            break;
        case NO_FLUTUANTE:
            printf("FLUTUANTE %f\n", no->valor.fval);
            break;
        case NO_IDENTIFICADOR:
            printf("IDENTIFICADOR %s\n", no->valor.sval);
            break;
        default:
            printf("NO tipo %d\n", no->tipo);
            break;
    }
}