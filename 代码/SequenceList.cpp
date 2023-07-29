#include <stdio.h>
#include <stdlib.h>

typedef int ElemType; // 数据类型

#define MaxSize 100
#define InitSize 100

typedef struct {
    ElemType data[MaxSize]; // 静态分配
    // ElemType *data; // 动态分配
    int length;
}SqList;

void InitList(SqList &L) { // 初始化
    // L.data = (ElemType*)malloc(sizeof(ElemType) * InitSize); // 动态分配时需要初始化
    L.length = 0;
}

bool ListInsert(SqList &L, int i, ElemType e) { // 插入到第i位(i>0)
    /*
        BestTime: 表尾插入(i=n+1), O(1)
        WorstTime: 表头插入(i=1), O(n)
        AvrgTime: (n+(n-1)+...+0)/(n+1)  ->  n/2
        -> 平均复杂度: O(n)
     */
    if (i < 1 || i > L.length+1) return false; // 越界判断
    if (L.length >= MaxSize) return false; // 是否还有空闲空间

    for (int j = L.length; j >= i; j--) { // 将第i个元素之后的元素后移
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList &L, int i, ElemType &e) { // 删除并返回第i位
    /*
        BestTime: 表尾删除(i=n), O(1)
        WorstTime: 表头删除(i=1), O(n)
        AvrgTime: ((n-1)+...+0)/n  ->  (n-1)/2
        -> 平均复杂度: O(n)
     */
    if (i < 1 || i > L.length) return false; // 越界判断

    e = L.data[i-1];
    for (int j = i; j < L.length; j++) { // 将第i位后的元素前移
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}

int LocateElem(SqList &L, ElemType e) {
    /*
        BestTime: 查找表头, O(1)
        WorstTime: 查找表尾, O(n)
        AvrgTime: (1+...+n)/n  ->  (n+1)/2
        -> 平均复杂度: O(n)
     */
    for(int i = 0; i < L.length; i++) {
        if(L.data[i] == e) { // 找到第一个为e的数据,返回位置
            return i+1;
        }
    }
    return 0;
}

ElemType GetElem(SqList &L, int i) {
    if (i < 1 || i > L.length) return 0; // 越界判断

    return L.data[i-1];
}

// 以下为题目答案
ElemType DeleteMinest(SqList &L) { // 删除最小值元素
    if (L.length == 0) {
        puts("List is empty");
        exit(0);
    }
    ElemType min = L.data[0];
    int minIndex = 0;
    for(int i = 1; i < L.length; i++) {
        if (L.data[i] < min) {
            min = L.data[i];
            minIndex = i;
        }
    }
    L.data[minIndex] = L.data[L.length--];
    return min;
}

void ReverseList(SqList &L) { // 逆转顺序表
    if (L.length == 0) return;

    for(int i = 0; i < L.length/2; i++) {
        ElemType tmp = L.data[i];
        L.data[i] = L.data[L.length-i-1];
        L.data[L.length-i-1] = tmp;
    }
}

int DeleteListByValue(SqList &L, ElemType x) { // 删除全部为x的元素,返回删除个数
    /*
        空间复杂度O(1)
        这是只用循环的做法，有点双指针思想，不太理解可以看下一题continue做法
    */
    if (L.length == 0) return 0;

    int count = 0, // 记录删除个数
        index = 0; // 记录有效个数(下标)
    for(int i = 0; i < L.length; i++) {
        int j = i;
        while (j < L.length && L.data[j] == x) { // 删除连续的元素
            count++;
            j++;
        }
        if(j < L.length) L.data[index++] = L.data[j]; // 将下一位不是x的元素放入
        i = j; // 下一次从j开始即可
    }
    L.length = index;
    return count;
}

int DeleteListBetweenValue(SqList &L, ElemType s, ElemType t) { // 删除值在s与t之间的元素
    /*
        可以复用上一题思路，不过这里给出另一种使用continue语法的代码
    */
    if (L.length == 0) {
        puts("List is empty");
        exit(0);
    }
    if (s >= t) {
        puts("error: S >= T");
        exit(0);
    }

    int count = 0,
        index = 0;
    for(int i = 0; i < L.length; i++) {
        if (L.data[i] >= s && L.data[i] <= t) {
            count++;
            continue; // 介于之间则跳过下面的赋值处理
        }
        L.data[index++] = L.data[i]; // 有效的元素
    }
    L.length = index;
    return count;
}

void UniqueList(SqList &L) { // 删除重复元素， 即去重
    /* 
        时间复杂度O(n^2)  -> (其他思路，看不懂无须关心：维护个set或者排序的话可以O(nlogn), hash处理的话也可以O(kn))
    */
    int index = 0;
    for(int i = 0; i < L.length; i++) {
        bool flag = true; // 维护标记，看是否之前已经出现这个元素了
        for(int j = 0; j < i; j++) {
            if(L.data[i] == L.data[j]) {
                flag = false;
                break;
            }
        }
        if (flag) L.data[index++] = L.data[i];
    }
    L.length = index;
}

bool MergeSortedList(SqList &a, SqList &b, SqList &c) { // 合并两个有序列表
    /* 
        从小的表头开始，每次判断取a还是b的元素，维护两个指针代表进行到哪里了。
     */
    if (a.length == 0 || b.length == 0) { // 理论上一个为空可以返回另一个，题目没要求严格的判断就随意写了
        return false;
    }
    if (a.length+b.length == 0 > MaxSize) {
        return false;
    }

    int indexa = 0,
        indexb = 0,
        indexc = 0;
    
    while (indexa < a.length && indexb < b.length) {
        if (a.data[indexa] < b.data[indexb]) {
            c.data[indexc++] = a.data[indexa++];
        } else {
            c.data[indexc++] = b.data[indexb++];
        }
    }
    while (indexa < a.length) c.data[indexc++] = a.data[indexa++];  // 这里还要处理剩余的元素，即长度不一致，剩下的直接插入后面即可
    while (indexb < b.length) c.data[indexc++] = b.data[indexb++];
    c.length = indexc; // 记得赋值长度。
    return true;
}


bool ReverseList(ElemType a[], int start, int ends) { // 逆转顺序表[s, e)内元素

    if (start >= ends) return false;

    int mid = (start + ends) / 2;
    for(int i = 0; i < mid-start; i++) { // 书里是闭区间逆转，和这里稍有不同
        ElemType tmp = a[start+i];
        a[start+i] = a[ends-i-1];
        a[ends-i-1] = tmp;
    }
    return true;
}

void SwapListLocation(ElemType a[], int m, int n) { // a[m+n] -> a[n+m]
    /* 
        思路：a1,...,am,b1,...,bn -> bn,...,b1,am,...,a1 -> b1,...,bn,a1,...,am
     */
    ReverseList(a, 0, m+n);
    ReverseList(a, 0, n);
    ReverseList(a, n, m+n);
}

void LowerBoundSelectOrInsert(ElemType a[], int length, ElemType x) { // 找到x元素的位置，找不到插入并保持有序，二分法
    int l = 0, r = length; // 二分上下界

    while (l < r) { // 不断收缩，直到l==r为止，1. l<lengtn, a[l]>=x  2. l==length, 都比x小
        /**
         * 这里不用担心l==length会不会越界，因为当l=mid+1 = length时，l<r就不符合就执行结束了
        */
        int mid = (l+r) / 2;
        if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if(l == length) { // 都比x小
        a[length] = x;
    } else if (a[l] == x) { // a[l] == x
        ElemType t = a[l];
        a[l] = a[l+1];
        a[l+1] = t;
    } else { // a[l] > x
        for(int i = length; i > l; i--) a[i] = a[i-1]; // 后面的后移
        a[l] = x;
    }
}


void DisplayList(SqList L) {
    printf("Length: %d, Data:", L.length);
    for(int i = 1; i <= L.length; i++) {
        printf(" %d", GetElem(L, i));
    }
    puts("");
}
void DisplayArr(ElemType a[], int length) {
    for(int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    puts("");
}

int main() {
    SqList L, a, b, c;
    ElemType arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4};
    // 4, 5, 6, 7, 8, 1, 2, 3, 4
    // 4, 3, 2, 1, 8, 7, 6, 5, 4
    InitList(L);
    InitList(a);
    InitList(b);
    InitList(c);
    ListInsert(a, 1, 1);ListInsert(a, 2, 3);ListInsert(a, 3, 6);ListInsert(a, 4, 12);ListInsert(a, 5, 14);
    ListInsert(b, 1, 2);ListInsert(b, 2, 4);ListInsert(b, 3, 5);ListInsert(b, 4, 13);
    ListInsert(L, 1, 3);
    ListInsert(L, 2, 5);
    ListInsert(L, 3, 3);
    ListInsert(L, 1, 3);
    ListInsert(L, 4, 6);
    ListInsert(L, 5, 6);
    ListInsert(L, 6, 6);
    ListInsert(L, 5, 3);
    ListInsert(L, 5, 3);
    // DisplayList(L);
    
    // ReverseList(a);
    // DeleteListByValue(L, 3);
    // DeleteListBetweenValue(L, 5, 6);
    // UniqueList(L);

    // MergeSortedList(a, b, c);DisplayList(c);
    // SwapListLocation(arr, 3, 9);
    LowerBoundSelectOrInsert(arr, 8, 0);
    
    DisplayArr(arr,9);
    // DisplayList(a);
    return 0;
}