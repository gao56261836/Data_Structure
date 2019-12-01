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
typedef int SElemType;      // SElemType ���͸���ʵ���������, �������Ϊ int

// ˳��ջ�洢�ṹ
typedef struct {
    SElemType data[MAXSIZE];
    int top;        // ����ջ��ָ��
} SqStack;

Status visit(SElemType c) {
    printf("%d ", c);
    return OK;
}

// ����һ����ջS
Status InitStack(SqStack *S) {
    S->top = -1;
    return OK;
}

// �� S ��Ϊ��ջ
Status ClearStack(SqStack *S) {
    S->top = -1;
    return OK;
}

// �� S Ϊ��ջ, �򷵻�TRUE ���򷵻�FALSE
Status StackEmpty(SqStack S) {
    if (S.top == -1)
        return TRUE;
    else
        return FALSE;
}

// ���� ջS��Ԫ�صĸ���, �� ===> ջ�ĳ���
int StackLength(SqStack S) {
    return S.top + 1;
}

// ��ջ����, ���� e ����S ��ջ��Ԫ�� ,�� ����OK. ���򷵻�FALSE
Status GetTop(SqStack S, SElemType *e) {
    if (S.top == -1)
        return ERROR;
    else
        *e = S.data[S.top];
    return OK;
}

// ���� Ԫ�� e Ϊ�µ�ջ��Ԫ��
Status Push(SqStack *S, SElemType e) {
    if (S->top == MAXSIZE - 1) {
        printf("ջ��\n");
        return ERROR;
    }
    // ��ջָ���� +1, ����ֵ��ջ��
    S->data[++S->top] = e;
    return OK;
}

// ��ջ, ��ջ����, ��ɾ�� S ��ջ��Ԫ��, �� e ������ֵ, ������OK, ���򷵻�ERROR
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == -1) {
        printf("ջΪ��ջ!\n");
        return ERROR;
    }

    // ��ջ��ȡջ��ֵ, ջ��ָ���� -1
    *e = S->data[S->top--];
    return OK;
}

// �� ջ�� �� ջ�� ���ζ�ջ�� ÿһ��Ԫ����ʾ
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
    printf("ջ��Ԫ������Ϊ : ");
    StackTraverse(S);

    Pop(&S,&e);
    printf("������ջ��Ԫ��Ϊ e = %d\n",e);

    /*Pop(&S,&e);
    printf("������ջ��Ԫ��Ϊ e = %d\n",e);
    Pop(&S,&e);
    printf("������ջ��Ԫ��Ϊ e = %d\n",e);
    Pop(&S,&e);
    printf("������ջ��Ԫ��Ϊ e = %d\n",e);*/

    printf("ջ�շ� : %d (1 : ��, 0 : ��Ϊ��)\n",StackEmpty(S));
    GetTop(S,&e);
    printf("ջ��Ԫ�� = %d  ջ�ĳ��� = %d\n",e,StackLength(S));

    ClearStack(&S);
    printf("���ջ��, ջ�շ� : %d (1 : ��, 0 : ��Ϊ��)\n",StackEmpty(S));

    return 0;
}


