#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20      /* 存储空间 初始分配增量 */

typedef int Status;
typedef int SElemType;      // SElemType 类型根据实际情况而定, 这里假设为 int

// 双向栈存储结构
typedef struct {
    SElemType data[MAXSIZE];
    int top1;       // 栈1 栈顶指针
    int top2;       // 栈2 栈顶指针
} SqDoubleStack;

Status visit(SElemType c) {
    printf("%d ", c);
    return OK;
}

// 构造一个 空栈 S
Status InitStack(SqDoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

// 把 S 置为 空栈
Status ClearStack(SqDoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

// 若 栈 S 为空栈, 则返回 TRUE 否则返回FALSE
Status StackEmpty(SqDoubleStack S) {
    if (S.top1 == -1 && S.top2 == MAXSIZE)
        return TRUE;
    else
        return FALSE;
}

// 返回 S 的元素个数, 即  栈的 长度
int StackLength(SqDoubleStack S) {
    return (S.top1 + 1) + (MAXSIZE - S.top2);
}

// 插入 元素 e 为新的栈顶元素
Status Push(SqDoubleStack *S, SElemType e, int stackNumber) {
    if (S->top1 + 1 == S->top2) {
        printf("栈已满!\n");
        return ERROR;
    }
    if (stackNumber == 1)   // 栈 1 有元素进栈
        S->data[++S->top1] = e;     // 若是栈1 则 先 top1 + 1 , 后给 数组元素赋值
    else if (stackNumber == 2)      // 栈 2 有元素进栈
        S->data[--S->top2] = e;     // 若是栈2 则 先 top2 - 1, 后给 数组元素赋值

    return OK;
}

// 若 栈 不空, 则删除 S 的栈顶元素, 用 e 返回其值, 并返回 OK. 否则返回ERROR
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
    if (stackNumber == 1) {
        if (S->top1 == -1)
            return ERROR;
        // 栈1 从 左到右 依次递增
        *e = S->data[S->top1--];

    } else if (stackNumber == 2) {
        if (S->top2 == MAXSIZE)
            return ERROR;
        // 栈2 从 左到右 依次递减
        *e = S->data[S->top2++];
    }
    return OK;
}

Status StackTraverse(SqDoubleStack S) {
    int i;
    i = 0;
    // 遍历 栈1
    while (i <= S.top1) {
        visit(S.data[i++]);
    }

    // 遍历 栈2
    i = S.top2;
    while (i < MAXSIZE) {
        visit(S.data[i++]);
    }

    printf("\n");
    return OK;
}

int main() {
    int j;
    SqDoubleStack S;
    int e;
    if (InitStack(&S) == OK) {
        for (j = 1; j <= 5; j++) {
            Push(&S, j, 1);
        }
        for (j = MAXSIZE; j >= MAXSIZE - 2; j--) {
            Push(&S, j, 2);
        }
    }

    printf("栈中元素 依次为: ");
    StackTraverse(S);

    printf("当前 栈中 元素 有: %d 个\n",StackLength(S));

    Pop(&S,&e,1);
    // 当 弹出 栈 为 1号栈 时, 值 为 5
    // 当 弹出 栈 为 2号栈 时, 值 为 18
    printf("弹出的 栈顶元素 e = %d\n",e);

    printf("栈的长度 : %d\n",StackLength(S));

    // 栈的长度 : 7

    printf("栈 空否 : %d (1 : 空, 0 : 不为空)\n",StackEmpty(S));

    // 压栈 压进去 为 6--18
    // 栈中元素依次为 : 1 2 3 4 6 7 8 9 10 11 12 13 14 15 16 17 18 18 19 20
    for (j = 6; j <= MAXSIZE -2; ++j) {
        Push(&S,j,1);
    }
    printf("栈中元素依次为 : ");
    StackTraverse(S);

    printf("栈 满否 : %d (1 : 否, 0 : 满)\n",Push(&S,100,1));

    ClearStack(&S);

    printf("清空栈后, 栈空否 : %d (1 : 空 0 : 否)\n",StackEmpty(S));
    return 0;
}