%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "ast.h"
#include "tabela.h"

int yylex(void);
void yyerror(const char *s);
void type_error(const char* expected, const char* got, const char* var_name);
%}

%union {
    int intValue;
    char* id;
    char* str;
    float floatValue;
    char charValue;
    NoAST* ast;
}

%code requires {
    #include "tipos.h"
}

%token EQ NEQ GE LE GT LT
%token IF ELSE COLON
%token <id> ID
%token <intValue> NUM
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

%type <ast> expr
%type <str> comp
%type <id> cond

%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc COLON
%nonassoc ELSE

%%


program:
    program stmt
    |
    ;

stmt:
    decl
    | assign
    | print
    | if_stmt
    ;

decl:
    INT ID
    {
        if (buscarSimbolo($2)) {
            fprintf(stderr, "Erro: Variável '%s' já foi declarada\n", $2);
            YYERROR;
        }
        inserirSimbolo($2, "int");
        printf("int %s;\n", $2);
        free($2);
    }
    ;

assign:
    ID ASSIGN expr
    {
        Simbolo *s = buscarSimbolo($1);
        if (!s) {
            fprintf(stderr, "Erro: Variável '%s' não foi declarada\n", $1);
            YYERROR;
        }
        // Aqui você pode verificar tipos se desejar
        printf("%s = ", $1);
        imprimirAST($3);
        printf(";\n");
        liberarAST($3);
        free($1);
    }
    | ID ASSIGN error SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Expressão inválida na atribuição. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    | error SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Atribuição mal formatada. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    ;

print:
    PRINT LPAREN ID RPAREN
    {
        if (!buscarSimbolo($3)) {
            fprintf(stderr, "Erro: Variável '%s' não foi declarada\n", $3);
            YYERROR;
        }
        printf("printf(\"%%d\\n\", %s);\n", $3);
        free($3);
    }
    | PRINT LPAREN NUM RPAREN
    {
        printf("printf(\"%%d\\n\", %d);\n", $3);
    }
    | PRINT LPAREN expr RPAREN
    {
        printf("printf(\"%%d\\n\", ");
        imprimirAST($3);
        printf(");\n");
        liberarAST($3);
    }
    | PRINT LPAREN error RPAREN SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Expressão inválida no print. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    | PRINT error SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Comando print mal formatado. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    ;

if_stmt:
    IF LPAREN cond RPAREN COLON stmt
    {
        printf("if (%s) {\n}\n", $3);
        free($3);
    }
    | IF LPAREN cond RPAREN COLON stmt ELSE COLON stmt
    {
        printf("if (%s) {\n} else {\n}\n", $3);
        free($3);
    }
    | IF LPAREN error RPAREN COLON stmt SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Condição inválida no if. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    | IF error SEMICOLON {
        fprintf(stderr, "[ERRO SINTATICO] Estrutura if mal formatada. Pulando até ';'\n");
        yyerrok;
        yyclearin;
    }
    ;

cond:
    expr comp expr
    {
        char buffer[256];
        sprintf(buffer, "(");
        imprimirAST($1);
        sprintf(buffer + strlen(buffer), " %s ", $2);
        imprimirAST($3);
        sprintf(buffer + strlen(buffer), ")");
        $$ = strdup(buffer);
        free($2);
        liberarAST($1);
        liberarAST($3);
    }
    | ID { $$ = strdup($1); }
    ;

comp:
    GT { $$ = strdup(">"); }
    | LT { $$ = strdup("<"); }
    | GE { $$ = strdup(">="); }
    | LE { $$ = strdup("<="); }
    | EQ { $$ = strdup("=="); }
    | NEQ { $$ = strdup("!="); }
    ;

expr:
    NUM { $$ = criarNoNum($1); }
    | ID {
        if (!buscarSimbolo($1)) {
            fprintf(stderr, "Erro: Variável '%s' não foi declarada\n", $1);
            YYERROR;
        }
        $$ = criarNoId($1);
        free($1);
    }
    | LPAREN expr RPAREN { $$ = $2; }
    | expr PLUS expr { $$ = criarNoOp('+', $1, $3); }
    | expr MINUS expr { $$ = criarNoOp('-', $1, $3); }
    | expr TIMES expr { $$ = criarNoOp('*', $1, $3); }
    | expr DIVIDE expr {
        // Não faz verificação de divisão por zero aqui, pois é AST
        $$ = criarNoOp('/', $1, $3);
    }
    ;

%%


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
void type_error(const char* expected, const char* got, const char* var_name) {
    fprintf(stderr, "Erro de tipo: Variável '%s' é do tipo '%s', mas recebeu valor do tipo '%s'\n",
            var_name, expected, got);
}