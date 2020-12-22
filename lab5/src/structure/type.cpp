#include "type.h"

bool Type::operator ==(const Type& b)
{
    if (b.type == NOT_SURE)
        return true;
    switch (type)
    {
    case NOT_SURE:
        return true;
    case VALUE_BOOL:
        if (b.type == VALUE_INT)
            return true;
        break;
    case VALUE_CHAR:
        if (b.type == VALUE_INT)
            return true;
        break;
    case VALUE_INT:
        if (b.type == VALUE_CHAR || 
            b.type == VALUE_BOOL)
            return true;
        break;
    default:
        break;
    }
    return type == b.type;
};

bool Type::operator !=(const Type& b)
{
    if (b.type == NOT_SURE)
        return false;
    switch (type)
    {
    case NOT_SURE:
        return false;
    case VALUE_BOOL:
        if (b.type == VALUE_INT)
            return false;
        break;
    case VALUE_CHAR:
        if (b.type == VALUE_INT)
            return false;
        break;
    case VALUE_INT:
        if (b.type == VALUE_CHAR ||
            b.type == VALUE_BOOL)
            return false;
        break;
    default:
        break;
    }
    return type != b.type;
}

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
    if (t == nullptr) return;
}

void Type::addParam(Type* t)
{
    if (t == nullptr) return;
}

void Type::addRet(Type* t)
{
    if (t == nullptr) return;
}