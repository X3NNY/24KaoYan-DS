#include "stdafx.h"

typedef struct LNode {  // 定义结点类型
    ElemType data;      // 数据域
    struct LNode *next; // 指针域
}LNode, *LinkList; // 上面的LNode是结构体名字，下面的LNode是这个结构体的别名（一样），LinkList是结构体指针(struct LNode*)的别名，记住typedef出来的东西只是个别名，该是什么还是什么类型
