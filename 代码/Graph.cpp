#include "Graph.h"
#include "Queue.h"

int FirstNeighbor(MGraph G, int v) {    // 返回顶点v的第一个邻接顶点，没有返回-1
    for (int i = 0; i < G.vexnum; i++) {
        if (G.Edge[v][i]) {
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G, int v, int w) {  // 返回顶点v除w外的下一个邻接顶点，没有返回-1
    for (int i = w+1; i < G.vexnum; i++) {
        if (G.Edge[v][i]) {
            return i;
        }
    }
    return -1;
}

SqQueue Q;
bool visited[MaxVertexNum];

void BFS(MGraph G, ElemType v) {                                                // 代表从顶点v出发
    visit(v);
    visited[v] = true;                                                          // 注意初始结点要先记录为已访问
    EnQueue(Q, v);
    while (!isEmpty(Q)) {
        DeQueue(Q, v);                                                          // 顶点v出队
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {  // 遍历v的邻边
            if (!visited[w]) {                                                  // 如果没有被访问过
                visit(w);
                visited[w] = true;                                              // 记录为已访问
                EnQueue(Q, w);                                                  // 入队，后续将会遍历w的邻边
            }
        }
    }
}

void BFSTraverse(MGraph G) {
    for (int i = 0; i < G.vexnum; i++) {        // 初始化
        visited[i] = false;
    }
    InitQueue(Q);
    for (int i = 0; i < G.vexnum; i++) {        // 从每个顶点开始，因为图不一定连通
        if (!visited[i]) {                      // 如果未被访问
            BFS(G, i);                          // 则BFS
        }
    }
}

void BFSMinDistance(MGraph G, ElemType u) {         // BFS寻找单源最短路
    int d[MaxVertexNum];                            // 代表从u到每个顶点的路径长度
    for (int i = 0; i < G.vexnum; ++i) {
        d[i] = 0x7fffffff;                          // 初始化路径
    }
    for (int i = 0; i < G.vexnum; i++) {            // 初始化
        visited[i] = false;
    }
    InitQueue(Q);
    visited[u] = true;
    d[u] = 0;
    EnQueue(Q, u);
    while(!isEmpty(Q)) {
        DeQueue(Q, u);
        for(int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]) {
                visited[w] = true;
                d[w] = d[u]+1;              // 因为w是u的邻接顶点，所以到w的距离等于到u的距离+1
                EnQueue(Q, w);
            }
        }
    }
    
    for (int i = 0; i < G.vexnum; i++) {
        printf("%d ", d[i]);
    }
}

void DFS(MGraph G, int v) {
    visit(v);
    visited[v] = true;                                                       // 标记为已访问
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {   // 遍历邻接点
        if (!visited[w]) {                                                   // 如果未被访问
            DFS(G, w);                                                       // 往下访问
        }
    }
}

void DFSTraverse(MGraph G) {
    for (int i = 0; i < G.vexnum; i++) {        // 初始化
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; i++) {        // 从每个顶点开始，因为图不一定连通
        if (!visited[i]) {                      // 如果未被访问
            DFS(G, i);                          // 则BFS
        }
    }
}

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


int main() {
    MGraph G;
    G.vexnum = 7;
    G.Edge[0][2] = G.Edge[0][3] = G.Edge[1][4] = 
    G.Edge[2][4] = G.Edge[2][5] = G.Edge[3][6] = 
    G.Edge[4][6] = G.Edge[5][3] = G.Edge[5][6] = G.Edge[6][1] = 1;

    // BFSTraverse(G);
    // BFSMinDistance(G, 0);

    DFSTraverse(G);
}