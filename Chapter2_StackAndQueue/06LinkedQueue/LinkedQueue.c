#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20      /* 存储空间初始分配量 */

typedef int Status;
typedef int QElemType;

typedef struct QNode {       // 链队列 的 节点结构
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {            // 链队列的 链表结构
    QueuePtr front, rear;        // 队头, 队尾指针
} LinkQueue;

Status visit(QElemType c) {
    printf("%d ", c);
    return OK;
}

// 构造一个 空队列 Q
Status InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front)
        exit(OVERFLOW);

    Q->front->next = NULL;
    return OK;
}

// 销毁 队列 Q
Status DestroyQueue(LinkQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

// 将 Q 清为 空队列
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

// 若 Q 为空队列, 则返回TRUE, 否则返回 FALSE
Status QueueEmpty(LinkQueue Q) {
    if (Q.rear == Q.front)
        return TRUE;
    else
        return FALSE;
}

// 求 队列 的长度
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

// 若 队列 不空, 则 用 e 返回Q 的队头元素, 并返回OK
Status GetHead(LinkQueue Q, QElemType *e) {
    QueuePtr p;
    if (Q.rear == Q.front)
        return ERROR;

    p = Q.front->next;
    *e = p->data;

    return OK;
}

// 插入 元素 e 为新的 队尾元素
Status EnQueue(LinkQueue *Q, QElemType e) {
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
    // 存储 空间分配失败
    if (!s)
        exit(OVERFLOW);

    s->data = e;
    s->next = NULL;
    Q->rear->next = s;       // 把 拥有元素 e 的新结点 s 赋值 给原队尾的 后继
    Q->rear = s;             // 把 当前的 s  设置为 队尾结点, rear 指向 s

    return OK;
}

// 若 队列不空, 删除 Q 的 队头 元素, 用 e 返回其值, 并 返回OK
Status DeQueue(LinkQueue *Q, QElemType *e) {
    QueuePtr p;
    // 若 队列 空, 则返回 ERROR
    if (Q->rear == Q->front)
        return ERROR;

    // 将 欲删除 的队头节点 暂时 赋值 给p
    p = Q->front->next;
    // 将 欲删除 的队头节点的值 暂时 赋值 给p
    *e = p->data;
    // 将 原队头 节点 的后继 p->next 赋值给 头结点 后继
    Q->front->next = p->next;

    // 若 队头 就是 队尾, 则删除 后将rear 指向头结点
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
        printf("成功地 构造了一个空队列!\n");

    printf("是否为空队列? %d (1 : 空 | 0 : 不为空)\n", QueueEmpty(Q));
    printf("队列的长度 : %d\n", QueueLength(Q));
    EnQueue(&Q, -5);
    EnQueue(&Q, 5);
    EnQueue(&Q, 10);
    printf("插入3个元素(-5,5,10)后, 队列的长度为 %d \n", QueueLength(Q));

    printf("是否为空队列? %d (1 : 空 | 0 : 不为空)\n", QueueEmpty(Q));

    printf("队列的元素依次为: \n");
    QueueTraverse(Q);

    // 获取队头元素
    i = GetHead(Q,&d);
    if(i == OK)
        printf("队头元素为 : %d\n",d);

    // 删除 队头元素
    DeQueue(&Q, &d);
    printf("删除的队头元素为 : %d\n", d);

    // 新的队头元素
    i = GetHead(Q, &d);
    if (i==OK)
        printf("新的队头元素为 : %d\n", d);

    ClearQueue(&Q);
    printf("清空队列后, Q.front = %u , Q.rear = %u , Q.front->next = %u \n", Q.front, Q.rear, Q.front->next);

    DestroyQueue(&Q);
    printf("销毁队列后, Q.front = %u , Q.rear = %u \n",Q.front, Q.rear);

}

















