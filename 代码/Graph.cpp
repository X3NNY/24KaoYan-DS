#include "Graph.h"

// 6.2 作业

void Convert(ALGraph &G, int n, int arcs[MaxVertexNum][MaxVertexNum]) { // 4. 邻接表转邻接矩阵
    ArcNode *p;
    for (int i = 0; i < n; i++) {       // 遍历每一个结点
        p = G.vertices[i].first;
        while (p != NULL) {             // 遍历每一条边
            arcs[i][p->adjvex] = 1;
            p = p->next;
        }
    }
}

int MAXV = 10;
int IsExistEl(MGraph G) { // 6. 判断G是否存在EL路径
    /**
     * EL路径：度为奇数的顶点个数=0 or 2时，存在一条包含所有边的路径
     * 其实就是判欧拉回路，并且题干解释已经告诉我们怎么判断了，奇数度的顶点要么0个要么2个。
    */
    int count = 0;                          // 记录度为奇数的顶点个数
    for (int i = 0; i < MAXV; i++) {
        int degree = 0;
        for (int j = 0; j < MAXV; j++) {
            if (G.Edge[i][j]) {
                degree++;
            }
        }
        if (degree % 2 == 1) {              // 如果度为奇数 则计数器+1
            count++;
        }
    }
    if (count == 2 || count == 0) {         // 满足条件，返回1，即存在EL路径
        return 1;
    }
    return 0;
}