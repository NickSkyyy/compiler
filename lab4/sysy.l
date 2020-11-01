%option noyywrap
%top{
    #include <cmath>
    #include <cstdlib>
    #include <cstdio>
    #include <cstring>
    #include <fstream>
    #include <iomanip>
    #include <iostream>
    #include <map>
    #include <stack>
    #include <stdio.h>
    #include <utility>
    using namespace std;
}
%{
    ifstream input("./testin");
    ofstream output("./testout");
    
    class domain
    {
    public:
        string block;
        int level;
        domain(){}
        domain(string block, int level):block(block), level(level){}
        bool operator <(const domain b) const
        {
            if (block==b.block)
                return level<b.level;
            return block<b.block;
        }
    };

    int step = 0;           // step of check block 
    bool isMain = false;    // check if main
    string block = "*";     // * as global as default
    string nextB = "*";     // domain coming next
    stack<domain> ss = stack<domain>(); // level depth in domain
    int level = 0;          // son domain in block
    int pathNum = 0;        // check parenthese pair

    
    map<domain, int> llen = map<domain, int>();
    map<domain, int>::iterator it1;
    map<pair<domain, string>, int> idt = map<pair<domain, string>, int>();
    map<pair<domain, string>, int>::iterator it2;

    int getHex(char ch)
    {
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
        int ans = 0;
        for (int i = 2; i < s.length(); i++)
            ans = (ans << 4) + getHex(s[i]);
        return ans;
    }

    int otod(string s)
    {
        int ans = 0;
        for (int i = 1; i < s.length(); i++)
            ans = (ans << 3) + s[i] - '0';
        return ans;
    }
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
rcomment_b  "*/"
lcomment_l  "//"
rcomment_l  \n
lparentheses    "("
rparentheses    ")"

and         "&&"
be          ">="
biger       ">"
equal       "=="
assign      "="
da          "/="
divide      "/"
id          [a-z_A-Z][0-9a-z_A-Z]*
le          "<="
less        "<"
mia         "-="
minus       "-"
mod         "%"
ma          "*="
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

comment_b   .|\n
comment_l   .

%x COMMENT_B
%x COMMENT_L
%%
{break}         {output<<"BREAK"<<setw(8)<<yytext<<endl;}
{const}         {output<<"CONST"<<setw(8)<<yytext<<endl;}
{continue}      {output<<"CONTINUE"<<setw(8)<<yytext<<endl;}
{else}          {output<<"ELSE"<<setw(8)<<yytext<<endl;}
{if}            {output<<"IF"<<setw(8)<<yytext<<endl;}
{main}          {block="main";output<<"MAIN"<<setw(8)<<yytext<<endl;}
{return}        {output<<"RETURN"<<setw(8)<<yytext<<endl;}
{type}          {
    step=1;
    output<<"TYPE"<<setw(8)<<yytext<<endl;
}
{while}         {output<<"WHILE"<<setw(8)<<yytext<<endl;}

{lbrace}        {
    if (isMain||block!="main")
    {
        ss.push(domain(block, level));
        if (step==4)
        {
            step=0;
            block=nextB;
            level=0;
        }
        else
            level++;
    }
    else
    {
        ss.push(domain("*", 0));
        block="main";
        level=0;
        if (!isMain) isMain=true;
    }      
    output<<"LBRACE"<<setw(8)<<yytext<<endl;
}
{rbrace}        {
    domain d = ss.top();
    ss.pop();
    // delete old value
    llen.erase(domain(block, level));
    stack<pair<domain, string> > temp;
    for (it2=idt.begin(); it2!=idt.end(); ++it2)
        if (it2->first.first.block==block&&it2->first.first.level==level)
            temp.push(it2->first);
    while (!temp.empty())
    {
        idt.erase(temp.top());
        temp.pop();
    }           
    // back trace
    block = d.block;
    level = d.level;
    output<<"RBRACE"<<setw(8)<<yytext<<endl;
}
{lcomment_b}    {BEGIN COMMENT_B;}
<COMMENT_B>{comment_b}  {;}
<COMMENT_B>{rcomment_b} {BEGIN INITIAL;}
{lcomment_l}    {BEGIN COMMENT_L;}
<COMMENT_L>{comment_l}  {;}
<COMMENT_L>{rcomment_l} {BEGIN INITIAL;}
{lparentheses}  {
    if (step==2) step=3;
    pathNum++;
    output<<"LPARENTHESES"<<setw(8)<<yytext<<endl;
}
{rparentheses}  {
    pathNum--;
    if (pathNum==0&&step==3) step=4;
    output<<"RPARENTHESES"<<setw(8)<<yytext<<endl;
}

{and}           {output<<"AND"<<setw(8)<<yytext<<endl;}
{assign}        {output<<"ASSIGN"<<setw(8)<<yytext<<endl;}
{be}            {output<<"BE"<<setw(8)<<yytext<<endl;}
{biger}         {output<<"BIGER"<<setw(8)<<yytext<<endl;}
{da}            {output<<"DA"<<setw(8)<<yytext<<endl;}
{divide}        {output<<"DIVIDE"<<setw(8)<<yytext<<endl;}
{equal}         {output<<"EQUAL"<<setw(8)<<yytext<<endl;}
{id}            {
    if (step==1) 
    {
        nextB=yytext;
        step=2;
    }
    domain d;
    pair<domain, string> p;

    int id;
    bool isFind=false;
    for (int i=level; i>=0; i--)
    {
        d=domain(block, i);
        p=make_pair(d, yytext);
        it2=idt.find(p);
        if (it2!=idt.end())
        {
            id=it2->second;
            isFind=true;
            break;
        }
        else if (step==2)
        {
            // create a new id
            it1=llen.find(d);
            if (it1==llen.end())
                // not in llen map
                llen.insert(make_pair(d, 0));
            id=llen.find(d)->second;
            llen.erase(d);
            llen.insert(make_pair(d, id+1));
            idt.insert(make_pair(p, id));
            isFind=true;
            break;
        }
    }
    if (!isFind)
    {
        // in global
        d=domain("*", 0);
        p=make_pair(d, yytext);
        it2=idt.find(p);
        if (it2!=idt.end())
        {
            id=it2->second;
            isFind=true;
        }
    }   
    if (!isFind)
    {
        // new id insert in table
        d=domain(block, level);
        p=make_pair(d, yytext);

        it1=llen.find(d);
        if (it1==llen.end())
            // not in llen map
            llen.insert(make_pair(d, 0));
        int r=llen.find(d)->second;
        llen.erase(d);
        llen.insert(make_pair(d, r+1));
        idt.insert(make_pair(p, r));
        output<<"ID"<<setw(8)<<yytext<<setw(8);
        output<<"("<<d.block<<", "<<d.level<<")"<<": "<<r<<endl;
    }
    else
    {
        output<<"ID"<<setw(8)<<yytext<<setw(8);
        output<<"("<<d.block<<", "<<d.level<<")"<<": "<<id<<endl;
    }   
}
{le}            {output<<"LE"<<setw(8)<<yytext<<endl;}
{less}          {output<<"LESS"<<setw(8)<<yytext<<endl;}
{mia}           {output<<"MIA"<<setw(8)<<yytext<<endl;}
{minus}         {output<<"MINUS"<<setw(8)<<yytext<<endl;}
{mod}           {output<<"MOD"<<setw(8)<<yytext<<endl;}
{ma}            {output<<"MA"<<setw(8)<<yytext<<endl;}
{multiply}      {output<<"MULTIPLY"<<setw(8)<<yytext<<endl;}
{ne}            {output<<"NE"<<setw(8)<<yytext<<endl;}
{not}           {output<<"NOT"<<setw(8)<<yytext<<endl;}
{num_d}         {output<<"NUMBER_D"<<setw(8)<<yytext<<setw(8)<<atoi(yytext)<<endl;}
{num_h}         {output<<"NUMBER_H"<<setw(8)<<yytext<<setw(8)<<htod(yytext)<<endl;}
{num_o}         {output<<"NUMBER_O"<<setw(8)<<yytext<<setw(8)<<otod(yytext)<<endl;}
{or}            {output<<"OR"<<setw(8)<<yytext<<endl;}
{pa}            {output<<"PA"<<setw(8)<<yytext<<endl;}
{plus}          {output<<"PLUS"<<setw(8)<<yytext<<endl;}
{semicolon}     {output<<"SEMICOLON"<<setw(8)<<yytext<<endl;if(step!=3)step=0;}
{space}         {;}
%%

int main()
{
    yyFlexLexer lexer(&input);
    lexer.yylex();
    return 0;
}