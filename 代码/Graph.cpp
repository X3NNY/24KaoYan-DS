#include "Graph.h"
#include "Queue.h"
#include "Stack.h"

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

int FirstNeighbor(ALGraph G, int v) {
    if (G.vertices[v].first == NULL) {
        return -1;
    }
    return G.vertices[v].first->adjvex;
}

int NextNeighbor(ALGraph G, int v, int w) {
    ArcNode *p = G.vertices[v].first;
    while (p != NULL) {
        if (p->adjvex == w) {
            return p->next == NULL ? -1 : p->next->adjvex;
        }
        p = p->next;
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


// 6.3 作业

void DFS(MGraph G, int v, int pre, bool &flag) {    // 记录上一结点的dfs
    visited[v] = true;                                                       // 标记为已访问
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {   // 遍历邻接点
        if (w == pre) continue;
        if (!visited[w]) {                                                   // 如果未被访问
            DFS(G, w, v, flag);                                              // 往下访问
        } else {                                                             // 成环了说明不是树
            flag = false;
        }
    }
}

void DFS(MGraph G, int v, int &vnum, int &edgenum) {
    vnum++;                 // 点数+1
    visited[v] = true;                                                       // 标记为已访问
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {   // 遍历邻接点
        edgenum++;          // 边数+1
        if (!visited[w]) {                                                   // 如果未被访问
            DFS(G, w, vnum, edgenum);                                        // 往下访问
        }
    }
}

bool IsTree(MGraph G) {     // 2. 判断无向图是否是一棵树
    /**
     * 思路一：树从任意顶点发起遍历依然满足树的性质
     *      所以结点的邻接只能是上一结点或未访问结点，
     *      否则说明有环
     * 思路二：树是连通的，且只有n-1条边
    */
    // 思路一
    // for (int i = 0; i < G.vexnum; i++) {
    //     visited[i] = false;
    // }
    // bool flag = true;
    // DFS(G, 0, -1, flag);
    // if (!flag) {
    //     return false;
    // }
    // for (int i = 0; i < G.vexnum; i++) {
    //     if (!visited[i]) {                  // 如果还有结点没被访问说明也不行
    //         return false;
    //     }
    // }

    // 思路二
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    int vnum = 0, edgenum = 0;
    DFS(G, 0, vnum, edgenum);
    if (vnum == G.vexnum && edgenum == 2*(G.vexnum-1)) {    // 乘2是因为每条边会计算两次，a->b, b->a
        return true;
    }
    return false;
}

void DFSNoRecursion(ALGraph G, ElemType v) {     // 3. 实现邻接表存储的图的非递归DFS
    SqStack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    Push(S, v);                             // 遍历起点
    visited[v] = true;
    while(!StackEmpty(S)) {
        Pop(S, v);
        visit(v);
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                Push(S, w);
                visited[w] = true;
            }
        }
    }
}

void DFS(ALGraph G, int i, int j, bool &flag) {
    if (i == j) {                                   // 如果遍历到j了， 说明能走通
        flag = true;
        return;
    }
    visited[i] = true;
    for (int w = FirstNeighbor(G, i); w >= 0; w = NextNeighbor(G, i, w)) {
        if (!visited[w] && !flag) {
            DFS(G, w, j, flag);
        }
    }
}

void BFS(ALGraph G, int i, int j, int &flag) {
    InitQueue(Q);
    EnQueue(Q, i);
    ElemType u;
    while(!isEmpty(Q)) {
        DeQueue(Q, u);
        visited[u] = true;
        if (u == j) {           // 遍历到j了
            flag = true;
            return;
        }
        for (int w = FirstNeighbor(G, i); w >= 0; w = NextNeighbor(G, i, w)) {
            if (!visited[w]) {
                EnQueue(Q, w);
                visited[w] = true;
            }
        }
    }
}

bool IsConnected(ALGraph G, int i, int j) {     // 4. 判断i和j之间的连通性
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    bool flag = false;
    DFS(G, i, j, flag);
    // BFS(G, i, j, flag);
    return flag;
}

void FindPath(ALGraph G, int i, int j, int path[], int d) {     // 5. 找到i到j的所有简单路径
    int w;
    path[++d] = i;                      // 代表从上一个点走过来
    visited[i] = true;
    if (i == j) {                       // 走到目标点，打印保存的路径
        for (int k = 0; k <= d; k++) {
            printf("%d ", path[k]);
        }
        puts("");
    }
    ArcNode *p = G.vertices[i].first;
    while (p != NULL) {
        w = p->adjvex;
        if (!visited[w]) {
            FindPath(G, w, j, path, d); // 继续遍历其他邻接点
        }
        p = p->next;
    }
    visited[i] = false;                 // 设置为可访问，因为还存在其他路径也使用这个顶点
}

int main() {
    MGraph G;
    G.vexnum = 7;
    G.Edge[0][2] = G.Edge[0][3] = G.Edge[1][4] = 
    G.Edge[2][4] = G.Edge[2][5] = G.Edge[3][6] = 
    G.Edge[4][6] = G.Edge[5][3] = G.Edge[5][6] = G.Edge[6][1] = 1;
    G.Edge[2][0] = G.Edge[3][0] = G.Edge[4][1] = 
    G.Edge[4][2] = G.Edge[5][2] = G.Edge[6][3] = 
    G.Edge[6][4] = G.Edge[3][5] = G.Edge[6][5] = G.Edge[1][6] = 1;

    ALGraph AG;
    AG.vexnum = 7;
    AG.vertices[0].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[0].first->adjvex = 2;
    AG.vertices[0].first->next = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[0].first->next->adjvex = 3;
    AG.vertices[0].first->next->next = NULL;
    AG.vertices[1].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[1].first->adjvex = 4;
    AG.vertices[1].first->next = NULL;
    AG.vertices[2].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[2].first->adjvex = 4;
    AG.vertices[2].first->next = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[2].first->next->adjvex = 5;
    AG.vertices[2].first->next->next = NULL;
    AG.vertices[3].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[3].first->adjvex = 6;
    AG.vertices[3].first->next = NULL;
    AG.vertices[4].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[4].first->adjvex = 6;
    AG.vertices[4].first->next = NULL;
    AG.vertices[5].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[5].first->adjvex = 3;
    AG.vertices[5].first->next = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[5].first->next->adjvex = 6;
    AG.vertices[5].first->next->next = NULL;
    AG.vertices[6].first = (ArcNode*)malloc(sizeof(ArcNode));
    AG.vertices[6].first->adjvex = 1;
    AG.vertices[6].first->next = NULL;

    

    // BFSTraverse(G);
    // BFSMinDistance(G, 0);

    // DFSTraverse(G);
    // puts("no\0yes"+3*IsTree(G));
    // DFSNoRecursion(AG, 0);
    int path[10];
    FindPath(AG, 0, 6, path, -1);
}