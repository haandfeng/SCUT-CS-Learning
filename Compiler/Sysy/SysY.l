%option yylineno
 
%{
    #include "translator.h"
%}
 
TYPE                int|void
KEYWORD             if|else|while|break|continue|return
OPERATOR            "+"|"-"|"!"|"*"|"%"|"/"|"="
COMPARISON          "=="|"!="|">"|"<"|">="|"<="
NONZERO             [1-9]
DIGIT               [0-9]
LETTER              [A-Za-z]
OCTAL_DIGIT         [0-7]
OCTAL_CONST         0{OCTAL_DIGIT}*
ILLEGAL_OCTAL_CONST 0[0-9a-wy-zA-WY-Z]({LETTER}|{DIGIT})*
HEX_PREFIX          0x|0X
HEX_DIGIT           [0-9a-fA-F]
HEX_CONST           {HEX_PREFIX}{HEX_DIGIT}+
ILLEGAL_HEX_CONST   {HEX_PREFIX}({LETTER}|{DIGIT})*
NONDIGIT            {LETTER}|"_"
ID                  {NONDIGIT}({DIGIT}|{NONDIGIT})*
DEC_CONST           {NONZERO}{DIGIT}*  
COMMENT1            "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"
COMMENT2            "//".*                                                                                
 
%%
 
{TYPE}                  { printf("\033[1;32mTYPE\033[0m\t\t%s\n",yytext);return TYPE; }
{OCTAL_CONST}           { printf("\033[1;32mOCTAL_CONST\033[0m\t");return OCTAL_CONST; }
{ILLEGAL_OCTAL_CONST}   { return ILLEGAL_OCTAL_CONST; }
{HEX_CONST}             { printf("\033[1;32mHEX_CONST\033[0m\t");return HEX_CONST; }
{ILLEGAL_HEX_CONST}     { return ILLEGAL_HEX_CONST; }
{DEC_CONST}             { printf("\033[1;32mDEC_CONST\033[0m\t%s\n",yytext);return DEC_CONST; }
{KEYWORD}               { printf("\033[1;32mKEYWORD\033[0m\t\t%s\n",yytext);return KEYWORD; }
{ID}                    { printf("\033[1;32mID\033[0m\t\t%s\n",yytext);return ID; }
{OPERATOR}              { printf("\033[1;32mOPERATOR\033[0m\t%s\n",yytext);return OPERATOR; }
{COMPARISON}            { printf("\033[1;32mCOMPARISON\033[0m\t%s\n",yytext);return COMPARISON; }
"("                     { printf("\033[1;32mLPARENT\033[0m\t\t%s\n",yytext);return LPARENT; }
")"                     { printf("\033[1;32mRPARENT\033[0m\t\t%s\n",yytext);return RPARENT; }
"["                     { printf("\033[1;32mLBRACKET\033[0m\t%s\n",yytext);return LBRACKET; }
"]"                     { printf("\033[1;32mRBRACKET\033[0m\t%s\n",yytext);return RBRACKET; }
"{"                     { printf("\033[1;32mLBRACE\033[0m\t\t%s\n",yytext);return LBRACE; }
"}"                     { printf("\033[1;32mRBRACE\033[0m\t\t%s\n",yytext);return RBRACE; }
";"                     { printf("\033[1;32mSEMICN\033[0m\t\t%s\n",yytext);return SEMICN; }
","                     { printf("\033[1;32mCOMMA\033[0m\t\t%s\n",yytext);return COMMA; }
"&&"                    { printf("\033[1;32mAND\033[0m\t\t%s\n",yytext);return AND; }
"||"                    { printf("\033[1;32mOR\033[0m\t\t%s\n",yytext);return OR; }
{COMMENT1}|{COMMENT2}   { }
[ \t\n]                 { }
.                       { return UNEXPECTED; }
 
%%
 
int main()
{
    int token_type;
    while (token_type = yylex())
    {
        if (token_type == UNEXPECTED)
            printf("\033[1;31mError type A at Line %d: Invalid character \"%s\"\033[0m\n", yylineno, yytext);
        else if (token_type == OCTAL_CONST)
        {
            int sum = 0;
            for (int i = 1; i < yyleng; ++i)
                sum = sum * 8 + (yytext[i] - '0');
            printf("%d\n", sum);
        }
        else if (token_type == HEX_CONST)
        {
            int sum = 0;
            for (int i = 2; i < yyleng; ++i)
            {
                if (yytext[i] <= '9' && yytext[i] >= '0')
                    sum = sum * 16 + (yytext[i] - '0');
                else
                {
                    switch (yytext[i])
                    {
                    case 'a':
                    case 'A':
                        sum = sum * 16 + 10;
                        break;
                    case 'b':
                    case 'B':
                        sum = sum * 16 + 11;
                        break;
                    case 'c':
                    case 'C':
                        sum = sum * 16 + 12;
                        break;
                    case 'd':
                    case 'D':
                        sum = sum * 16 + 13;
                        break;
                    case 'e':
                    case 'E':
                        sum = sum * 16 + 14;
                        break;
                    case 'f':
                    case 'F':
                        sum = sum * 16 + 15;
                        break;
                    }
                }
            }
            printf("%d\n", sum);
        }
        else if (token_type == ILLEGAL_OCTAL_CONST)
            printf("\033[1;31mError type B at line %d: Illegal octal number \'%s\'\033[0m\n", yylineno, yytext);
        else if (token_type == ILLEGAL_HEX_CONST)
            printf("\033[1;31mError type B at line %d: Illegal hex number \'%s\'\033[0m\n", yylineno, yytext);
    }
}
