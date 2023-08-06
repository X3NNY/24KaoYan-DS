#include "stdafx.h"

#define MaxSize 50

typedef struct {
    ElemType data[MaxSize]; // 存放数据
    int top;                // 栈顶指针
} SqStack;

void InitStack(SqStack &S) { // 初始化
    S.top = -1; // 初始化栈顶指针
}

bool StackEmpty(SqStack &S) { // 判空
    return S.top == -1;
}

bool Push(SqStack &S, ElemType x) { // 入栈
    if(S.top == MaxSize - 1) { // 栈满
        return false;
    }
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S,ElemType &x) { // 出栈
    if(S.top == -1) { // 栈空
        return false;
    }
    x = S.data[S.top--];
    return true;
}

bool GetTop(SqStack &S,ElemType &x) { // 读取栈顶
    if(S.top == -1) { // 栈空
        return false;
    }
    x = S.data[S.top];
    return true;
}