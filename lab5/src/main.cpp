#include "common.h"

#define YYSTYPE TreeNode*

extern TreeNode* root;
extern FILE* yyin;
extern int yyparse();

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
        root->genNodeId(0);
        printInfo(argv);
        root->printAST();
        //root->printRe();
    }
    return 0;
}