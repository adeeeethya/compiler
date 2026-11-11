%{
#include "y.tab.h"
#include<stdio.h>
%}

%%
"if" return IF;
"else" return ELSE;
"<"|">"|"<="|">="|"=="|"!=" return RELOP;
[0-9]+ return NUM;
[a-zA-Z]+ return ID;
[ \t\n] ;
. return yytext[0];
%%
int yywrap()
{
	return 1;
}
