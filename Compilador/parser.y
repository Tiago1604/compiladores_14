%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int yylex(void);
void yyerror(const char *s);
void type_error(const char* expected, const char* got, const char* var_name);

// Array simples para armazenar variáveis
Variable variables[100];
int var_count = 0;
%}



%union {
    int intValue;
    char* id;
    char* str;
    float floatValue;
    char charValue;
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

%type <intValue> expr
%type <str> comp         //(>, <, etc)
%type <id> cond          //condicao

%left PLUS MINUS    // Lower precedence
%left TIMES DIVIDE  // Higher precedence
%nonassoc COLON
%nonassoc ELSE     // Resolve the dangling else problem

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
        // Verifica se variável já foi declarada
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].name, $2) == 0) {
                fprintf(stderr, "Erro: Variável '%s' já foi declarada\n", $2);
                YYERROR;
            }
        }
        
        // Adiciona variável à tabela de símbolos
        variables[var_count].name = strdup($2);
        variables[var_count].type = TYPE_INT;
        var_count++;
        printf("int %s;\n", $2);
        free($2);
    }
    ;
assign:
    ID ASSIGN expr
    {
        // Procura a variável na tabela de símbolos
        int found = 0;
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].name, $1) == 0) {
                found = 1;
                if (variables[i].type == TYPE_INT) {
                    printf("%s = %d;\n", $1, $3);
                }
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "Erro: Variável '%s' não foi declarada\n", $1);
            YYERROR;
        }
        free($1);
    }
    ;
print:
    PRINT LPAREN ID RPAREN
    {
        printf("printf(\"%%d\\n\", %s);\n", $3);
    }
    | PRINT LPAREN NUM RPAREN
    {
        printf("printf(\"%%d\\n\", %d);\n", $3);
    }
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
    ;
cond:
    expr comp expr
    {
        char buffer[256];
        sprintf(buffer, "%d %s %d", $1, $2, $3); //"5 > 3"
        $$ = strdup(buffer);
        free($2);
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
    NUM { $$ = $1; }
    | ID { $$ = 0; }
    | LPAREN expr RPAREN { $$ = $2; }
    | expr PLUS expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr TIMES expr { $$ = $1 * $3; }
    | expr DIVIDE expr { 
        if ($3 == 0) {
            fprintf(stderr, "Erro: Divisão por zero\n");
            $$ = 0;
        } else {
            $$ = $1 / $3; 
        }
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