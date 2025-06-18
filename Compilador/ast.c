#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include <stdbool.h>

// Funções de criação de nós da árvore sintática
ASTNode *criar_no(enum NodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->middle = NULL;
    return node;
}

ASTNode *criar_function_def(char *name, ASTNode *params, ASTNode *body) {
    ASTNode *node = criar_no(NODE_FUNCTION_DEF, params, body);
    node->value.sval = strdup(name);
    return node;
}

ASTNode *criar_if(ASTNode *condition, ASTNode *if_body, ASTNode *else_body) {
    ASTNode *node = criar_no(NODE_IF, condition, else_body);
    node->middle = if_body;
    return node;
}

ASTNode *criar_for(char *var, ASTNode *range, ASTNode *body) {
    ASTNode *node = criar_no(NODE_FOR, range, body);
    node->value.sval = strdup(var);
    return node;
}

ASTNode *criar_print(ASTNode *expr) {
    return criar_no(NODE_PRINT, expr, NULL);
}

ASTNode *criar_assignment(char *var, ASTNode *expr) {
    ASTNode *node = criar_no(NODE_ASSIGNMENT, NULL, expr);
    node->value.sval = strdup(var);
    return node;
}

ASTNode *criar_comparison(enum OpType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = criar_no(NODE_COMPARISON, left, right);
    node->op = op;
    return node;
}

ASTNode *criar_arithmetic(enum OpType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = criar_no(NODE_ARITHMETIC, left, right);
    node->op = op;
    return node;
}

ASTNode *criar_number(int value) {
    ASTNode *node = criar_no(NODE_NUMBER, NULL, NULL);
    node->value.ival = value;
    return node;
}

ASTNode *criar_float(float value) {
    ASTNode *node = criar_no(NODE_FLOAT, NULL, NULL);
    node->value.fval = value;
    return node;
}

ASTNode *criar_identifier(char *name) {
    ASTNode *node = criar_no(NODE_IDENTIFIER, NULL, NULL);
    node->value.sval = strdup(name);
    return node;
}

// Função auxiliar para obter o símbolo da operação
const char *get_op_string(enum OpType op) {
    switch (op) {
        case OP_PLUS: return "+";
        case OP_MINUS: return "-";
        case OP_TIMES: return "*";
        case OP_DIVIDE: return "/";
        case OP_EQ: return "==";
        case OP_NEQ: return "!=";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LTE: return "<=";
        case OP_GTE: return ">=";
        default: return "?";
    }
}

// Estrutura para armazenar variáveis já declaradas
struct VarList {
    char name[64];
    bool is_float;
    struct VarList *next;
};

// Função auxiliar para checar se variável já foi declarada e seu tipo
static struct VarList *find_var(struct VarList *vars, const char *name) {
    while (vars) {
        if (strcmp(vars->name, name) == 0) return vars;
        vars = vars->next;
    }
    return NULL;
}

// Função para determinar se um nó é float
static bool is_float_node(ASTNode *node) {
    if (!node) return false;
    if (node->type == NODE_FLOAT) return true;
    if (node->type == NODE_ARITHMETIC) {
        // Se qualquer lado for float, resultado é float
        return is_float_node(node->left) || is_float_node(node->right);
    }
    if (node->type == NODE_IDENTIFIER) {
        // Não é possível saber aqui, assume int (ou poderia melhorar)
        return false;
    }
    return false;
}

// Função auxiliar para adicionar variável à lista, promovendo para float se necessário
void add_var(struct VarList **vars, const char *name, bool is_float) {
    struct VarList *v = find_var(*vars, name);
    if (v) {
        if (is_float) v->is_float = true; // Promove para float se necessário
        return;
    }
    struct VarList *new_var = malloc(sizeof(struct VarList));
    strncpy(new_var->name, name, 63);
    new_var->name[63] = '\0';
    new_var->is_float = is_float;
    new_var->next = *vars;
    *vars = new_var;
}

// Função para coletar variáveis
void collect_vars(ASTNode *node, struct VarList **vars) {
    if (!node) return;
    switch (node->type) {
        case NODE_ASSIGNMENT:
            add_var(vars, node->value.sval, is_float_node(node->right));
            collect_vars(node->right, vars);
            break;
        case NODE_STMT_LIST:
            collect_vars(node->left, vars);
            collect_vars(node->right, vars);
            break;
        case NODE_IF:
            collect_vars(node->left, vars);
            collect_vars(node->middle, vars);
            collect_vars(node->right, vars);
            break;
        case NODE_FOR:
            collect_vars(node->left, vars);
            collect_vars(node->right, vars);
            break;
        case NODE_PRINT:
            collect_vars(node->left, vars);
            break;
        case NODE_COMPARISON:
        case NODE_ARITHMETIC:
            collect_vars(node->left, vars);
            collect_vars(node->right, vars);
            break;
        default:
            break;
    }
}

// Função para imprimir declarações de variáveis
void print_var_decls(struct VarList *vars, FILE *output) {
    struct VarList *cur = vars;
    while (cur) {
        fprintf(output, "%s %s;\n", cur->is_float ? "float" : "int", cur->name);
        cur = cur->next;
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
        struct VarList *tmp = vars;
        vars = vars->next;
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
            fprintf(output, "\n");
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
            if (node->left && node->left->type == NODE_FLOAT) {
                fmt = "%f";
            }
            fprintf(output, "%sprintf(\"%s\\n\", ", ind, fmt);
            gerar_codigo_c_interno(node->left, output, 0);
            fprintf(output, ");\n");
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
void imprimirAST(ASTNode *no, int nivel) {
    if (!no) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    switch (no->type) {
        case NODE_STMT_LIST:
            printf("STMT_LIST\n");
            imprimirAST(no->left, nivel + 1);
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_IF:
            printf("IF\n");
            imprimirAST(no->left, nivel + 1);    // cond
            for (int i = 0; i < nivel; i++) printf("  ");
            printf("THEN:\n");
            imprimirAST(no->middle, nivel + 1);  // then
            if (no->right) {
                for (int i = 0; i < nivel; i++) printf("  ");
                printf("ELSE:\n");
                imprimirAST(no->right, nivel + 1); // else
            }
            break;
        case NODE_FOR:
            printf("FOR var=%s\n", no->value.sval);
            imprimirAST(no->left, nivel + 1);    // range
            imprimirAST(no->right, nivel + 1);   // body
            break;
        case NODE_FUNCTION_DEF:
            printf("DEF %s\n", no->value.sval);
            imprimirAST(no->left, nivel + 1);    // range
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_PRINT:
            printf("PRINT\n");
            imprimirAST(no->left, nivel + 1);
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGN %s\n", no->value.sval);
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_COMPARISON:
            printf("COMP %s\n", get_op_string(no->op));
            imprimirAST(no->left, nivel + 1);
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_ARITHMETIC:
            printf("ARITH %s\n", get_op_string(no->op));
            imprimirAST(no->left, nivel + 1);
            imprimirAST(no->right, nivel + 1);
            break;
        case NODE_NUMBER:
            printf("NUMBER %d\n", no->value.ival);
            break;
        case NODE_FLOAT:
            printf("FLOAT %f\n", no->value.fval);
            break;
        case NODE_IDENTIFIER:
            printf("IDENT %s\n", no->value.sval);
            break;
        default:
            printf("NODE type %d\n", no->type);
            break;
    }
}