#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20      /* �洢�ռ� ��ʼ�������� */

typedef int Status;
typedef int SElemType;      // SElemType ���͸���ʵ���������, �������Ϊ int

// ˫��ջ�洢�ṹ
typedef struct {
    SElemType data[MAXSIZE];
    int top1;       // ջ1 ջ��ָ��
    int top2;       // ջ2 ջ��ָ��
} SqDoubleStack;

Status visit(SElemType c) {
    printf("%d ", c);
    return OK;
}

// ����һ�� ��ջ S
Status InitStack(SqDoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

// �� S ��Ϊ ��ջ
Status ClearStack(SqDoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

// �� ջ S Ϊ��ջ, �򷵻� TRUE ���򷵻�FALSE
Status StackEmpty(SqDoubleStack S) {
    if (S.top1 == -1 && S.top2 == MAXSIZE)
        return TRUE;
    else
        return FALSE;
}

// ���� S ��Ԫ�ظ���, ��  ջ�� ����
int StackLength(SqDoubleStack S) {
    return (S.top1 + 1) + (MAXSIZE - S.top2);
}

// ���� Ԫ�� e Ϊ�µ�ջ��Ԫ��
Status Push(SqDoubleStack *S, SElemType e, int stackNumber) {
    if (S->top1 + 1 == S->top2) {
        printf("ջ����!\n");
        return ERROR;
    }
    if (stackNumber == 1)   // ջ 1 ��Ԫ�ؽ�ջ
        S->data[++S->top1] = e;     // ����ջ1 �� �� top1 + 1 , ��� ����Ԫ�ظ�ֵ
    else if (stackNumber == 2)      // ջ 2 ��Ԫ�ؽ�ջ
        S->data[--S->top2] = e;     // ����ջ2 �� �� top2 - 1, ��� ����Ԫ�ظ�ֵ

    return OK;
}

// �� ջ ����, ��ɾ�� S ��ջ��Ԫ��, �� e ������ֵ, ������ OK. ���򷵻�ERROR
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
    if (stackNumber == 1) {
        if (S->top1 == -1)
            return ERROR;
        // ջ1 �� ���� ���ε���
        *e = S->data[S->top1--];

    } else if (stackNumber == 2) {
        if (S->top2 == MAXSIZE)
            return ERROR;
        // ջ2 �� ���� ���εݼ�
        *e = S->data[S->top2++];
    }
    return OK;
}

Status StackTraverse(SqDoubleStack S) {
    int i;
    i = 0;
    // ���� ջ1
    while (i <= S.top1) {
        visit(S.data[i++]);
    }

    // ���� ջ2
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

    printf("ջ��Ԫ�� ����Ϊ: ");
    StackTraverse(S);

    printf("��ǰ ջ�� Ԫ�� ��: %d ��\n",StackLength(S));

    Pop(&S,&e,1);
    // �� ���� ջ Ϊ 1��ջ ʱ, ֵ Ϊ 5
    // �� ���� ջ Ϊ 2��ջ ʱ, ֵ Ϊ 18
    printf("������ ջ��Ԫ�� e = %d\n",e);

    printf("ջ�ĳ��� : %d\n",StackLength(S));

    // ջ�ĳ��� : 7

    printf("ջ �շ� : %d (1 : ��, 0 : ��Ϊ��)\n",StackEmpty(S));

    // ѹջ ѹ��ȥ Ϊ 6--18
    // ջ��Ԫ������Ϊ : 1 2 3 4 6 7 8 9 10 11 12 13 14 15 16 17 18 18 19 20
    for (j = 6; j <= MAXSIZE -2; ++j) {
        Push(&S,j,1);
    }
    printf("ջ��Ԫ������Ϊ : ");
    StackTraverse(S);

    printf("ջ ���� : %d (1 : ��, 0 : ��)\n",Push(&S,100,1));

    ClearStack(&S);

    printf("���ջ��, ջ�շ� : %d (1 : �� 0 : ��)\n",StackEmpty(S));
    return 0;
}