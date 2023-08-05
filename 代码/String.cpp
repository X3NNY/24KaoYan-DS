#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 255 // 最大长度

typedef struct {
    char ch[MAXLEN];    // 每个分量存储一个字符
    int length;         // 记录实际长度
}SString;               // 定长顺序存储

typedef struct {
    char *ch;           // 指向串的基地址
    int length;
}HString;               // 堆分配存储

void StrAssign(SString &T, const char* chars) {
    T.length = 0;
    for (int i = 0; chars[i] != '\0'; i++) {
        T.ch[++T.length] = chars[i];
    }
}

int Index(SString S, SString T) { // 朴素的模式匹配
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length) {
        if (S.ch[i] == T.ch[j]) {   // 对应位相同，则检查下一位
            ++i, ++j;
        } else {                    // 对应位不同，则j回到开头重新检查，i回到已匹配的开头第二个位置重新检查
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T.length) return i - T.length;  // 如果>length，说明S中存在子串T，返回此时i指针匹配起始位置
    return 0;
}

void getNext(SString T, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;            // 初值
    while(i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i, ++j;
            next[i] = j;    // a_i = a_j，同时其前面内容也相等，所以如果在i+1这个位置失败，则下一跳可以跳到j+1上进行匹配
        } else {
            j = next[j];    // 即匹配失败，此时j跳到下一条地址
        }
    }
}

void getNextval(SString T, int nextval[]) { // next数组的优化
    /**
     * 这也就是我们在描述中所写的算法，除了相等的部分外，我们还判断不等的部分的值从而排除更多可能
    */
    int i = 1, j = 0;
    nextval[1] = 0;            // 初值
    while(i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i, ++j;
            if (T.ch[i] != T.ch[j]) nextval[i] = j; // 这个位置不等，则跳到j
            else {
                nextval[i] = nextval[j];            // 这个位置相同，则可以直接等同于如果j失败的下一跳
            }
        } else {
            j = nextval[j];    // 即匹配失败，此时j跳到下一条地址
        }
    }
}

int KMP(SString S, SString T, int next[]) {
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (j == 0 || S.ch[i] == T.ch[j]) { // 匹配成功，继续匹配
            ++i, ++j;
        } else {
            j = next[j];                    // 匹配失败，子串到下一跳，主串不回溯
        }
    }
    if(j > T.length) {
        return i - T.length;
    } else {
        return 0;
    }
}

int main() {
    SString S, T;
    StrAssign(S, "ababcabcacbab");
    StrAssign(T,      "abcac");
    
    int next[MAXLEN];
    getNext(T, next);
    int index = KMP(S, T, next);
    int index2 = Index(S, T);
    printf("Index: %d %d\n", index, index2);
}