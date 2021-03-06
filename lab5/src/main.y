%{
    #include "common.h"
    TreeNode* root;
    extern bool isRet;
    extern int lineNo;
    extern int Lloop;
    extern int tErr;
    extern stack<TreeNode*> inFunc;
    bool isNTS(Type* t) { return t->type == NOT_SURE; }
    int tempID;
    int yyerror(char const*);  
    int yylex();
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
// special mark
%token COMA
%token LBRAC RBRAC
%token LPATH RPATH
%token LSQ   RSQ
%token SEMI
// i/o
%token CHAR_IN  INT_IN  STR_IN
%token CHAR_OUT INT_OUT STR_OUT
%start StartProg
%% 

Assign
: Lval T_ASS BOOL {
    $1->bval = $3->bval;
    $1->ival = $3->bval ? 1 : 0;
    $1->cval = (char)$1->ival;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_ASS CHAR {
    $1->cval = $3->cval;
    $1->ival = (int)$1->cval;
    $1->bval = $1->ival == 0 ? 0 : 1;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_ASS CHAR_IN LPATH RPATH {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "input";
    node->type = TYPE_CHAR;
    if (*($1->type) != *(node->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;   
    node->addChild($1); 
    $$ = node;
}
| Lval T_ASS Exp {
    $1->ival = $3->ival;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_ASS INT_IN LPATH RPATH {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "input";
    node->type = TYPE_INT;
    if (*($1->type) != *(node->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    $$ = node;
}
| Lval T_ASS STRING {
    $1->sval = $3->sval;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_ASS STR_IN LPATH RPATH {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "input";
    node->type = TYPE_STRING;
    if (*($1->type) != *(node->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    $$ = node;
}
| Lval T_DIVE Exp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_DIVE;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_MINE Exp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MINE;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_MODE Exp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MODE;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_MULE Exp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MULE;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
| Lval T_PLUE Exp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_PLUE;
    node->type = $3->type;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $3->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $1->varName << ">" << endl;
    }
    else
        $1->type->type = $3->type->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
;

Block
:  LBRAC BlockItem RBRAC {
    if ($2 == nullptr)
        $$ = nullptr;
    else
    {
        TreeNode* node = new TreeNode($2->lineNo, NODE_STMT);
        node->stmtType = STMT_BLCK;
        node->addChild($2);
        $$ = node;
    }  
}
;

BlockItem
: Decl BlockItem {
    $1->addSibling($2);
    $$ = $1;
}
| Stmt BlockItem {
    $1->addSibling($2);
    $$ = $1;
}
| {
    $$ = nullptr;
}
;

CompUnit
: Decl {
    $$ = $1;
}
| Decl CompUnit {
    $1->addSibling($2);
    $$ = $1;
}
| FuncDef {
    $$ = $1;
}
| FuncDef CompUnit {
    $1->addSibling($2);
    $$ = $1;
}
;

Cond
: LOrExp {
    $$ = $1;
}
;

ConstDecl
: CONST TYPE ConstDef ConstRest SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_DECL;
    node->addChild($1);
    node->addChild($2);
    if (*($2->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $2->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $3->child->varName << ">" << endl;
    }
    else
    {
        $3->type = $2->type;
        $3->child->isConst = true;
    }  
    node->addChild($3);
    TreeNode* p = $4;
    while (p != nullptr)
    {
        if (*($2->type) != *(p->type))
        {
            tErr++;
            cout << "error @" << $1->lineNo << ": ";
            cout << "cannot match type <";
            cout << $2->type->getTypeInfo() << "> ";
            cout << "to identifier <";
            cout << p->child->varName << ">" << endl;
        }
        else
        {
            p->type = $2->type;
            p->child->isConst = true;
        }
        p = p->rsib;
    }
    node->addChild($4);
    $$ = node;
}
;

ConstDef
: ID T_ASS ConstInitVal {
    $1->type = $3->type;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $1->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
;

ConstInitVal
: BOOL {
    $$ = $1;
}
| CHAR {
    $$ = $1;
}
| Exp {
    $$ = $1;
}
| STRING {
    $$ = $1;
}
;

ConstRest
: COMA ConstDef ConstRest {
    $2->addSibling($3);
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

Decl
: ConstDecl {
    $$ = $1;
}
| VarDecl {
    $$ = $1;
}
;

EqExp
: EqExp T_EQ RelExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_EQ;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| EqExp T_NOTE RelExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_NOTE;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| RelExp {
    $$ = $1;
}
;

Exp
: Cond {
    $$ = $1;
}
| LowExp {
    $$ = $1;
}
;

ForEnd
: Assign {
    $$ = $1;
}
| {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = "forend";
    $$ = node;
}
;

ForHead
: Assign SEMI {
    $$ = $1;
}
| Decl {
    $$ = $1;
}
| ID SEMI {
    $$ = $1;
}
| SEMI {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = "forhead";
    $$ = node;
}
;

ForMid
: Cond SEMI {
    $$ = $1;
}
| SEMI {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = "formid";
    $$ = node;
}
;

FuncDef
: TYPE MAIN LPATH FuncFParams RPATH { inFunc.push($1); } Block {
    TreeNode* node = new TreeNode($1->lineNo, NODE_PROG);
    node->addChild($1);
    node->addChild($2);
    node->addChild($4);
    node->addChild($7);
    $$ = node;
    inFunc.pop();
}
| TYPE ID LPATH FuncFParams RPATH {
    inFunc.push($1); 
    isRet = false;
} Block {
    TreeNode* node = new TreeNode($1->lineNo, NODE_PROG);
    node->addChild($1);
    node->addChild($2);
    node->addChild($4);
    node->addChild($7);
    $$ = node;
    inFunc.pop();
    if (!isRet && *($1->type) != *(TYPE_VOID))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "no <" << $1->type->getTypeInfo();
        cout << "> return for function\n";
    }
}
;

FuncFParam
: TYPE ID {
    TreeNode* node = new TreeNode($1->lineNo, NODE_PARM);
    node->addChild($1);
    $2->type = $1->type;
    node->addChild($2);
    $$ = node;
}
;

FuncFParams
: FuncFParam FuncFRest {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_PARM;
    node->addChild($1);
    node->addChild($2);
    $$ = node;
}
| {
    $$ = nullptr;
}
;

FuncRParams
: Exp FuncRRest {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_PARM;
    node->addChild($1);
    node->addChild($2);
    $$ = node;
}
| {
    $$ = nullptr;
}
;

FuncFRest
: COMA FuncFParam FuncFRest {
    $2->addSibling($3);
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

FuncRRest
: COMA Exp FuncRRest {
    $2->addSibling($3);
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

HighExp
: HighExp T_DIV UnaryExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_DIV;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| HighExp T_MOD UnaryExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_MOD;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| HighExp T_MUL UnaryExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_MUL;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
} 
| UnaryExp {
    $$ = $1;
}
;

IfRest
: ELSE IF LPATH Cond RPATH Stmt IfRest {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_COND;
    node->addChild($1);
    node->addChild($4);
    node->addChild($6);
    node->addChild($7);
    $$ = node;
}
| ELSE Stmt {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_COND;
    node->addChild($1);
    node->addChild($2);
    $$ = node;
}
| {
    $$ = nullptr;
}
;

IO
: CHAR_OUT LPATH CHAR RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    node->addChild($3);
    $$ = node;
}
| CHAR_OUT LPATH ID RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    $3->type = TYPE_CHAR;
    node->addChild($3);
    $$ = node;    
}
| CHAR_OUT LPATH INT RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    $3->type = TYPE_CHAR;
    node->addChild($3);
    $$ = node;    
}
| INT_OUT LPATH Exp RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    $3->type = TYPE_INT;
    node->addChild($3);
    $$ = node;
}
| STR_OUT LPATH ID RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    node->addChild($3);
    $$ = node;
}
| STR_OUT LPATH STRING RPATH SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->varName = "output";
    node->addChild($3);
    $$ = node;
}
;

LAndExp
: EqExp {
    $$ = $1;
}
| LAndExp T_AND EqExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_AND;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    node->type = $1->type;
    $$ = node;
}
;

LOrExp
: LAndExp {
    $$ = $1;
}
| LAndExp T_OR LOrExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_OR;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
;

LowExp
: HighExp {
    $$ = $1;
}
| LowExp T_PLUS HighExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_PLUS;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| LowExp T_MINS HighExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_MINS;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
;

Lval
: ID LvalRest{
    $1->addChild($2);
    $$ = $1;
}
;

LvalRest
: LSQ Exp RSQ {
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

PrimaryExp
: LPATH Cond RPATH {
    $$ = $2;
}
| LPATH Exp RPATH {
    $$ = $2;
}
| INT {
    $$ = $1;
}
| Lval {
    $$ = $1;
}
;

RelExp
: LowExp {
    $$ = $1;
}
| RelExp T_LA LowExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_LA;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| RelExp T_LAE LowExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_LAE;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| RelExp T_LE LowExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_LE;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
| RelExp T_LEE LowExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = OP_LEE;
    if (*($1->type) != *($3->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot calculate type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "with <";
        cout << $3->type->getTypeInfo() << ">" << endl;
    }
    if (!isNTS($1->type))
    {
        $3->type = $1->type;
        node->type = $1->type;
    }
    else
    {
        $1->type = $3->type;
        node->type = $3->type;   
    }
    node->addChild($1);
    node->addChild($3);
    $$ = node;
}
;

StartProg
: CompUnit {
    root = new TreeNode(0, NODE_PROG);
    root->addChild($1);
}
;

Stmt
: Assign SEMI {
    $$ = $1;
}
| Block {
    $$ = $1;
}
| BREAK SEMI {
    if (Lloop == 0)
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "<break> must be in loop" << endl;
    }
    $$ = $1;
}
| CONTINUE SEMI {
    if (Lloop == 0)
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "<continue> must be in loop" << endl;
    }
    $$ = $1;
}
| Exp SEMI {
    $$ = $1;
}
| FOR { Lloop++; } LPATH ForHead ForMid ForEnd RPATH Stmt {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_LOOP;
    node->addChild($1);
    node->addChild($4);
    node->addChild($5);
    node->addChild($6);
    node->addChild($8);
    $$ = node;
    Lloop--;
}
| IF LPATH Cond RPATH Stmt IfRest {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_COND;
    node->addChild($3);
    node->addChild($5);
    node->addChild($6);
    $$ = node;
}
| IO {
    $$ = $1;
}
| RETURN SEMI {
    if (inFunc.empty())
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "<return> must be in function\n";
    }
    else if (*(inFunc.top()->type) != *(TYPE_VOID))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "type <void> cannot match with ";
        cout << "<" << inFunc.top()->type->getTypeInfo();
        cout << ">\n";
    }
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_RET;
    $$ = node;
    isRet = true;
}
| RETURN Exp SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_RET;
    node->addChild($2);
    $$ = node;
    if (inFunc.empty())
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "<return> must be in function\n";
    }
    else if (*(inFunc.top()->type) != *($2->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "type <" << $2->type->getTypeInfo();
        cout << "> cannot match with ";
        cout << "<" << inFunc.top()->type->getTypeInfo();
        cout << ">\n";
    }
    isRet = true;
}
| SEMI {
    $$ = nullptr;
}
| WHILE { Lloop++; } LPATH Cond RPATH Stmt {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_LOOP;
    node->addChild($1);
    node->addChild($4);
    node->addChild($6);
    $$ = node;
    Lloop--;
}
;

UnaryExp
: ID LPATH { tempID = lineNo; } FuncRParams RPATH {
    TreeNode* node = new TreeNode(tempID, NODE_FUNC);
    node->type = TYPE_INT;
    node->addChild($1);
    node->addChild($4);
    $$ = node;
}
| PrimaryExp {
    $$ = $1;
}
| UnaryOp UnaryExp {
    TreeNode* node = new TreeNode($1->lineNo, NODE_EXPR);
    node->opType = $1->opType;
    node->type = $2->type;
    node->addChild($2);
    $$ = node;
}
;

UnaryOp
: T_MINS {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_MINS;
    $$ = node;
}
| T_NOT {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_NOT;
    $$ = node;
}
| T_PLUS {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_PLUS;
    $$ = node;  
}
;

VarArray
: VarInitVal VarInitRest {
    $1->addSibling($2);
    $$ = $1;
}
;

VarDecl
: TYPE VarDef VarRest SEMI {
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_DECL;
    node->addChild($1);
    if (*($1->type) != *($2->type))
    {
        tErr++;
        cout << "error @" << $1->lineNo << ": ";
        cout << "cannot match type <";
        cout << $1->type->getTypeInfo() << "> ";
        cout << "to identifier <";
        cout << $2->child->varName << ">" << endl;
    }
    else
        $2->type->type = $1->type->type;          
    node->addChild($2);
    TreeNode* p = $3;
    while (p != nullptr)
    {
        if (*($1->type) != *(p->type))
        {
            tErr++;
            cout << "error @" << $1->lineNo << ": ";
            cout << "cannot match type <";
            cout << $1->type->getTypeInfo() << "> ";
            cout << "to identifier <";
            cout << p->child->varName << ">" << endl;
        }
        else
            p->type->type = $1->type->type;
        p = p->rsib;
    }
    node->addChild($3);
    $$ = node;
}
;

VarDef
: ID {
    $$ = $1;
}
| ID LSQ LowExp RSQ {
    $1->type->isArray = true;
    $1->type->size = $3->ival;
    $$ = $1;
}
| ID LSQ LowExp RSQ T_ASS VarInitVal {
    $1->type->isArray = true;
    $1->type->size = $3->ival;
    $1->addSibling($6);
    $$ = $1;
}
| ID T_ASS VarInitVal {
    $1->type = $3->type;
    TreeNode* node = new TreeNode($1->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->type = $1->type;
    node->addChild($1);
    node->addChild($3);
    node->bval = true;
    $$ = node;
}
;

VarInitRest
: COMA VarInitVal VarInitRest {
    $2->addSibling($3);
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

VarInitVal
: BOOL {
    $$ = $1;
}
| CHAR {
    $$ = $1;
}
| Exp {
    $$ = $1;
}
| LBRAC VarArray RBRAC {

}
| STRING {
    $$ = $1;
}
;

VarRest
: COMA VarDef VarRest {
    $2->addSibling($3);
    $$ = $2;
}
| {
    $$ = nullptr;
}
;

%%

int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}