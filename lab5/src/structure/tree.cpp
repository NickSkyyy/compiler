#include "iomanip"
#include "tree.h"

/* 符号表：{<父亲节点，变量名>: 节点} */
extern map<pair<TreeNode*, string>, TreeNode*> idt;
extern int tErr;
// 类型检查标记位
bool isDecl, isLv, isLval;
// 代码生成标记位
bool isMain;

/**
 * 检查树的类型结构
 * 
 * @return 错误类型的数量
 */
int TreeNode::checkType()
{
    return 0;
}

/**
 * 生成节点ID（nodeID）
 * 
 * @param id 当前节点ID起始位置
 * 
 * @return int 子树最大ID
 */
int TreeNode::genNodeId(int id)
{
    if (nodeType == NODE_VAR)
    {
        isDecl = false, isLv = false;
        if (parent != nullptr && 
            parent->nodeType == NODE_STMT &&
            parent->stmtType == STMT_ASS &&
            parent->child == this)
            isLval = true;
        else
            isLval = false;
        int p = find(varName);
        if (p == 0)
        {
            // new id
            nodeID = id++;
            pair<TreeNode*, string> 
            p = make_pair(parent, varName);
            idt.insert(make_pair(p, this)); 
        }
        else if (p == -1)
        {
            // not declared
            nodeID = id++;
            tErr++;
            cout << "error @" << lineNo << ": ";
            cout << "identifier " << varName;
            cout << " not declared" << endl;    
        }
        else if (p == -2)
        {
            // duplicated
            nodeID = id++;
            tErr++;
            cout << "error @" << lineNo << ": ";
            cout << "identifier " << varName;
            cout << " duplicated" << endl;  
        }
        else if (p == -3)
        {
            // const lval
            nodeID = id++;
            tErr++;
            cout << "error @" << lineNo << ": ";
            cout << "const " << varName;
            cout << " cannot be lval" << endl;  
        }
        else
            nodeID = p;         
    }  
    else
        nodeID = id++;
    TreeNode* p;
    // children
    p = child;
    if (p != nullptr) id = p->genNodeId(id);
    p = rsib;
    if (p != nullptr) 
    {
        rsib->parent = parent;
        id = p->genNodeId(id);
    }
    return id;
}

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
    case STMT_COND:
        return "condition";
    case STMT_DECL:
        return "declaration";
    case STMT_IO:
        return "i/o";
    case STMT_LOOP:
        return "loop";
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

/**
 * 寻找正确ID（符号表）
 * 
 * @return int 正确的ID位置
 */
int TreeNode::find(string name)
{
    // new id
    if (parent != nullptr && isLval && 
        parent->nodeType == NODE_STMT &&
        parent->stmtType == STMT_DECL)
        isDecl = true;
    // the same level
    TreeNode* p = lsib;
    while (p != nullptr) {
        // declaration
        if (p->nodeType == NODE_STMT &&
            p->stmtType == STMT_DECL)
        {
            TreeNode* son = p->child;
            while (son != nullptr)
            {
                // variable
                if (son->nodeType == NODE_VAR &&
                    son->varName == name)
                {
                    if (isLval && son->isConst) return -3; 
                    return isDecl ? -2 : son->nodeID;
                }    
                // assign(const, var)
                if (son->nodeType == NODE_STMT &&
                    son->stmtType == STMT_ASS)
                {
                    TreeNode* temp = son->child;
                    while (temp != nullptr)
                    {
                        if (temp->nodeType == NODE_VAR &&
                            temp->varName == name)
                        {
                            if (isLval && temp->isConst) return -3;
                            return isDecl ? -2 : temp->nodeID;
                        }
                        temp = temp->rsib;
                    }
                }
                son = son->rsib;
            }
        }
        // variable
        else if (p->nodeType == NODE_VAR &&
                 p->varName == name)
        {
            if (isLval && p->isConst) return -3;
            return isDecl ? -2 : p->nodeID;
        }
        // params
        else if (p->nodeType == NODE_STMT &&
                 p->stmtType == STMT_PARM)
        {
            TreeNode* son = p->child;
            while (son != nullptr)
            {                
                TreeNode* node = son->child->rsib;
                if (node->varName == name)
                {
                    if (isLval && node->isConst) return -3;
                    return isDecl ? -2 : node->nodeID;
                }
                son = son->rsib;
            }
        }
        // IO
        else if (p->nodeType == NODE_STMT &&
                (p->stmtType == STMT_ASS ||
                 p->stmtType == STMT_IO))
        {
            TreeNode* son = p->child;
            while (son != nullptr)
            {
                if (son->nodeType == NODE_VAR &&
                    son->varName == name)
                {
                    if (isLval && son->isConst) return -3;
                    return isDecl ? -2 : son->nodeID;
                }
                son = son->rsib;
            }
        }          
        p = p->lsib;
    }
    // check higher level
    if (isDecl && !isLv)
    {
        isLv = true;
        return parent->find(name);
    }   
    if (isDecl && isLv) return 0;
    if (parent != nullptr) return parent->find(name);     
    return isDecl ? 0 : -1;
}

void TreeNode::addChild(TreeNode* child)
{
    if (child == nullptr) return;
    if (this->child == nullptr)
        this->child = child;
    else
    {
        TreeNode* p = this->child;
        while (p->rsib != nullptr) { p = p->rsib; }
        p->rsib = child;
        child->lsib = p;
    } 
    child->parent = this;
}

void TreeNode::addSibling(TreeNode* rsib)
{
    if (rsib == nullptr) return;
    if (this->rsib == nullptr) {
        this->rsib = rsib;
        rsib->lsib = this;
    }
    else
    {
        TreeNode* p = this->rsib;
        while (p->rsib != nullptr) { p = p->rsib; }
        p->rsib = rsib;
        rsib->lsib = p;
    }
}

void TreeNode::genCode(ofstream &os)
{
    if (nodeType == NODE_STMT &&
        stmtType == STMT_IO)
    {
        switch (child->type->type)
        {
        case VALUE_CHAR:
            if (child->nodeType == NODE_VAR)
            {
                    
            }
            else if (child->nodeType == NODE_CONST)
            {
                os << "\t# printf\n";
                os << "\tmovl\t$" << (int)child->cval;
                os << ", %eax\n";
                os << "\tpushl\t%eax\n";
                os << "\tpushl\t$_CHAR\n";
                os << "\tcall\tprintf\n";
                os << "\taddl\t$8, %esp\n";
            }
            break;
        case VALUE_INT:
            if (child->nodeType == NODE_VAR)
            {
                    
            }
            else if (child->nodeType == NODE_CONST)
            {
                os << "\t# printf\n";
                os << "\tmovl\t$" << child->ival;
                os << ", %eax\n";
                os << "\tpushl\t%eax\n";
                os << "\tpushl\t$_INT\n";
                os << "\tcall\tprintf\n";
                os << "\taddl\t$8, %esp\n";
            }
            break;
            
        default:
            break;
        }
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_DECL)
    {
        if (isMain)
        {

        }
        else
        {
            TreeNode* p = child;
            while (p != nullptr)
            {
                if (p->nodeType == NODE_STMT &&
                    p->stmtType == STMT_ASS)
                {
                    
                }
                p = p->rsib;
            }
        }
    }
    else if (nodeType == NODE_PROG &&
             child->rsib->varName == "main")
    {
        isMain = true;
        os << "\t.text\n";
        os << "\t.globl\tmain\n";
        os << "\t.type\tmain, @function\n";
        os << "main:\n";
        os << "\tpushl\t%ebp\n";
        os << "\tpushl\t%eax\n";
        os << "\tmovl\t%esp, %ebp\n";
        child->rsib->rsib->genCode(os);
        os << ".END:\n";
        os << "\tmovl\t%ebp, %esp\n";
        os << "\tpopl\t%eax\n";
        os << "\tpopl\t%ebp\n";
        os << "\tmovl\t$0, %eax\n";
        os << "\tret\n";
    }
    else
    {
        if (nodeType == NODE_PROG)
        {
            if (child->rsib->varName == "")
            {
                // start
                os << "\t.section\t.rodata\n";
                os << "_CHAR:\n";
                os << "\t.string\t\"%c\"\n";
                os << "_INT:\n";
                os << "\t.string\t\"%d\"\n";
                os << "_STRING:\n";
                os << "\t.string\t\"%s\"\n";
                isMain = false;
            }
        }
        if (child != nullptr) child->genCode(os);
    }
    // next stmt
    if (rsib != nullptr) rsib->genCode(os);  
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
    p = rsib;
    if (p != nullptr) p->printAST();
}

void TreeNode::printRe()
{
    TreeNode* p;
    p = child;
    if (p != nullptr) p->printRe();
    printNodeInfo();
    printSpecialInfo(); 
    p = rsib;
    if (p != nullptr) p->printRe();
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
            p = p->rsib;
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
            if (cval == '\n')
                cout << "\\n";
            else
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