#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 50

typedef int ElemType; // 数据类型

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


// 以下为代码题答案

bool tag = true; // 代表是否为空
/**
 * 1. 用tag表示是否为空则
 * 入队时如果不是空 且两指针在一起就是满，同时每次入队都让tag=false
 * 出队时如果两指针在一起且显示为空就是空，且如果取走后指针相等，则tag置true
*/
bool EnQueueWithTag(SqQueue &Q, ElemType x) { // 入队
    if(Q.rear==Q.front && !tag) { // 队满
        return false;
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize; // 队尾+1取模
    tag = false;
    return true;
}

bool DeQueueWithTag(SqQueue &Q, ElemType &x) { // 出队
    if(Q.rear == Q.front && tag) return false; // 队空
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize; // 队首+1 取模
    if(Q.rear == Q.front) tag = true;
    return true;
}


typedef struct {
    ElemType data[MaxSize]; // 存放数据
    int top;                // 栈顶指针
} SqStack;
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

void ReverseQueue(SqQueue &Q, SqStack &S) { // 2. 利用一个空栈逆转队列里面的元素·
    /**
     * 其实只需要一个额外变量暂存即可
    */
    ElemType x;
    while(!isEmpty(Q)) {
        DeQueue(Q, x);
        Push(S, x);
    }
    while(!StackEmpty(S)) {
        Pop(S, x);
        EnQueue(Q, x);
    }
}

bool EnqueueSimulate(SqStack &S1, SqStack &S2, ElemType x) { // 3. 两个栈模拟队列 入队操作
    if(S1.top != MaxSize - 1) { // 如果S1还没满
        Push(S1, x);
        return true;
    }
    if(S1.top == MaxSize - 1 && !StackEmpty(S2)) { //  如果S1满了 S2也不为空 则整个队列满了
        puts("队列已满");
        return false;
    }
    ElemType e;
    if(S1.top == MaxSize - 1 && StackEmpty(S2)) { // 如果S1满了S2为空，则将S1的数据存到S2
        while(!StackEmpty(S1)) {
            Pop(S1, e);
            Push(S2, e);
        }
    }
    Push(S1, x);
    return true;
}

bool DequeueSimulate(SqStack &S1, SqStack &S2, ElemType &x) { // 3. 两个栈模拟队列 出队操作
    if(!StackEmpty(S2)) { // 如果S2里面有数据，直接返回，因为S1的栈让顺序逆转一遍，再到S2再次逆转一遍反而等于原顺序了，即FIFO
        Pop(S2, x);
    } else if (StackEmpty(S1)) { // 如果S2没东西，S1也没东西，则队列为空
        puts("队列为空");
        return false;
    } else {
        while(!StackEmpty(S1)) { // 否则先将数据倒腾到S2，让数据变成FIFO进行输出
            Pop(S1, x);
            Push(S2, x);
        }
        Pop(S2, x);
    }
    return true;
}

bool QueueEmptySimulate(SqStack &S1, SqStack &S2) { // 3. 两个栈模拟队列 判空
    return StackEmpty(S1) && StackEmpty(S2); // 如果两个栈都为空则队列为空
}

// 3.3题目

void CarFerry(char* cars) { // 4. 汽车轮渡
    /**
     * 有个优先级概念，所以需要另一个队列维护等待
     * 这里我用C代表客车，T代表货车
     * 标答是直接给客车货车分队列了，我这里代表他们在一起等
    */
    int ccount = 0, tcount = 0; //分别记录客车和货车数量
    SqQueue Q, W; // W为货车等待队列
    InitQueue(Q);
    InitQueue(W);
    ElemType c;
    for(int i = 0; cars[i] != '\0'; i++) {
        if (cars[i] == 'C') {
            if (ccount + tcount < 10) {
                EnQueue(Q, cars[i]);
                ccount++;
            }
        } else if (cars[i] == 'T') {
            EnQueue(W, cars[i]); // 先放到等待队列
        }

        if (ccount % 4 == 0 && ccount + tcount < 10) { // 如果放了四辆客车 且还没放满 放个货车进去
            DeQueue(W, c);
            EnQueue(Q, c);
            tcount++;
        }
    }

}

void DisplayList(SqQueue &Q) {
    ElemType x;
    while(!isEmpty(Q)) {
        DeQueue(Q, x);
        printf("%d ", x);
    };
    puts("");
}

int main() {
    SqQueue Q;
    SqStack S;
    S.top = -1;
    InitQueue(Q);
    ElemType x;
    EnQueueWithTag(Q, 1);
    EnQueueWithTag(Q, 2);
    EnQueueWithTag(Q, 3);
    EnQueueWithTag(Q, 4);
    // for (int i = 0; i < 3; i++)
    //     printf("%d ", DeQueueWithTag(Q, x));

    // ReverseQueue(Q, S);

    DisplayList(Q);
}