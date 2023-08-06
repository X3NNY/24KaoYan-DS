#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

void PreOrder(BiTree T) { // 先序遍历
    if (T != NULL) {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) { // 中序遍历
    if (T != NULL) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) { // 后序遍历
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

void PreOrder2(BiTree T) { // 先序遍历 根左右
    SqStack S;
    InitStack(S);
    BiTree p = T;
    ElemType x;
    while (p || !StackEmpty(S)) {
        if (p) {                            // 如果当前子树还没遍历完
            visit(p);Push(S, (intptr_t)p);  // 访问根结点，并且压栈
            p = p->lchild;                  // 继续遍历左子树
        } else {
            Pop(S, x);                      // 出栈，即上一个左子树已经遍历完，此时遍历上一轮压栈的子树的右子树
            p = ((BiTree)x)->rchild;
        }
    }
    puts("");
}

void InOrder2(BiTree T) { // 中序遍历 左根右
    SqStack S;
    InitStack(S);
    BiTree p = T;
    ElemType x;
    while (p || !StackEmpty(S)) {
        if (p) {                            // 如果当前子树还没遍历完
            Push(S, (intptr_t)p);  
            p = p->lchild;                  // 继续遍历左子树
        } else {
            Pop(S, x);                      // 出栈，即上一个左子树已经遍历完，此时遍历上一轮压栈的子树的右子树
            visit(p);                       // 访问根结点
            p = ((BiTree)x)->rchild;
        }
    }
    puts("");
}

void PostOrder2(BiTree T) { // 中序遍历 左右根
    SqStack S;
    InitStack(S);
    BiTree p = T, r;
    ElemType x = 1;
    while (p || !StackEmpty(S)) {
        if (p) {                                // 如果当前子树还没遍历完
            Push(S, (intptr_t)p);  
            p = p->lchild;                      // 继续遍历左子树
        } else {
            GetTop(S, x);                       // 出栈，即上一个左子树已经遍历完，此时遍历上一轮压栈的子树的右子树
            if (((BiTree)x)->rchild != NULL && \
                ((BiTree)x)->rchild != r) {     // 如果上一个结点还有右子树且未访问 则还需遍历右子树
                p = ((BiTree)x)->rchild;
            } else {
                Pop(S, x);
                visit((BiTree)x);               // 否则访问该结点，此时该结点无右子树且左子树已被访问。
                p = ((BiTree)x);
                r = p;                          // 记录最近被访问的结点
                p = NULL;                       // 将结点置空
            }
        }
    }
    puts("");
}

void LevelOrder(BiTree T) {
    SqQueue Q;
    InitQueue(Q);
    BiTree p;
    ElemType x;
    EnQueue(Q, (intptr_t)T);
    while(!isEmpty(Q)) {
        DeQueue(Q, x);
        p = (BiTree)x;
        visit(p);
        if (p->lchild != NULL) {
            EnQueue(Q, (intptr_t)p->lchild);
        }
        if (p->rchild != NULL) {
            EnQueue(Q, (intptr_t)p->rchild);
        }
    }
}

// 5.2 作业

int LCA(SqTree T, int i, int j) {     // 5. 找到最近公共祖先
    /**
     * 思想1：当i>j，说明i在j的右边或下一层，此时i回溯到双亲
     *        同理j回溯，当i=j时，说明是两个结点的公共祖先
     *        时间复杂度：O(n)
     * 思想2：这是查询一对可以思路1作，如果是多对查询可以用ST表、倍增LCA、tarjan等算法
    */
    // 方法一
    if (T.data[i] != '#' && T.data[j] != '#') {
        while(i != j) {
            if (i > j) {
                i = i/2;
            } else {
                j = j/2;
            }
        }
        return T.data[i];
    }
    return -1;
}

int main() {
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = 1;
    T->lchild = (BiTree)malloc(sizeof(BiTNode));
    T->lchild->data = 2;
    T->rchild = (BiTree)malloc(sizeof(BiTNode));
    T->rchild->data = 3;

    T->rchild->lchild = NULL;
    T->rchild->rchild = NULL;

    
    T->lchild->lchild = (BiTree)malloc(sizeof(BiTNode));
    T->lchild->lchild->data = 4;
    T->lchild->rchild = (BiTree)malloc(sizeof(BiTNode));
    T->lchild->rchild->data = 5;

    T->lchild->lchild->lchild = NULL;
    T->lchild->lchild->rchild = NULL;
    T->lchild->rchild->lchild = NULL;
    T->lchild->rchild->rchild = NULL;

    // PostOrder2(T);
    // PostOrder(T);

    LevelOrder(T);

    return 0;
}