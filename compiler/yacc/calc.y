%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(char *s);
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
S : E { 
	printf("Result : %d",$1);
	exit(0); 
      }
      ;
E : E '+' E {$$=$1+$3;}
  | E '-' E {$$=$1-$3;}
  | E '*' E {$$=$1*$3;}
  | E '/' E {$$=$1/$3;}
  | '(' E ')' {$$=$2;}
  | NUM {$$=$1;}
  ;
%%
int main()
{
	printf("enter the expression:\n");
	yyparse();
	return 0;
}

void yyerror(char *s)
{
	printf("error\n");
}
