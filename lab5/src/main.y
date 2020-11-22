%{
    #include "common.h"
    extern int lineNo;
    extern int yylex();
    int yyerror(char const*);
}

// OPs
%token OP_ADD  OP_ASS  OP_DIV   OP_DIVE OP_EQ
%token OP_LA   OP_LAE  OP_LE    OP_LEE  OP_MINE
%token OP_MINS OP_MOD  OP_MODE  OP_MUL  OP_MULE
%token OP_NOT  OP_NOTE OP_OR    OP_PLUE OP_PLUS
// consts(value)
%token BOOL    CHAR    INT     STRING
// keys
%token BREAK   CONST   CONTINUE ELSE    FOR
%token IF      MAIN    RETURN   TYPE    WHILE
// semi(;)
%token SEMI
// type(definition)
%token TYPE
// orders
%left  OP_ADD OP_MINS
%left  OP_MUL OP_DIV
%right OP_ASS

%% 



%%

int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}