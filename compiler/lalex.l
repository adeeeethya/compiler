
%{
#include<stdio.h>
%}

%%
"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return"|"void"|"break"|"do" {
    fprintf(yyout,"%s is a keyword\n",yytext);
}

[0-9]+(\.[0-9]+)? {
    fprintf(yyout,"%s is a number\n",yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    fprintf(yyout,"%s is an identifier\n",yytext);
}

"=="|"!="|"<="|">="|"++"|"--"|"&&"|"||"|"+"|"-"|"*"|"/"|"="|"<"|">" {
    fprintf(yyout,"%s is an operator\n",yytext);
}

[(){};,] {
    fprintf(yyout,"%s is a special symbol\n",yytext);
}

[ \t\n]+ ;

. {
    fprintf(yyout,"%s is an unknown character\n",yytext);
}
%%

int main()
{
    yyin = fopen("input.txt","r");
    yyout = fopen("output.txt","w");

    if(yyin == NULL || yyout == NULL)
    {
        printf("File opening error");
        return 1;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);

    return 0;
}

int yywrap()
{
    return 1;
}

