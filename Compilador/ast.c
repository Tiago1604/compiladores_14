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
// Função para gerar código C a partir da AST
// Esta função percorre a AST e gera o código C correspondente
void gerar_funcoes(ASTNode *node, FILE *output) {
    if (!node) return;

    if (node->type == NODE_STMT_LIST) {
        gerar_funcoes(node->left, output);
        gerar_funcoes(node->right, output);
    } else if (node->type == NODE_FUNCTION_DEF) {
        // Cabeçalho da função
        fprintf(output, "void %s() {\n", node->value.sval);

        // 1) Coletar e declarar variáveis locais, com 1 nível de indentação (4 espaços)
        struct VarList *vars = NULL;
        collect_vars(node->right, &vars);
        for (struct VarList *cur = vars; cur; cur = cur->next) {
            fprintf(output, "    %s %s;\n",
                    cur->is_float ? "float" : "int",
                    cur->name);
        }

        // 2) Gerar o corpo da função, também com indentação de 1 nível
        gerar_codigo_c_interno(node->right, output, 1);

        // 3) Liberar a lista de variáveis
        while (vars) {
            struct VarList *tmp = vars;
            vars = vars->next;
            free(tmp);
        }

        // Fecha a função
        fprintf(output, "}\n\n");
    }
}



// Função principal para gerar código C a partir da AST


void gerar_codigo_c(ASTNode *node, FILE *output) {
    static bool header_printed = false;
    struct VarList *vars = NULL;

    // imprime o include apenas na primeira vez
    if (!header_printed) {
        fprintf(output, "#include <stdio.h>\n\n");
        header_printed = true;
    }

    // Primeiro: gerar as funções fora do main
    gerar_funcoes(node, output);

    // Agora o main
    collect_vars(node, &vars);
    fprintf(output, "int main() {\n");
    print_var_decls(vars, output);
    gerar_codigo_c_interno(node, output, 1);
    fprintf(output, "    return 0;\n}\n");

    while (vars) {
        struct ListaVar *tmp = vars;
        vars = vars->prox;
        free(tmp);
    }
}


// Função recursiva auxiliar para geração de código C com indentação

void gerar_codigo_c_interno(ASTNode *node, FILE *output, int indent) {
    if (!node) return;

    char ind[32];
    memset(ind, ' ', indent * 4);
    ind[indent * 4] = '\0';

    switch (node->type) {
        case NODE_FUNCTION_DEF:
            // Ignorar: as funções já foram geradas antes do main
            break;

        case NODE_STMT_LIST:
            gerar_codigo_c_interno(node->left, output, indent);
            if (node->right) gerar_codigo_c_interno(node->right, output, indent);
            break;

        case NODE_IF:
            fprintf(output, "%sif ", ind);
            gerar_codigo_c_interno(node->left, output, 0);
            fprintf(output, " {\n");
            gerar_codigo_c_interno(node->middle, output, indent + 1);
            fprintf(output, "%s}", ind);
            if (node->right) {
                fprintf(output, " else {\n");
                gerar_codigo_c_interno(node->right, output, indent + 1);
                fprintf(output, "%s}", ind);

            }
            fprintf(saida, "\n");
            break;


        case NODE_FOR:
            fprintf(output, "%sfor (int %s = 0; %s < ", ind, node->value.sval, node->value.sval);
            gerar_codigo_c_interno(node->left, output, 0);
            fprintf(output, "; %s++) {\n", node->value.sval);
            gerar_codigo_c_interno(node->right, output, indent + 1);
            fprintf(output, "%s}\n", ind);
            break;

        case NODE_PRINT: {

            const char *fmt = "%d";
            if (no->esquerda && no->esquerda->tipo == NO_FLUTUANTE) {
                fmt = "%f";
            }
            fprintf(saida, "%sprintf(\"%s\\n\", ", ind, fmt);
            gerar_codigo_c_interno(no->esquerda, saida, 0);
            fprintf(saida, ");\n");
            break;
        }

        case NODE_ASSIGNMENT:
            fprintf(output, "%s%s = ", ind, node->value.sval);
            gerar_codigo_c_interno(node->right, output, 0);
            fprintf(output, ";\n");
            break;

        case NODE_COMPARISON:
        case NODE_ARITHMETIC:
            fprintf(output, "(");
            gerar_codigo_c_interno(node->left, output, 0);
            fprintf(output, " %s ", get_op_string(node->op));
            gerar_codigo_c_interno(node->right, output, 0);
            fprintf(output, ")");
            break;

        case NODE_NUMBER:
            fprintf(output, "%d", node->value.ival);
            break;

        case NODE_FLOAT:
            fprintf(output, "%f", node->value.fval);
            break;

        case NODE_IDENTIFIER:
            fprintf(output, "%s", node->value.sval);

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

        case NODE_FUNCTION_DEF:
            printf("DEF %s\n", no->value.sval);
            imprimirAST(no->left, nivel + 1);    // range
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_PRINT:

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