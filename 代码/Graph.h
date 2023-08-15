#include "stdafx.h"

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {                                // 邻接矩阵法存储图
    VertexType Vex[MaxVertexNum];               // 顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum];  // 邻接矩阵
    int vexnum, arcnum;                         // 顶点数和边数
}MGraph;

typedef struct ArcNode {                        // 边表结点
    int adjvex;                                 // 指向的顶点
    struct ArcNode *next;                       // 下一结点指针
}ArcNode;

typedef struct VNode {                          // 顶点表结点
    VertexType data;                            // 边结点指针
}VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;                           // 邻接表
    int vexnum, arcnum;                         // 图的顶点数和边数
}ALGraph;
