#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20      /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int QElemType;

typedef struct QNode {       // ������ �� �ڵ�ṹ
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {            // �����е� ����ṹ
    QueuePtr front, rear;        // ��ͷ, ��βָ��
} LinkQueue;

Status visit(QElemType c) {
    printf("%d ", c);
    return OK;
}

// ����һ�� �ն��� Q
Status InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front)
        exit(OVERFLOW);

    Q->front->next = NULL;
    return OK;
}

// ���� ���� Q
Status DestroyQueue(LinkQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

// �� Q ��Ϊ �ն���
Status ClearQueue(LinkQueue *Q) {
    QueuePtr p, q;
    Q->rear = Q->front;
    p = Q->front->next;
    Q->rear->next = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

// �� Q Ϊ�ն���, �򷵻�TRUE, ���򷵻� FALSE
Status QueueEmpty(LinkQueue Q) {
    if (Q.rear == Q.front)
        return TRUE;
    else
        return FALSE;
}

// �� ���� �ĳ���
int QueueLength(LinkQueue Q) {
    int i = 0;
    QueuePtr p;
    p = Q.front;
    while (Q.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

// �� ���� ����, �� �� e ����Q �Ķ�ͷԪ��, ������OK
Status GetHead(LinkQueue Q, QElemType *e) {
    QueuePtr p;
    if (Q.rear == Q.front)
        return ERROR;

    p = Q.front->next;
    *e = p->data;

    return OK;
}

// ���� Ԫ�� e Ϊ�µ� ��βԪ��
Status EnQueue(LinkQueue *Q, QElemType e) {
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
    // �洢 �ռ����ʧ��
    if (!s)
        exit(OVERFLOW);

    s->data = e;
    s->next = NULL;
    Q->rear->next = s;       // �� ӵ��Ԫ�� e ���½�� s ��ֵ ��ԭ��β�� ���
    Q->rear = s;             // �� ��ǰ�� s  ����Ϊ ��β���, rear ָ�� s

    return OK;
}

// �� ���в���, ɾ�� Q �� ��ͷ Ԫ��, �� e ������ֵ, �� ����OK
Status DeQueue(LinkQueue *Q, QElemType *e) {
    QueuePtr p;
    // �� ���� ��, �򷵻� ERROR
    if (Q->rear == Q->front)
        return ERROR;

    // �� ��ɾ�� �Ķ�ͷ�ڵ� ��ʱ ��ֵ ��p
    p = Q->front->next;
    // �� ��ɾ�� �Ķ�ͷ�ڵ��ֵ ��ʱ ��ֵ ��p
    *e = p->data;
    // �� ԭ��ͷ �ڵ� �ĺ�� p->next ��ֵ�� ͷ��� ���
    Q->front->next = p->next;

    // �� ��ͷ ���� ��β, ��ɾ�� ��rear ָ��ͷ���
    if (Q->rear == p)
        Q->rear = Q->front;

    free(p);
    return OK;
}

Status QueueTraverse(LinkQueue Q) {
    QueuePtr p;
    p = Q.front->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}


int main() {
    int i;
    QElemType d;
    LinkQueue Q;
    i = InitQueue(&Q);
    if (i)
        printf("�ɹ��� ������һ���ն���!\n");

    printf("�Ƿ�Ϊ�ն���? %d (1 : �� | 0 : ��Ϊ��)\n", QueueEmpty(Q));
    printf("���еĳ��� : %d\n", QueueLength(Q));
    EnQueue(&Q, -5);
    EnQueue(&Q, 5);
    EnQueue(&Q, 10);
    printf("����3��Ԫ��(-5,5,10)��, ���еĳ���Ϊ %d \n", QueueLength(Q));

    printf("�Ƿ�Ϊ�ն���? %d (1 : �� | 0 : ��Ϊ��)\n", QueueEmpty(Q));

    printf("���е�Ԫ������Ϊ: \n");
    QueueTraverse(Q);

    // ��ȡ��ͷԪ��
    i = GetHead(Q,&d);
    if(i == OK)
        printf("��ͷԪ��Ϊ : %d\n",d);

    // ɾ�� ��ͷԪ��
    DeQueue(&Q, &d);
    printf("ɾ���Ķ�ͷԪ��Ϊ : %d\n", d);

    // �µĶ�ͷԪ��
    i = GetHead(Q, &d);
    if (i==OK)
        printf("�µĶ�ͷԪ��Ϊ : %d\n", d);

    ClearQueue(&Q);
    printf("��ն��к�, Q.front = %u , Q.rear = %u , Q.front->next = %u \n", Q.front, Q.rear, Q.front->next);

    DestroyQueue(&Q);
    printf("���ٶ��к�, Q.front = %u , Q.rear = %u \n",Q.front, Q.rear);

}

















