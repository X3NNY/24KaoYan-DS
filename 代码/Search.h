#include "stdafx.h"

typedef struct {        // 顺序查找表
    ElemType *elem;     // 元素存储空间基地址
    int TableLen;       // 表长
}SSTable;

typedef struct BSTNode {                // 链式存储的BST
    ElemType data;                      // 数据域
    struct BSTNode *lchild, *rchild;    // 左右孩子指针
    int count;                          // 记录子树结点数（7.3 11题用）
}BSTNode, *BSTree;