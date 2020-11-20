%{
    #include "common.h"
    extern int lineNo;
    extern int yylex();
    int yyerror(char const*);
}
%token T_BOOL T_CHAR T_INT T_STRING
%token SEMICOLON
%token BOOL CHAR INT STRING
%token ID ID_ALPHA ID_DIGIT
%token OP_ADD  OP_ADDE  OP_AND    OP_ASS OP_DIV
%token OP_DIVE OP_EQ    OP_LA     OP_LAE OP_LE
%token OP_LEE  OP_MINUS OP_MINUSE OP_MOD OP_MUL
%token OP_MULE OP_NOT   OP_NOTE   OP_OR
%left OP_DIV OP_MUL
%left OP_ADD OP_MINUS

%%

ID: ID_ALPHA
| ID ID_ALPHA
| ID ID_DIGIT
;

TYPE: T_BOOL {$$ = new TreeNode(lineNo, NODE_TYPE);}
| T_CHAR
| T_INT
| T_STRING

%%

int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}