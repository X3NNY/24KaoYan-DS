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

BSTNode *BSTSearch(BSTree T, ElemType key) {    // 二叉排序树查找
    while (T != NULL && key != T->data) {       // 非空且值不等，则递归寻找
        if (key < T->data) T = T->lchild;
        else T = T->rchild;
    }
    return T;                                   // 找到相等的结点或为空
}

bool BSTInsert(BSTree &T, ElemType key) {        // 二叉排序树插入
    if (T == NULL) {                            // 为空直接插入
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
        return true;
    } else if (key == T->data) {                // 已存在，插入失败
        return false;
    } else if (key < T->data) {                 // 小于则插入到左子树中
        return BSTInsert(T->lchild, key);
    } else {                                    // 否则插入右子树中
        return BSTInsert(T->rchild, key);
    }
}

void BSTCreate(BSTree &T, ElemType key[], int n) {  // 二叉排序树的构建
    T = NULL;
    for (int i = 0; i < n; i++) {
        BSTInsert(T, key[i]);
    }
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


// 7.3 作业答案

bool IsBST(BSTree T) {      // 6. 判断一棵二叉树是否为BST
    /**
     * 按照定义比较即可，根结点一定大于左子树，小于右子树
    */
    if (!T) return true;    // 空树是BST
    bool lflag = true, rflag = true;
    if (T->lchild) {        // 递归比较左子树
        lflag = (T->data > T->lchild->data) && IsBST(T->lchild);
    }
    if (T->rchild) {        // 递归比较右子树
        rflag = (T->data < T->rchild->data) && IsBST(T->rchild);
    }
    return lflag && rflag;  // 只有根和左右孩子大小关系满足，且左右子树都是BST时为BST
}

int GetLevel(BSTree T, ElemType e) { // 7. 查找结点在BST中的层级
    /**
     * 每比较一次就层级+1
    */
    if (!T) return 0;               // 如果要更严谨点对于不存在BST中的结点返回-1的话，则需要每次递归判断返回值或增加成功标记
    if (T->data == e) {
        return 1;
    } else if (T->data > e) {       // 大了，去左子树中找
        return 1+GetLevel(T->lchild, e);
    } else {                        // 否则去右子树中找
        return 1+GetLevel(T->rchild, e);
    }
}

void GetMinMax(BSTree T, ElemType &min, ElemType &max) { // 9. 返回BST中最小和最大结点
    BSTree r = T;
    while(T->lchild != NULL) {      // 最左边的最小
        T = T->lchild;
    }
    min = T->data;
    
    while(r->rchild != NULL) {      // 最右边的最大
        r = r->rchild;
    }
    max = r->data;
}

void PrintBigger(BSTree T, ElemType k) {    // 10. 从大到小输出BST中大于等于k的值
    /**
     * 按照右根左遍历可以得到从大到小序列，然后每次判断是否大于k即可
    */
    if (!T) return;
    if (T->rchild) PrintBigger(T->rchild, k); // 右
    if (T->data >= k) {                       // 根
        printf("%d ", T->data);
    }
    if (T->lchild) PrintBigger(T->lchild, k); // 左
}

BSTNode* KthSmall(BSTree T, int k) {    // 11. 在BST上查询第k小的元素，
    /**
     * 本题每个结点新增count元素，记录以该结点为根的子树有多少结点。
     * 显然根结点是第m小元素，若其左子树结点即m-1>k，则第k小在左子树中，否则在右子树中
     * 如果在左子树中，则我们去左子树继续寻找第k小。
     * 如果在右子树中，则我们去右子树寻找第k-m小。
    */
    if (k < 1 || k > T->count) return NULL;     // 特判出界
    if (T->lchild == NULL) {                    // 左子树不存在，则无法计算m，此时直接是根结点或去右子树找
        if (k == 1) return T;
        else return KthSmall(T->rchild, k-1);
    } else {
        if (T->lchild->count == k-1) return T;  // 左子树结点有k-1个，则根就是第k个
        else if (T->lchild->count > k-1) {      // 左子树结点大于k-1，则去左子树中继续找
            return KthSmall(T->lchild, k);
        } else {                                // 否则去右子树中找第k-m个，m=左子树结点+1
            return KthSmall(T->rchild, k-(T->lchild->count+1));
        }
    }
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

    BSTree T;
    ElemType key[] = {13,43,12,576,1235,5412,3125,645};
    BSTCreate(T, key, 8);

    // printf("%d ", BinarySearch(ST, 9));
    // printf("%d ", BinarySearchRecursion(ST, 5, 0, 4));
    // puts("no\0yes"+3*IsBST(T));
    // printf("%d", GetLevel(T, 645));
    PrintBigger(T, 1235);
}