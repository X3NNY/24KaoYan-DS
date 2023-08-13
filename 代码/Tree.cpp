#include "Tree.h"

// 5.4 作业

int CountLeafNode(CSTree T) {   // 4. 求孩子兄弟法存储的森林的叶结点数
    /**
     * 第i棵树：若左子树空，说明无孩子，则为叶结点
     * 全部：第1棵+右子树叶结点数（兄弟树）
    */
    if (!T) return 0;
    if (T->firstchid == NULL) {
        return CountLeafNode(T->nextsibling)+1;
    }
    return CountLeafNode(T->firstchid)+CountLeafNode(T->nextsibling);
}

int max(int a, int b) { return a<b?b:a; }

int GetHeight(CSTree T) {   // 5. 求孩子兄弟法树的深度
    /**
     * 对于任意子树根结点来说，深度为max(1+孩子深度，兄弟深度)
    */
    if (!T) return 0;
    return max(GetHeight(T->firstchid)+1, GetHeight(T->nextsibling));
}

CSTree CreateTreeByDegree(ElemType a[], int degree[], int n) {  // 6. 已知层次遍历和每个结点度，返回孩子兄弟法表示的树
    CSNode* nodes[n];
    for (int i = 0; i < n; i++) {   // 初始化n个结点
        nodes[i] = (CSNode*)malloc(sizeof(CSNode));
        nodes[i]->data = a[i];
        nodes[i]->firstchid = nodes[i]->nextsibling = NULL;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i]) {                            // 如果第i个结点度不为0，说明有孩子
            k++;                                    // 孩子位置
            nodes[i]->firstchid = nodes[k];         // 左子树为第一个孩子
            for (int j = 2; j <= degree[i]; j++) {  // 从第2个孩子开始
                k++;
                nodes[k-1]->nextsibling = nodes[k]; // 上一个孩子的右指针指向这个兄弟
            }
        }
    }
    return nodes[0];
}

int main() {
    CSTree T = (CSNode*)malloc(sizeof(CSNode));

    T->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->nextsibling = (CSNode*)malloc(sizeof(CSNode));

    T->firstchid->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->firstchid->nextsibling = (CSNode*)malloc(sizeof(CSNode));

    T->firstchid->firstchid->firstchid = NULL;
    T->firstchid->firstchid->nextsibling = NULL;

    T->firstchid->nextsibling->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->firstchid->nextsibling->nextsibling = NULL;

    T->firstchid->nextsibling->firstchid->firstchid = NULL;
    T->firstchid->nextsibling->firstchid->nextsibling = NULL;

    T->nextsibling->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->nextsibling->nextsibling = (CSNode*)malloc(sizeof(CSNode));

    T->nextsibling->firstchid->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->nextsibling->firstchid->nextsibling = NULL;

    T->nextsibling->firstchid->firstchid->firstchid = NULL;
    T->nextsibling->firstchid->firstchid->nextsibling = (CSNode*)malloc(sizeof(CSNode));
    T->nextsibling->firstchid->firstchid->nextsibling->firstchid = NULL;
    T->nextsibling->firstchid->firstchid->nextsibling->nextsibling = NULL;

    T->nextsibling->nextsibling->firstchid = NULL;
    T->nextsibling->nextsibling->nextsibling = (CSNode*)malloc(sizeof(CSNode));

    T->nextsibling->nextsibling->nextsibling->firstchid = (CSNode*)malloc(sizeof(CSNode));
    T->nextsibling->nextsibling->nextsibling->nextsibling = NULL;

    T->nextsibling->nextsibling->nextsibling->firstchid->firstchid = NULL;
    T->nextsibling->nextsibling->nextsibling->firstchid->nextsibling = (CSNode*)malloc(sizeof(CSNode));

    T->nextsibling->nextsibling->nextsibling->firstchid->nextsibling->firstchid = NULL;
    T->nextsibling->nextsibling->nextsibling->firstchid->nextsibling->nextsibling = NULL;

    // printf("%d\n", CountLeafNode(T));
    // printf("%d\n", GetHeight(T));
    ElemType a[] = {1, 2, 3, 4, 5};int degree[] = {2, 1, 1, 0, 0};
    CSTree T1 = CreateTreeByDegree(a, degree, 5);
}