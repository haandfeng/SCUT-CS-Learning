%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void yyerror(const char* msg) {}
int yylex();
%}

%token T_num


%left '+'
%left '*' 


%%

/* Define the grammar rules */
S      :        S E '\n'        { printf("ans = %d\n",$2);}
        |        /*empty */                    { /*empty */  }
        ;

E      :        E  '+'  T          { $$ = $1 +$3;  }
        |        T                    { $$ = $1;  }
        ;

T      :        T  '*'  F            { $$ = $1 * $3;  }
        |        F                     { $$ = $1;  }
        ;

F      :        '(' E ')'              { $$ = $2;  }
        |        T_num                { $$ = $1;  }
        ;
%%

/* Define the main function */
int main()
{
    return yyparse();
}

