%option nounput
%{
    #include "common.h"
    #include "main.tab.h"
    int lineNo = 1;
%}

break       break
const       const
continue    continue
else        else
if          if
main        main
return      return
type        int|void
while       while

lbrace      \{
rbrace      \}
lcomment_b  "/*"
comment_b   \" (\* \/ | .)* \"|.|\n
rcomment_b  "*/"
lcomment_l  "//"
rcomment_l  \n
lparentheses    "("
rparentheses    ")"

and         "&&"
assign      "="
be          ">="
biger       ">"
da          "/="
divide      "/"
equal       "=="
id          [a-z_A-Z][0-9a-z_A-Z]*
le          "<="
less        "<"
ma          "*="
mia         "-="
minus       "-"
mod         "%"
multiply    "*"
ne          "!="
not         "!"
num_d       [1-9][0-9]*
num_h       (0x|0X)[0-9a-fA-F]*
num_o       0[0-7]*
or          "||"
pa          "+="
plus        "+"
semicolon   ";"
space       [ \t\n]

comment_l   .

%x COMMENT_B
%x COMMENT_L
%%

%%
// functions