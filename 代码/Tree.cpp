#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType; // 数据类型
#define MAXLEN 256

typedef struct {
    ElemType data[MAXLEN];
}SqTree;

typedef struct BiTNode {                // 链式存储
    ElemType data;                      // 数据域
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
}BiTNode, *BiTree;

// 5.1 作业

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
}