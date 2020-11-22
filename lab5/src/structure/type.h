#ifndef TYPE_H
#define TYPE_H

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
    ValueType type;
    Type(ValueType valueType);
};

static Type* TYPE_BOOL = new Type(VALUE_BOOL);
static Type* TYPE_CHAR = new Type(VALUE_CHAR);
static Type* TYPE_INT = new Type(VALUE_INT);
static Type* TYPE_STRING = new Type(VALUE_STRING);

#endif TYPE_H