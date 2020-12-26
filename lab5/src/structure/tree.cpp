#include "iomanip"
#include "tree.h"

extern int tErr;
// 类型检查标记位
bool isDecl, isLv, isLval;
// 代码生成标记位
bool isMain;
/* 符号表：{节点ID： 节点} */
map<int, TreeNode*> id2id;
/* 符号表：{节点ID： 字符串} */
map<int, TreeNode*> id2str;
/* 符号表：{<父亲节点，变量名>: 节点} */
map<pair<TreeNode*, string>, TreeNode*> idt;
// 当前标签标识
int Lson = 0;
int Lcond = 0, Lloop = 0, Ltemp = 0;
stack<int> LC1, LC2, LL1;
stack<TreeNode*> inFunc, noSib;

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
            id2id.insert(make_pair(nodeID, this));
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
        else    // right identifier
            cpFrom(id2id.at(p));      
    }  
    else
        nodeID = id++;
    if (nodeType == NODE_CONST && 
        *(type) == *(TYPE_STRING) &&
        (lsib == nullptr || lsib->nodeType != NODE_VAR))
        id2str.insert(make_pair(nodeID, this));
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
 * @return TreeNode* 正确的节点类型
 */
int TreeNode::find(string name)
{
    // new id
    if (parent != nullptr && 
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

void TreeNode::cpFrom(TreeNode* node)
{
    bval = node->bval;
    cval = node->cval;
    isConst = node->isConst;
    ival = node->ival;
    sval = node->sval;
    nodeID = node->nodeID;
    nodeType = node->nodeType;
    varName = node->varName;
    type = node->type;
}

void TreeNode::genCode(ofstream &os)
{
    if (nodeType == NODE_CONST)
        os << "\tpushl\t" << ival << endl;
    else if (nodeType == NODE_EXPR)
    {
        TreeNode* first = child;
        TreeNode* second = child->rsib;
        if (second == nullptr)
        {
            // unaryExp
            switch (opType)
            {
            case OP_MINS:
                if (first->nodeType == NODE_CONST)
                    os << "\tpushl\t$" << (-1) * first->ival << endl;
                else if (first->nodeType == NODE_VAR)
                {
                    os << "\tmovl\t" << first->varName;
                    os << ", %eax\n";
                    os << "\tmovl\t$-1, %ecx\n";
                    os << "\timull\t%ecx\n";
                    os << "\tpushl\t%eax\n"; 
                } 
                break;
            case OP_NOT:
                if (first->nodeType == NODE_CONST)
                {
                    os << "\tpushl\t$";
                    os << (first->ival == 0 ? 1 : 0) << endl;
                }
                else if (first->nodeType == NODE_VAR)
                {
                    os << "\tmovl\t" << first->varName;
                    os << ", %eax\n";
                    os << "\tcmp\t$0, %eax\n";
                    os << "\tjz\tTEMP_NEXT" << Ltemp << endl;
                    os << "\tpushl\t$0\n";
                    os << "\tjmp\tTEMP_END" << Ltemp << endl;
                    os << "TEMP_NEXT" << Ltemp << ":\n";
                    os << "\tpushl\t$1\n";
                    os << "TEMP_END" << Ltemp << ":\n";
                    Ltemp++;
                } 
                break;
            case OP_PLUS:
                if (first->nodeType == NODE_CONST)
                    os << "\tpushl\t$" << first->ival << endl;
                else if (first->nodeType == NODE_VAR)
                    os << "\tpushl\t" << first->varName << endl; 
                break;
            default:
                break;
            }
            return;
        }
        switch (first->nodeType)
        {
        case NODE_CONST:  
            os << "\tpushl\t$" << first->ival << endl;        
            break;
        case NODE_EXPR:
            first->genCode(os);
            break;
        case NODE_VAR:
            os << "\tpushl\t" << first->varName << endl;  
            break;
        default:
            break;
        }
        switch (second->nodeType)
        {
        case NODE_CONST:  
            os << "\tpushl\t$" << second->ival << endl;        
            break;
        case NODE_EXPR:
            second->genCode(os);
            break;
        case NODE_VAR:
            os << "\tpushl\t" << second->varName << endl;  
            break;
        default:
            break;
        }
        switch (opType)
        {
        case OP_AND:
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t$0, %eax\n";
            os << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t$0, %eax\n";
            os << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$1\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$0\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_DIV:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tmovl\t$0, %edx\n";
            os << "\tidivl\t%ecx\n";               
            os << "\tpushl\t%eax\n";
            break;
        case OP_EQ:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%eax, %ecx\n";
            os << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LA:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%ecx, %eax\n";
            os << "\tjg\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LAE:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%ecx, %eax\n";
            os << "\tjnl\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LE:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%ecx, %eax\n";
            os << "\tjl\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LEE:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%ecx, %eax\n";
            os << "\tjle\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_MINS:         
            os << "\tpopl\t%edx\n";
            os << "\tpopl\t%eax\n";     
            os << "\tsubl\t%edx, %eax\n";
            os << "\tpushl\t%eax\n";
            break;
        case OP_MOD:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tmovl\t$0, %edx\n";
            os << "\tidivl\t%ecx\n";               
            os << "\tpushl\t%edx\n";
            break;
        case OP_MUL:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\timull\t%ecx\n";               
            os << "\tpushl\t%eax\n";
            break;
        case OP_NOTE:
            os << "\tpopl\t%ecx\n";
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t%eax, %ecx\n";
            os << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$1\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$0\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_OR:
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t$0, %eax\n";
            os << "\tjnz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t$0, %eax\n";
            os << "\tjnz\tTEMP_NEXT" << Ltemp << endl;
            os << "\tpushl\t$0\n";
            os << "\tjmp\tTEMP_END" << Ltemp << endl;
            os << "TEMP_NEXT" << Ltemp << ":\n";
            os << "\tpushl\t$1\n";
            os << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_PLUS:
            os << "\tpopl\t%edx\n";
            os << "\tpopl\t%eax\n";     
            os << "\taddl\t%edx, %eax\n";
            os << "\tpushl\t%eax\n";
            break;
        default:
            break;
        }
        return;
    }
    else if (nodeType == NODE_KEY)
    {
        if (varName == "break")
            os << "\tjmp\tLOOP" << LL1.top() << "_END\n";
        else if (varName == "continue")
            os << "\tjmp\tLOOP" << LL1.top() << "_BGN\n";
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
        TreeNode* params = child->rsib->rsib;
        if (params != nullptr)
        { 
            if (params->stmtType == STMT_PARM &&
                params->rsib != nullptr) 
                params->rsib->genCode(os);
            else
                params->genCode(os);
        }            
        os << ".END:\n";
        os << "\tmovl\t%ebp, %esp\n";
        os << "\tpopl\t%eax\n";
        os << "\tpopl\t%ebp\n";
        os << "\tmovl\t$0, %eax\n";
        os << "\tret\n";
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_ASS)
    {
        TreeNode* val = child->rsib;
        switch (val->nodeType)
        {
        case NODE_CONST:
            if (*(val->type) == *(TYPE_STRING))
                os << "\tpushl\t_STR_" << val->nodeID << endl;
            else
                os << "\tpushl\t$" << val->ival << endl;
            break;
        case NODE_EXPR:
            val->genCode(os);
            break;
        case NODE_VAR:
            os << "\tpushl\t" << val->varName << endl;
            break;
        default:
            break;
        }
        switch (opType)
        {
        case OP_ASS:
            os << "\tpopl\t" << child->varName << endl;
            break;
        case OP_DIVE:
            os << "\tpopl\t%ecx\n";
            os << "\tmovl\t" << child->varName;
            os << ", %eax\n";
            os << "\tmovl\t$0, %edx\n";
            os << "\tidivl\t%ecx\n";
            os << "\tmovl\t%eax, " << child->varName << endl;
            break;
        case OP_MINE:
            os << "\tpopl\t%eax\n";
            os << "\tsubl\t%eax, " << child->varName << endl;
            break;
        case OP_MODE:
            os << "\tpopl\t%ecx\n";
            os << "\tmovl\t" << child->varName;
            os << ", %eax\n";
            os << "\tmovl\t$0, %edx\n";
            os << "\tidivl\t%ecx\n";
            os << "\tmovl\t%edx, " << child->varName << endl;
            break;
        case OP_MULE:
            os << "\tpopl\t%ecx\n";
            os << "\tmovl\t" << child->varName;
            os << ", %eax\n";
            os << "\tmovl\t$0, %edx\n";
            os << "\timull\t%ecx\n";
            os << "\tmovl\t%eax, " << child->varName << endl;
            break;
        case OP_PLUE:
            os << "\tpopl\t%eax\n";
            os << "\taddl\t%eax, " << child->varName << endl;
            break;
        default:
            break;
        }
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_COND)
    {
        if (child->nodeType == NODE_KEY &&
            child->rsib->rsib == nullptr)
        {
            // else
            TreeNode* stmt = child->rsib;
            stmt->genCode(os);
            os << "COND" << LC1.top() << "_END:\n";
            LC1.pop();
            Lson = LC2.top(), LC2.pop();
            return;
        }   
        TreeNode* cond, * stmt, * rest;    
        if (child->nodeType == NODE_KEY)
        {
            // else if
            cond = child->rsib;
            stmt = cond->rsib;
            rest = stmt->rsib;
            Lson = LC2.top() + 1;
        }
        else 
        {
            // new if
            LC1.push(Lcond), Lcond++;
            LC2.push(Lson), Lson = 0;
            cond = child;
            stmt = child->rsib;
            rest = stmt->rsib;
        }
        noSib.push(stmt);
        cond->genCode(os);
        noSib.pop();
        os << "\tpopl\t%eax\n";
        os << "\tcmp\t$0, %eax\n";
        if (rest != nullptr)
        {
            // (else) if (cond) stmt rest
            os << "\tjz\tCOND" << LC1.top() << "_";
            os << Lson << endl;
            noSib.push(rest);
            stmt->genCode(os);
            noSib.pop();   
            os << "\tjmp\tCOND" << LC1.top() << "_END\n";
            os << "COND" << LC1.top() << "_";
            os << Lson << ":\n";
            rest->genCode(os);
        }
        else
        {
            // (else) if (cond) stmt
            os << "\tjz\tCOND" << LC1.top() << "_END\n";
            stmt->genCode(os);
            os << "COND" << LC1.top() << "_END:\n";
            LC1.pop();
            Lson = LC2.top(), LC2.pop();
        } 
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_DECL)
    {
        if (isMain)
        {
            // 局部
        }
        else    // 全局
        {
            TreeNode* p = child;
            while (p != nullptr)
            {
                if (p->nodeType == NODE_VAR)
                {
                    os << "\t.bss\n";
                    os << "\t.comm\t" << p->varName;
                    switch (p->type->type)
                    {
                    case VALUE_CHAR:
                        os << ",1,1\n";    
                        break;
                    case VALUE_INT:
                        os << ",4,4\n";
                        break;
                    case VALUE_STRING:
                        os << ",8,8\n";
                        break;
                    default:
                        break;
                    }
                }
                else if (p->nodeType == NODE_STMT &&
                         p->stmtType == STMT_ASS)
                {
                    TreeNode* tid = p->child;
                    os << "\t.globl\t" << tid->varName << endl;
                    if (child->varName == "const")
                        os << "\t.section\t.rodata\n"; 
                    else
                        os << "\t.data\n";                       
                    if (*(tid->type) == *(TYPE_INT))
                        os << "\t.align\t4\n";
                    else if (*(tid->type) == *(TYPE_STRING))
                        os << "\t.align\t8\n";                 
                    os << "\t.type\t" << tid->varName;
                    os << ", @object\n";
                    os << "\t.size\t" << tid->varName;
                    switch (tid->type->type)
                    {
                    case VALUE_CHAR:
                        os << ", 1\n";
                        break;
                    case VALUE_INT:
                        os << ", 4\n";
                        break;
                    case VALUE_STRING:
                        os << ", 8\n";
                        break;
                    default:
                        break;
                    }
                    os << tid->varName << ":\n";
                    tid = tid->rsib;
                    if (tid->nodeType == NODE_CONST)
                    {
                        switch (tid->type->type)
                        {
                        case VALUE_CHAR:
                            os << "\t.byte\t" << (int)tid->cval << endl;
                            break;
                        case VALUE_INT:
                            os << "\t.long\t" << tid->ival << endl;
                            break;
                        case VALUE_STRING:
                            os << "\t.string\t\"" << tid->sval << "\"\n";
                            break;
                        default:
                            break;
                        }
                    }
                    else    // EXP
                    {

                    }
                }
                p = p->rsib;
            }
        }
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_IO)
    {
        switch (child->type->type)
        {
        case VALUE_CHAR:
            if (child->nodeType == NODE_VAR)
            {
                if (varName == "input")
                {
                    os << "\t# scanf\n";
                    os << "\tpushl\t$" << child->varName << endl;
                    os << "\tpushl\t$_CHAR\n";
                    os << "\tcall\tscanf\n";
                    os << "\taddl\t$8, %esp\n";
                }   
                else
                {
                    os << "\t# printf\n";
                    os << "\tmovl\t" << child->varName;
                    os << ", %eax\n";
                    os << "\tpushl\t%eax\n";
                    os << "\tpushl\t$_CHAR\n";
                    os << "\tcall\tprintf\n";
                    os << "\taddl\t$8, %esp\n";
                }   
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
                if (varName == "input")
                {
                    os << "\t# scanf\n";
                    os << "\tpushl\t$" << child->varName << endl;
                    os << "\tpushl\t$_INT\n";
                    os << "\tcall\tscanf\n";
                    os << "\taddl\t$8, %esp\n";
                }   
                else
                {
                    os << "\t# printf\n";
                    os << "\tmovl\t" << child->varName;
                    os << ", %eax\n";
                    os << "\tpushl\t%eax\n";
                    os << "\tpushl\t$_INT\n";
                    os << "\tcall\tprintf\n";
                    os << "\taddl\t$8, %esp\n";
                }  
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
            else if (child->nodeType == NODE_EXPR)
            {
                child->genCode(os);
                os << "\t# printf\n";
                os << "\tpushl\t$_INT\n";
                os << "\tcall\tprintf\n";
                os << "\taddl\t$8, %esp\n";
            }
            break; 
        case VALUE_STRING:
            if (child->nodeType == NODE_CONST)
            {
                os << "\t# printf\n";
                os << "\tpushl\t$_STR_" << child->nodeID << endl;
                os << "\tpushl\t$_STRING\n";
                os << "\tcall\tprintf\n";
                os << "\taddl\t$8, %esp\n";
            }   
            else if (child->nodeType == NODE_VAR)
            {
                if (varName == "input")
                {
                    os << "\t# scanf\n";
                    os << "\tpushl\t$" << child->varName << endl;
                    os << "\tpushl\t$_STRING\n";
                    os << "\tcall\tscanf\n";
                    os << "\taddl\t$8, %esp\n";
                }
                else
                {
                    os << "\t# printf\n";
                    os << "\tpushl\t$" << child->varName << endl;
                    os << "\tpushl\t$_STRING\n";
                    os << "\tcall\tprintf\n";
                    os << "\taddl\t$8, %esp\n";
                }
            }       
        default:
            break;
        }
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_LOOP)
    {
        LL1.push(Lloop), Lloop++;
        if (child->varName == "while")
        {
            os << "LOOP" << LL1.top() << "_BGN:\n";   
            TreeNode* cond = child->rsib;
            TreeNode* stmt = cond->rsib;
            noSib.push(stmt);
            cond->genCode(os);
            noSib.pop();
            os << "\tpopl\t%eax\n";
            os << "\tcmp\t$0, %eax\n";
            os << "\tjz\tLOOP" << LL1.top() << "_END\n";
            stmt->genCode(os);
        }
        else if (child->varName == "for")
        {
            TreeNode* forhead = child->rsib;
            TreeNode* formid = forhead->rsib;
            TreeNode* forend = formid->rsib; 
            TreeNode* stmt = forend->rsib;
            if (forhead->nodeType != NODE_KEY)
            {
                noSib.push(formid);
                forhead->genCode(os);
                noSib.pop();
            }
            os << "LOOP" << LL1.top() << "_BGN:\n";
            if (formid->nodeType != NODE_KEY)
            {
                noSib.push(forend);
                formid->genCode(os);
                noSib.pop();
                os << "\tpopl\t%eax\n";
                os << "\tcmp\t$0, %eax\n";
                os << "\tjz\tLOOP" << LL1.top() << "_END\n";
            }
            stmt->genCode(os);
            if (forend->nodeType != NODE_KEY)
            {
                noSib.push(stmt);
                forend->genCode(os);
                noSib.pop();
            }
        }
        os << "\tjmp\tLOOP" << LL1.top() << "_BGN\n";
        os << "LOOP" << LL1.top() << "_END:\n";
        LL1.pop();
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_RET)
    {
        
    }
    else if (nodeType == NODE_VAR)
        os << "\tpushl\t" << varName << endl;
    else
    {
        if (child != nullptr) child->genCode(os);
    }
    // next stmt
    if (rsib != nullptr &&
        (noSib.empty() || rsib != noSib.top())) 
        rsib->genCode(os);
}

void TreeNode::genStr(ofstream &os)
{
    os << "\t.text\n";
    os << "\t.section\t.rodata\n";
    os << "_CHAR:\n";
    os << "\t.string\t\"%c\"\n";
    os << "_INT:\n";
    os << "\t.string\t\"%d\"\n";
    os << "_STRING:\n";
    os << "\t.string\t\"%s\"\n";
    for (auto &it : id2str)
    {
        TreeNode* node = it.second;
        os << "_STR_" << node->nodeID << ":\n";
        os << "\t.string\t\"" << node->sval << "\"" << endl;
    }
    isMain = false;
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
        if (stmtType == STMT_IO)
            cout << varName;
        else
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