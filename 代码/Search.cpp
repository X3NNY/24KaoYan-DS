#include "Search.h"

int SearchSeq(SSTable ST, ElemType key) { // 顺序查找
    ST.elem[0] = key;                     // 哨兵，目的是为了不用处理越界情况
    int i;
    for (i = ST.TableLen; ST.elem[i] != key; i--);
    return i;
}

int BinarySearch(SSTable ST, ElemType key) {    // 二分查找
    int l = 0, r = ST.TableLen-1, mid;          // 左右边界
    while (l < r) {
        mid = (l + r) / 2;
        if (ST.elem[mid] < key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return ST.elem[l] == key ? l : -1;          // 这里不用担心返回l还是r还是mid，跳出时候三者值相等                     
}

int main() {
    SSTable ST;
    ST.elem = new ElemType[20];
    ST.elem[0] = 1;
    ST.elem[1] = 3;
    ST.elem[2] = 5;
    ST.elem[3] = 7;
    ST.elem[4] = 9;
    ST.TableLen = 5;

    printf("%d ", BinarySearch(ST, 9));
}