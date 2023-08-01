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

// 3.3作业题

bool BracketCheck(SqStack &S, char *s) { // 1. 括号匹配
    ElemType x; // 实际应该考虑类型转换，不过本身char转为int也没问题所以直接用
    bool flag = true;
    for(int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            flag = Push(S, s[i]);
            if (!flag) { // 如果栈已满，则说明有问题，当然这里应该取决题目是否有对最大长度做限制
                return false;
            }
        } else {
            flag = Pop(S, x);
            if (!flag) { // 如果栈已空，则说明有问题
                return false;
            }
            if ((x == '(' && s[i] == ')') || \
                (x == '[' && s[i] == ']') || \
                (x == '{' && s[i] == '}')) { // 匹配，则无问题
                    ;
                } else { // 否则说明错误
                    return false;
                }
        }
    }
    return StackEmpty(S); // 最后还需要保证栈是空的，这样才能保证刚好匹配
}

void TrainSchedule(SqStack &S, char *vans) { // 2. 车厢调度
    /**
     * 让S先走，H入栈等着就行
    */
    int index = 0;
    ElemType x;
    for (int i = 0; vans[i] != '\0'; i++) {
        if (vans[i] == 'H') { // 是H就入栈
            Push(S, vans[i]);
        } else { // 否则就放到头部去
            vans[index++] = vans[i];
        }
    }
    while(!StackEmpty(S)) {  // 把H车厢拼到后面
        Pop(S, x);
        vans[index++] = x;
    }
}

int CalcPoly(int n, int x) { // 3. 使用栈计算递归表达式
    /**
     * 原来的递归函数调用等于OS除了压/出栈，转换为自己管理即可
     * 私以为书上的答案不太行，就是拿栈当计数器用了，还不如直接写for递推
    */
    SqStack S;
    InitStack(S);
    ElemType tn;
    int P[MaxSize];
    memset(P, 0, sizeof(P));
    Push(S, n); // 将n压栈进行运算

    while(!StackEmpty(S)) { // 如果栈内还有待运算的
        Pop(S, tn);
        if (tn == 0) { // 边界
            P[0] = 1;
        } else if (tn == 1) { // 边界
            P[1] = 2*x;
        } else {
            if(P[tn] == 0) { // 如果还没计算出Pn的值
                if (P[tn-1] && P[tn-2]) {   // 如果Pn-1和Pn-2已经被计算了
                    P[tn] = 2*x*P[tn-1] - 2*(tn-1)*P[tn-2];
                } else { // 否则压栈 等待tn-1和tn-2的计算完成再计算。
                    Push(S, tn);
                    Push(S, tn-1);
                    Push(S, tn-2);
                }
            }
        }
    }
    return P[n]; // 计算完成后Pn即是答案
}

int main() {
    char s1[]="IOIIOIOO";
    char s2[]="IOOIOIIO";
    char s3[]="IIIOIOIO";
    char s4[]="IIIOOIOO";

    SqStack S;
    InitStack(S);

    // char s[] = "(({{}{{}}[[]](())[[]]}))";
    // puts("no\0ok"+3*BracketCheck(S, s));

    // char vans[] = "HHHSHSHSHSHHHSSSSSSHHHS";
    // TrainSchedule(S, vans);
    // puts(vans);

    printf("%d\n", CalcPoly(3, 123)); // 把n增大会算出来负的，很正常因为这个多项式增长太快了，就越界了，
    
    // puts("no\0ok"+3*ValidCheck(s3));
}