%{
    #include "headfile.h"
    #define YYSTYPE node
    #include "yacc.tab.h"

    int yyerror();
    int yyerror(char* msg);
    extern int yylex();
    
    codelist* list;
%}


%token BASIC NUMBER REAL ID TRUE FALSE
%token INT LONG CHAR BOOL FLOAT DOUBLE HALT
%token REL
%token IF ELSE WHILE DO BREAK FOR SWITCH CASE DEFAULT 
%left '+' '-'
%left '*' '/'
%%


block     :  statement  { }
    ;

statement    :
     IF '(' boolean ')' statement        
		{
		 backpatch(list, $3.truelist, $5.instr);
                                 $$.nextlist = merge($3.falselist, $6.nextlist); 
		}
    | WHILE '(' boolean ')' statement    
		{
		 backpatch(list, $7.nextlist, $2.instr);
                          	 backpatch(list, $4.truelist, $6.instr);
                                 $$.nextlist = $4.falselist;
                                 gen_goto(list, $2.instr); 
		}
    | assignment ';'        { $$.nextlist = NULL; }
    | HALT        { $$.nextlist = NULL; }
    ;



assignment    : ID '=' boolean         
		 {
		   copyaddr(&$1, $1.lexeme); gen_assignment(list, $1, $3);
		 }
    ;


boolean    :  expression REL expression        
		{ 
		  $$.truelist = new_instrlist(nextinstr(list));
                           	  $$.falselist = new_instrlist(nextinstr(list)+1);
                           	  gen_if(list, $1, $2.oper, $3);
                          	  gen_goto_blank(list); 
		}
   
    | expression        { copyaddr_fromnode(&$$, $1); }
    ;

expression    : 
      expression '+' expression        
		{ new_temp(&$$, get_temp_index(list)); 
		  gen_3addr(list, $$, $1, "+", $3); 
		}
    | expression '-' expression        
		{ new_temp(&$$, get_temp_index(list)); 
		  gen_3addr(list, $$, $1, "-", $3); 
		}
    | expression '*' expression           
		{ new_temp(&$$, get_temp_index(list)); 
		  gen_3addr(list, $$, $1, "*", $3); 
		}
    | expression '/' expression       
		{ new_temp(&$$, get_temp_index(list)); 
		  gen_3addr(list, $$, $1, "/", $3); 
		}
    | NUMBER          { copyaddr(&$$, $1.lexeme); }
    ;

%%


int yyerror(char* msg)
{
    printf("\nERROR: %s\n", msg);
    return 0;
}


int main()
{
    list = newcodelist();
	
    //打开文件
    freopen("test.in", "rt+", stdin);
    freopen("test.out", "wt+", stdout);
    
    yyparse();
    print(list);

    //关闭文件
    fclose(stdin);  
    fclose(stdout);

    return 0;
}

