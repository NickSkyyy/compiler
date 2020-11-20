#ifnedf TREE_H
#define TREE_H

#include "../pch.h"
#include "type.h"

enum NodeType
{
    NODE_CONST, // 常量
    NODE_EXPR,  // 表达式
    NODE_PROG,  // 程序段
    NODE_STMT,  // 语句
    NODE_TYPE,  // 类型
    NODE_VAR    // 变量
};

enum OpType
{
    OP_ADD,     // +
    OP_ADDE,    // +=
    OP_AND,     // &&
    OP_ASS,     // =
    OP_DIV,     // /
    OP_DIVE,    // /=
    OP_EQ,      // ==
    OP_LA,      // >
    OP_LAE,     // >=
    OP_LE,      // <
    OP_LEE,     // <=
    OP_MINUS,   // -
    OP_MINUSE,  // -=
    OP_MOD,     // %
    OP_MUL,     // *
    OP_MULE,    // *=
    OP_NOT,     // !
    OP_NOTE,    // !=
    OP_OR,      // ||
};

enum StmtType
{
    STMT_DECL,  // 声明
    STMT_SKIP,  // 注释
};

struct TreeNode
{
public:
    bool bval;
    char cval;
    int ival;
    int lineNo;
    int nodeID;
    NodeType nodeType;
    OpType opType;
    StmtType stmeType;
    string sval;
    string varName;
    TreeNode* child = nullptr;
    TreeNode* sibling = nullptr;
    Type* type;
    
public:
    static string nodeType2Str(NodeType type);
    static string opType2Str(NodeType type);
    static string stmtType2Str(StmtType type);
    TreeNode(int lineNo, NodeType type);
    void addChild(TreeNode*);
    void addSibling(TreeNode*);
    void genNodeId();   // 生成节点ID（nodeID）
    void printAST();
    void printChildrenId();
    void printNodeInfo();
    void printSpecialInfo();
};

#endif TREE_H