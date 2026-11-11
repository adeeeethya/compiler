%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(char *s);
extern FILE *yyin;
extern FILE *yyout;
%}
%token IF ELSE NUM RELOP ID

%%

stmt : IF condition '{' assignment '}' ELSE '{' assignment '}' {fprintf(yyout,"valid if else syntax \n");}
     ;
condition : ID RELOP ID
          | ID RELOP NUM
          ;
assignment : ID '=' NUM ';'
	   ;
	   
%%
int main()
{
	yyin=fopen("input.txt","r");
	yyout=fopen("output.txt","w");
	yyparse();
	fclose(yyin);
	fclose(yyout);
	return 0;
}

void yyerror(char *s)
{
	fprintf(yyout,"error \n");
}
