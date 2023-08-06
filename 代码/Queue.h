#include "stdafx.h"
#define MaxSize 50

typedef struct {
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue &Q) { // 初始化循环队列，后续都为循环队列操作，普通的去掉取模就行
    Q.rear = Q.front = 0;
}

bool isEmpty(SqQueue Q) { // 判空
    return Q.rear == Q.front;
}

bool EnQueue(SqQueue &Q, ElemType x) { // 入队
    if((Q.rear+1)%MaxSize == Q.front) return false; // 队满
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize; // 队尾+1取模 
    return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) { // 出队
    if(Q.rear == Q.front) return false; // 对空
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize; // 队首+1 取模
    return true;
}