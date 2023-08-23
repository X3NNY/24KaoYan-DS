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

// 7.2 作业答案

int BinarySearchRecursion(SSTable ST, ElemType key, int low, int high) {    // 5. 递归折半查找
    /**
     * 和正常一样，如果是中间，直接返回，否则答案在左边或者右边选择返回即可
    */
    if (low > high) {                   // 越界，说明无答案
        return 0;
    }
    int mid = (low + high) / 2;
    if (ST.elem[mid] > key) {           // 说明答案在左半部分
        return BinarySearchRecursion(ST, key, low, mid-1);
    } else if (ST.elem[mid] < key) {    // 说明答案在右半部分
        return BinarySearchRecursion(ST, key, mid+1, high);
    } else {
        return mid;                     // 说明答案就是mid
    }
}

int  SeqSearch(SSTable ST, ElemType key) {  // 6. 找到key后和前驱交换
    for (int i = 0; i < ST.TableLen; i++) {
        if (ST.elem[i] == key) {
            if (i != 0) {                   // 存在前驱
                ElemType tp = ST.elem[i];
                ST.elem[i] = ST.elem[i-1];
                ST.elem[i-1] = tp;
                return i-1;                 // 注意此时返回新位置
            } else {
                return i;
            }
        }
    }
    return -1;                              // 不存在key
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
    printf("%d ", BinarySearchRecursion(ST, 5, 0, 4));
}