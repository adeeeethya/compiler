%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

int yylex();
void yyerror(const char *s);
%}

%token IF ELSE ID NUM RELOP

%%

stmt : IF '(' condition ')' '{' assign '}' ELSE '{' assign '}'
       {
           printf("Valid if-else statement\n");
       }
     ;

condition : ID RELOP ID
          | ID RELOP NUM
          ;

assign : ID '=' ID ';'
       | ID '=' NUM ';'
       ;

%%

void yyerror(const char *s)
{
    printf("Invalid if-else statement\n");
}

int main()
{
    yyin = fopen("input.txt", "r");

    if (yyin == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    yyparse();

    fclose(yyin);

    return 0;
}

