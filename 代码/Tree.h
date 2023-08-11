#include "stdafx.h"
#define MAXLEN 256

typedef struct {                        // 顺序存储的二叉树，双亲和孩子看作满二叉树计算
    ElemType data[MAXLEN];
}SqTree;

typedef struct BiTNode {                // 链式存储的二叉树
    ElemType data;                      // 数据域
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
}BiTNode, *BiTree;

typedef struct ThreadNode {             // 线索二叉树
    ElemType data;                      // 数据元素
    struct ThreadNode *lchild, *rchild; // 左、右孩子指针
    int ltag, rtag;                     // 左、右线索标识
}ThreadNode, *ThreadTree;

typedef struct {                        // 双亲表示法 结点
    ElemType data;
    int parent;                         // 存储双亲下标
}PTNode;
typedef struct {                        // 双亲表示法 树
    PTNode nodes[MAXLEN];
}PTree;

typedef struct CSNode {                 // 孩子兄弟表示法
    ElemType data;
    struct CSNode *firstchid,           // 存储第一个孩子指针
                  *nextsibling;         // 存储自己的下一个兄弟指针
}CSNode, *CSTree;



void visit(BiTree T) {
    printf("%d ", T->data);
}

void visit(ThreadTree T) {
    if (T != NULL)
        printf("%d ", T->data);
    else
        puts("N;");
}