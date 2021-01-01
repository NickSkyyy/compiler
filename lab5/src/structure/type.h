#include "../pch.h"

enum ValueType
{ 
    NOT_SURE,
    COMPOSE_STRUCT,
    COMPOSE_UNION,
    VALUE_BOOL,
    VALUE_CHAR,
    VALUE_INT,
    VALUE_STRING,
    VALUE_VOID,
};

class Type
{
public:
    bool isArray = false;
    int size = 0;
    Type* child = nullptr;
    Type* lsib = nullptr, * rsib = nullptr;
    ValueType type;

public:
    bool operator ==(const Type& b);
    bool operator !=(const Type& b);
    string getTypeInfo();
    Type(ValueType valueType) : type(valueType){};
    void addChild(Type* t);     // 子列表
    void addParam(Type* t);     // 参数
    void addRet(Type* t);       // 返回值
};

static Type* TYPE_BOOL = new Type(VALUE_BOOL);
static Type* TYPE_CHAR = new Type(VALUE_CHAR);
static Type* TYPE_INT = new Type(VALUE_INT);
static Type* TYPE_STRING = new Type(VALUE_STRING);
static Type* TYPE_VOID = new Type(VALUE_VOID);