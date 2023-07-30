%{
#include "yacc.tab.h"
%}

digit [0-9]

%%

"+"    { return PLUS; }
"*"    { return MULT; }
"("    { return LPAREN; }
")"    { return RPAREN; }
{digit}+  { yylval = atoi(yytext); return DIGIT; }

%%
int yywrap() {
    return 1;
}

