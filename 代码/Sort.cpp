#include "stdafx.h"

void swap(ElemType &a, ElemType &b) {
    ElemType tp = a;
    a = b;
    b = tp;
}

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


void BubbleSort(ElemType A[], int n) {      // 冒泡排序
    for (int i = 0; i < n-1; i++) {         // 共n-1轮
        bool flag = false;                  // 记录该轮是否发生交换
        for (int j = n-1; j > i; j--) {     // 从后往前遍历
            if (A[j-1] > A[j]) {            // 如果前大于后
                int tp = A[j];
                A[j] = A[j-1];
                A[j-1] = tp;
                flag = true;                // 代表有交换发生
            }
        }
        if (flag == false) {                // 该轮无交换，则代表已经全部有序。
            return;
        }
    }
}


void QuickSort(ElemType A[], int low, int high) {   // 快速排序
    if (low < high) {                               // 不为空
        ElemType pivot = A[low];                    // 一般选择第一个元素为枢轴
        int l = low, r = high;
        while (l < r) {                             // 不断从两端逼近
            while (l < r && A[r] >= pivot) r--;     // 从右往左找小于pivot元素的位置
            A[l] = A[r];                            // 移动到左边
            while (l < r && A[l] <= pivot) l++;     // 从左往右找大于pivot元素的位置
            A[r] = A[l];                            // 移动到右边
        }
        A[l] = pivot;                               // 最后 l=r 也就是pivot的位置

        QuickSort(A, low, l-1);              // 对左右部分分别递归
        QuickSort(A, l+1, high);             
    }
}


void SelectSort(ElemType A[], int n) {      // 选择排序
    for (int i = 0; i < n-1; i++) {         // 共n-1轮
        int min = i;
        for (int j = i+1; j < n; j++) {     // 找到最小的元素
            if (A[j] < A[min]) min = j;
        }
        if (min != i) swap(A[i], A[min]);   // i与min位进行交换
    }
}

void HeadAdjust(ElemType A[], int k, int n) {   // 调整以k为根的堆
    /**
     * 思路就是一直往更大的子树走
     * 如果发现更大的子树都小于则跳出，否则则交换。
     * 当前正确性的前提是子树也是一个大根堆，所以BuildMaxHeap是从大往下遍历的
     * 对应树就是从底往上遍历
    */
    A[0] = A[k];                                // 暂存子树根结点
    for (int i = 2*k; i <= n; i *= 2) {         // 一直走向左子树
        if (i < n && A[i] < A[i+1]) {           // 如果兄弟（根的右子树）值要大
            i++;                                // 则走向右子树
        }
        if (A[0] >= A[i]) break;                // 如果 根结点比i大 则跳出
        else {
            A[k] = A[i];                        // 否则说明i更大，则i放入根的位置。
            k = i;
        }
    }
    A[k] = A[0];                                // 将根放回序列中
}

void BuildMaxHeap(ElemType A[], int n) {    // 建立堆
    for (int i = n/2; i > 0; i--) {         // 从n/2~1，不断调整堆
        HeadAdjust(A, i, n);
    }
}

void HeapSort(ElemType A[], int n) {        // 堆排序
    BuildMaxHeap(A, n);
    for (int i = n; i > 1; i--) {           // 从后往前交换
        swap(A[1], A[i]);                   // A[1]是此时堆最大的，放到最后
        HeadAdjust(A, 1, i-1);              // 调整以1为首的堆，重新使得A[1]最大
    }
}

// 8.3 作业

void Bubble2Sort(ElemType A[], int n) {     // 2. 双向冒泡排序
    int l = 0, r = n-1;
    bool flag = true;                       // 记录某轮是否发生交换
    while (l < r && flag) {                 // 双向逼近
        flag = false;
        for (int i = l; i < r; i++) {       // 从前往后
            if (A[i] > A[i+1]) {            // 如果前面大于后面则交换
                swap(A[i], A[i+1]);
                flag = true;
            }
        }
        r--;                                // 此时一定把最大值冒到r位置了，可以r--
        for (int i = r; i > l; i--) {       // 从后往前
            if (A[i] < A[i-1]) {            // 如果后面小于前面则交换
                swap(A[i], A[i-1]);
                flag = true;
            }
        }
        l++;                                // 此时把最小的冒到l位置了，可以l++
    }
}

void QuickMove(ElemType A[], int n) {       // 3. 将所有奇数移动到偶数前
    /**
     * 同理可以利用快排思路
     * 这里相当于一趟划分
    */
    int l = 0, r = l-1;
    while (l < r) {                         // 对区间进行划分
        while (l < r && A[l] % 2 != 0) l++; // 从左往右找偶数
        while (l < r && A[r] % 2 != 1) r--; // 从右往左找奇数
        if (l < r) {                        // 如果偶数在奇数左边则交换
            swap(A[l], A[r]);
        }
        l++, r--;                           // 缩减区间 继续下一轮交换
    }
}

void QuickSort2(ElemType A[], int low, int high) {  // 4. 每次随机选取枢轴的快排
    if (low < high) {                               // 不为空
        int index = low + rand()%(high-low+1);      // 随机选取枢轴
        swap(A[index], A[low]);                     // 还是放到low位置，方便处理
        ElemType pivot = A[low];                    // 这样枢轴还是第一个元素
        int l = low, r = high;
        while (l < r) {                             // 不断从两端逼近
            while (l < r && A[r] >= pivot) r--;     // 从右往左找小于pivot元素的位置
            A[l] = A[r];                            // 移动到左边
            while (l < r && A[l] <= pivot) l++;     // 从左往右找大于pivot元素的位置
            A[r] = A[l];                            // 移动到右边
        }
        A[l] = pivot;                               // 最后 l=r 也就是pivot的位置

        QuickSort(A, low, l-1);                     // 对左右部分分别递归
        QuickSort(A, l+1, high);             
    }
}

ElemType KthElement(ElemType A[], int low, int high, int k) {   // 5. 找到第k小元素
    /**
     * 要求O(n)找到第k小，不能使用排序再返回的方式
     * 但是我们可以利用快排划分的方式，让k-1个比m小的在左边，则k位就是我们要的
    */
    int pivot = A[low];                                         // 第一个作为枢轴
    int ltp = low, htp = high;
    while (low < high) {
        while (low < high && A[high] >= pivot) high--;          // 从右往左找比pivot小的
        A[low] = A[high];                                       // 换到最左边
        while (low < high && A[low] <= pivot) low++;            // 从左往右找比pivot大的
        A[high] = A[low];                                       // 换到最右边
    }
    A[low] = pivot;                                             // 最终l=r就是pivot该放的位置
    if (low == k) {                                             // 如果放在第k位，则pivot就是我们需要的
        return A[low];
    } else if (low > k) {                                       // 如果第k位在左边
        return KthElement(A, ltp, low-1, k);                    // 则去左边部分继续寻找
    } else {
        return KthElement(A, low+1, htp, k);                    // 否则则去右边部分寻找
    }
}

ElemType FlagArrange(ElemType A[], int n) {  // 6. 荷兰国旗问题：将颜色序列按红白蓝顺序排列 O(n)
    /**
     * 利用三指针操作，这里设0，1，2分别为红白蓝。
     * 中间指针为遍历指针，其他指针维护边界，通过不断将中间指针和边界进行交换使得红蓝分别移动到左右两端
     * 这样中间剩下的就是白了。
    */
    int i = 0, j = 0, k = n-1;
    while (j <= k) {
        switch (A[j]) {
        case 0:                         // 如果j是红，则应该放到左边，则交换到i指针位置，同时边界++
            swap(A[i], A[j]);i++,j++;
            break;
        case 1:                         // 如果是白，则放在中间无问题，j++
            j++;break;
        case 2:
            swap(A[j], A[k]); k--;      // 如果是蓝，则应放在后面，边界--
        }
    }
}

ElemType SetSlice(ElemType A[], int n) {    // 7. 划分成块，要求两块长度只差尽量小，两块元素和之差尽量大
    /**
     * 显然我们把小的放一边，大的放另一边即可
     * 这样的话变成了把n/2位放到既定位置，然后小的放左边，大的放右边，也就变成了上面那题的做法
    */
    int low = 0, high = n-1, flag = true;
    while (flag) {
        int ltp = low, htp = high;
        int pivot = A[low];                                 // 第一个作为枢轴
        while (low < high) {
            while (low < high && A[high] >= pivot) high--;  // 从右往左找比pivot小的
            A[low] = A[high];                               // 换到最左边
            while (low < high && A[low] <= pivot) low++;    // 从左往右找比pivot大的
            A[high] = A[low];                               // 换到最右边
        }
        A[low] = pivot;                                     // 最终l=r就是pivot该放的位置
        if (low == n/2) {                                   // 如果放在第n/2位，则划分完成
            flag = false;
        } else if (low > n/2) {                             // 如果n/2位在左边，则去左边找
            low = ltp;
            high = low-1;
        } else {                                            // 否则去右边找
            low = low+1;
            high = htp;
        }
    }

    ElemType s1 = 0, s2 = 0;

    for (int i = 0; i < n/2; i++) s1 += A[i];
    for (int i = n/2; i < n; i++) s2 += A[i];
    return s2-s1;
}

int main() {
    ElemType A[] = {1152,28269,95422,28902,59695,51038,92653,22568,62664,65812,85193,6970,117181,108792,99284,97047,52711,18498,57024,62044};
    int n = 20;
    // InsertSort(A, n);
    // HalfInsertSort(A, n);
    // ShellSort(A, n);
    // BubbleSort(A, n);
    QuickSort(A, 0, n-1);

    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}