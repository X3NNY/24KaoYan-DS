#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType; // 数据类型

typedef struct DNode {  // 定义结点类型
    ElemType data;      // 数据域
    struct DNode *prior, *next; // 指针域
}DNode, *DLinkList;

DNode *GetElem(DLinkList L, int i) { // 按序号查找结点
    if (i < 1) { // 非法判断
        return NULL;
    }

    int j = 1;
    DNode *p = L->next; // 指向第一个数据节点
    while(p != NULL && j < i) { // 往下找，并且判空
        p = p->next;
        j++;
    }
    return p; // 这里俩情况，j=i了，跳出，代表找到了第i位，或者遍历到表尾的NULL指针都还没有找到（即长度<i），则返回NULL
}

bool ListInsertNode(DLinkList &L, int i, DNode *e) { // 在第i位插入元素
    /**
     * 获取到第i-1位
     * 将e->next 指向第i-1位的后继，同时e->prior指向i-1位
     * 将第i-1位next指向e，同时原本第i位的prior指向e
    */
    if (i == 1) { // 特判一下第一位插入
        if (L->next != NULL) L->next->prior = e;
        e->next = L->next;
        L->next = e;
        e->prior = L;
        return true;
    }
    DNode *p = GetElem(L, i-1);
    if (p == NULL) { // 第i-1位不存在
        return false;
    }

    e->next = p->next;
    e->prior = p;

    if (p->next != NULL) p->next->prior = e; // 这句得在前面，即原本的第i位
    p->next = e;
    
    return true;
}

bool ListDeleteNode(DLinkList &L, int i) { // 删除第i位元素
    /**
     * 获取第i位数据
     * 将第i+1位的prior指向第i-1位
     * 将第i-1位的next指向第i+1位
     * 
    */
    DNode *p = GetElem(L, i);
    if (p == NULL) { // 第第i位不存在
        return false;
    }
    if (p->next != NULL) p->next->prior = p->prior; // 后继可能时空，要判断一下
    p->prior->next = p->next;
    free(p); // 删除记得free，不然野指针了
    return true;
}

void DisplayList(DLinkList &L) {
    DNode *p = L->next;
    printf("Head ->");
    while (p != NULL) {
        printf(" %d ->", p->data);
        p = p->next;
    }
    puts(" NULL;");
}

int main() {
    DLinkList L = (DLinkList)malloc(sizeof(DNode));
    L->next = NULL;

    DNode *s = (DNode*)malloc(sizeof(DNode));
    s->data = 3;
    DNode *s2 = (DNode*)malloc(sizeof(DNode));
    s2->data = 23;
    DNode *s3 = (DNode*)malloc(sizeof(DNode));
    s3->data = 4;

    ListInsertNode(L, 1, s);
    ListInsertNode(L, 1, s2);
    ListDeleteNode(L, 2);
    ListInsertNode(L, 2, s3);

    DisplayList(L);
}