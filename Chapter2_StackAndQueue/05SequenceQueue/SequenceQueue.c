#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <io.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20   /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int QElemType;      /* QElemType ���� ����ʵ���������, ������� Ϊ int */


// ѭ�� ���е�˳��洢 �ṹ
typedef struct {
    QElemType data[MAXSIZE];
    int front;      // ͷָ��
    int rear;       // βָ��, �����в���, ָ���βԪ�ص� ��һ��λ��
} SqQueue;

Status visit(QElemType c) {
    printf("%d ", c);
    return OK;
}

// ��ʼ�� һ���ն��� Q
Status InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

// �� Q ��� Ϊ �ն���
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

// �� ���� Q Ϊ�ն���, �򷵻�TRUE, ���򷵻�FALSE
Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

// ���� Q ��Ԫ�ظ���, Ҳ���Ƕ��е� ��ǰ����
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// �� ���в���, ���� e ���� Q �Ķ�ͷԪ��, �� ����OK, ���򷵻�FALSE
Status GetHead(SqQueue Q, QElemType *e) {
    //
    if (Q.front == Q.rear) {
        printf("ѭ����������\n");
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

// �� ����δ��, �� ����Ԫ�� e Ϊ�µ� ��βԪ��
Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        printf("ѭ����������!\n");\
        return ERROR;
    }
    Q->data[Q->rear] = e;       // �� Ԫ�� e
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

// ɾ�� ���� Ԫ��, ������Ϊ��, �򷵻�FALSE, ���򷵻�TRUE
Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        printf("ѭ������Ϊ��!\n");
        return ERROR;
    }
    *e = Q->data[Q->front];     // �� ���� ָ�� ��ֵ�� e
    Q->front = (Q->front + 1) % MAXSIZE;      // front  ָ�� ����� 1λ
    // ������� �� ת�� ����ͷ��
    return OK;
}


// �� ��ͷ�� ��β ���ζ� ����Q �� ÿ��Ԫ�����
Status QueueTraverse(SqQueue Q) {
    int i;
    i = Q.front;
    while ((i + Q.front) != Q.rear) {
        visit(Q.data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}

int main() {
    Status j;
    int i = 0, l;
    QElemType d;
    SqQueue Q;
    InitQueue(&Q);
    printf("��ʼ�����к�, ���пշ�? %u (1 : �� | 0 : ��Ϊ��)\n", QueueEmpty(Q));

    printf("������ ���Ͷ���Ԫ��(������ %d ��, -1 Ϊ��ǰ������: )", MAXSIZE - 1);
    do {
        d = i + 100;
        if (d == -1)
            break;
        i++;
        EnQueue(&Q, d);
    } while (i < MAXSIZE - 1);

    QueueTraverse(Q);
    printf("���г���Ϊ: %d\n", QueueLength(Q));
    printf("����ѭ�����пշ�? %u (1 : �� | 0 : ��Ϊ��)\n", QueueEmpty(Q));

    printf("���� %d �� �ɶ�ͷ ɾ��Ԫ��, ��β����Ԫ��: \n", MAXSIZE);
    // ɾ��֮���ٲ���Ԫ��
    for (l = 1; l <= MAXSIZE; ++l) {
        //  ɾ��Ԫ��
        DeQueue(&Q, &d);
        printf("ɾ����Ԫ���� %d, ��β����Ԫ��: %d \n", d, l + 1000);
        // ��ɾ��Ԫ�� ,�����Ԫ��
        d = l + 1000;
        EnQueue(&Q, d);
    }

    // l = 19
    l = QueueLength(Q);

    printf("���ڶ����е�Ԫ��Ϊ : \n");
    QueueTraverse(Q);

    printf("���� ��β ������ %d ��Ԫ��\n",i+MAXSIZE);
    //printf("=========================");
    //printf("%d ",l);

    if(l -2>0)
        printf("������ ��ͷ ɾ�� %d ��Ԫ��:\n",l-2);

    while (QueueLength(Q)>2){
        DeQueue(&Q,&d);
        printf("ɾ����Ԫ��ֵΪ: %d \n",d);
    }

    j = GetHead(Q,&d);
    if (j)
        printf("���� ��ͷ Ԫ��Ϊ %d \n",d);

    ClearQueue(&Q);
    printf("��� ���� ��, ���пշ�?  %u (1 : �� | 0 : ��Ϊ��)\n",QueueEmpty(Q));

    return 0;
}