#include "stdafx.h"

void InsertSort(ElemType A[], int n) {              // 直接插入排序
    int j;
    ElemType tp;
    for (int i = 1; i < n; i++) {                   // 遍历每个位置
        tp = A[i];
        for (j = i-1; j >= 0 && tp < A[j]; j--) {   // 寻找插入位置并后移其他元素
            A[j+1] = A[j];
        }
        A[j+1] = tp;                                // 复制到插入位置
    }
}

void HalfInsertSort(ElemType A[], int n) {      // 折半插入排序
    int l, r, mid;
    ElemType tp;
    for (int i = 1; i < n; i++) {               // 遍历每个位置
        l = 0, r = i-1, tp = A[i];
        while (l <= r) {                        // 二分寻找插入位置
            mid = (l + r) / 2;
            if (A[mid] > tp) r = mid - 1;
            else l = mid + 1;
        }                                       // 此时r就是第一个小于tp的值，即A[r]<tp<A[r+1]
        for (int  j = i-1; j >= r+1; j--) {     // 把r+1到i-1的元素全部后移一位
            A[j+1] = A[j];
        }
        A[r+1] = tp;                            // 复制到插入位置
    }
}

void ShellSort(ElemType A[], int n) {                            // 希尔排序
    int j;
    ElemType tp;
    for (int dk = n/2; dk >= 1; dk /= 2) {                       // 不断减小缩量，最终会缩小成1，也就变成直接插入排序
        for (int i = dk; i < n; i++) {                           // 遍历序列
            if (A[i] < A[i-dk]) {                                // 代表需要进行交换和移动
                tp = A[i];
                for (j = i - dk; j >= 0 && tp < A[j]; j -= dk) { // 直接插入法寻找插入位置并移动，
                    A[j+dk] = A[j];
                }
                A[j+dk] = tp;                                    // 复制到插入位置
            }
        }
    }
}

int main() {
    ElemType A[] = {1152,28269,95422,28902,59695,51038,92653,22568,62664,65812,85193,6970,117181,108792,99284,97047,52711,18498,57024,62044};
    int n = 20;
    // InsertSort(A, n);
    // HalfInsertSort(A, n);
    ShellSort(A, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}