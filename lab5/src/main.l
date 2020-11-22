%option nounput
%top{
    #include "common.h"
    #include "main.tab.h"
    int lineNo = 1;
}
%{
    int hex(char ch) {
        if (ch >= '0' && ch <= '9')
            return ch - '0';
        if (ch >= 'a' && ch <= 'f')
            return ch - 'a' + 10;
        if (ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;
    }
    int htod(string s)
    {
        int sum = 0;
        for (int i = 2; i < s.length(); i++)
            sum = sum * 16 + hex(s[i]);
        return sum;
    }
    int otod(string s)
    {
        int sum = 0;
        for (int i = 1;i < s.length(); i++)
            sum = sum * 8 + (s[i] - '0');
        return sum;
    }
%}

BOOL        True|False
BREAK       break
CONST       const
CONTINUE    continue
ELSE        else
FOR         for
IF          if
MAIN        main
RETURN      return
TYPE        bool|char|int|string|void
WHILE       while

lbrace      \{
rbrace      \}
lcomment_b  "/*"
comment_b   \" (\* \/ | .)* \"|.|\n
rcomment_b  "*/"
lcomment_l  "//"
rcomment_l  \n
lparentheses    "("
rparentheses    ")"

AND         "&&"
ASS         "="
CHAR        \'.?\'
DIV         "/"
DIVE        "/="
EOL         [\r\n|\r|\n]
EQ          "=="
ID          [a-z_A-Z][0-9a-z_A-Z]*
LA          ">"
LAE         ">="
LE          "<"
LEE         "<="
MINE        "-="
MINS        "-"
MOD         "%"
MODE        "%="
MUL         "*"
MULE        "*="
NOT         "!"
NOTE        "!="
NUMD        [1-9][0-9]*
NUMH        (0x|0X)[0-9a-fA-F]*
NUMO        0[0-7]*
OR          "||"
PLUE        "+="
PLUS        "+"
SEMI        ";"
SPAC        [ \t]
STR         \".*\"

comment_l   .

%x COMMENT_B
%x COMMENT_L
%%

{BOOL} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_BOOL;
    if (yytext == "True")
        node->bval = true;
    else if (yytext == "False")
        node->bval = false;
    yylval = node;
    return BOOL;
}
{BREAK} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return BREAK;
}
{CONST} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return CONST;
}
{CONTINUE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return CONTINUE;
}
{ELSE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return ELSE;
}
{FOR} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return FOR;
}
{IF} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return IF;
}
{MAIN} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return MAIN;
}
{RETURN} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return RETURN;
}
{TYPE} {
    TreeNode* node = new TreeNode(lineNo, NODE_TYPE);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return TYPE;
}
{WHILE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->type = KEY;
    node->vname = yytext;
    yylval = node;
    return WHILE;
}

{lcomment_b} {BEGIN COMMENT_B;}
<COMMENT_B>{comment_b} {;}
<COMMENT_B>{rcomment_b} {BEGIN INITIAL;}
{lcomment_l} {BEGIN COMMENT_L;}
<COMMENT_L>{comment_l} {;}
<COMMENT_L>{rcomment_l} {BEGIN INITIAL;}

{AND} {return OP_AND;}
{ASS} {return OP_ASS;}
{CHAR} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_CHAR;
    node->cval = yytext[1];
    yylval = node;
    return CHAR;
}
{DIV} {return OP_DIV;}
{DIVE} {return OP_DIVE;}
{EOL} {lineNo++;}
{EQ} {return OP_EQ;}
{ID} {
    TreeNode* node = new TreeNode(lineNo, NODE_VAR);
    node->vname = string(yytext);
    node->bval = false;
    node->cval = '';
    node->ival = 0;
    node->sval = "";
    yyval = node;
    return ID;
}
{LA} {return OP_LA;}
{LAE} {return OP_LAE;}
{LE} {return OP_LE;}
{LEE} {return OP_LEE;}
{MINE} {return OP_MINE;}
{MINS} {return OP_MINS;}
{MOD} {return OP_MOD;}
{MODE} {return OP_MODE;}
{MUL} {return OP_MUL;}
{MULE} {return OP_MULE;}
{NOT} {return OP_NOT;}
{NOTE} {return OP_NOTE;}
{NUMD} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_INT;
    node->ival = atoi(yytext);
    yylval = node;
    return INT;
}
{NUMH} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_INT;
    node->ival = htod(yytext);
    yylval = node;
    return INT;
}
{NUMO} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_INT;
    node->ival = otod(yytext);
    yylval = node;
    return INT;
}
{OR} {return OP_OR;}
{PLUE} {return OP_PLUE;}
{PLUS} {return OP_PLUS;}
{SEMI} {return SEMI;}
{SPAC} {;}
{STR} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_STRING;
    node->sval = yytext;
    yylval = node;
    return STRING;
}

%%
// functions