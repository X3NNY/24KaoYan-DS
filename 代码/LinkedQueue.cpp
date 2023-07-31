#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 50

typedef int ElemType; // 数据类型

typedef struct QNode {  // 链式队列结点
    ElemType data;
    struct QNode *next;
}QNode;

typedef struct {  // 链式队列
    QNode *front, *rear;
}*LinkQueue;


void InitQueue(LinkQueue &Q) { // 初始化链式队列
    Q = (LinkQueue)malloc(sizeof(LinkQueue));
    Q->front = Q->rear = (QNode*)malloc(sizeof(QNode)); // 建立头结点 当然有些也不用头结点，此时直接指向NULL
    Q->front->next = NULL; // 初始化为空
}

bool isEmpty(LinkQueue &Q) { // 判空
    return Q->front == Q->rear;
}

void EnQueue(LinkQueue &Q, ElemType x) { // 入队
    QNode *s = (QNode*)malloc(sizeof(QNode));
    s->data = x;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;        // 链接到队尾并移动队尾指针
}

bool DeQueue(LinkQueue &Q, ElemType &x) {
    if(Q->front == Q->rear) return false; // 空队
    QNode *p = Q->front->next;
    x = p->data;
    Q->front->next = p->next;   // 移动队头
    if (Q->rear == p) {         // 说明为空了，此时让队尾指回来
        Q->rear = Q->front;
    }
    free(p);
    return true;
}


// 以下为代码题答案
/**
 * 4. 队列设计
 * 因为需要动态扩容，所以使用链式队列
 * 又因为涉及循环使用，所以使用循环链式队列
 * 初始化时Q->front->next = Q->front;
 * 并且使用一个空结点判空/满。
 * 入队：
 *  如果满了则先增加一个空结点，每次把数据放到队尾并且移动队尾。
 * 出队：
 *  队空则失败。否则返回队头元素，并且移动队头，注意这里不要free
*/
void EnQueue2(LinkQueue &Q, ElemType x) {   // 入队操作
    if (Q->front == Q->rear->next) {// 队满 插入新的空闲队列
        QNode *s = (QNode*)malloc(sizeof(QNode));
        s->next = Q->rear->next;
        Q->rear->next = s;
    }
    Q->rear->data = x;
    Q->rear = Q->rear->next;
}

bool DeQueue2(LinkQueue &Q, ElemType &x) {
    if (Q->front == Q->rear) { // 队空
        return false;
    }
    x = Q->front->data;
    Q->front = Q->front->next;
    return true;
}

void DisplayList(LinkQueue &Q) {
    ElemType x;
    while(!isEmpty(Q)) {
        DeQueue2(Q, x);
        printf("%d ", x);
    };
    puts("");
}

int main() {
    LinkQueue Q;
    ElemType x;
    InitQueue(Q);
    Q->front->next = Q->front;

    EnQueue2(Q, 1);
    EnQueue2(Q, 2);
    EnQueue2(Q, 3);
    DeQueue2(Q, x);
    EnQueue2(Q, 4);
    DeQueue2(Q, x);
    EnQueue2(Q, 5);
    EnQueue2(Q, 6);

    DisplayList(Q);
}