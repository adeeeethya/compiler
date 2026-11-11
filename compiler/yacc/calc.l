%{
#include "y.tab.h"
#include<stdio.h>
%}

%%
[0-9]+ {
yylval=atoi(yytext);
	return NUM;
	}
[ \t] ;
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"\n" return '\n';


%%
int yywrap()
{
	return 1;
}
