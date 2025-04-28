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
}

%token EQ NEQ GE LE GT LT
%token IF ELSE COLON
%token <id> ID
%token <intValue> NUM
%token PRINT INT
%token ASSIGN SEMICOLON LPAREN RPAREN
%token PLUS MINUS TIMES DIVIDE

%type <intValue> expr
%type <str> comp         //(>, <, etc)
%type <id> cond          //condicao

%%

program:
    program stmt            
    |
    ;
stmt:
    decl SEMICOLON           // Declaração seguida de ponto e vírgula
    | assign SEMICOLON       // Atribuição seguida de ponto e vírgula
    | print SEMICOLON        // Print seguido de ponto e vírgula
    | if_stmt                //"if"
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
decl:
    INT ID
    {
        printf("int %s;\n", $2);
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