#include "Tree.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"

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
    */
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

bool IsCompleteTree(BiTree T) { // 7. 判断是否完全二叉树
    /**
     * 显然完全二叉树的定时是前n-1层是满二叉树，即每层都有2^i-1个结点
     * 可以通过遍历计数的方式，也可以通过判断叶结点是否在最后两层来操作
    */
    if (!T) return 1;               // 注意，空树是满二叉树
    BiTree p;
    ElemType x;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, (intptr_t)T);
    while(!isEmpty(Q)) {
        DeQueue(Q, x);
        p = BiTree(x);
        if (p) {                                // 如果非空，子结点入队
            EnQueue(Q, (intptr_t)p->lchild);
            EnQueue(Q, (intptr_t)p->rchild);
        } else {                                // 遇到空结点说明上一层是叶子结点了，此时后续应该都为空结点
            while(!isEmpty(Q)) {
                DeQueue(Q, x);
                if(BiTree(x)) return 0;         // 还有非空，则返回0
            }
        }
    }
    return 1;
}

int CountDegree2(BiTree T) { // 8. 计算双分支结点个数
    /**
     * 其实就是计算度为2的结点个数，可递归可层次遍历，
     * 层次遍历则是每次如果左右结点都存在则计数加1，递归则是个数等于左子树个数+右子树个数+当前结点是否度为2
    */
    if (!T) return 0;
    int count = 0;
    // 思路一：层次遍历
    BiTree p;
    ElemType x;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, (intptr_t)T);
    while(!isEmpty(Q)) {
        DeQueue(Q, x);
        p = BiTree(x);
        if (p->lchild) {                                // 如果非空，子结点入队
            EnQueue(Q, (intptr_t)p->lchild);
        } if (p->rchild) {
            EnQueue(Q, (intptr_t)p->rchild);
        }
        if (p->lchild && p->rchild) {
            count++;
        }
    }

    // 思路二：递归
    if (T->lchild) {
        count += CountDegree2(T->lchild);
    }
    if (T->rchild) {
        count += CountDegree2(T->rchild);
    }
    if (T->lchild && T->rchild) count++;

    return count;
}

void SwapChildTree(BiTree T) { // 9. 交换所有结点左右子树
    /**
     * 显然涉及到所有结点我们都需遍历，我们可以用递归轻松分解问题
     * 递归交换左子树中结点子树
     * 递归交换右子树中结点子树
     * 交换左右子树
    */
    if (T->lchild) SwapChildTree(T->lchild);
    if (T->rchild) SwapChildTree(T->rchild);
    BiTree p = T->lchild;
    T->lchild = T->rchild;
    T->rchild = p;
}

int count = 1;
ElemType NthPreElem(BiTree T, int k) { // 10. 求先序序列中第k个结点的值
    /**
     * 先序递归时计数即可，可以用全局遍历或者引用传参即可
    */
    ElemType r;
    if(T) {
        if (count == k) {
            return T->data;
        }
        count++;
        r = NthPreElem(T->lchild, k);
        if (r != '#') return r;

        r = NthPreElem(T->rchild, k);
        if (r != '#') return r;
    }
    return '#';
}

void RemoveChildTree(BiTree T) {
    if (T) {
        RemoveChildTree(T->lchild);
        RemoveChildTree(T->rchild);
        free(T);
    }
}
void RemoveElemByValue(BiTree T, ElemType x) { // 11. 删除结点值为x的且以结点为根的子树，并释放空间
    /**
     * 和遍历一样，删除也需要遍历检查，当发现不合法时，也是遍历free掉该删除的子树
    */
    if (!T) return;
    if (T->lchild) {
        if (T->lchild->data == x) {
            RemoveChildTree(T->lchild);
            T->lchild = NULL;                   // 记得赋空
        } else {
            RemoveElemByValue(T->lchild, x);
        }
    }
    if (T->rchild) {
        if (T->rchild->data == x) {
            RemoveChildTree(T->rchild);
            T->rchild = NULL;                   // 记得赋空
        } else {
            RemoveElemByValue(T->rchild, x);
        }
    }
}

void SearchAllAncestors(BiTree T, ElemType x) { // 12. 打印值为x的结点（最多存在一个）的所有祖先
    /**
     * 遇到这种需要打印所有东西的显然我们可以利用栈来保存祖先
     * 然后进行后序遍历，当找到值为x的结点时，此时栈中元素便是x的祖先
    */
    SqStack S;
    InitStack(S);
    BiTree p = T, r;
    ElemType k;
    while (p || !StackEmpty(S)) {
        if (p && p->data == x) {     // 遍历到x了
            while (!StackEmpty(S)) {
                Pop(S, k);
                p = ((BiTree)k);
                printf("%d ", p->data);
            }
            puts("");
            return;
        }
        if (p) {                                // 如果当前子树还没遍历完
            Push(S, (intptr_t)p);  
            p = p->lchild;                      // 继续遍历左子树
        } else {
            GetTop(S, k);                       // 出栈，即上一个左子树已经遍历完，此时遍历上一轮压栈的子树的右子树
            if (((BiTree)k)->rchild != NULL && \
                ((BiTree)k)->rchild != r) {     // 如果上一个结点还有右子树且未访问 则还需遍历右子树
                p = ((BiTree)k)->rchild;
            } else {
                Pop(S, k);
                r = ((BiTree)k);                // 记录最近被访问的结点
                p = NULL;                       // 将结点置空
            }
        }
    }
    puts("");
}

BiTNode* ANCESTOR(BiTree T, BiTNode* p, BiTNode* q) {   // 13. 找到p和q的最近公共祖先
    /**
     * 之前是数组存储的找LCA可以方便的找到双亲，但是这里是链式存储的
     * 同样，我们可以考虑非递归的后序遍历，因为是LRN，所以当遍历到p时，栈内元素全是p的祖先，
     * 然后保存此时状态，再继续遍历到q，此时栈内全是q的祖先，再从后往前找第一个公共祖先即可。
    */
    SqStack S;
    BiTNode *TS1[MAXLEN], *TS2[MAXLEN], *res = NULL;
    int len1, len2;
    InitStack(S);
    BiTree tp = T, r;
    ElemType k;
    while (tp || !StackEmpty(S)) {
        if (tp == p) {                          // 遍历到p了
            int i = 0;
            while(!StackEmpty(S)) {             // 保存栈内元素
                Pop(S, k);
                TS1[i++] = (BiTNode*)k;
            }
            len1 = i;
            while (i) {                         // 恢复栈
                Push(S, (intptr_t)TS1[--i]);
            }
        } else if (tp == q) {                   // 遍历到q了
            int i = 0;
            while(!StackEmpty(S)) {             // 保存栈内元素
                Pop(S, k);
                TS2[i++] = (BiTNode*)k;
            }
            len2 = i;
            while (i) {                         // 恢复栈
                Push(S, (intptr_t)TS2[--i]);
            }
        }
        if (tp) {                               // 如果当前子树还没遍历完
            Push(S, (intptr_t)tp);  
            tp = tp->lchild;                    // 继续遍历左子树
        } else {
            GetTop(S, k);                       // 出栈，即上一个左子树已经遍历完，此时遍历上一轮压栈的子树的右子树
            if (((BiTree)k)->rchild != NULL && \
                ((BiTree)k)->rchild != r) {     // 如果上一个结点还有右子树且未访问 则还需遍历右子树
                tp = ((BiTree)k)->rchild;
            } else {
                Pop(S, k);
                r = ((BiTree)k);                // 记录最近被访问的结点
                tp = NULL;                      // 将结点置空
            }
        }
    }
    for (int i = len1-1; i >= 0; i--) {          // 我们是从栈顶开始存的，也就是根结点在TS最后面
        if (TS1[i] == TS2[len2-(len1-i)]) {      // 相等，说明是公共祖先
            res = TS1[i];                        // 不断更新，找到最近的
        } else break;
    }
    return res;
}

int GetWidth(BiTree T) {    // 14. 求非空二叉树的宽度
    /**
     * 显然使用层次遍历，每次更新最大结点数即可
    */
    BiTree p;
    ElemType x;
    BiTree Q[MaxSize];
    int last = 0,
        front = -1,                 // 队首
        rear = -1,                  // 队尾
        max = 0;                   // 记录上一层最后结点位置
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
            if (rear - front > max) max = rear - front;
            last = rear;            // 同时代表当前层的所有结点都已入队，更新最后一个结点位置
        }
    }
    return max;
}

void PreToPost(ElemType pre[], int ls, int le, ElemType post[], int rs, int re) {   // 15. 满二叉树先序转后序
    /**
     * 先序是NLR，后序是LRN，并且是满二叉树，所以左右序列长度相同，显然我们只需要把
     * NLR -> LRN 然后LR的分割点就是中间，再分别对左右子树做转换即可
    */
    int mid = (le - ls) / 2;
    if (mid >= 0) {
        post[re] = pre[ls];
        PreToPost(pre, ls+1, mid+mid, post, rs, rs+mid-1);
        PreToPost(pre, ls+mid+1, le, post, rs+mid, re-1);
    }
}

void GetLeafNodeList(BiTree T, BiTree &pre, BiTree &head) {    // 16. 将叶子结点从左到右变成一个链表
    /**
     * 显然我们使用任意一种遍历都是LR，所以满足从左到右，然后记录一下叶子结点即可
     * 这里我们让二叉树结点作为链表使用rchild指向后继
    */
    if (T) {
        GetLeafNodeList(T->lchild, pre, head);
        if (T->lchild == NULL && T->rchild == NULL) {   // 叶子结点
            if (pre == NULL) {                          // 第一个结点
                head = T;
                pre = T;
            } else {
                pre->rchild = T;
                pre = T;
            }
        }
        GetLeafNodeList(T->rchild, pre, head);
        pre->rchild = NULL;
    }
}

bool IsSimilar(BiTree T1, BiTree T2) {  // 17. 判断两棵二叉树是否相似
    /**
     * 定义已经说明白了，都为空或只有一个结点相似，或者递归比较子树是否相似
    */
    if (T1 == NULL && T2 == NULL) {             // 都为空 相似
        return true;
    } else if (T1 == NULL || T2 == NULL) {      // 一个空 不相似
        return false;
    }
    bool left = IsSimilar(T1->lchild, T2->lchild);  // 判断左子树是否相似
    bool right = IsSimilar(T1->rchild, T2->rchild); // 判断右子树是否相似
    return left && right;
}


int main() {
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = 1;
    T->lchild = (BiTree)malloc(sizeof(BiTNode));
    T->lchild->data = 2;
    T->rchild = (BiTree)malloc(sizeof(BiTNode));
    T->rchild->data = 3;

    T->rchild->lchild = (BiTree)malloc(sizeof(BiTNode));
    T->rchild->lchild->data = 6;
    T->rchild->lchild->lchild = NULL;
    T->rchild->lchild->rchild = NULL;
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

    // ElemType pre[] = {1,2,4,5,3};ElemType in[] = {4,2,5,1,3};
    // BiTree T2 = PreInOrderCreate(pre, in, 0, 4, 0, 4);
    // PreOrder(T2);InOrder(T2);

    // puts("no\0ok"+IsCompleteTree(T)*3);

    // printf("%d\n", CountDegree2(T));
    // SwapChildTree(T);PreOrder(T);

    // printf("%d\n", NthPreElem(T, 5));
    // RemoveElemByValue(T, 4);PreOrder(T);
    // SearchAllAncestors(T, 4);
    // visit(ANCESTOR(T, T->lchild->lchild, T->lchild->rchild));
    // printf("%d\n", GetWidth(T));

    // ElemType pre[] = {1,2,4,5,3}, post[] = {0, 0, 0, 0, 0};
    // PreToPost(pre, 0, 4, post, 0, 4);
    // for(int i = 0; i < 5; i++) printf("%d ", post[i]);
    return 0;
}