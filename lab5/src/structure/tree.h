#ifndef TREE_H
#define TREE_H

#include "../pch.h"
#include "type.h"

enum NodeType
{
    NODE_CONST, // 常量
    NODE_EXPR,  // 表达式
    NODE_KEY,   // 保留字
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
    OP_MINS,    // -
    OP_MINE,    // -=
    OP_MOD,     // %
    OP_MODE,    // %=
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
    bool bval;  // 布尔
    char cval;  // 字符
    int ival;   // 整型
    int lineNo; // 行号
    int nodeID; // 节点号
    NodeType nodeType;  // 节点类型
    OpType opType;      // 操作符类型
    StmtType stmtType;  // 语句类型
    string sval;        // 字符串
    string varName;     // 变量名
    TreeNode* child = nullptr;      // 孩子指针
    TreeNode* sibling = nullptr;    // 兄弟指针
    Type* type;                     // 类型
    
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