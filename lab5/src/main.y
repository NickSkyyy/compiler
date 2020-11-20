%{
    #include "common.h"
    extern int lineNo;
    extern int yylex();
    int yyerror(char const*);
}

%token OP_ADD OP_ASS OP_DIV OP_DIVE
%token CHAR

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