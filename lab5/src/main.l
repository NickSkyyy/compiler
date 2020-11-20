%option nounput
%{
    #include "common.h"
    #include "main.tab.h"
    int lineNo = 1;
%}

BOOL        True|False
BREAK       break
CONST       const
CONTINUE    continue
ELSE        else
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
{SPAC} {;}

%%
// functions