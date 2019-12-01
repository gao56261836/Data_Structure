#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;     /* Status 是函数的类型, 其值是函数结果状态码 如 OK */
typedef char ELemType;  /* ElemType 类型根据 实际情况 而定, 这里假设为 char */

Status visit(ELemType c){
    printf("%c ",c);
    return OK;
}

// 线性表的 静态链表 存储结构
typedef struct {
    ELemType data;
    int cur;    /* 游标 (Cursor), 为 0 时表示 无指向 */
}Component,StaticLinkedList[MAXSIZE];

// 将一维数组 space 中 各分量 链成一个备用链表, space[0].cur 为头指针, "0" 表示空指针
Status InitList(StaticLinkedList space){
    int i;
    for (i = 0; i < MAXSIZE -1; ++i)
        space[0].cur = i+1;

    space[MAXSIZE-1].cur = 0;   // 目前静态链表为空, 最后一个元素的 cur 为 0
    return OK;
}

// 若备用空间 链表非空, 则返回 分配的结点下标, 否则返回 0
int Malloc_SSL(StaticLinkedList space){
    int i = space[0].cur;       // 当前数组第一个元素 的 cur 存 的值
                                // 就是要返回的第一个 备用空闲的下标

    // 由于要拿出来 一个 分量来使用,  所以我们就得  把它的下一个分量 用来做备用
    if (space[0].cur)
        space[0].cur = space[i].cur;

    return i;
}

// 将 下标 为 k  的空闲结点 回收到备用链表
void Free_SSL(StaticLinkedList space, int k){
    // 把第一个 元素的 cur 值赋值给要删除的分量 cur
    // 把要删除的分量下标 赋值给 第一个元素的 cur
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// 返回L 中数据元素的个数
int ListLength(StaticLinkedList L){
    int j = 0;
    int i = L[MAXSIZE-1].cur;
    while (i){
        i = L[i].cur;
        j++;
    }
    return j;
}

// 在 L 中第 i 个元素之前插入新的数据元素e
Status ListInsert(StaticLinkedList L, int i,ELemType e){

}