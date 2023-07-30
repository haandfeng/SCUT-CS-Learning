%{
#include<stdio.h>
void yyerror(char * );
#include"y.tab.h"
%}

digit [0-9]

%%
[0-9]+    { yylval = atoi(yytext);  return T_NUM; }
[-+*/()\n] { return yytext[0]; }
[ t]         {; /* 去除空格 */}
·       {return 0; }

%%

int yywrap(void) {
    return 1;
}

