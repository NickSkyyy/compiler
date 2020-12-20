#include "common.h"

#define YYSTYPE TreeNode*

extern FILE* yyin;
extern int yyparse();
extern TreeNode* root;

map<pair<TreeNode*, string>, TreeNode*> idt;
int tErr = 0;   // 错误类型数量

void printIdt()
{
    cout << "++ idt map ++" << endl;
    for (auto &it : idt)
    {
        pair<TreeNode*, string> p = it.first;
        TreeNode* parent = p.first;
        string name = p.second;
        TreeNode* myself = it.second;
        cout << "var: " << name << " ";
        cout << "(@" << myself->nodeID;
        cout << ", @" << parent->nodeID << ")" << endl;
    }
}

void printInfo(char* argv[])
{
    cout << "+--------------";
    for (int i = 0; i <= strlen(argv[1]); i++)
        cout << "-";
    cout << "+" << endl;
    cout << "- Source file: " << argv[1];
    cout << " -" << endl;
    cout << "+--------------";
    for (int i = 0; i <= strlen(argv[1]); i++)
        cout << "-";
    cout << "+" << endl;
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        FILE* fin = fopen(argv[1], "r");
        if (fin != nullptr)
            yyin = fin;
        else
            cerr << "failed to open file: " << argv[1] << endl;
    }
    yyparse();
    if (root != NULL) 
    {
        printInfo(argv);
        root->genNodeId(0);   
        root->checkType();
        if (tErr == 0)
        {
            root->printAST();
            // root->printRe();
            printIdt();
        }
        
    }
    return 0;
}