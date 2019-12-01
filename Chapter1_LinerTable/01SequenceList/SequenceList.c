#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
/* 存储空间初始化分配量 */
#define MAXSIZE 20

typedef int Status;     // Status 是函数的类型, 其值是函数结果的代码, 如OK 等
typedef int ElemType;   // ElemType 类型根据实际情况而定, 这里假设为int

Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

typedef struct {
    ElemType data[MAXSIZE];     // 数组, 存储数据元素
    int length;         // 线性表的长度
} SqList;


// 初始化顺序线性表
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

// 判空, 若线性表L 存在, 则返回TRUE, 否则返回FALSE
Status ListEmpty(SqList L) {
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

// 清空线性表
Status ClearList(SqList *L) {
    L->length = 0;
    return OK;
}

// 返回线性表长度
int ListLength(SqList L) {
    return L.length;
}


// 按位查找, 用e 返回 L 中第i 个数据元素的值, 注意 i 是指位置, 数组中第 i 个位置是从0 开始
// 为什么获取到ElemType e 的值要用指针类型呢
//  这里利用了 C 语言中的引用传参, C 语言中无法返回2 个值, 其中返回值 OK 默认为 int 类型 的1
// 而 引用传参可以通过指针返回多个值, 避免了 C 语言无法返回多个值的情况
Status GetElem(SqList L, int i, ElemType *e) {
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;
    *e = L.data[i - 1];

    return OK;
}

// 按位查找, 返回 L 中第 1 个与e 相等的元素的位序
// 若这样的元素不存在, 则返回0
int LocateElem(SqList L, ElemType e) {
    int i;
    if (L.length == 0)
        return 0;
    // 对线性表的数组进行遍历, 如果找到数组中第 i 个 与e 相等的值, 则退出循环, 返回 值的位序
    for (i = 0; i < L.length; ++i) {
        if (L.data[i] == e)
            break;
    }
    if (i >= L.length)
        return 0;

    return i + 1;
}

// i 代表元素的位置, 从1 开始, ElemType e 代表要插入的元素的值
// 在L中第 i 个位置之前插入新的数据元素e, L的长度+1
Status ListInsert(SqList *L, int i, ElemType e) {
    int k;
    if (L->length == MAXSIZE) {
        printf("线性表已满\n");
        return ERROR;
    }
    if (i < 1 || i > L->length + 1) {
        // i 比第一个位置小 or i 比最后一个位置还要大
        printf("i值不合法\n");
        return ERROR;
    }

    if (i <= L->length) {
        // 比较难理解, 其实就是 从 L 的最后一个元素开始,
        // 将 i 之后的每一个元素都向后 移动一位, 给 插入的元素空出位置
        for (k = L->length - 1; k >= i - 1; k--)
        {
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i - 1] = e;
    L->length++;

    return OK;
}

// 删除L 的第 i 个元素, 并用e 返回其值, L 的长度 -1
Status ListDelete(SqList *L, int i, ElemType *e) {
    int k;
    if (L->length == 0) {
        printf("线性表为空\n");
        return ERROR;
    }

    if (i < 1 || i > L->length) {
        printf("删除位置不正确!     ");
        return ERROR;
    }

    *e = L->data[i - 1];
    // 如果删除元素不是最后一个位置
    if (i <= L->length) {
        for (k = i; k < L->length; ++k) {   // 将删除元素前移
            // 从 第 i 个位置开始, 将i 之后的每一个元素均向前移动一位
            L->data[k - 1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

// 顺序表L 已存在 . 依次对 L 的每个数据元素输出
/*Status ListTraverse(SqList L){
    for (int i = 0; i < L.length; ++i) {
        visit(L.data[i]);
    }
    printf("\n");
    return OK;
}*/
Status ListTraverse(SqList L) {
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

// 对两个顺序表进行合并
void unionL(SqList *La, SqList Lb) {
    int La_len, Lb_len, i;
    ElemType e;
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    // 为什么 i 是从 1 开始的呢
    // GetElem 这个函数获取数组中的元素时, 是从 位序 开始获取的
    // 第1个元素是data[0]. 依次类推
    // 为什么获取的是指针类型, 因为 GetElem 函数已经有返回值, 只能通过指针来返回
    for (i = 1; i <= Lb_len; ++i) {
        GetElem(Lb, i, &e);
        if (!LocateElem(*La, e))
            ListInsert(La, ++La_len, e);
    }
}

int main() {
    SqList L;
    SqList Lb;

    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("初始化L后: L.length= %d \n", L.length);

    for (j = 1; j <= 5; j++) {
        // 因为总是在第一个位置插入元素, 所以打印时 打印出来是倒序输出
        i = ListInsert(&L,1, j);
    }
    printf("在 L 的表头依次插入1--5后, L.data = ");
    ListTraverse(L);

    printf("L.length = %d \n",L.length);
    i = ListEmpty(L);
    printf("L 是否为空: i = %d(1:是 0:否)\n",i);

    i = ClearList(&L);
    printf("清空 L 后: L.length = %d\n",L.length);
    i = ListEmpty(L);
    printf("L 是否为空: i = %d(1:是 0:否)\n",i);

    for (j = 1; j <=10; ++j) {
        ListInsert(&L,j,j);
    }
    printf("在 L 的表尾依次插入 1--10 后, L.data = ");
    ListTraverse(L);

    printf("L.length = %d \n",L.length);

    ListInsert(&L,1,0);
    printf("在 L 的表头插入0后: L.data = ");
    ListTraverse(L);
    printf("L.length = %d \n",L.length);

    // 因为 L.data[i] 是从0 开始, 所以查找第 5 个元素实际上获取到的是 L.data[4] 的值
    GetElem(L,5,&e);
    printf("第 5 个元素的值为: %d\n",e);
    printf("===========================================\n");

    // 查找元素 , 按位序查找
    for (j = 0; j <=11 ; ++j) {
        k=LocateElem(L,j);
        if (k)
            printf("第 %d 个元素的值为 %d\n",k,j);
        else
            printf("没有值为 %d 的元素\n",j);
    }

    printf("删除前,L.length = %d \n",L.length);
    k = ListLength(L);      // k 为表长
    //printf("%d",k);
    // j = 12 ; j >= 11 ; j--
    for (j = k +1; j >=k ; j--) {
        i = ListDelete(&L,j,&e);
        //printf("%d======\n",i);
        if (i == ERROR)
            printf("删除第 %d 个数据失败\n",j);
        else
            printf("删除第 %d 个的元素值为: %d\n",j,e);
    }
    k=ListLength(L);
    printf("删除后,L.length = %d \n",L.length);

    printf("依次输出顺序表 L 中的元素: L.data = ");
    ListTraverse(L);

    j=5;
    // 删除 第 5 个数据
    ListDelete(&L,j,&e);
    printf("删除第 %d 个的元素值为: %d\n",j,e);

    printf("依次输出顺序表 L 中的元素: L.data = ");
    ListTraverse(L);

    i=InitList(&Lb);
    for (j = 6; j <= 15; ++j) {
        // 若为正序, j 应该从 1 就是开始
        // ListInsert(&Lb,j,j);     此为正序
        i = ListInsert(&Lb,1,j);    // 此为逆序插入 进数组中
    }
    printf("依次输出顺序表 Lb 中的元素: Lb.data = ");
    ListTraverse(Lb);

    unionL(&L,Lb);
    printf("依次输出合并了 Lb 的 L 的元素:");
    ListTraverse(L);

    return 0;
}

