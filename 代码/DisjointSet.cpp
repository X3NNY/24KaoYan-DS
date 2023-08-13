#include "stdafx.h"
#include "Tree.h"

/**
 * 用数组存储树，方便操作
 * 第i个结点同时代表元素i
 * 结点值代表双亲位置，-1代表无双亲（自己就是根）
*/

void Initial(SqTree T) { // 初始化
    for (int i = 0; i < MAXLEN; i++) {
        T.data[i] = -1;
    }
}

int Find(SqTree T, int x) { // 寻找
    while(T.data[x] >= 0) x = T.data[x];    // 找到最上面的根
    return x;
}

void Union(SqTree T, int R1, int R2) {  // 合并，R1，R2是根结点
    if (R1 == R2) return;   // 如果相等，无须操作
    T.data[R2] = R1;        // 让R2的双亲为R1
}

void Merge(SqTree T, int x, int y) {    // 合并元素x，y所在集合
    T.data[Find(T, y)] = Find(T, x);   // 让集合y的根结点的双亲为x集合的根结点
}


int main() {
    SqTree T;
}