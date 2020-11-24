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

%% 

// 表达式文法
HighExp
: HighExp OP_MUL UnaryExp {

}
| HighExp OP_DIV UnaryExp {

}
| HighExp OP_MOD UnaryExp {

} 
| UnaryExp {

}
;

LowExp
: HighExp {

}
| LowExp OP_ADD HighExp {

}
| LowExp OP_MINS HighExp {

}
;

UnaryExp
: PrimaryExp {

}
| UnaryOp UnaryExp {

}
;

UnaryOp
: OP_MINS {

}
| OP_NOT {

}
| OP_PLUS {
    
}
;

%%

int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}