%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void yyerror(const char* msg) {}
int yylex();
%}

%token T_NUM

%left '+'   '-'
%left '*'   '/'


%%

/* Define the grammar rules */
S      :       S E '\n'             {  printf("ans = %d\n",$2);  }
        |       /* empty */     { /* empty */  }
        ;

E      :        E  '+'  E          { $$ = $1 +$3;  }
        |        E  '-'  E           { $$ = $1 - $3;  }
        |        E  '*'  E           { $$ = $1 * $3;  }
        |        E  '/'  E           { $$ = $1 / $3;  }
        |        T_NUM          { $$ = $1;  }
        |        '(' E ')'             { $$ = $2;  }
        ;

%%

/* Define the main function */
int main()
{
    return yyparse();
}

