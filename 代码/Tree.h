#include "stdafx.h"
#define MAXLEN 256

typedef struct {
    ElemType data[MAXLEN];
}SqTree;

typedef struct BiTNode {                // 链式存储
    ElemType data;                      // 数据域
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
}BiTNode, *BiTree;

void visit(BiTree T) {
    printf("%d ", T->data);
}