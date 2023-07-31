#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 50

typedef int ElemType; // 数据类型

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


// 以下为作业代码答案

/**
 * 1. 第一个出C则栈内此时为BA，第二个为D说明栈内此时为BA，还剩一个E自由人
 * E可以插入剩下的任何位置，所以可以
 * CDEBA、CDBEA、CDBAE
 * 
 * 2. BCAED可以，DBACE不行，因为D出来时栈内一定为CBA，此时B要想出来必须C先出来。
*/

bool ValidCheck(char* s) { // 3. 合法性判断
    SqStack S;
    InitStack(S);
    int x = 1;
    bool flag = true;
    for(int i = 0;s[i] != '\0';i++) {
        if(s[i] == 'I') {
            flag = Push(S, x); // 栈满了 不合法
        } else {
            flag = Pop(S, x); // 栈已空 不合法
        }
        if(!flag) break;
    }
    return flag && StackEmpty(S); // 终态也得是空栈
}



int main() {
    char s1[]="IOIIOIOO";
    char s2[]="IOOIOIIO";
    char s3[]="IIIOIOIO";
    char s4[]="IIIOOIOO";
    
    puts("no\0ok"+3*ValidCheck(s3));
}