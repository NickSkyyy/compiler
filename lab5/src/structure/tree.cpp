#include "iomanip"
#include "tree.h"

string TreeNode::nodeType2Str(NodeType type)
{
    switch (type)
    {
    case NODE_CONST:
        return "const";
    case NODE_EXPR:
        return "expression";
    case NODE_KEY:
        return "key";
    case NODE_OP:
        return "operator";
    case NODE_PARM:
        return "param";
    case NODE_PROG:
        return "program";
    case NODE_STMT:
        return "statement";
    case NODE_TYPE:
        return "type";
    case NODE_VAR:
        return "variable";
    default:
        return "NOT SURE";
    }
}

string TreeNode::opType2Str(OpType type)
{
    switch (type)
    {
    case OP_AND:
        return "&&";
    case OP_ASS:
        return "=";
    case OP_DIV:
        return "/";
    case OP_DIVE:
        return "/=";
    case OP_EQ:
        return "==";
    case OP_LA:
        return ">";
    case OP_LAE:
        return ">=";
    case OP_LE:
        return "<";
    case OP_LEE:
        return "<=";
    case OP_MINS:
        return "-";
    case OP_MINE:
        return "-=";
    case OP_MOD:
        return "%";
    case OP_MODE:
        return "%=";
    case OP_MUL:
        return "*";
    case OP_MULE:
        return "*=";
    case OP_NOT:
        return "!";
    case OP_NOTE:
        return "!=";
    case OP_OR:
        return "||";
    case OP_PLUE:
        return "+=";
    case OP_PLUS:
        return "+";
    default:
        return "NOT SURE";
    }
}

string TreeNode::stmtType2Str(StmtType type)
{
    switch (type)
    {
    case STMT_ASS:
        return "assign";
    case STMT_BLCK:
        return "block";
    case STMT_DECL:
        return "declaration";
    case STMT_PARM:
        return "params";
    case STMT_RET:
        return "return";
    case STMT_SKIP:
        return "comments";
    default:
        return "NOT SURE";
    }
}

TreeNode::TreeNode(int lineNo, NodeType type)
{
    this->lineNo = lineNo;
    this->nodeType = type;
}

void TreeNode::addChild(TreeNode* child)
{
    if (child == nullptr) return;
    if (this->child == nullptr)
        this->child = child;
    else
    {
        TreeNode* p = this->child;
        while (p->sibling != nullptr) { p = p->sibling; }
        p->sibling = child;
    } 
}

void TreeNode::addSibling(TreeNode* sibling)
{
    if (sibling == nullptr) return;
    if (this->sibling == nullptr)
        this->sibling = sibling;
    else
    {
        TreeNode* p = this->sibling;
        while (p->sibling != nullptr) { p = p->sibling; }
        p->sibling = sibling;
    }
}

int TreeNode::genNodeId(int id)
{
    nodeID = id++;
    TreeNode* p;
    // children
    p = child;
    if (p != nullptr) id = p->genNodeId(id);
    p = sibling;
    if (p != nullptr) id = p->genNodeId(id);
    return id;
}

void TreeNode::printAST()
{
    printNodeInfo();
    printSpecialInfo();
    TreeNode* p;
    // children
    p = child;
    if (p != nullptr) p->printAST();
    // siblings
    p = sibling;
    if (p != nullptr) p->printAST();
}

void TreeNode::printChildrenId()
{
    TreeNode* p = child;
    if (p != nullptr)
    {
        cout << "children: [ ";
        while (p != nullptr)
        {
            cout << "@" << p->nodeID << " ";
            p = p->sibling;
        }
        cout << "]";     
    }
}

void TreeNode::printNodeInfo()
{
    // self info
    if (nodeType == NODE_PROG) cout << endl;
    cout << "lno@";
    cout << setiosflags(ios::left) << setw(5) << lineNo;
    cout << "@";
    cout << setiosflags(ios::left) << setw(5) << nodeID;
    cout << setiosflags(ios::left) << setw(15) << nodeType2Str(nodeType);
    printChildrenId();
}

void TreeNode::printSpecialInfo()
{
    if (nodeType == NODE_CONST)
    {
        cout << "value: ";
        switch (type->type)
        {
        case VALUE_BOOL:
            cout << bval;
            break;
        case VALUE_CHAR:
            cout << cval;
            break;
        case VALUE_INT:
            cout << ival;
            break;
        case VALUE_STRING:
            cout << sval;
            break;
        default:
            cout << "NOT SURE";
            break;
        }
    }
    if (nodeType == NODE_EXPR)
    {
        cout << endl;
        for (int i = 0; i < 15; i++) cout << " ";
        cout << "opeartor: ";
        cout << opType2Str(opType);
    }
    if (nodeType == NODE_KEY)
    {
        cout << "key: ";
        cout << varName;
    }
    if (nodeType == NODE_STMT)
    {
        cout << endl;
        for (int i = 0; i < 15; i++) cout << " ";
        cout << "stmt: ";
        cout << stmtType2Str(stmtType);
    }
    if (nodeType == NODE_TYPE)
    {
        cout << "type: ";
        cout << type->getTypeInfo();
    }
    if (nodeType == NODE_VAR)
    {
        cout << "varname: ";
        cout << varName;
    }
    cout << endl;
}