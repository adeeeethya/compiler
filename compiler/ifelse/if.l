%{
#include "y.tab.h"
%}

%%

"if"                    { return IF; }
"else"                  { return ELSE; }

[a-zA-Z_][a-zA-Z0-9_]*    { return ID; }
[0-9]+                  { return NUM; }

"=="|"!="|"<="|">="|"<"|">"  { return RELOP; }

[ \t\n]+                ;

.                       { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}

