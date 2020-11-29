#include "common.h"

#define YYSTYPE TreeNode*

extern TreeNode* root;
extern FILE* yyin;
extern int yyparse();

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
        root->printAST();
    }
    return 0;
}