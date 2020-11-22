# lab5 notes
## 1 lex
返回的叶节点有：
+ 常量（nodeType: NODE_CONST, type: 数据类型，并在对应的存储位置上记录值）
> bool、char、int、string
> 
> bval、cval、ival、sval
+ 关键字（nodeType: NODE_KEY, vname: 关键字名）
+ 类型（nodeType: NODE_TYPE, vname: 数据类型）
> bool、char、int、string、void
+ 变量（nodeType: NODE_VAR, *val: 初始化为默认值）
> bval、cval、ival、sval
> 
> false、''、0、""

## 2 cfg