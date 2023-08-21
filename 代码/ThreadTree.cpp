#include "Tree.h"


void InThread(ThreadTree &p, ThreadTree &pre) {     // 中序线索化
    if (p != NULL) {
        InThread(p->lchild, pre);                   // 线索化子子树
        if (p->lchild == NULL) {                    // 若左子树为空，则赋值为前驱
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {   // 若右子树为空，则将为前驱结点赋值为后继
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;                                    // 改变上一访问结点
        InThread(p->rchild, pre);                   // 线索化右子树
    }
}

void CreateInThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        InThread(T, pre);               // 最开始的上一结点为NULL
        pre->rchild = NULL;             // 最后一个结点的后继也应为NULL
        pre->rtag = 1;
    }
}

void PreThread(ThreadTree &p, ThreadTree &pre) {     // 先序线索化
    if (p != NULL) {
        if (p->lchild == NULL) {                    // 若左子树为空，则赋值为前驱
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {   // 若右子树为空，则将为前驱结点赋值为后继
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;                                    // 改变上一访问结点
        InThread(p->lchild, pre);                   // 线索化子子树
        InThread(p->rchild, pre);                   // 线索化右子树
    }
}

void CreatePreThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PreThread(T, pre);              // 最开始的上一结点为NULL
        pre->rchild = NULL;             // 最后一个结点的后继也应为NULL
        pre->rtag = 1;
    }
}

void PostThread(ThreadTree &p, ThreadTree &pre) {   // 后序线索化
    if (p != NULL) {
        InThread(p->lchild, pre);                   // 线索化子子树
        InThread(p->rchild, pre);                   // 线索化右子树
        if (p->lchild == NULL) {                    // 若左子树为空，则赋值为前驱
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {   // 若右子树为空，则将为前驱结点赋值为后继
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;                                    // 改变上一访问结点
    }
}

void CreatePostThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PreThread(T, pre);              // 最开始的上一结点为NULL
        pre->rchild = NULL;             // 最后一个结点的后继也应为NULL
        pre->rtag = 1;
    }
}

ThreadNode *Firstnode(ThreadNode *p) {  // 找到初始结点
    while(p->ltag != 1) p = p->lchild;  // 若ltag!=1，则代表存储左子树，继续遍历
    return p;
}

ThreadNode *Nextnode(ThreadNode *p) {   // 找到下一结点
    if (p->rtag != 1) return Firstnode(p->rchild);  // 如果右子树非空，则返回右子树的初始结点
    else return p->rchild;              // 否则返回后继
}

void Inorder(ThreadNode *T) {   // 线索二叉树的中序遍历
    for (ThreadNode *p = Firstnode(T);p != NULL; p = Nextnode(p))
        visit(p);
}


// 5.3作业

ThreadNode* SearchPreNode(ThreadTree T, ThreadNode* p) { // 18. 查找中序线索二叉树中指定结点在后序下的前驱结点
    /**
     * 在后序序列中，若结点p有右子女，则右子女是其前驱，若无右子女有左子女，则左子女是前驱。
     * 否则左线索为某祖先结点f，p是f的右子树中中序遍历的第一个结点，则f若有左子女，则左子女是p的前驱。
     * 否则同样寻找f的祖先找到有左子女的为止。
     * 若找不到满足条件的结点，说明p是中序遍历的第一个结点，此时p在中序和后序下均无前驱。
    */
    if (p->rtag != 1) {                             // 有右子女
        return p->rchild;
    } else if (p->ltag != 1) {                      // 有左子女
        return p->lchild;
    } else if (p->lchild == NULL) {                 // 说明没有前驱，此时也就是p是第一个结点
        return NULL;
    } else {
        while(p->ltag == 1 && p->lchild != NULL) {  // 找到有左子女的祖先
            p = p->lchild;
        }
        if (p->ltag != 1) {                         // 如果有左子女
            return p->lchild;
        } else {                                    // 否则说明没有前驱
            return NULL;
        }
    }
}

int main() {
    ThreadTree T = (ThreadTree)malloc(sizeof(ThreadNode));
    T->data = 1;
    T->lchild = (ThreadTree)malloc(sizeof(ThreadTree));
    T->lchild->data = 2;
    T->rchild = (ThreadTree)malloc(sizeof(ThreadTree));
    T->rchild->data = 3;

    T->rchild->lchild = NULL;
    T->rchild->rchild = NULL;

    
    T->lchild->lchild = (ThreadTree)malloc(sizeof(ThreadTree));
    T->lchild->lchild->data = 4;
    T->lchild->rchild = (ThreadTree)malloc(sizeof(ThreadTree));
    T->lchild->rchild->data = 5;

    T->lchild->lchild->lchild = NULL;
    T->lchild->lchild->rchild = NULL;
    T->lchild->rchild->lchild = NULL;
    T->lchild->rchild->rchild = NULL;

    CreateInThread(T);
    Inorder(T);
    return 0;
}