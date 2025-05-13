%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"
#include "tipos.h"

extern FILE *yyin;
extern int yylex();
extern int yylineno;
void yyerror(const char *s);

int escopo_atual = ESCOPO_GLOBAL;
%}

%union {
    int intValue;
    float floatValue;
    char* id;
    char* str;
    struct AST* ast;
}

%token EQ NEQ GE LE GT LT
%token IF ELSE COLON
%token <id> ID
%token <intValue> NUM
%token <floatValue> FLOAT_NUM
%token PRINT INT FLOAT
%token ASSIGN SEMICOLON LPAREN RPAREN
%token PLUS MINUS TIMES DIVIDE

%type <ast> expr
%type <str> comp
%type <str> cond

%%

program:
    program stmt            
    |
    ;

stmt:
    decl SEMICOLON           // Declaração seguida de ponto e vírgula
    | assign SEMICOLON       // Atribuição seguida de ponto e vírgula
    | print SEMICOLON        // Print seguido de ponto e vírgula
    | if_stmt                // "if"
    ;

if_stmt:
    //if sem else
    IF LPAREN cond RPAREN COLON stmt
    {
        printf("if (%s) {\n}\n", $3);
        free($3);
    }
    //if-else
    | IF LPAREN cond RPAREN COLON stmt ELSE COLON stmt
    {
        printf("if (%s) {\n} else {\n}\n", $3);
        free($3);
    }
    //if usando um identificador
    | IF ID COLON stmt
    {
        printf("if (%s) {\n}\n", $2);
    }
    //if-else usando identificador
    | IF ID COLON stmt ELSE COLON stmt
    {
        printf("if (%s) {\n} else {\n}\n", $2);
    }
    ;

cond:
    expr comp expr
    {
        char buffer[256];
        // Convertemos para string para simular a geração de código
        // Em um compilador real, criaríamos um nó AST para a comparação
        sprintf(buffer, "%d %s %d", 
                ($1->categoria == CONSTANTE && $1->tipo == TIPO_INT) ? $1->dado.valor_int : 0, 
                $2, 
                ($3->categoria == CONSTANTE && $3->tipo == TIPO_INT) ? $3->dado.valor_int : 0);
        $$ = strdup(buffer);
        free($2);
        liberar_ast($1);
        liberar_ast($3);
    }
    | ID 
    { 
        $$ = strdup($1); 
    }
    ;

comp:
    GT { $$ = strdup(">"); }
    | LT { $$ = strdup("<"); }
    | GE { $$ = strdup(">="); }
    | LE { $$ = strdup("<="); }
    | EQ { $$ = strdup("=="); }
    | NEQ { $$ = strdup("!="); }
    ;

decl:
    INT ID
    {
        if (!inserir_identificador($2, TIPO_INT, escopo_atual)) {
            yyerror("Erro na declaração");
        } else {
            printf("int %s;\n", $2);
        }
    }
    | FLOAT ID
    {
        if (!inserir_identificador($2, TIPO_FLOAT, escopo_atual)) {
            yyerror("Erro na declaração");
        } else {
            printf("float %s;\n", $2);
        }
    }
    ;

assign:
    ID ASSIGN expr
    {
        int tipo = buscar_tipo($1);
        if (tipo == -1) {
            fprintf(stderr, "Erro semântico: Variável '%s' não declarada\n", $1);
        } else {
            printf("%s = ", $1);
            // Impressão do valor baseado no tipo da expressão
            if ($3->categoria == CONSTANTE) {
                if ($3->tipo == TIPO_INT) {
                    printf("%d", $3->dado.valor_int);
                } else if ($3->tipo == TIPO_FLOAT) {
                    printf("%f", $3->dado.valor_float);
                }
            } else {
                printf("expr");  // Simplificação para demonstração
            }
            printf(";\n");
        }
        liberar_ast($3);
    }
    ;

print:
    PRINT LPAREN ID RPAREN
    {
        int tipo = buscar_tipo($3);
        if (tipo == -1) {
            fprintf(stderr, "Erro semântico: Variável '%s' não declarada\n", $3);
        } else {
            if (tipo == TIPO_INT) {
                printf("printf(\"%%d\\n\", %s);\n", $3);
            } else if (tipo == TIPO_FLOAT) {
                printf("printf(\"%%f\\n\", %s);\n", $3);
            }
        }
    }
    | PRINT LPAREN expr RPAREN
    {
        if ($3->categoria == CONSTANTE) {
            if ($3->tipo == TIPO_INT) {
                printf("printf(\"%%d\\n\", %d);\n", $3->dado.valor_int);
            } else if ($3->tipo == TIPO_FLOAT) {
                printf("printf(\"%%f\\n\", %f);\n", $3->dado.valor_float);
            }
        } else {
            printf("printf(\"Expressão\\n\");\n");
        }
        liberar_ast($3);
    }
    ;

expr:
    NUM 
    { 
        $$ = criar_no_constante_int($1); 
    }
    | FLOAT_NUM 
    { 
        $$ = criar_no_constante_float($1); 
    }
    | ID 
    { 
        int tipo = buscar_tipo($1);
        if (tipo == -1) {
            fprintf(stderr, "Erro semântico: Variável '%s' não declarada\n", $1);
            $$ = criar_no_constante_int(0);  // Valor padrão para erro
        } else {
            $$ = criar_no_variavel($1);
            $$->tipo = tipo;
        }
    }
    | expr PLUS expr 
    { 
        $$ = criar_no_operacao(OP_SOMA, $1, $3); 
        if ($1->tipo == TIPO_FLOAT || $3->tipo == TIPO_FLOAT) {
            $$->tipo = TIPO_FLOAT;
        } else {
            $$->tipo = TIPO_INT;
        }
    }
    | expr MINUS expr 
    { 
        $$ = criar_no_operacao(OP_SUBTRACAO, $1, $3); 
        if ($1->tipo == TIPO_FLOAT || $3->tipo == TIPO_FLOAT) {
            $$->tipo = TIPO_FLOAT;
        } else {
            $$->tipo = TIPO_INT;
        }
    }
    | expr TIMES expr 
    { 
        $$ = criar_no_operacao(OP_MULTIPLICACAO, $1, $3); 
        if ($1->tipo == TIPO_FLOAT || $3->tipo == TIPO_FLOAT) {
            $$->tipo = TIPO_FLOAT;
        } else {
            $$->tipo = TIPO_INT;
        }
    }
    | expr DIVIDE expr 
    { 
        $$ = criar_no_operacao(OP_DIVISAO, $1, $3); 
        if ($1->tipo == TIPO_FLOAT || $3->tipo == TIPO_FLOAT) {
            $$->tipo = TIPO_FLOAT;
        } else {
            $$->tipo = TIPO_INT;
        }
    }
    | LPAREN expr RPAREN 
    { 
        $$ = $2; 
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", yylineno, s);
}