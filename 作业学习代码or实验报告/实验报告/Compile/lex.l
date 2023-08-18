%{
    #include "yacc.tab.h"
%}

delim       [ \t\n\r]
ws        	{delim}+
letter        [A-Za-z]
digit       	[0-9]
id        	{letter}({letter}|{digit})*
integer        {digit}+
exponent    E[+-]?{integer}
number      {integer}{exponent}?
real        	   integer(\.integer)?{exponent}?
halt	[EOF]
%option noyywrap
%%


if    	{ return( IF ); }
else     	{ return( ELSE ); }
while    	{ return( WHILE ); }
do    	{ return( DO ); }
for    	{ return( FOR ); }
switch    	{ return( SWITCH ); }
case    	{ return( CASE ); }
default    	{ return( DEFAULT ); }
break    	{ return( BREAK ); }
true    	{ return( TRUE ); }
false    	{ return( FALSE ); }
int    	{ return( INT ); }
long    	{ return( LONG ); }
char    	{ return( CHAR ); }
bool   	{ return( BOOL ); }
float    	{ return( FLOAT ); }
double   	{ return( DOUBLE ); }
"<"|"<="|">"|">="|"!="|"=="    { filloperator(&yylval, yytext); return( REL); }
"+"    	{ return( '+' ); }
"-"    	{ return( '-' ); }
"*"    	{ return( '*' ); }
"/"    	{ return( '/' ); }
"="    	{ return( '=' ); }
"{"    	{ return( '{' ); }
"}"    	{ return( '}' ); }
"["    	{ return( '[' ); }
"]"    	{ return( ']' ); }
"("    	{ return( '(' ); }
")"    	{ return( ')' ); }
";"    	{ return( ';' ); }
{ws}   	{ }
{id}    	{ filllexeme(&yylval, yytext); return( ID ); }
{number} { filllexeme(&yylval, yytext); return( NUMBER ); }
{real}        { filllexeme(&yylval, yytext); return( REAL ); }
{halt}        { filllexeme(&yylval, yytext); return( HALT ); }

%%

