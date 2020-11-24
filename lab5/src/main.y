%{
    #include "common.h"
    extern int lineNo;
    int yylex();
    int yyerror(char const*);
%}

// OPs
%token T_AND  T_ASS  T_DIV   T_DIVE T_EQ
%token T_LA   T_LAE  T_LE    T_LEE  T_MINE
%token T_MINS T_MOD  T_MODE  T_MUL  T_MULE
%token T_NOT  T_NOTE T_OR    T_PLUE T_PLUS
%token ID
// consts(value)
%token BOOL    CHAR    INT     STRING
// keys
%token BREAK   CONST   CONTINUE ELSE    FOR
%token IF      MAIN    RETURN   TYPE    WHILE

%% 

// 表达式文法
Cond
: LOrExp {

}
;

ConstExp
: LowExp {

}
;

EqExp
: EqExp T_EQ RelExp {

}
| EqExp T_NOTE RelExp {

}
| RelExp {

}
;

Exp
: LowExp {

}
;

HighExp
: HighExp T_DIV UnaryExp {

}
| HighExp T_MOD UnaryExp {

}
| HighExp T_MUL UnaryExp {

} 
| UnaryExp {

}
;

LAndExp
: EqExp {

}
| LAndExp T_AND EqExp {

}
;

LOrExp
: LAndExp {

}
| LAndExp T_OR LOrExp {

}
;

LowExp
: HighExp {

}
| LowExp T_PLUS HighExp {

}
| LowExp T_MINS HighExp {

}
;

Lval
: ID {

}
;

PrimaryExp
: "(" Exp ")" {

}
| INT {

}
| Lval {

}

RelExp
: LowExp {

}
| RelExp T_LA LowExp {

}
| RelExp T_LAE LowExp {

}
| RelExp T_LE LowExp {

}
| RelExp T_LEE LowExp {

}
;

UnaryExp
: PrimaryExp {

}
| UnaryOp UnaryExp {

}
;

UnaryOp
: T_MINS {

}
| T_NOT {

}
| T_PLUS {
    
}
;

%%

int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}