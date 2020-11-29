#include "type.h"

string Type::getTypeInfo()
{
    switch (type)
    {
    case VALUE_BOOL:
        return "boolean";
    case VALUE_CHAR:
        return "character";
    case VALUE_INT:
        return "integer";
    case VALUE_STRING:
        return "string";
    case VALUE_VOID:
        return "void";
    default:
        return "NOT SURE";
    }
}

void Type::addChild(Type* t)
{

}

void Type::addParam(Type* t)
{

}

void Type::addRet(Type* t)
{

}