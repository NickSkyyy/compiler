%option nounput
%top{
    #include "common.h"
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
        return 0;
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

COMMENT_B          \"(\*\/|.)*\"|.
COMMENT_BL         "\n"
COMMENT_L          .
lbrace             "{"
lcb                "/*"
lcl                "//"
lparentheses       "("
rbrace             "}"
rcb                "*/"
rcl                \n
rparentheses       ")"

AND         "&&"
ASS         "="
CHAR        \'.?\'
COMA        ","
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

%x COMMENT_B
%x COMMENT_L
%%

{BOOL} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_BOOL;
    if (strcmp(yytext, "True") == 0)
        node->bval = true;
    else if (strcmp(yytext, "False") == 0)
        node->bval = false;
    yylval = node;
    return BOOL;
}
{BREAK} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);   
    node->varName = yytext;
    yylval = node;
    return BREAK;
}
{CONST} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY); 
    node->varName = yytext;
    yylval = node;
    return CONST;
}
{CONTINUE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = yytext;
    yylval = node;
    return CONTINUE;
}
{ELSE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = yytext;
    yylval = node;
    return ELSE;
}
{FOR} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);   
    node->varName = yytext;
    yylval = node;
    return FOR;
}
{IF} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);  
    node->varName = yytext;
    yylval = node;
    return IF;
}
{MAIN} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY); 
    node->varName = yytext;
    yylval = node;
    return MAIN;
}
{RETURN} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = yytext;
    yylval = node;
    return RETURN;
}
{TYPE} {
    TreeNode* node = new TreeNode(lineNo, NODE_TYPE);
    if (strcmp(yytext, "bool") == 0)
        node->type = TYPE_BOOL;
    else if (strcmp(yytext, "char") == 0)
        node->type = TYPE_CHAR;
    else if (strcmp(yytext, "int") == 0)
        node->type = TYPE_INT;
    else if (strcmp(yytext, "string") == 0)
        node->type = TYPE_STRING;
    else if (strcmp(yytext, "void") == 0)
        node->type = TYPE_VOID;
    else
        node->type = new Type(NOT_SURE);
    yylval = node;
    return TYPE;
}
{WHILE} {
    TreeNode* node = new TreeNode(lineNo, NODE_KEY);
    node->varName = yytext;
    yylval = node;
    return WHILE;
}

<COMMENT_B>{COMMENT_B} {;}
<COMMENT_B>{COMMENT_BL} {lineNo++;}
<COMMENT_L>{COMMENT_L} {;}
{lbrace} {return LBRAC;}
{lcb} {BEGIN COMMENT_B;}
{lcl} {BEGIN COMMENT_L;}
{lparentheses} {return LPATH;}
{rbrace} {return RBRAC;}
<COMMENT_B>{rcb} {BEGIN INITIAL;}
<COMMENT_L>{rcl} {lineNo++; BEGIN INITIAL;}
{rparentheses} {return RPATH;}

{AND} {return T_AND;}
{ASS} {return T_ASS;}
{CHAR} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_CHAR;
    node->cval = yytext[1];
    yylval = node;
    return CHAR;
}
{COMA} {return COMA;}
{DIV} {return T_DIV;}
{DIVE} {return T_DIVE;}
{EOL} {lineNo++;}
{EQ} {return T_EQ;}
{ID} {
    TreeNode* node = new TreeNode(lineNo, NODE_VAR);
    node->varName = string(yytext);
    yylval = node;
    return ID;
}
{LA} {return T_LA;}
{LAE} {return T_LAE;}
{LE} {return T_LE;}
{LEE} {return T_LEE;}
{MINE} {return T_MINE;}
{MINS} {return T_MINS;}
{MOD} {return T_MOD;}
{MODE} {return T_MODE;}
{MUL} {return T_MUL;}
{MULE} {return T_MULE;}
{NOT} {return T_NOT;}
{NOTE} {return T_NOTE;}
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
{OR} {return T_OR;}
{PLUE} {return T_PLUE;}
{PLUS} {return T_PLUS;}
{SEMI} {return SEMI;}
{SPAC} {;}
{STR} {
    TreeNode* node = new TreeNode(lineNo, NODE_CONST);
    node->type = TYPE_STRING;
    for (int i = 1; i < strlen(yytext) - 1; i++)
        node->sval += yytext[i];
    yylval = node;
    return STRING;
}

%%
// functions