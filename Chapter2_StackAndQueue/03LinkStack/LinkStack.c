#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <time.h>


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int SElemType;

// 链栈结构
typedef struct StackNode {
    SElemType data;     // 链栈的数据域
    struct StackNode *next;     // 链栈的 指针域
} StackNode, *LinkStackPtr;

typedef struct {
    LinkStackPtr top;       // 链栈的栈顶指针
    int count;      // 计数器
} LinkStack;

Status visit(SElemType c) {
    printf("%d ", c);
    return OK;
}

// 构造一个 空栈
Status InitStack(LinkStack *S) {
    // 初始化 链栈 头结点
    S->top = (LinkStackPtr) malloc(sizeof(StackNode));
    if (!S->top)
        return ERROR;

    // 栈顶 指针 为空
    S->top = NULL;
    // 计数器 为 0
    S->count = 0;
    return OK;

}

// 把 S 置为空栈
Status ClearStack(LinkStack *S) {
    LinkStackPtr p, q;
    p = S->top;
    while (p) {
        // 先 把 p 赋值 给 q;
        q = p;
        // p 指针后移
        p = p->next;
        // 释放 q 结点
        free(q);
    }
    S->count = 0;
    return OK;
}