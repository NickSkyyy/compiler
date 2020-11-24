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
    case NODE_PROG:
        return "program";
    case NODE_STMT:
        return "statement";
    case NODE_TYPE:
        return "type";
    case NODE_VAR:
        return "variable";
    default:
        break;
    }
    return "";
}

string TreeNode::opType2Str(OpType type)
{
    switch (type)
    {
    case OP_ADD:
        return "+";
    case OP_ADDE:
        return "+=";
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
    default:
        break;
    }
    return "";
}

string TreeNode::stmtType2Str(StmtType type)
{
    switch (type)
    {
    case STMT_DECL:
        return "declaration";
    case STMT_SKIP:
        return "comments";
    default:
        break;
    }
    return "";
}

TreeNode::TreeNode(int lineNo, NodeType type)
{
    this->lineNo = lineNo;
    this->nodeType = type;
}

void TreeNode::addChild(TreeNode* child)
{
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
    if (this->sibling == nullptr)
        this->sibling = sibling;
    else
    {
        TreeNode* p = this->sibling;
        while (p->sibling != nullptr) { p = p->sibling; }
        p->sibling = sibling;
    }
}

void TreeNode::genNodeId()
{
    
}

void TreeNode::printAST()
{
    printNodeInfo();
    printSpecialInfo();
    cout << endl;
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
    TreeNode* p = p->child;
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
    cout << "lno@";
    cout << setiosflags(ios::left) << setw(5) << lineNo;
    cout << "@";
    cout << setiosflags(ios::left) << setw(5) << nodeID;
    cout << setiosflags(ios::left) << setw(15) << nodeType2Str(nodeType);
    printChildrenId();
}

void TreeNode::printSpecialInfo()
{
    TreeNode* p = p->child;
    if (nodeType == NODE_TYPE)
    {
        cout << "type: ";
        cout << p->type->getTypeInfo();
    }
    if (nodeType == NODE_VAR)
    {
        cout << "varname: ";
        cout << varName;
    }
}