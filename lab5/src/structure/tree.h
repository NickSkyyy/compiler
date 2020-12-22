#include "../pch.h"
#include "type.h"

enum NodeType
{
    NODE_CONST, // 常量
    NODE_EXPR,  // 表达式
    NODE_KEY,   // 保留字
    NODE_OP,    // 符号
    NODE_PARM,  // 参数
    NODE_PROG,  // 程序段
    NODE_STMT,  // 语句
    NODE_TYPE,  // 类型
    NODE_VAR    // 变量
};

enum OpType
{
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
    OP_PLUE,    // +=
    OP_PLUS,    // +
};

enum StmtType
{
    STMT_ASS,   // 赋值
    STMT_BLCK,  // 语句块
    STMT_COND,  // 条件
    STMT_DECL,  // 声明
    STMT_IO,    // 输入输出
    STMT_LOOP,  // 循环
    STMT_PARM,  // 参数列表
    STMT_RET,   // 返回（带值）
    STMT_SKIP,  // 注释
};

struct TreeNode
{
public:
    bool bval = 0;    // 布尔
    bool isConst = 0; // 是否为常量
    char cval = ' ';  // 字符
    int ival = 0;     // 整型
    int lineNo; // 行号
    int nodeID; // 节点号
    NodeType nodeType;  // 节点类型
    OpType opType;      // 操作符类型
    StmtType stmtType;  // 语句类型
    string sval = "";   // 字符串
    string varName = "";     // 变量名
    TreeNode* child = nullptr;      // 孩子指针
    TreeNode* parent = nullptr;     // 父亲节点（符号表）
    TreeNode* lsib = nullptr;       // 左兄弟
    TreeNode* rsib = nullptr;       // 右兄弟
    Type* type = nullptr;           // 类型
    
public:
    bool operator <(const TreeNode b) const
    {
        if (nodeID == b.nodeID)
        {
            if (parent->nodeID == b.parent->nodeID)
                return lineNo < b.lineNo;
            return parent->nodeID < b.parent->nodeID;
        }
        return nodeID < b.nodeID;
    };
    int checkType();
    int find(string name);
    int genNodeId(int id);
    static string nodeType2Str(NodeType type);
    static string opType2Str(OpType type);
    static string stmtType2Str(StmtType type);
    TreeNode(int lineNo, NodeType type);   
    void addChild(TreeNode*);
    void addSibling(TreeNode*); 
    void genCode(ofstream &os);
    void printAST();
    void printRe();
    void printChildrenId();
    void printNodeInfo();
    void printSpecialInfo();
};