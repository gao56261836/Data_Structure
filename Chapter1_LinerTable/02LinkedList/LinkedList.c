#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

// 存储空间初始分配量
#define MAXSIZE

typedef int Status;     // Status 是函数的原型, 其值是函数结果状态码, 如OK 等
typedef int ElemType;   // ElemType 类型根据实际情况而定, 这里假设为int

// 依次打印
Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

// 节点类型
typedef struct Node {
    ElemType data;      // 数值类型
    struct Node *next;      // 指针类型
} Node;

// 定义LinkedList
typedef struct Node *LinkList;

// 初始化顺序线性表
Status InitList(LinkList *L) {
    // 产生头结点, 并使 L 指向此头结点
    // 即  L 即为 该链表的 头结点
    *L = (Node *) malloc(sizeof(Node));
    if (!(*L))
        // 存储分配失败
        return ERROR;
    // 只有链表的头结点
    (*L)->next = NULL;  // 指针域为空
    return OK;
}

// 判断 线性表为空
Status ListEmpty(LinkList L) {
    if (L->next) {
        // 如果 L->next 此结点存在, 则此 单链表不为空
        return ERROR;
    } else {
        printf("线性表为空表!\n");
        return TRUE;
    }
}

// 将L 重置为空表
Status ClearList(LinkList *L) {
    LinkList p, q;
    p = (*L)->next;     // p 指向 第一个结点
    while (p) {     // 没到表尾
        q = p->next;
        free(p);
        p = q;  // 把 q 的值赋值给 p
    }
    (*L)->next = NULL;      // 再把头结点指针域置空
    return OK;
}

// 返回 单链表L 中数据元素的个数
int ListLength(LinkList L) {
    int i = 0;
    LinkList p = L->next;       // p 指向第一个结点
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

// 用 e 返回 L 中第 i 个数据元素的值
// 即 ====> 按位查找 , 返回其值
Status GetElem(LinkList L, int i, ElemType *e) {
    int j;
    LinkList p;     // 声明一结点 p
    p = L->next;    // p 指向 L 的第一个结点
    j = 1;          // j 为计数器
    while (p && j < i) {
        // p  不为空或者 计数器还没有等于 i  时, 继续循环
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;       // 第 i 个元素不存在

    *e = p->data;       // 取第i 个元素的 数据域
    return OK;
}

// 返回 L 中 第1个 与 e 满足关系的数据元素的位序
// 若这样的数据元素不存在, 则返回值为 0
// 即  ====>  按值查找, 返回其位序
int LocateElem(LinkList L, ElemType e) {
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        if (p->data == e)
            return i;
        p = p->next;
    }
    // 若未找到, 则返回 0
    return 0;
}

// 插入元素: 在 L 中 第 i 个位置之前插入 新的数据元素 e, L 的长度 +1
Status ListInsert(LinkList *L, int i, ElemType e) {
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p && j < i) {
        // 寻找第 i 个结点
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("第 i 个元素不存在");
        return ERROR;
    }
    s = (LinkList) malloc(sizeof(Node));     // 生成新结点
    s->data = e;
    s->next = p->next;      // 把 p 的后继 赋值给 s 的后继
    p->next = s;            // 将s 赋值给 p 的后继

    return OK;
}

// 删除 单链表 L 中 第i 个数据元素, 并用 e 返回其值, L 的长度-1
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i) {
        // 找到第 i 个数据元素
        p = p->next;
        j++;
    }
    // 第 i 个数据元素不存在
    if (!p || j > i) {
        printf("第 i 个数据元素不存在");
        return ERROR;
    }
    // 删除操作
    q = p->next;
    p->next = q->next;      // 将 q 的后继 赋值 给 p的后继
    *e = q->data;       // 将 q 结点中的数据 赋值给 e
    free(q);    // 让系统回收此结点 , 删除q 结点
    return OK;
}

// 单链表 L 已存在
// 依次对单链表 L 中的每个数据元素输出
Status ListTraverse(LinkList L) {
    // L 即为 头结点 , 不需要输出打印
    LinkList p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

// 头插法 , 利用 rand 函数, 随机产生 n 个元素的值
// 建立带头结点的单链表
// 头插法输入的顺序为逆序
void CreateListHead(LinkList *L, int n) {
    LinkList p;
    int i;
    srand(time(0));     // 初始化随机数种子
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;
    for (i = 0; i < n; ++i) {
        p = (LinkList) malloc(sizeof(Node));
        // 随机生成 100 以内的随机数
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p; // 插入到表头
    }
}

// 尾插法, 利用 rand 函数, 随机产生 n 个元素的值
// 尾插法的输入顺序为 正序
void CreateListTail(LinkList *L, int n) {
    LinkList p, r;
    int i;
    srand(time(0));     // 初始化随机数种子
    *L = (LinkList) malloc(sizeof(Node));   // 创建带头结点的单链表
    r = (*L);   // r 为指向尾部的结点
    for (i = 0; i < n; ++i) {
        p = (LinkList) malloc(sizeof(Node));    // 生成新节点
        p->data = rand() % 100 + 1;
        r->next = p;      // 将 表尾终端节点的指针指向新节点
        r = p;    // 将当前的新节点定义为 表尾终端节点
    }
    r->next = NULL;       // 当前链表结束
}

int main() {
    LinkList L;
    ElemType e;
    Status i;
    int j, k;

    //  初始化单链表
    i = InitList(&L);
    printf("初始化单链表 L 后, ListLength(L) = %d\n", ListLength(L));
    /*
        //此代码块为顺序在单链表中插入, 是 ListInsert 函数
       for (j = 1; j < 6; ++j) {
        i = ListInsert(&L,j,j);
        // 打印信息为
        // 在单链表 L 的表头依次插入 1--5 后, L.data = 1 2 3 4 5
    }*/
    for (j = 0; j < 5; ++j) {
        i = ListInsert(&L, 1, j);
    }
    printf("在单链表 L 的表头依次插入 1--5 后, L.data = ");
    ListTraverse(L);

    printf("ListLength(L) = %d \n", ListLength(L));

    // 判断 单链表 L 是否为空
    i = ListEmpty(L);
    printf("=========================\n");
    printf("单链表 L 是否为空 : %d (1 : 是，0 : 否) \n", i);
    // 清空单链表
    printf("=========================\n");
    i = ClearList(&L);
    printf("清空单链表之后============\n");
    printf("清空单链表是否成功 : %d (1 : 是，0 : 否)\n", i);
    printf("清空单链表 L 后, ListLength = %d \n", ListLength(L));

    printf("单链表 L 是否为空 : %d (1 : 是，0 : 否) \n", i);

    for (j = 1; j <= 10; ++j) {
        ListInsert(&L, j, j);
    }
    printf("在单链表 L 的表尾依次插入 1--10 之后: L.data = ");
    ListTraverse(L);

    printf("ListLength(L) = %d \n", ListLength(L));

    // 在 单链表 的表头 插入0 元素
    ListInsert(&L, 1, 0);
    printf("在单链表 L 的表头插入 0 后, L.data = ");
    ListTraverse(L);
    printf("ListLength(L) = %d \n", ListLength(L));

    // 获取 第 5 个元素的值
    GetElem(L, 5, &e);
    printf("第 5 个元素的值为: %d\n", e);
    //printf("======================\n");
    for (j = 3; j <= 4; ++j) {
        /*
            while (p) {
                i++;
                if (p->data == e)
                    return i;
                p = p->next;
    }
         获取到的 返回值 i 即为 该节点在链表中的位置
         k = LocateElem(L,j);
         将 i 赋值给 k
         */
        k = LocateElem(L, j);
        if (k)
            // 获取到的值 是 与 j 相等的值的位置
            // j 的取值 为 3 , 4
            printf("第 %d 个元素的值为: %d\n", k, j);
        else
            printf("没有值为 %d 的元素!\n", j);
    }

    k = ListLength(L);
    printf("ListLength : %d\n",ListLength(L));
    printf("==========\n");
    // for (j = 11; j >= 10; j--) {
    for (j = k; j >= k-1; j--) {
        i = ListDelete(&L,j,&e);
        if (i == ERROR)
            printf("删除第 %d 个数据失败\n",j);
        else
            printf("删除第 %d 个的元素值 为: %d \n",j,e);
    }
    printf("依次输出单链表 L 中的元素: L.data = ");
    ListTraverse(L);
    // ClearList(&L);
    // printf("清空单链表 L 后, 单链表的长度 ListLength = %d\n",ListLength(L));

    i = ListDelete(&L,5,&e);
    printf("删除单链表中第 5 个的元素值为 : %d\n",e);
    printf("依次输出单链表 L 中的元素: L.data = ");
    ListTraverse(L);

    i = ClearList(&L);
    printf("清空是否成功 : %d (1 : 成功 , 0 : 失败),ListLength(L) = %d\n",i,ListLength(L));

    CreateListHead(&L,20);
    printf("整体创建 单链表 L 的元素(头插法), L.data = ");
    ListTraverse(L);
    printf("==========================\n");

    i = ClearList(&L);
    printf("清空是否成功 : %d (1 : 成功 , 0 : 失败),ListLength(L) = %d\n",i,ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建 单链表 L 的元素(尾插法), L.data = ");
    ListTraverse(L);


    return 0;
}


