#include "Stack.h"


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
    ElemType x = 1;
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


int priority(char op) { // 返回运算符优先级
    if (op == '*' || op == '/') {
        return 1;
    } else if (op == '+' || op == '-') {
        return 0;
    } else {
        return -1;
    }
}

void expr_convert(const char* expr, char rexpr[]) { // 选择题11题，中缀表达式转后缀表达式
    /**
     * 如果操作符比栈顶的操作符优先级高，例如a*b+c，则出栈，因为此时b是*的操作数而不是+的操作数，+需要等待前面运算的结果作为操作数。
     * 遇到(需要等到)再处理。
     * 
     * 这里这样操作是因为只包含左结合操作符，如果有右结合操作符，例如a^a^a = a^(a^a)的话，则遇到^则入栈（当作括号处理，即高优先级操作符）。
    */
    SqStack S;
    InitStack(S);
    ElemType x;
    int index = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= 97 && expr[i] <= 127) { // 是字符，即操作数
            rexpr[index++] = expr[i];
        } else {
            if (StackEmpty(S)) {               // 如果栈空，入栈
                Push(S, expr[i]);
            } else {
                if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
                    while(!StackEmpty(S)) {
                        GetTop(S, x);
                        if (priority(expr[i]) <= priority(x)) { // 如果栈顶优先级比当前大，则出栈
                            Pop(S, x);
                            rexpr[index++] = x;
                        } else {
                            break;
                        }
                    }
                    Push(S, expr[i]);                           // 入栈
                } else if (expr[i] == '(') {                    // 入栈
                    Push(S, expr[i]);
                } else if (expr[i] == ')') {
                    while (!StackEmpty(S)) {
                        Pop(S, x);
                        if (x != '(') {                         // 将括号内操作符出栈
                            rexpr[index++] = x;
                        } else {
                            break;
                        }
                    }
                } else {
                    Push(S, expr[i]);
                }
            }
        }
    }
    while(!StackEmpty(S)) {                                     // 将剩余出栈
        Pop(S, x);
        rexpr[index++] = x;
    }
    rexpr[index++] = '\0';
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

    // printf("%d\n", CalcPoly(3, 123)); // 把n增大会算出来负的，很正常因为这个多项式增长太快了，就越界了，
    
    // puts("no\0ok"+3*ValidCheck(s3));
    char rexpr[100];
    expr_convert("a+b-a*((c+d)/e-f)+g", rexpr);
    puts(rexpr);
}