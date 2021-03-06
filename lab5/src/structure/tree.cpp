#include "iomanip"
#include "tree.h"

extern int tErr;
// 类型检查标记位
bool isDecl, isFunc, isLv, isLval;
// 代码生成标记位
bool isMain = false, isRet = true;

int param = 0;
/* 符号表：{节点ID： 节点} */
map<int, TreeNode*> id2id;
int offset = 0, tempoff = 0;
/* 局部变量：{节点ID： offset} */
map<int, int> id2off;
stack<int> ids;
/* 字符串：{节点ID： 字符串} */
map<int, TreeNode*> id2str;
/* 符号表：{<父亲节点，变量名>: 节点} (已废弃)*/
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
        if (parent->nodeType == NODE_PARM)
        {
            // param
            nodeID = id++;
            pair<TreeNode*, string> 
            p = make_pair(parent, varName);
            idt.insert(make_pair(p, this)); 
            id2id.insert(make_pair(nodeID, this));
        }
        else
        {
            isDecl = false, isLv = false;
            if (parent != nullptr)
            {
                if (parent->nodeType == NODE_STMT &&
                    parent->stmtType == STMT_ASS &&
                    parent->child == this)
                {
                    isLval = true;
                    isFunc = false;
                }   
                else if (parent->nodeType == NODE_PROG)
                {
                    isLval = false;
                    isFunc = true;
                }
                else
                {
                    isLval = false;
                    isFunc = false;
                }   
            }
            else
            {
                isLval = false;
                isFunc = false;
            }
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
                if (isFunc)
                {
                    nodeID = id++;
                    pair<TreeNode*, string> 
                    p = make_pair(parent, varName);
                    idt.insert(make_pair(p, this)); 
                    id2id.insert(make_pair(nodeID, this));
                }
                else
                {
                    nodeID = id++;
                    tErr++;
                    cout << "error @" << lineNo << ": ";
                    cout << "identifier " << varName;
                    cout << " not declared" << endl; 
                }        
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
    if (nodeType == NODE_VAR && child != nullptr) 
        type->isArray = true;
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
    case NODE_FUNC:
        return "function";
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
    {
        TreeNode* p = parent->child;
        while (p != nullptr)
        {
            if (p->nodeType == NODE_VAR &&
                p->varName == name)
                isDecl = true;
            else if (p->nodeType == NODE_STMT &&
                  p->stmtType == STMT_ASS &&
                  p->child->varName == name)
                  isDecl = true;
            p = p->rsib;
        }
    }
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
            if (!isDecl) return p->nodeID;
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
                    if (!isDecl) return node->nodeID;
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
                    if (!isDecl) return son->nodeID;
                }
                son = son->rsib;
            }
        }   
        // PROG
        else if (p->nodeType == NODE_PROG &&
                 p->nodeID != 0)
        {
            if (p->child->rsib->varName == name)
                return p->child->rsib->nodeID;
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
    type->type = node->type->type;
}

void TreeNode::genCode()
{
    if (nodeType == NODE_CONST)
        cout << "\tpushl\t$" << ival << endl;
    else if (nodeType == NODE_EXPR)
    {
        TreeNode* first = child;
        TreeNode* second = child->rsib;
        switch (first->nodeType)
        {
        case NODE_CONST:  
            cout << "\tpushl\t$" << first->ival << endl;        
            break;
        case NODE_EXPR:
            first->genCode();
            break;
        case NODE_FUNC:
            if (first->rsib != nullptr) noSib.push(first->rsib);
            first->genCode();
            noSib.pop();
            cout << "\tpushl\t%eax\n";
            break;
        case NODE_VAR:
            if (id2off.find(first->nodeID) != id2off.end())
            { 
                int t = id2off.find(first->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp), %eax\n";
                cout << "\tpushl\t%eax\n";
            }
            else
                cout << "\tpushl\t" << first->varName << endl;  
            break;
        default:
            break;
        }
        if (second == nullptr)
        {
            // unaryExp
            switch (opType)
            {
            case OP_MINS:
                cout << "\tpopl\t%eax\n";
                cout << "\tmovl\t$-1, %ecx\n";
                cout << "\timull\t%ecx\n";
                cout << "\tpushl\t%eax\n"; 
                break;
            case OP_NOT:
                cout << "\tpopl\t%eax\n";
                cout << "\tcmp\t$0, %eax\n";
                cout << "\tjz\tTEMP_NEXT" << Ltemp << endl;
                cout << "\tpushl\t$0\n";
                cout << "\tjmp\tTEMP_END" << Ltemp << endl;
                cout << "TEMP_NEXT" << Ltemp << ":\n";
                cout << "\tpushl\t$1\n";
                cout << "TEMP_END" << Ltemp << ":\n";
                Ltemp++;
                break;
            default:
                break;
            }
            return;
        }
        
        switch (second->nodeType)
        {
        case NODE_CONST:  
            cout << "\tpushl\t$" << second->ival << endl;        
            break;
        case NODE_EXPR:
            second->genCode();
            break;
        case NODE_FUNC:
            second->genCode();
            cout << "\tpushl\t%eax\n";
            break;
        case NODE_VAR:
            if (id2off.find(second->nodeID) != id2off.end())
            { 
                int t = id2off.find(second->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp), %eax\n";
                cout << "\tpushl\t%eax\n";
            }
            else
                cout << "\tpushl\t" << second->varName << endl;  
            break;
        default:
            break;
        }
        switch (opType)
        {
        case OP_AND:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t$0, %eax\n";
            cout << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tcmp\t$0, %ecx\n";
            cout << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$1\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$0\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_DIV:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcltd\n";
            cout << "\tidivl\t%ecx\n";               
            cout << "\tpushl\t%eax\n";
            break;
        case OP_EQ:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%eax, %ecx\n";
            cout << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LA:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%ecx, %eax\n";
            cout << "\tjg\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LAE:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%ecx, %eax\n";
            cout << "\tjnl\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LE:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%ecx, %eax\n";
            cout << "\tjl\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_LEE:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%ecx, %eax\n";
            cout << "\tjle\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_MINS:         
            cout << "\tpopl\t%edx\n";
            cout << "\tpopl\t%eax\n";     
            cout << "\tsubl\t%edx, %eax\n";
            cout << "\tpushl\t%eax\n";
            break;
        case OP_MOD:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcltd\n";
            cout << "\tidivl\t%ecx\n";               
            cout << "\tpushl\t%edx\n";
            break;
        case OP_MUL:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcltd\n";
            cout << "\timull\t%ecx\n";               
            cout << "\tpushl\t%eax\n";
            break;
        case OP_NOTE:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t%eax, %ecx\n";
            cout << "\tjz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$1\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$0\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_OR:
            cout << "\tpopl\t%ecx\n";
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t$0, %eax\n";
            cout << "\tjnz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tcmp\t$0, %ecx\n";
            cout << "\tjnz\tTEMP_NEXT" << Ltemp << endl;
            cout << "\tpushl\t$0\n";
            cout << "\tjmp\tTEMP_END" << Ltemp << endl;
            cout << "TEMP_NEXT" << Ltemp << ":\n";
            cout << "\tpushl\t$1\n";
            cout << "TEMP_END" << Ltemp << ":\n";
            Ltemp++;
            break;
        case OP_PLUS:
            cout << "\tpopl\t%edx\n";
            cout << "\tpopl\t%eax\n";     
            cout << "\taddl\t%edx, %eax\n";
            cout << "\tpushl\t%eax\n";
            break;
        default:
            break;
        }
        return;
    }
    else if (nodeType == NODE_FUNC)
    {
        TreeNode* params = child->rsib;
        int toff = 0;
        if (params != nullptr) 
        {
            params = params->child;
            while (params->rsib != nullptr) { params = params->rsib; }
            while (params != nullptr)
            {
                switch (params->nodeType)
                {
                case NODE_CONST:
                    cout << "\tpushl\t$" << params->ival << endl;
                    break;
                case NODE_EXPR:
                    params->genCode();
                    break;
                case NODE_FUNC:
                    params->genCode();
                    cout << "\tpushl\t%eax\n";
                    break;
                case NODE_VAR:
                    if (id2off.find(params->nodeID) != id2off.end())
                    {
                        int t = id2off.find(params->nodeID)->second;
                        cout << "\tpushl\t" << (-1) * t;
                        cout << "(%ebp)\n";
                    }
                    else
                        cout << "\tpushl\t" << params->varName << endl;
                    break;
                default:
                    break;
                }
                params = params->lsib;
                toff += 4;
            }
        }
        cout << "\tcall\t" << child->varName << endl;
        if (toff != 0)
            cout << "\taddl\t$" << toff << ", %esp\n";
    }
    else if (nodeType == NODE_KEY)
    {
        if (varName == "break")
            cout << "\tjmp\tLOOP" << LL1.top() << "_END\n";
        else if (varName == "continue")
            cout << "\tjmp\tLOOP" << LL1.top() << "_COND\n";
    }
    else if (nodeType == NODE_PROG &&
             nodeID != 0)
    {
        inFunc.push(this);
        isRet = false;
        cout << "\t.text\n";
        cout << "\t.globl\t" << child->rsib->varName << endl;
        cout << "\t.type\t" << child->rsib->varName;
        cout << ", @function\n";
        cout << child->rsib->varName << ":\n";
        if (child->rsib->varName == "main") isMain = true; 
        else isFunc = true, tempoff = 0;
        cout << "\tpushl\t%ebp\n";
        cout << "\tmovl\t%esp, %ebp\n";
        param -= 4;    // ebp offset
        TreeNode* params = child->rsib->rsib;
        if (params != nullptr)
        { 
            params->genCode();
            if (params->stmtType == STMT_PARM &&
                params->rsib != nullptr)            
                params->rsib->genCode(); 
            
        }           
        inFunc.pop();
        if (!isRet) // 手动退出
        {
            if (child->rsib->varName == "main") cout << ".END:\n";
                cout << "\tmovl\t%ebp, %esp\n";
                cout << "\tpopl\t%ebp\n";
                cout << "\tmovl\t$0, %eax\n";             
                cout << "\tret\n";
        }
        param = 0;
        isFunc = false;
        offset -= tempoff, tempoff = 0;
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_ASS)
    {
        TreeNode* val = child->rsib;
        switch (val->nodeType)
        {
        case NODE_CONST:
            if (*(val->type) == *(TYPE_STRING))
                cout << "\tpushl\t_STR_" << val->nodeID << endl;
            else if (val->type->type == VALUE_CHAR)
                cout << "\tmovb\t$" << val->ival;
            else
                cout << "\tpushl\t$" << val->ival << endl;
            break;
        case NODE_EXPR:
            val->genCode();
            break;
        case NODE_FUNC:
            val->genCode();
            cout << "\tpushl\t%eax\n";
            break;
        case NODE_VAR:
            if (id2off.find(val->nodeID) != id2off.end())
            { 
                int t = id2off.find(val->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp), %eax\n";
                cout << "\tpushl\t%eax\n";
            }
            else
                cout << "\tpushl\t" << val->varName << endl;
            break;
        default:
            break;
        }
        switch (opType)
        {
        case OP_ASS:
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                if (type->type == VALUE_CHAR)
                    cout << ", ";
                else
                {
                    cout << "\tpopl\t%eax\n";
                    cout << "\tmovl\t%eax, ";
                }    
                cout << (-1) * t;
                cout << "(%ebp)\n";         
            }
            else
            {
                if (child->type->isArray)
                {
                    child->child->genCode();
                    cout << "\tlea\t";
                    cout << child->varName;
                    cout << ", %ebx\n";
                    cout << "\tpopl\t%eax\n";
                    cout << "\tmovl\t$4, %ecx\n";
                    cout << "\timull\t%ecx\n";
                    cout << "\tsubl\t%eax, %ebx\n";
                    cout << "\tpopl\t0(%ebx)\n";
                }
                else if (child->type->type == VALUE_CHAR)
                    cout << ", " << child->varName << endl;
                else
                    cout << "\tpopl\t" << child->varName << endl;          
            }
            break;
        case OP_DIVE:
            cout << "\tpopl\t%ecx\n";
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp)";
            }
            else
                cout << "\tmovl\t" << child->varName;
            cout << ", %eax\n";
            cout << "\tmovl\t$0, %edx\n";
            cout << "\tidivl\t%ecx\n";
            cout << "\tmovl\t%eax, " << child->varName << endl;
            break;
        case OP_MINE:
            cout << "\tpopl\t%eax\n";
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                cout << "\tsubl\t%eax, " << (-1) * t;
                cout << "(%ebp)\n";
            }
            else
                cout << "\tsubl\t%eax, " << child->varName << endl;
            break;
        case OP_MODE:
            cout << "\tpopl\t%ecx\n";
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp)";               
            }
            else
                cout << "\tmovl\t" << child->varName;
            cout << ", %eax\n";
            cout << "\tmovl\t$0, %edx\n";
            cout << "\tidivl\t%ecx\n";
            cout << "\tmovl\t%edx, " << child->varName << endl;
            break;
        case OP_MULE:
            cout << "\tpopl\t%ecx\n";
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                cout << "\tmovl\t" << (-1) * t;
                cout << "(%ebp)";               
            }
            else
                cout << "\tmovl\t" << child->varName;
            cout << ", %eax\n";
            cout << "\tmovl\t$0, %edx\n";
            cout << "\timull\t%ecx\n";
            cout << "\tmovl\t%eax, " << child->varName << endl;
            break;
        case OP_PLUE:
            cout << "\tpopl\t%eax\n";
            if (id2off.find(child->nodeID) != id2off.end())
            { 
                int t = id2off.find(child->nodeID)->second;
                cout << "\taddl\t%eax, " << (-1) * t;
                cout << "(%ebp)\n";  
            }
            else
                cout << "\taddl\t%eax, " << child->varName << endl;
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
            stmt->genCode();
            cout << "COND" << LC1.top() << "_END:\n";
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
        cond->genCode();
        noSib.pop();
        cout << "\tpopl\t%eax\n";
        cout << "\tcmp\t$0, %eax\n";
        if (rest != nullptr)
        {
            // (else) if (cond) stmt rest
            cout << "\tjz\tCOND" << LC1.top() << "_";
            cout << Lson << endl;
            noSib.push(rest);
            stmt->genCode();
            noSib.pop();   
            cout << "\tjmp\tCOND" << LC1.top() << "_END\n";
            cout << "COND" << LC1.top() << "_";
            cout << Lson << ":\n";
            rest->genCode();
        }
        else
        {
            // (else) if (cond) stmt
            cout << "\tjz\tCOND" << LC1.top() << "_END\n";
            stmt->genCode();
            cout << "COND" << LC1.top() << "_END:\n";
            LC1.pop();
            Lson = LC2.top(), LC2.pop();
        } 
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_DECL)
    {
        if (isMain || isFunc)
        {
            // 局部
            TreeNode* p = child;
            while (p != nullptr)
            {
                if (p->nodeType == NODE_VAR)
                {
                    switch (p->type->type)
                    {
                    case VALUE_CHAR:
                        offset++;
                        if (isFunc) tempoff++;
                        cout << "\tsubl\t$1, %esp\n";
                        break;
                    case VALUE_INT:
                        offset += 4;
                        if (isFunc) tempoff += 4;
                        cout << "\tsubl\t$4, %esp\n";
                        break;
                    case VALUE_STRING:
                        offset += 8;
                        if (isFunc) tempoff += 8;
                        cout << "\tsubl\t$8, %esp\n";
                        break;
                    default:
                        break;
                    }
                    id2off.insert(make_pair(p->nodeID, offset));
                    ids.push(p->nodeID);
                }
                else if (p->nodeType == NODE_STMT && 
                         p->stmtType == STMT_ASS)
                {
                    TreeNode* tid = p->child;
                    tid->rsib->genCode();
                    if (tid->rsib->nodeType != NODE_FUNC)
                        cout << "\tpopl\t%eax\n";
                    switch (tid->type->type)
                    {
                    case VALUE_CHAR:
                        offset++;
                        if (isFunc) tempoff++;
                        cout << "\tsubl\t$1, %esp\n";
                        break;
                    case VALUE_INT:
                        offset += 4;
                        if (isFunc) tempoff += 4;
                        cout << "\tsubl\t$4, %esp\n";
                        break;
                    case VALUE_STRING:
                        offset += 8;
                        if (isFunc) tempoff += 8;
                        cout << "\tsubl\t$8, %esp\n";
                        break;
                    default:
                        break;
                    }
                    cout << "\tmovl\t%eax, ";
                    cout << (-1) * offset << "(%ebp)\n";
                    id2off.insert(make_pair(tid->nodeID, offset));
                    ids.push(tid->nodeID);
                }
                p = p->rsib;
            }
        }
        else    // 全局
        {
            TreeNode* p = child;
            while (p != nullptr)
            {
                if (p->nodeType == NODE_VAR)
                {
                    cout << "\t.bss\n";
                    cout << "\t.comm\t" << p->varName;
                    switch (p->type->type)
                    {
                    case VALUE_CHAR:
                        cout << ",1,1\n";    
                        break;
                    case VALUE_INT:
                        if (p->type->isArray)
                        {
                            cout << "," << 4 * p->type->size;
                            cout << ",32\n";
                        }
                        else cout << ",4,4\n";
                        break;
                    case VALUE_STRING:
                        cout << ",8,8\n";
                        break;
                    default:
                        break;
                    }
                }
                else if (p->nodeType == NODE_STMT &&
                         p->stmtType == STMT_ASS)
                {
                    TreeNode* tid = p->child;
                    cout << "\t.globl\t" << tid->varName << endl;
                    if (child->varName == "const")
                        cout << "\t.section\t.rodata\n"; 
                    else
                        cout << "\t.data\n";   
                    if (tid->type->isArray)
                        cout << "\t/align\t32\n";
                    else if (*(tid->type) == *(TYPE_INT))
                        cout << "\t.align\t4\n";
                    else if (*(tid->type) == *(TYPE_STRING))
                        cout << "\t.align\t8\n";                 
                    cout << "\t.type\t" << tid->varName;
                    cout << ", @object\n";
                    cout << "\t.size\t" << tid->varName;
                    switch (tid->type->type)
                    {
                    case VALUE_CHAR:
                        cout << ", 1\n";
                        break;
                    case VALUE_INT:
                        if (tid->type->isArray) 
                            cout << ", " << 4 * tid->type->size << "\n";
                        else cout << ", 4\n";
                        break;
                    case VALUE_STRING:
                        cout << ", 8\n";
                        break;
                    default:
                        break;
                    }
                    cout << tid->varName << ":\n";
                    tid = tid->rsib;
                    if (tid->nodeType == NODE_CONST)
                    {
                        switch (tid->type->type)
                        {
                        case VALUE_CHAR:
                            cout << "\t.byte\t" << (int)tid->cval << endl;
                            break;
                        case VALUE_INT:
                            cout << "\t.long\t" << tid->ival << endl;
                            break;
                        case VALUE_STRING:
                            cout << "\t.string\t\"" << tid->sval << "\"\n";
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
        if (child->nodeType == NODE_FUNC)
        {
            child->genCode();
            cout << "\t# printf\n";
            cout << "\tpushl\t%eax\n";
            cout << "\tpushl\t$_INT\n";
            cout << "\tcall\tprintf\n";
            cout << "\taddl\t$8, %esp\n";
        }
        else
        {
            switch (child->type->type)
            {
            case VALUE_CHAR:
                if (child->nodeType == NODE_VAR)
                {
                    if (varName == "input")
                    {
                        cout << "\t# scanf\n";
                        if (id2off.find(child->nodeID) != id2off.end())
                        {
                            int t = id2off.find(child->nodeID)->second;
                            cout << "\tmovb\t" << (-1) * t;                      
                            cout << "(%ebp), %al\n";
                            cout << "\tpushl\t%eax\n";
                        }
                        else
                            cout << "\tpushl\t$" << child->varName << endl;
                        cout << "\tpushl\t$_CHAR\n";
                        cout << "\tcall\tscanf\n";
                        cout << "\taddl\t$5, %esp\n";
                    }   
                    else
                    {
                        cout << "\t# printf\n";
                        if (id2off.find(child->nodeID) != id2off.end())
                        {
                            int t = id2off.find(child->nodeID)->second;
                            cout << "\tmovb\t" << (-1) * t;
                            cout << "(%ebp)";
                        }
                        else
                            cout << "\tmovb\t" << child->varName;
                        cout << ", %al\n";
                        cout << "\tpushl\t%eax\n";
                        cout << "\tpushl\t$_CHAR\n";
                        cout << "\tcall\tprintf\n";
                        cout << "\taddl\t$5, %esp\n";
                    }   
                }
                else if (child->nodeType == NODE_CONST)
                {
                    cout << "\t# printf\n";
                    cout << "\tmovl\t$" << (int)child->cval;
                    cout << ", %eax\n";
                    cout << "\tpushl\t%eax\n";
                    cout << "\tpushl\t$_CHAR\n";
                    cout << "\tcall\tprintf\n";
                    cout << "\taddl\t$8, %esp\n";
                }
                break;
            case VALUE_INT:
                if (child->nodeType == NODE_VAR)
                {
                    if (varName == "input")
                    {
                        cout << "\t# scanf\n";
                        if (id2off.find(child->nodeID) != id2off.end())
                        {
                            int t = id2off.find(child->nodeID)->second;
                            cout << "\tlea\t";
                            cout << (-1) * t << "(%ebp), %ebx\n";
                            cout << "\tpushl\t%ebx\n";
                            cout << "\tpushl\t$_INT\n";
                            cout << "\tcall\tscanf\n";
                            cout << "\taddl\t$8, %esp\n";                            
                        }
                        else
                        {
                            cout << "\tpushl\t$" << child->varName << endl;
                            cout << "\tpushl\t$_INT\n";
                            cout << "\tcall\tscanf\n";
                            cout << "\taddl\t$8, %esp\n";
                        }
                    }   
                    else
                    {
                        cout << "\t# printf\n";
                        if (child->type->isArray && 
                            child->child != nullptr)
                        {
                            cout << "\tlea\t";
                            cout << child->varName;
                            cout << ", %ebx\n";
                            child->child->genCode();
                            cout << "\tpopl\t%eax\n";
                            cout << "\tmovl\t$4, %ecx\n";
                            cout << "\timull\t%ecx\n";
                            cout << "\tsubl\t%eax, %ebx\n";
                            cout << "\tpushl\t0(%ebx)\n";
                            cout << "\tpushl\t$_INT\n";
                            cout << "\tcall\tprintf\n";
                            cout << "\taddl\t$8, %esp\n";
                        }
                        else
                        {
                            if (id2off.find(child->nodeID) != id2off.end())
                            {
                                int t = id2off.find(child->nodeID)->second;
                                cout << "\tmovl\t" << (-1) * t;
                                cout << "(%ebp)";                 
                            }
                            else
                                cout << "\tmovl\t" << child->varName;
                            cout << ", %eax\n";
                            cout << "\tpushl\t%eax\n";
                            cout << "\tpushl\t$_INT\n";
                            cout << "\tcall\tprintf\n";
                            cout << "\taddl\t$8, %esp\n";
                        }
                    }  
                }
                else if (child->nodeType == NODE_CONST)
                {
                    cout << "\t# printf\n";
                    cout << "\tmovl\t$" << child->ival;
                    cout << ", %eax\n";
                    cout << "\tpushl\t%eax\n";
                    cout << "\tpushl\t$_INT\n";
                    cout << "\tcall\tprintf\n";
                    cout << "\taddl\t$8, %esp\n";
                }
                else if (child->nodeType == NODE_EXPR)
                {
                    child->genCode();
                    cout << "\t# printf\n";
                    cout << "\tpushl\t$_INT\n";
                    cout << "\tcall\tprintf\n";
                    cout << "\taddl\t$8, %esp\n";
                }
                break; 
            case VALUE_STRING:
                if (child->nodeType == NODE_CONST)
                {
                    cout << "\t# printf\n";
                    cout << "\tpushl\t$_STR_" << child->nodeID << endl;
                    cout << "\tpushl\t$_STRING\n";
                    cout << "\tcall\tprintf\n";
                    cout << "\taddl\t$8, %esp\n";
                }   
                else if (child->nodeType == NODE_VAR)
                {
                    if (varName == "input")
                    {
                        cout << "\t# scanf\n";
                        if (id2off.find(child->nodeID) != id2off.end())
                        {
                            int t = id2off.find(child->nodeID)->second;
                            cout << "\tmovl\t" << (-1) * t;
                            cout << "(%ebp), %eax\n";
                            cout << "\tpushl\t%eax\n";
                        }
                        else
                            cout << "\tpushl\t$" << child->varName << endl;
                        cout << "\tpushl\t$_STRING\n";
                        cout << "\tcall\tscanf\n";
                        cout << "\taddl\t$8, %esp\n";
                    }
                    else
                    {
                        cout << "\t# printf\n";
                        if (id2off.find(child->nodeID) != id2off.end())
                        {
                            int t = id2off.find(child->nodeID)->second;
                            cout << "\tmovl\t" << (-1) * t; 
                            cout << "(%ebp), %eax\n";
                            cout << "\tpushl\t%eax\n";
                        }
                        else
                            cout << "\tpushl\t$" << child->varName << endl;
                        cout << "\tpushl\t$_STRING\n";
                        cout << "\tcall\tprintf\n";
                        cout << "\taddl\t$8, %esp\n";
                    }
                }       
            default:
                break;
            }
        }
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_LOOP)
    {
        LL1.push(Lloop), Lloop++;
        if (child->varName == "while")
        {
            cout << "LOOP" << LL1.top() << "_BGN:\n";   
            TreeNode* cond = child->rsib;
            TreeNode* stmt = cond->rsib;
            noSib.push(stmt);
            cond->genCode();
            noSib.pop();
            cout << "\tpopl\t%eax\n";
            cout << "\tcmp\t$0, %eax\n";
            cout << "\tjz\tLOOP" << LL1.top() << "_END\n";
            stmt->genCode();
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
                forhead->genCode();
                noSib.pop();
            }
            cout << "LOOP" << LL1.top() << "_BGN:\n";
            if (formid->nodeType != NODE_KEY)
            {
                noSib.push(forend);
                formid->genCode();
                noSib.pop();
                cout << "\tpopl\t%eax\n";
                cout << "\tcmp\t$0, %eax\n";
                cout << "\tjz\tLOOP" << LL1.top() << "_END\n";
            }
            stmt->genCode();
            if (forend->nodeType != NODE_KEY)
            {
                noSib.push(stmt);
                cout << "LOOP" << LL1.top() << "_COND:\n";
                forend->genCode();
                noSib.pop();
            }
        }
        cout << "\tjmp\tLOOP" << LL1.top() << "_BGN\n";
        cout << "LOOP" << LL1.top() << "_END:\n";
        LL1.pop();
    }    
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_PARM)
    {
        TreeNode* p = child;
        while (p != nullptr)
        {
            switch (p->child->type->type)
            {
            case VALUE_CHAR:
                param--;
                break;
            case VALUE_INT:
                param -= 4;
                break;
            case VALUE_STRING:
                param -= 8;
                break;
            default:
                break;
            }
            id2off.insert(make_pair(p->child->rsib->nodeID, param));
            ids.push(p->child->rsib->nodeID);
            p = p->rsib;
        }
        return;
    }
    else if (nodeType == NODE_STMT &&
             stmtType == STMT_RET)
    {
        if (inFunc.top()->child->rsib->varName == "main")
        {
            cout << ".END:\n";
            cout << "\tmovl\t%ebp, %esp\n";
            cout << "\tpopl\t%ebp\n";
            cout << "\tmovl\t$0, %eax\n";
            cout << "\tret\n";
        }
        else
        {
            if (child != nullptr)
            {
                child->genCode();
                if (child->nodeType != NODE_FUNC)
                    cout << "\tpopl\t%eax\n";    
            }
            cout << "\tmovl\t%ebp, %esp\n";
            cout << "\tpopl\t%ebp\n";
            cout << "\tret\n";
            param += 4;    // ebp offset
        }      
        if (rsib == nullptr &&
            parent->nodeType == NODE_STMT &&
            parent->stmtType == STMT_BLCK)
            isRet = true;
    }
    else if (nodeType == NODE_VAR)
    {
        if (id2off.find(nodeID) != id2off.end())
        {
            int t = id2off.find(nodeID)->second;
            cout << "\tpushl\t" << (-1) * t;
            cout << "(%ebp)\n"; 
        }
        else
            cout << "\tpushl\t" << varName << endl;
    }
    else
    {
        if (child != nullptr) child->genCode();
    }
    // next stmt
    if (rsib != nullptr &&
        (noSib.empty() || rsib != noSib.top())) 
    {
        rsib->genCode();
    }
}

void TreeNode::genStr()
{
    cout << "\t.text\n";
    cout << "\t.section\t.rodata\n";
    cout << "_CHAR:\n";
    cout << "\t.string\t\"%c\"\n";
    cout << "_INT:\n";
    cout << "\t.string\t\"%d\"\n";
    cout << "_STRING:\n";
    cout << "\t.string\t\"%s\"\n";
    for (auto &it : id2str)
    {
        TreeNode* node = it.second;
        cout << "_STR_" << node->nodeID << ":\n";
        cout << "\t.string\t\"" << node->sval << "\"" << endl;
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
        if (type->isArray) 
        {
            cout << endl;
            for (int i = 0; i < 15; i++) cout << " ";
        }
        cout << "varname: ";
        cout << varName;  
    }
    cout << endl;
}