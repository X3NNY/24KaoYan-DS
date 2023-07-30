#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
ElemType DeleteMinest(SqList &L) { // 1. 删除最小值元素
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

void ReverseList(SqList &L) { // 2. 逆转顺序表
    if (L.length == 0) return;

    for(int i = 0; i < L.length/2; i++) {
        ElemType tmp = L.data[i];
        L.data[i] = L.data[L.length-i-1];
        L.data[L.length-i-1] = tmp;
    }
}

int DeleteListByValue(SqList &L, ElemType x) { // 3. 删除全部为x的元素,返回删除个数
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

int DeleteListBetweenValue(SqList &L, ElemType s, ElemType t) { // 4. 5. 删除值在s与t之间的元素
    /*
        4和5就是小于和小于等于的区别
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

void UniqueList(SqList &L) { // 6. 删除重复元素， 即去重
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

bool MergeSortedList(SqList &a, SqList &b, SqList &c) { // 7. 合并两个有序列表
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

void SwapListLocation(ElemType a[], int m, int n) { // 8. a[m+n] -> a[n+m]
    /* 
        思路：a1,...,am,b1,...,bn -> bn,...,b1,am,...,a1 -> b1,...,bn,a1,...,am
     */
    ReverseList(a, 0, m+n);
    ReverseList(a, 0, n);
    ReverseList(a, n, m+n);
}

void LowerBoundSelectOrInsert(ElemType a[], int length, ElemType x) { // 9. 找到x元素的位置，找不到插入并保持有序，二分法
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

void LeftShiftList(ElemType R[], int n, int p) { // 10. 循环左移
    /**
     * 思想1：第i个元素循环左移后的新位置为(i-p+n)%n
     *        可以用一个新的数组记录，这样时间复杂度O(n), 空间复杂度O(n)
     * 思想2：将数组看成两部分，即X_{0~p-1}和X_{p~n-1}，
     *        这样我们只需把X_{0~p-1}和X_{p~n-1}互换位置即可。
     *        要完成这个算法只需要先全部逆转变成X_{n-1},...,X_0，再分别逆转前(p-n)个元素和后p个元素
     *        时间复杂度O(n), 空间复杂度O(1)
     *          
    */
    // 方法一
    // ElemType RN[n];
    // for(int i = p; i < n; i++) {
    //     RN[i-p] = R[i];
    // }
    // for(int i = 0; i < p; i++) {
    //     RN[i+p] = R[i];
    // }
    // for(int i = 0; i < n; i++) {
    //     R[i] = RN[i];
    // }

    // 方法二：借用之前的逆转函数
    ReverseList(R, 0, n);
    ReverseList(R, 0, n-p);
    ReverseList(R, n-p, n);
}

ElemType SelectMediumValue(ElemType A[], ElemType B[], int n) { // 11. 找到A和B的中位数，等长
    /**
     * 思路1：合并A和B到新数组，并维护有序，这样返回中位数即可
     *        时间复杂度O(n), 空间复杂度O(n)
     * 思路2：中位数就是第n个，维护两个指针从小的开始找即可
     *        时间复杂度O(n), 空间复杂度O(1)
     * 思路3：二分思维，设A,B的中位数分别为a,b，此时有
     *          1. a=b，则合并后a,b在一起，中位数还是a
     *          2. a<b, 则合并后为...a...b..., 显然此时中位数在a，b中间
     *                  即中位数在A_{n/2~n}或B_{0~n/2}中
     *          3. a>b，则合并后为...b...a...,显然此时中位数在b，a中间
     *                  即中位数在A_{0~n/2}或B_{n/2~n}中
     *          此时我们记录两个下标的值，不断缩小范围，直到俩数组都只剩一个元素，此时较小的是中位数。
     *          缩小时还需要保证每次都去掉等长元素,所以需要通过剩余长度判断是否保留中位数.
     *          时间复杂度O(logn), 空间复杂度O(1)
    */

    // 方法一：懒得写了，看之前关于合并有序数组的代码，合并后返回C[n]即可

    // 方法二
    // int indexa = 0,
    //     indexb = 0,
    //     cnt = 0, // cnt代表已经比较了cnt次
    //     mid = 0; // 记录中位数
    
    // while (indexa < n && indexb < n) {
    //     if (A[indexa] < B[indexb]) {
    //         cnt++;
    //         mid = A[indexa++];
    //     } else {
    //         mid = B[indexb++];
    //         cnt++;
    //     }
    //     if(cnt == n) { // 第n个数便是中位数
    //         return mid;
    //     }
    // }
    // // 可能会担心循环跳出了找不到，实际上不可能，因为保证了等长，所以例如B最大的小于A最小的
    // // 那么也将在循环中返回B[n-1]
    // return -1;

    // 方法三
    int al = 0, ar = n-1,
        bl = 0, br = n-1,
        amid, bmid;
    
    while (al < ar && bl < br) {
        amid = (al+ar)/2;
        bmid = (bl+br)/2; // 分别是A,B剩余数组中中位数位置
        if (A[amid] == B[bmid]) { // a=b的情况
            return A[amid];
        } else if (A[amid] < B[bmid]) {
            if ((ar+al)%2 == 0) { // 剩余奇数个元素,需要保留此时中位数
                al = amid;
            } else {
                al = amid+1;
            }
            br = bmid;
        } else {
            if ((br+bl)%2 == 0) { // 剩余奇数个元素,需要保留此时中位数
                bl = bmid;
            } else {
                bl = bmid+1;
            }
            ar = amid;
        }
    }
    return A[al]<B[bl]?A[al]:B[bl]; // 都只剩一个元素的,较小的时中位数
}

ElemType SelectMainValue(ElemType a[], int n) { // 12. 找到出现次数大于n/2的数
    /**
     * 思路1: 找众数, 同时记录出现次数判断是否大于n/2
     *        因为ai < n,可以开个新数组记录每个数的出现次数并维护最大出现次数
     *        时间复杂度O(n),空间复杂度O(n)
     * 思路2: 排序后找次数>n/2,
     *        时间复杂度O(n^2), O(nlogn),空间复杂度O(1)
     * 思路3: 刷过算法的应该是做过这题的, 因为次数大于n/2次, 所以维护一个滚动变量x即可
     *           1. a[i] = x, 次数+1
     *           2. a[i] != x, 次数-1, 若次数=0,则x=a[i]
     *        最后次数>0, 后再检测一遍最后的x是否出现n/2次即可, 否则则直接说明不存在主元
     *        原理: 若存在主元素m, 出现次数超过了一半, 无论位置怎么分布, 遍历时总是有
     *              1. 若此时x=m,能够得到n/2次+1, 其他的-1无法使得次数=0从而更换x.
     *              2. 若此时x!=m,总是能有n/2次使得将次数=0,从而更新x=m.
    */
    // 方法一
    // int map[n], cnt = 0, index = 0;
    // for(int i = 0; i < n; i++) {map[i]=0;} // 注意初始化
    // for(int i = 0; i < n; i++) {
    //     map[a[i]]++;
    //     if (map[a[i]] > cnt) {
    //         cnt = map[a[i]];
    //         index = i;
    //     }
    // }
    // if (cnt > n/2) {
    //     return a[index];
    // }
    // return -1;

    // 方法二
    // 现在不会手搓归并排序了, 懒得写冒泡了... 就不写法二了

    // 方法三
    int x = 0,
        cnt = 0;
    
    for(int i = 0; i < n; i++) {
        if (a[i] == x) {
            cnt++;
        } else {
            if (cnt > 0) cnt--;
            else {
                x = a[i];
                cnt = 1;
            }
        }
    }
    if (cnt > 0) {
        cnt = 0;
        for(int i = 0; i < n; i++) {
            if (a[i] == x) {
                cnt++;
            }
        }
    }
    if (cnt > n/2) {
        return x;
    } else {
        return -1;
    }
}

int SelectMissingInteger(ElemType a[], int n) { // 13. 寻找未出现的最小正整数
    /**
     * 思路1：这类题基本都可以开另外一个标记数组维护是否出现，再遍历找一次未出现即可
     *        时间复杂度O(n),空间复杂度O(n)
     * 思路2：优化都是将空间压缩成一个状态转换的关系，
     *       首先排除一些不能的数，例如非正数，或者大于n的数
     *       即剩下的数处于(0, n]之间，此时一种朴素的思想就是不断的遍历
     *       从1开始找2,...,3是否出现，最后返回做大连续数+1，但是这样遍历次数是未定的
     *       我们可以将此思路换成维护这个连续的数列，显然其中应该满足a[i]=i+1（即1,...,i+1）
     *       设l=0,我们让a[0~l-1]=1,...,l,这样最终l+1就是未出现的最小正整数，
     *       同时我们维护一个右边界。对于维护的a[0~l]，未出现的数x显然小于n-l，因为最大是n+1，已经有l+1个数不可能了，只剩下n+1-l-1=n-l个数了。
     *       我们从l开始遍历
     *       1. 若a[l] = l+1，因为我们已经维护了a[0~l-1]，所以此时我们得到了a[0~l]，l++;
     *       2. 若a[l]非法（<=0, > r）
     *          此时a[l] = a[--r]; 因为此时a[l]不可能是符合条件的值，这个位置是无用的，我们可以将他赋值为一个右边界的值，进行下一轮分析
     *       3. 这里还有一种非法状态，a[a[l]-1] = a[l]
     *          我们有a[0~l-1]=1,...,l, 这里也就是说明a[l]-1如果<=l-1的话，则是已经在连续序列出现过了，所以也是无用位置。
     *       4. 否则交换a[l]和a[a[l]-1]
     *          如果这个数既不能为维护的连续序列+1，也不是非法的值，则说明值在(l+1, r)之间，此时我们不能像非法值一样直接进行丢弃，
     *          但是也要保证循环的进行，所以要和一个有用位置进行交换，在将来可能还会继续检查这个值。
     *          同时这里的有用位置也不是随意选的，如果随意选的话将和朴素的不断遍历无区别，这里我们将a[l]放置在a[a[l]-1]上
     *          这样我们将来遍历到a[a[l]-1]时，就有a[l]=l+1了，即这就是a[l]该待的位置。
     *     
     *      没刷过算法题的话下面这种思路还是比较绕的，其实本质上就是利用程序中可以利用的空间a，将其分段为
     *          连续序列：a[0~l-1]，待检查值: a[l], 右边界：r
     *          这样不断增加l的长度，将非法值丢弃，将可能值放入正确的位置。这样就可以无须额外的空间解决问题。
     *      时间复杂度：显然对于一个正确值我们最多检查两次，错误值直接丢弃，所以是O(n)，空间复杂度：O(1)
    */
    // 方法一
    // int vis[n];
    // memset(vis, 0, sizeof(int)*n);
    // for(int i = 0; i < n; i++) {
    //     if (a[i] >= 1 && a[i] <= n) {
    //         vis[a[i]] = 1;
    //     }
    // }
    // for(int i = 1; i <= n; i++) {
    //     if (vis[i] == 0) {
    //         return i;
    //     }
    // }
    // return n+1;

    // 方法二
    int l = 0, r = n;
    while(l < r) {
        if (a[l] == l+1) {
            l++;
        } else if (a[l] <= l || a[l] > r || a[a[l]-1] == a[l]) {
            a[l] = a[--r];
        } else {
            int tmp = a[l];
            a[l] = a[a[l]-1];
            a[tmp-1] = tmp;  // 注意a[l]已经被改了，下标别写成a[l]-1了
        }
    }
    return l+1;
}

int CalcShortestDistance(int S1[], int S2[], int S3[], int n1, int n2, int n3) { // 14. 寻找最短距离的三元组, 返回最短距离
    /**
     * 思路1：三重循环枚举所有距离，返回最小值。
     * 思路2：显然差的越多距离越大, 考虑维护三个下标值a, b, c，此时d=|a-b|+|b-c|+|c-a|
     *        1. 将a,b,c对应值最小的下标+1，计算新距离d_n（如果是最大的+1，距离只会更大，中间的+1，最好情况也是一个变大一个变小）
     *              d_n < d, 更新距离
     *              otherwise, 不变
     *        正确性分析：只有最小坐标更新，才可能使得离另两个值的距离都变小，所以每次我们都是选取的最小值，这样一次遍历就可以得到最小距离了
     *        时间复杂度O(n)，空间复杂度O(1)
    */
    // 方法一：懒得写
    // int d = 0x7fffffff, dn;
    // for(int i = 0; i < n1; i++)
    //     for(int j = 0; j < n2; j++)
    //         for(int k = 0; k < n3; k++) {
    //             dn =abs(S1[i] - S2[j]) + \
    //                 abs(S2[j] - S3[k]) + \
    //                 abs(S3[k] - S1[i]);
    //             if (dn < d) {
    //                 d = dn;
    //             }
    //         }
    // return d;
    
    // 方法二：
    int a = 0, b = 0, c = 0;
    int d = 0x7fffffff, dn;
    while (a < n1 && b < n2 && c < n3) {
        if (S1[a] <= S2[b] && S1[a] <= S3[c]) { // a对应值最小
            a++;
        } else if (S2[b] <= S1[a] && S2[b] <= S3[c]) {
            b++;
        } else {
            c++;
        }
        dn = abs(S1[a] - S2[b]) + abs(S2[b] - S3[c]) + abs(S3[c] - S1[a]);
        if (dn < d) {
            d = dn;
        }
    }
    return d;
}
/**
 * 总结：后面的真题基本都是一些算法题，说实话我好歹刷过一点算法也不敢保证一次写对，初试手写代码还是朴素算法就好。
 * 
 * 优化的思想无非就是
 * 排除一些不可能满足的值 -> 优化时间
 * 将存储额外状态的空间 -> 利用程序本来的空间，或者将空间变成一种状态转移，动态的更新符合条件的值
 *  
 *  状态转移无非就是：分治的思想，大问题变成小问题、维护一个结构（连续值，堆，有序...）、不断的缩减可能值（二分、双端遍历...）
 *  如果你是从头学起的话，很多都是后面的思想现在看起来困难很正常，可以之后再回来回顾。
*/

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
    ElemType ar[] = {11, 13, 15, 17, 19};
    ElemType br[] = {2, 4, 6, 8, 120};
    ElemType mr[] = {3, 5, 6, 5, 5};
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
    // LowerBoundSelectOrInsert(arr, 8, 0);
    // LeftShiftList(arr, 12, 6);
    // int mid = SelectMediumValue(ar, br, 5);printf("%d\n", mid);
    // int x = SelectMainValue(mr, 5);printf("%d\n", x);
    // int x = SelectMissingInteger(br, 5);printf("%d\n", x);

    // DisplayArr(arr, 12);
    // DisplayList(a);
    return 0;
}