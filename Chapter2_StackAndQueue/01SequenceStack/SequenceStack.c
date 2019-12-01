#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int SElemType;      // SElemType 类型根据实际情况而定, 这里假设为 int

// 顺序栈存储结构
typedef struct {
    SElemType data[MAXSIZE];
    int top;        // 用于栈顶指针
} SqStack;

Status visit(SElemType c) {
    printf("%d ", c);
    return OK;
}

// 构造一个空栈S
Status InitStack(SqStack *S) {
    S->top = -1;
    return OK;
}

// 把 S 置为空栈
Status ClearStack(SqStack *S) {
    S->top = -1;
    return OK;
}

// 若 S 为空栈, 则返回TRUE 否则返回FALSE
Status StackEmpty(SqStack S) {
    if (S.top == -1)
        return TRUE;
    else
        return FALSE;
}

// 返回 栈S中元素的个数, 即 ===> 栈的长度
int StackLength(SqStack S) {
    return S.top + 1;
}

// 若栈不空, 则用 e 返回S 的栈顶元素 ,并 返回OK. 否则返回FALSE
Status GetTop(SqStack S, SElemType *e) {
    if (S.top == -1)
        return ERROR;
    else
        *e = S.data[S.top];
    return OK;
}

// 插入 元素 e 为新的栈顶元素
Status Push(SqStack *S, SElemType e) {
    if (S->top == MAXSIZE - 1) {
        printf("栈满\n");
        return ERROR;
    }
    // 入栈指针先 +1, 再送值到栈顶
    S->data[++S->top] = e;
    return OK;
}

// 出栈, 若栈不空, 则删除 S 的栈顶元素, 用 e 返回其值, 并返回OK, 否则返回ERROR
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == -1) {
        printf("栈为空栈!\n");
        return ERROR;
    }

    // 出栈先取栈顶值, 栈顶指针再 -1
    *e = S->data[S->top--];
    return OK;
}

// 从 栈底 到 栈顶 依次对栈中 每一个元素显示
Status StackTraverse(SqStack S) {
    int i;
    i = 0;
    while (i <= S.top) {
        visit(S.data[i++]);
    }
    printf("\n");
    return OK;
}

int main() {
    int j;
    SqStack S;
    int e;
    if (InitStack(&S)==OK){
        for (j = 1; j <= 10; ++j) {
            Push(&S,j);
        }
    }
    printf("栈中元素依次为 : ");
    StackTraverse(S);

    Pop(&S,&e);
    printf("弹出的栈顶元素为 e = %d\n",e);

    /*Pop(&S,&e);
    printf("弹出的栈顶元素为 e = %d\n",e);
    Pop(&S,&e);
    printf("弹出的栈顶元素为 e = %d\n",e);
    Pop(&S,&e);
    printf("弹出的栈顶元素为 e = %d\n",e);*/

    printf("栈空否 : %d (1 : 空, 0 : 不为空)\n",StackEmpty(S));
    GetTop(S,&e);
    printf("栈顶元素 = %d  栈的长度 = %d\n",e,StackLength(S));

    ClearStack(&S);
    printf("清空栈后, 栈空否 : %d (1 : 空, 0 : 不为空)\n",StackEmpty(S));

    return 0;
}


