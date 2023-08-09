#include "stdafx.h"
#define MAXLEN 256

typedef struct {
    ElemType data[MAXLEN];
}SqTree;

typedef struct BiTNode {                // 链式存储
    ElemType data;                      // 数据域
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
}BiTNode, *BiTree;

typedef struct ThreadNode {             // 线索二叉树
    ElemType data;                      // 数据元素
    struct ThreadNode *lchild, *rchild; // 左、右孩子指针
    int ltag, rtag;                     // 左、右线索标识
}ThreadNode, *ThreadTree;


void visit(BiTree T) {
    printf("%d ", T->data);
}

void visit(ThreadTree T) {
    if (T != NULL)
        printf("%d ", T->data);
    else
        puts("N;");
}