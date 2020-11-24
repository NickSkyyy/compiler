#include "../pch.h"

enum ValueType
{ 
    COMPOSE_FUNCTION,
    COMPOSE_STRUCT,
    COMPOSE_UNION,
    KEY,
    VALUE_BOOL,
    VALUE_CHAR,
    VALUE_INT,
    VALUE_STRING
};

class Type
{
public:
    ValueType* sibling;
    ValueType type;

public:
    string getTypeInfo();
    Type(ValueType valueType) : type(valueType){};
    void addChild(Type* t); // 子列表？
    void addParam(Type* t); // 参数
    void addRet(Type* t);   // 返回值
};

static Type* TYPE_BOOL = new Type(VALUE_BOOL);
static Type* TYPE_CHAR = new Type(VALUE_CHAR);
static Type* TYPE_INT = new Type(VALUE_INT);
static Type* TYPE_KEY = new Type(KEY);
static Type* TYPE_STRING = new Type(VALUE_STRING);