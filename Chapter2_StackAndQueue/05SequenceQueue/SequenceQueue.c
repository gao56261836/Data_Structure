#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <io.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20   /* 存储空间初始分配量 */

typedef int Status;
typedef int QElemType;      /* QElemType 类型 根据实际情况而定, 这里假设 为 int */


// 循环 队列的顺序存储 结构
typedef struct {
    QElemType data[MAXSIZE];
    int front;      // 头指针
    int rear;       // 尾指针, 若队列不空, 指向队尾元素的 下一个位置
} SqQueue;

Status visit(QElemType c) {
    printf("%d ", c);
    return OK;
}

// 初始化 一个空队列 Q
Status InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

// 将 Q 清空 为 空队列
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

// 若 队列 Q 为空队列, 则返回TRUE, 否则返回FALSE
Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

// 返回 Q 的元素个数, 也就是队列的 当前长度
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// 若 队列不空, 则用 e 返回 Q 的队头元素, 并 返回OK, 否则返回FALSE
Status GetHead(SqQueue Q, QElemType *e) {
    //
    if (Q.front == Q.rear) {
        printf("循环队列已满\n");
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

// 若 队列未满, 则 插入元素 e 为新的 队尾元素
Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        printf("循环队列已满!\n");\
        return ERROR;
    }
    Q->data[Q->rear] = e;       // 将 元素 e
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

// 删除 队首 元素, 若队列为空, 则返回FALSE, 否则返回TRUE
Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        printf("循环队列为空!\n");
        return ERROR;
    }
    *e = Q->data[Q->front];     // 将 队首 指针 赋值给 e
    Q->front = (Q->front + 1) % MAXSIZE;      // front  指针 向后移 1位
    // 若到最后 则 转到 数组头部
    return OK;
}


// 从 队头到 队尾 依次对 队列Q 中 每个元素输出
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
    printf("初始化队列后, 队列空否? %u (1 : 空 | 0 : 不为空)\n", QueueEmpty(Q));

    printf("请输入 整型队列元素(不超过 %d 个, -1 为提前结束符: )", MAXSIZE - 1);
    do {
        d = i + 100;
        if (d == -1)
            break;
        i++;
        EnQueue(&Q, d);
    } while (i < MAXSIZE - 1);

    QueueTraverse(Q);
    printf("队列长度为: %d\n", QueueLength(Q));
    printf("现在循环队列空否? %u (1 : 空 | 0 : 不为空)\n", QueueEmpty(Q));

    printf("连续 %d 次 由队头 删除元素, 队尾插入元素: \n", MAXSIZE);
    // 删除之后再插入元素
    for (l = 1; l <= MAXSIZE; ++l) {
        //  删除元素
        DeQueue(&Q, &d);
        printf("删除的元素是 %d, 队尾插入元素: %d \n", d, l + 1000);
        // 先删除元素 ,再添加元素
        d = l + 1000;
        EnQueue(&Q, d);
    }

    // l = 19
    l = QueueLength(Q);

    printf("现在队列中的元素为 : \n");
    QueueTraverse(Q);

    printf("共向 队尾 插入了 %d 个元素\n",i+MAXSIZE);
    //printf("=========================");
    //printf("%d ",l);

    if(l -2>0)
        printf("现在由 队头 删除 %d 个元素:\n",l-2);

    while (QueueLength(Q)>2){
        DeQueue(&Q,&d);
        printf("删除的元素值为: %d \n",d);
    }

    j = GetHead(Q,&d);
    if (j)
        printf("现在 队头 元素为 %d \n",d);

    ClearQueue(&Q);
    printf("清空 队列 后, 队列空否?  %u (1 : 空 | 0 : 不为空)\n",QueueEmpty(Q));

    return 0;
}