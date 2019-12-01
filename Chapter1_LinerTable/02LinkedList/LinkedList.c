#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

// �洢�ռ��ʼ������
#define MAXSIZE

typedef int Status;     // Status �Ǻ�����ԭ��, ��ֵ�Ǻ������״̬��, ��OK ��
typedef int ElemType;   // ElemType ���͸���ʵ���������, �������Ϊint

// ���δ�ӡ
Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

// �ڵ�����
typedef struct Node {
    ElemType data;      // ��ֵ����
    struct Node *next;      // ָ������
} Node;

// ����LinkedList
typedef struct Node *LinkList;

// ��ʼ��˳�����Ա�
Status InitList(LinkList *L) {
    // ����ͷ���, ��ʹ L ָ���ͷ���
    // ��  L ��Ϊ ������� ͷ���
    *L = (Node *) malloc(sizeof(Node));
    if (!(*L))
        // �洢����ʧ��
        return ERROR;
    // ֻ�������ͷ���
    (*L)->next = NULL;  // ָ����Ϊ��
    return OK;
}

// �ж� ���Ա�Ϊ��
Status ListEmpty(LinkList L) {
    if (L->next) {
        // ��� L->next �˽�����, ��� ������Ϊ��
        return ERROR;
    } else {
        printf("���Ա�Ϊ�ձ�!\n");
        return TRUE;
    }
}

// ��L ����Ϊ�ձ�
Status ClearList(LinkList *L) {
    LinkList p, q;
    p = (*L)->next;     // p ָ�� ��һ�����
    while (p) {     // û����β
        q = p->next;
        free(p);
        p = q;  // �� q ��ֵ��ֵ�� p
    }
    (*L)->next = NULL;      // �ٰ�ͷ���ָ�����ÿ�
    return OK;
}

// ���� ������L ������Ԫ�صĸ���
int ListLength(LinkList L) {
    int i = 0;
    LinkList p = L->next;       // p ָ���һ�����
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

// �� e ���� L �е� i ������Ԫ�ص�ֵ
// �� ====> ��λ���� , ������ֵ
Status GetElem(LinkList L, int i, ElemType *e) {
    int j;
    LinkList p;     // ����һ��� p
    p = L->next;    // p ָ�� L �ĵ�һ�����
    j = 1;          // j Ϊ������
    while (p && j < i) {
        // p  ��Ϊ�ջ��� ��������û�е��� i  ʱ, ����ѭ��
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;       // �� i ��Ԫ�ز�����

    *e = p->data;       // ȡ��i ��Ԫ�ص� ������
    return OK;
}

// ���� L �� ��1�� �� e �����ϵ������Ԫ�ص�λ��
// ������������Ԫ�ز�����, �򷵻�ֵΪ 0
// ��  ====>  ��ֵ����, ������λ��
int LocateElem(LinkList L, ElemType e) {
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        if (p->data == e)
            return i;
        p = p->next;
    }
    // ��δ�ҵ�, �򷵻� 0
    return 0;
}

// ����Ԫ��: �� L �� �� i ��λ��֮ǰ���� �µ�����Ԫ�� e, L �ĳ��� +1
Status ListInsert(LinkList *L, int i, ElemType e) {
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p && j < i) {
        // Ѱ�ҵ� i �����
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("�� i ��Ԫ�ز�����");
        return ERROR;
    }
    s = (LinkList) malloc(sizeof(Node));     // �����½��
    s->data = e;
    s->next = p->next;      // �� p �ĺ�� ��ֵ�� s �ĺ��
    p->next = s;            // ��s ��ֵ�� p �ĺ��

    return OK;
}

// ɾ�� ������ L �� ��i ������Ԫ��, ���� e ������ֵ, L �ĳ���-1
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i) {
        // �ҵ��� i ������Ԫ��
        p = p->next;
        j++;
    }
    // �� i ������Ԫ�ز�����
    if (!p || j > i) {
        printf("�� i ������Ԫ�ز�����");
        return ERROR;
    }
    // ɾ������
    q = p->next;
    p->next = q->next;      // �� q �ĺ�� ��ֵ �� p�ĺ��
    *e = q->data;       // �� q ����е����� ��ֵ�� e
    free(q);    // ��ϵͳ���մ˽�� , ɾ��q ���
    return OK;
}

// ������ L �Ѵ���
// ���ζԵ����� L �е�ÿ������Ԫ�����
Status ListTraverse(LinkList L) {
    // L ��Ϊ ͷ��� , ����Ҫ�����ӡ
    LinkList p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

// ͷ�巨 , ���� rand ����, ������� n ��Ԫ�ص�ֵ
// ������ͷ���ĵ�����
// ͷ�巨�����˳��Ϊ����
void CreateListHead(LinkList *L, int n) {
    LinkList p;
    int i;
    srand(time(0));     // ��ʼ�����������
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;
    for (i = 0; i < n; ++i) {
        p = (LinkList) malloc(sizeof(Node));
        // ������� 100 ���ڵ������
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p; // ���뵽��ͷ
    }
}

// β�巨, ���� rand ����, ������� n ��Ԫ�ص�ֵ
// β�巨������˳��Ϊ ����
void CreateListTail(LinkList *L, int n) {
    LinkList p, r;
    int i;
    srand(time(0));     // ��ʼ�����������
    *L = (LinkList) malloc(sizeof(Node));   // ������ͷ���ĵ�����
    r = (*L);   // r Ϊָ��β���Ľ��
    for (i = 0; i < n; ++i) {
        p = (LinkList) malloc(sizeof(Node));    // �����½ڵ�
        p->data = rand() % 100 + 1;
        r->next = p;      // �� ��β�ն˽ڵ��ָ��ָ���½ڵ�
        r = p;    // ����ǰ���½ڵ㶨��Ϊ ��β�ն˽ڵ�
    }
    r->next = NULL;       // ��ǰ�������
}

int main() {
    LinkList L;
    ElemType e;
    Status i;
    int j, k;

    //  ��ʼ��������
    i = InitList(&L);
    printf("��ʼ�������� L ��, ListLength(L) = %d\n", ListLength(L));
    /*
        //�˴����Ϊ˳���ڵ������в���, �� ListInsert ����
       for (j = 1; j < 6; ++j) {
        i = ListInsert(&L,j,j);
        // ��ӡ��ϢΪ
        // �ڵ����� L �ı�ͷ���β��� 1--5 ��, L.data = 1 2 3 4 5
    }*/
    for (j = 0; j < 5; ++j) {
        i = ListInsert(&L, 1, j);
    }
    printf("�ڵ����� L �ı�ͷ���β��� 1--5 ��, L.data = ");
    ListTraverse(L);

    printf("ListLength(L) = %d \n", ListLength(L));

    // �ж� ������ L �Ƿ�Ϊ��
    i = ListEmpty(L);
    printf("=========================\n");
    printf("������ L �Ƿ�Ϊ�� : %d (1 : �ǣ�0 : ��) \n", i);
    // ��յ�����
    printf("=========================\n");
    i = ClearList(&L);
    printf("��յ�����֮��============\n");
    printf("��յ������Ƿ�ɹ� : %d (1 : �ǣ�0 : ��)\n", i);
    printf("��յ����� L ��, ListLength = %d \n", ListLength(L));

    printf("������ L �Ƿ�Ϊ�� : %d (1 : �ǣ�0 : ��) \n", i);

    for (j = 1; j <= 10; ++j) {
        ListInsert(&L, j, j);
    }
    printf("�ڵ����� L �ı�β���β��� 1--10 ֮��: L.data = ");
    ListTraverse(L);

    printf("ListLength(L) = %d \n", ListLength(L));

    // �� ������ �ı�ͷ ����0 Ԫ��
    ListInsert(&L, 1, 0);
    printf("�ڵ����� L �ı�ͷ���� 0 ��, L.data = ");
    ListTraverse(L);
    printf("ListLength(L) = %d \n", ListLength(L));

    // ��ȡ �� 5 ��Ԫ�ص�ֵ
    GetElem(L, 5, &e);
    printf("�� 5 ��Ԫ�ص�ֵΪ: %d\n", e);
    //printf("======================\n");
    for (j = 3; j <= 4; ++j) {
        /*
            while (p) {
                i++;
                if (p->data == e)
                    return i;
                p = p->next;
    }
         ��ȡ���� ����ֵ i ��Ϊ �ýڵ��������е�λ��
         k = LocateElem(L,j);
         �� i ��ֵ�� k
         */
        k = LocateElem(L, j);
        if (k)
            // ��ȡ����ֵ �� �� j ��ȵ�ֵ��λ��
            // j ��ȡֵ Ϊ 3 , 4
            printf("�� %d ��Ԫ�ص�ֵΪ: %d\n", k, j);
        else
            printf("û��ֵΪ %d ��Ԫ��!\n", j);
    }

    k = ListLength(L);
    printf("ListLength : %d\n",ListLength(L));
    printf("==========\n");
    // for (j = 11; j >= 10; j--) {
    for (j = k; j >= k-1; j--) {
        i = ListDelete(&L,j,&e);
        if (i == ERROR)
            printf("ɾ���� %d ������ʧ��\n",j);
        else
            printf("ɾ���� %d ����Ԫ��ֵ Ϊ: %d \n",j,e);
    }
    printf("������������� L �е�Ԫ��: L.data = ");
    ListTraverse(L);
    // ClearList(&L);
    // printf("��յ����� L ��, ������ĳ��� ListLength = %d\n",ListLength(L));

    i = ListDelete(&L,5,&e);
    printf("ɾ���������е� 5 ����Ԫ��ֵΪ : %d\n",e);
    printf("������������� L �е�Ԫ��: L.data = ");
    ListTraverse(L);

    i = ClearList(&L);
    printf("����Ƿ�ɹ� : %d (1 : �ɹ� , 0 : ʧ��),ListLength(L) = %d\n",i,ListLength(L));

    CreateListHead(&L,20);
    printf("���崴�� ������ L ��Ԫ��(ͷ�巨), L.data = ");
    ListTraverse(L);
    printf("==========================\n");

    i = ClearList(&L);
    printf("����Ƿ�ɹ� : %d (1 : �ɹ� , 0 : ʧ��),ListLength(L) = %d\n",i,ListLength(L));
    CreateListTail(&L,20);
    printf("���崴�� ������ L ��Ԫ��(β�巨), L.data = ");
    ListTraverse(L);


    return 0;
}


