#include "LinkedList.h"

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

void SortedList(LinkList &L) { // 6. 排序
    /**
     * 维护一个有序链表，每次从原链表中插入一个到lowerbound位置
    */
    LNode *p = L->next, *q = L, *tp;
    L->next = NULL; //  此时L就是空链表，p指向原来的元素，不断追加到L上
    while(p != NULL) {
        tp = p->next;
        q = L;
        while(q->next != NULL && q->next->data < p->data) { // 寻找lowerbound位置
            q = q->next;
        }
        p->next = q->next;
        q->next = p; // 新元素插入至有序表
        p = tp; // 继续插入下一个
    }    
}

void DeleteElemBetweenValue(LinkList &L, ElemType s, ElemType e) { // 7. 删除值介于(s, e)之间的元素
    /**
     * 遍历并删除，记住单链表每次都是用前驱判断后继就行
    */
    LNode *p = L, *tp;
    while(p->next != NULL) {
        if (p->next->data > s && p->next->data < e) {
            tp = p->next;
            p->next = p->next->next;
            free(tp);
        } else { // 这里不是每次都到next，因为删除之后结点指向原来的->next->next，相当于已经执行next了
            p = p->next;
        }
    }
}

LinkList SelectCommonNode(LinkList &L1, LinkList &L2) { // 8. 找两个链表的公共结点
    /**
     * 公共结点后的数据都相同，如果是双链表，可以从尾部开始找起看何时不同
     * 可以考虑先遍历到尾结点看是否相同判断是否有公共结点，若有则从等长的地方开始同步遍历至结点相等即可
     * （结点判断不是判断值，直接比较指针即可，记得指针本质就是个地址就行，东西相同地址相同则指针相同，充要）
    */
    LNode *p1 = L1, *p2 = L2;
    int len1 = 0, len2 = 0, d; // 记录长度
    
    while(p1->next != NULL) {
        p1 = p1->next;
        len1++;
    }
    while(p2->next != NULL) {
        p2 = p2->next;
        len2++;
    }

    if (p1 != p2) { // 尾结点不同
        return NULL;
    } else if (len1 > len2) { // L1比L2，长要先走这部分差值到等长部分
        d = len1 - len2;
        p1 = L1->next;p2 = L2->next;
        while (d--){
            p1 = p1->next;
        }
        
    } else if (len2 > len1) { // L2比L1，长要先走这部分差值到等长部分
        d = len2 - len1;
        p1 = L1->next;p2 = L2->next;
        while (d--){
            p2 = p2->next;
        }
    }

    while(p1 != NULL && p2 != NULL) {
        if (p1 == p2) { // 相等时返回
            return p1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return NULL;
}

void SortedDisplayAndDestroy(LinkList &L) { // 9. 有序输出并销毁链表
    /**
     * 可以先用之前的排序函数排好序，再依次打印并free
     * 也可以每次找最小的直接打印 free掉
    */
    LNode *p, *q, *tp;
    ElemType min = 0x7fffffff;
    while (L->next != NULL) {
        p = L;
        min = 0x7fffffff;
        while (p->next != NULL) { // 枚举前驱，比较后继
            if (p->next->data < min) {
                min = p->next->data;
                q = p;
            }
            p = p->next;
        }
        tp = q->next;
        q->next = q->next->next;
        printf("%d ", tp->data);
        free(tp); // 打印并删除最小值
    }
    free(L);
}

void SplitList(LinkList &L, LinkList &O, LinkList &E) { // 10. 拆成两个带头结点的链表，分别保留奇数号和偶数号元素
    LNode *p = L->next, *o = O, *e = E, *tp;
    int cnt = 1;
    O->next = E->next = NULL;
    while(p != NULL) {
        tp = p->next;
        if (cnt % 2 == 1) { // 奇数号
            p->next = o->next;
            o->next = p;
            o = o->next;
        } else { // 偶数号
            p->next = e->next;
            e->next = p;
            e = e->next;
        }
        cnt++;
        p = tp;
    }
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
    LinkList L, O, E;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    O = (LinkList)malloc(sizeof(LNode));
    O->next = NULL;
    E = (LinkList)malloc(sizeof(LNode));
    E->next = NULL;

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
    // DeleteMinElem(L);
    // ReverseList(L);
    // SortedList(L);
    // DeleteElemBetweenValue(L, 3, 5);
    // SortedDisplayAndDestroy(L);
    SplitList(L, O, E);

    // DisplayList(L);
    DisplayList(O);
    DisplayList(E);
}