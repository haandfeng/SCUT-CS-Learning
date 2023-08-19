%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
%}

%token DIGIT PLUS MULT LPAREN RPAREN

%type <int> E T F
%token INT

/* Define the type and value of an attribute for a grammar symbol */
%union {
  int value;
  char type;
}


%%
/* Define the grammar rules */
E: E PLUS T
  {
    if ($1.type != 'i' || $3.type != 'i') {
      yyerror("Error: Operator '+' cannot be used for non-integer values");
    }
    $$.type = 'i';
    $$.value = $1.value + $3.value;
  }
  | T
  {
    $$.type = $1.type;
    $$.value = $1.value;
  }
  ;

T: T MULT F
  {
    if ($1.type != 'i' || $3.type != 'i') {
      yyerror("Error: Operator '*' cannot be used for non-integer values");
    }
    $$.type = 'i';
    $$.value = $1.value * $3.value;
  }
  | F
  {
    $$.type = $1.type;
    $$.value = $1.value;
  }
  ;

F: LPAREN E RPAREN
  {
    $$.type = $2.type;
    $$.value = $2.value;
  }
  | DIGIT
  {
    $$.type = 'i';
    $$.value = $$;
  }
  ;

%%

/* Define the main function */
int main()
{
    yyparse();
    return 0;
}

/* Define the error handler function */
int yyerror(const char *msg)
{
    printf("%s\n", msg);
    exit(1);
}
