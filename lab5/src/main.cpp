#include "common.h"

#define YYSTYPE TreeNode*

extern FILE* yyin;
extern int yyparse();
extern map<pair<TreeNode*, string>, TreeNode*> idt;
extern map<int, TreeNode*> id2id;
extern TreeNode* root;

int tErr = 0;   // 错误类型数量

void printIdt()
{
    cout << "\n++ idt map ++\n";
    for (auto &it : idt)
    {
        pair<TreeNode*, string> p = it.first;
        TreeNode* parent = p.first;
        string name = p.second;
        TreeNode* myself = it.second;
        cout << name << " : " << myself->type->getTypeInfo();
        cout << "(@" << myself->nodeID;
        cout << ", @" << parent->nodeID << ") ";
        cout << (myself->isConst ? "const" : "var") << endl;
    }
}

void printInfo(char* argv[])
{
    cout << "+--------------";
    for (int i = 0; i <= (int)strlen(argv[1]); i++)
        cout << "-";
    cout << "+" << endl;
    cout << "- Source file: " << argv[1];
    cout << " -" << endl;
    cout << "+--------------";
    for (int i = 0; i <= (int)strlen(argv[1]); i++)
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
            printIdt();
            ofstream os("./out/test.s"); 
            root->genStr(os);
            root->genCode(os);
            os << "\t.section\t.note.GNU-stack,\"\",@progbits";
            os.close();
        }
        else
            cout << "error tot: " << tErr << endl;      
    }
    return 0;
}