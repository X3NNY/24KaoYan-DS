#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType; // 数据类型

typedef struct LNode {  // 定义结点类型
    ElemType data;      // 数据域
    struct LNode *next; // 指针域
}LNode, *LinkList; // 上面的LNode是结构体名字，下面的LNode是这个结构体的别名（一样），LinkList是结构体指针(struct LNode*)的别名，记住typedef出来的东西只是个别名，该是什么还是什么类型


LinkList ListHeadInsert(LinkList &L) { // 头插法，即每次插入到表头
    LNode *s;
    int x;
    L = (LinkList)malloc(sizeof(LNode)); // 分配头结点的空间
    L->next = NULL;
    while(~scanf("%d", &x)) {
        s = (LNode*)malloc(sizeof(LNode)); // 注意前面的类型转换为指针，实质还是个结点，指针只是为了统一操作类型(.和->)
        s->data = x;
        s->next = L->next; // 将这个数据指向头结点的后续即第一个数据结点
        L->next = s; // 头结点指向它，连成一串
    }
    return L;
}

LinkList ListTailInsert(LinkList &L) { // 尾插法，即每次插入到表尾
    LNode *s, *r = L; // r为表尾指针，链表只能从结点开始往下找，没有表尾指针的话就得每次从头找了，初始化时就是头结点
    int x;
    L = (LinkList)malloc(sizeof(LNode)); // 分配头结点的空间, 这里不用担心之前先对r的赋值，L地址并没有改变
    while(~scanf("%d", &x)) {
        s = (LNode*)malloc(sizeof(LNode)); // 注意前面的类型转换为指针，实质还是个结点，指针只是为了统一操作类型(.和->)
        s->data = x;
        r->next = s; // 将表尾的后继指向s
        r = s; // 更新表尾
    }
    r->next = NULL; // 记得尾结点要置为NULL
    return L;
}

LNode *GetElem(LinkList L, int i) { // 按序号查找结点
    if (i < 1) { // 非法判断
        return NULL;
    }

    int j = 1;
    LNode *p = L->next; // 指向第一个数据节点
    while(p != NULL && j < i) { // 往下找，并且判空
        p = p->next;
        j++;
    }
    return p; // 这里俩情况，j=i了，跳出，代表找到了第i位，或者遍历到表尾的NULL指针都还没有找到（即长度<i），则返回NULL
}

LNode *LocateElem(LinkList &L, ElemType e) { // 按值查找结点
    LNode *p = L->next; // 指向第一个数据节点
    while(p != NULL && p->data != e) { // 往下找到data=e的为止，并且判空
        p = p->next;
    }
    return p;
}

bool ListInsertNode(LinkList &L, int i, LNode *e) { // 在第i位插入元素
    /**
     * 获取到第i-1位
     * 将e->next 指向第i-1位的后继
     * 将第i-1位next指向e
    */
    if (i == 1) { // 特判一下第一位插入
        e->next = L->next;
        L->next = e;
        return true;
    }
    LNode *p = GetElem(L, i-1);
    if (p == NULL) { // 第i-1位不存在
        return false;
    }

    e->next = p->next;
    p->next = e;
    return true;
}

bool ListDeleteNode(LinkList &L, int i) { // 删除第i位元素
    /**
     * 获取第i-1位数据
     * 将第i-1位next指向第i位next
     * 
     * 书上还有第二种方法就是无须找i-1位，也就是将i+1位数据覆盖到i位上，i再指向i+2，这样第i位就不存在了
    */
    LNode *p = GetElem(L, i-1);
    if (p == NULL || p->next == NULL) { // 第i-1位或第i位不存在
        return false;
    }
    p->next = p->next->next;
    free(p); // 删除记得free，不然野指针了
    return true;
}

int GetLength(LinkList &L) { // 求表长度
    int i = 0;
    LNode *p = L->next; // 第一个数据结点或NULL
    while(p != NULL) {
        p = p->next;
        i++;
    }
    return i;
}


// 2.3作业单链表代码

void DeleteElemByValueRecursion(LinkList &L, ElemType x) { // 1. 递归删除值为x
    /**
     * 思路就是如果当前结点值为x，则执行删除，并返回DeleteElemByValue(L->next, x);
     * 边界为如果next为NULL则直接返回
    */
    LNode *p;
    if (L == NULL) return;
    if (L->data == x) {
        p = L;
        L = L->next;
        free(L); // 清空当前结点
        DeleteElemByValueRecursion(L, x);
    } else {
        DeleteElemByValueRecursion(L->next, x);
    }
}

void DeleteElemByValue(LinkList &L, ElemType x) { // 2. 删除值为x
    /**
     * 可以复用上面代码，也可以不用递归
    */
    LNode *p = L, *tp;

    while(p != NULL) {
        if (p->next != NULL && p->next->data == x) { // 下一个元素是x
            tp = p->next;
            p->next = p->next->next;
            free(tp);
        }
        p = p->next;
    }
}

void ReverseDisplayList(LinkList &L) { // 3. 反向输出结点值
    /**
     * 递归，输出
    */
    if (L->next != NULL) ReverseDisplayList(L->next);
    printf("%d ", L->data);
}

void DeleteMinElem(LinkList &L) { // 4. 删除带头结点链表中值最小的元素
    LNode *p = L, *mp, *t; // mp记录最小值的前驱
    ElemType min = 0x7fffffff;
    while(p->next != NULL) {
        if (p->next->data < min) {
            min = p->next->data;
            mp = p;
        }
        p = p->next;
    }
    t = mp->next;
    mp->next = mp->next->next;
    free(t);
}

void ReverseList(LinkList &L) { // 5. 逆转带头结点链表，且O(1)空间复杂度
    /**
     * 维护两个滚动变量，不断逆转，
    */
    if (L->next == NULL || L->next->next == NULL) return; // 为空或者只有一个元素直接返回
    LNode *h = L, *p = L->next, *q = L->next->next, *t; // 保存表头指针和游标指针
    p->next = NULL; // 第一个元素变成表尾，记得next赋NULL
    while(p != NULL && q != NULL) { // q为原顺序上p的后继
        t = q->next; // 需要先把下一个保存下来
        q->next = p; // 将q指向前驱，即逆转
        p = q;
        q = t;
    }
    h->next = p; // 将头结点指向新的第一个元素，即原来的表尾
}



void DisplayList(LinkList &L) {
    LNode *p = L->next;
    printf("Head ->");
    while (p != NULL) {
        printf(" %d ->", p->data);
        p = p->next;
    }
    puts(" NULL;");
}

int main() {
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;

    LNode *s1 = (LNode*)malloc(sizeof(LNode));
    s1->data = 3;
    LNode *s2 = (LNode*)malloc(sizeof(LNode));
    s2->data = 2;
    LNode *s3 = (LNode*)malloc(sizeof(LNode));
    s3->data = 3;
    LNode *s4 = (LNode*)malloc(sizeof(LNode));
    s4->data = 4;

    ListInsertNode(L, 1, s1);
    ListInsertNode(L, 2, s2);
    ListInsertNode(L, 3, s3);
    ListInsertNode(L, 4, s4);
    DisplayList(L);

    // DeleteElemByValue(L, 3);
    // ReverseDisplayList(L->next);
    DeleteMinElem(L);
    // ReverseList(L);

    DisplayList(L);
}