%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
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
        printf("int %s;\n", $2);
        free($2);
    }
    ;
assign:
    ID ASSIGN expr
    {
        printf("%s = %d;\n", $1, $3);
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
    | expr PLUS expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr TIMES expr { $$ = $1 * $3; }
    | expr DIVIDE expr { $$ = $1 / $3; }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}