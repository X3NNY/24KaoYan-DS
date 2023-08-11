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
            visit((BiTree)x);                       // 访问根结点
            p = ((BiTree)x)->rchild;
        }
    }
    puts("");
}

void PostOrder2(BiTree T) { // 后序遍历 左右根
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

// 5.3 作业

void CustomOrder(BiTree T) { // 4. 自下而上，从右到左 就是RLN
    if (T != NULL) {
        CustomOrder(T->rchild);
        CustomOrder(T->lchild);
        visit(T);
    }
}

int GetHeight(BiTree T) { // 5. 用非递归方法求高度
    /**
     * 用层次遍历的方法，每层高度加一，或者用栈保存结点以及深度
    */
    if (!T) return 0;
    BiTree p;
    ElemType x;
    BiTree Q[MaxSize];
    int height = 0,
        front = -1,                 // 队首
        rear = -1,                  // 队尾
        last = 0;                   // 记录上一层最后结点位置
    Q[++rear] = T;
    while(front < rear) {
        p = Q[++front];             // 出队
        if (p->lchild != NULL) {
            Q[++rear] = p->lchild;  // 入队
        }
        if (p->rchild != NULL) {    
            Q[++rear] = p->rchild;  // 入队
        }
        if(front == last) {         // 如果遍历到上一轮最后一个结点
            height++;               // 层数+1
            last = rear;            // 同时代表当前层的所有结点都已入队，更新最后一个结点位置
        }
    }
    return height;
}

BiTree PreInOrderCreate(ElemType A[], ElemType B[], int ls, int le, int rs, int re) { // 6. 用前序和中序序列建树
    /**
     * 就是将自己转化变成代码
     * 先序第一个位置是根，然后在中序中找根的位置，将树划分为两半
     * 然后就可以递归的对左右子树分别建树了
     * ls，le分别代表A中的起始结束位置，rs，re同理
    */ElemType pre[] = {1,2,4,5,3};ElemType in[] = {4,2,5,1,3};
    int i;
    BiTree T = (BiTNode*)malloc(sizeof(BiTNode));
    T->data = A[ls];                                       // 前序的第一个就是根结点
    for (i = rs; B[i] != T->data; i++);                    // 寻找根结点在中序中的位置

    int llen = i-rs, rlen = re-i;                          // 左右子树长度
    if (llen) {                                            // 如果左子树序列长度不为0，也就是存在左子树
        T->lchild = PreInOrderCreate(A, B, ls+1, ls+llen, rs, rs+llen-1);
                                                           // 此时，先序中的左子树序列便是根结点后llen长度
                                                           // 中序便是开始位置到根结点前一个共llen长度
    } else T->lchild = NULL;

    if (rlen) {
        T->rchild = PreInOrderCreate(A, B, le-rlen+1, le, re-rlen+1, re);
                                                           // 同理操作右子树，此时先序是根左右，所以右子树序列应该出现在最后面，
                                                           // 则是从后往前rlen个位置，同理中序也是从后往前rlen个位置
    } else T->rchild = NULL;
    return T;
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

    // PreOrder(T);
    // InOrder2(T);
    // PostOrder2(T);
    // PostOrder(T);

    // LevelOrder(T);

    // int x = GetHeight(T);printf("%d\n", x);

    ElemType pre[] = {1,2,4,5,3};ElemType in[] = {4,2,5,1,3};
    BiTree T2 = PreInOrderCreate(pre, in, 0, 4, 0, 4);
    PreOrder(T2);InOrder(T2);
    return 0;
}