#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
/* �洢�ռ��ʼ�������� */
#define MAXSIZE 20

typedef int Status;     // Status �Ǻ���������, ��ֵ�Ǻ�������Ĵ���, ��OK ��
typedef int ElemType;   // ElemType ���͸���ʵ���������, �������Ϊint

Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

typedef struct {
    ElemType data[MAXSIZE];     // ����, �洢����Ԫ��
    int length;         // ���Ա�ĳ���
} SqList;


// ��ʼ��˳�����Ա�
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

// �п�, �����Ա�L ����, �򷵻�TRUE, ���򷵻�FALSE
Status ListEmpty(SqList L) {
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

// ������Ա�
Status ClearList(SqList *L) {
    L->length = 0;
    return OK;
}

// �������Ա���
int ListLength(SqList L) {
    return L.length;
}


// ��λ����, ��e ���� L �е�i ������Ԫ�ص�ֵ, ע�� i ��ָλ��, �����е� i ��λ���Ǵ�0 ��ʼ
// Ϊʲô��ȡ��ElemType e ��ֵҪ��ָ��������
//  ���������� C �����е����ô���, C �������޷�����2 ��ֵ, ���з���ֵ OK Ĭ��Ϊ int ���� ��1
// �� ���ô��ο���ͨ��ָ�뷵�ض��ֵ, ������ C �����޷����ض��ֵ�����
Status GetElem(SqList L, int i, ElemType *e) {
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;
    *e = L.data[i - 1];

    return OK;
}

// ��λ����, ���� L �е� 1 ����e ��ȵ�Ԫ�ص�λ��
// ��������Ԫ�ز�����, �򷵻�0
int LocateElem(SqList L, ElemType e) {
    int i;
    if (L.length == 0)
        return 0;
    // �����Ա��������б���, ����ҵ������е� i �� ��e ��ȵ�ֵ, ���˳�ѭ��, ���� ֵ��λ��
    for (i = 0; i < L.length; ++i) {
        if (L.data[i] == e)
            break;
    }
    if (i >= L.length)
        return 0;

    return i + 1;
}

// i ����Ԫ�ص�λ��, ��1 ��ʼ, ElemType e ����Ҫ�����Ԫ�ص�ֵ
// ��L�е� i ��λ��֮ǰ�����µ�����Ԫ��e, L�ĳ���+1
Status ListInsert(SqList *L, int i, ElemType e) {
    int k;
    if (L->length == MAXSIZE) {
        printf("���Ա�����\n");
        return ERROR;
    }
    if (i < 1 || i > L->length + 1) {
        // i �ȵ�һ��λ��С or i �����һ��λ�û�Ҫ��
        printf("iֵ���Ϸ�\n");
        return ERROR;
    }

    if (i <= L->length) {
        // �Ƚ������, ��ʵ���� �� L �����һ��Ԫ�ؿ�ʼ,
        // �� i ֮���ÿһ��Ԫ�ض���� �ƶ�һλ, �� �����Ԫ�ؿճ�λ��
        for (k = L->length - 1; k >= i - 1; k--)
        {
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i - 1] = e;
    L->length++;

    return OK;
}

// ɾ��L �ĵ� i ��Ԫ��, ����e ������ֵ, L �ĳ��� -1
Status ListDelete(SqList *L, int i, ElemType *e) {
    int k;
    if (L->length == 0) {
        printf("���Ա�Ϊ��\n");
        return ERROR;
    }

    if (i < 1 || i > L->length) {
        printf("ɾ��λ�ò���ȷ!     ");
        return ERROR;
    }

    *e = L->data[i - 1];
    // ���ɾ��Ԫ�ز������һ��λ��
    if (i <= L->length) {
        for (k = i; k < L->length; ++k) {   // ��ɾ��Ԫ��ǰ��
            // �� �� i ��λ�ÿ�ʼ, ��i ֮���ÿһ��Ԫ�ؾ���ǰ�ƶ�һλ
            L->data[k - 1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

// ˳���L �Ѵ��� . ���ζ� L ��ÿ������Ԫ�����
/*Status ListTraverse(SqList L){
    for (int i = 0; i < L.length; ++i) {
        visit(L.data[i]);
    }
    printf("\n");
    return OK;
}*/
Status ListTraverse(SqList L) {
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

// ������˳�����кϲ�
void unionL(SqList *La, SqList Lb) {
    int La_len, Lb_len, i;
    ElemType e;
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    // Ϊʲô i �Ǵ� 1 ��ʼ����
    // GetElem ���������ȡ�����е�Ԫ��ʱ, �Ǵ� λ�� ��ʼ��ȡ��
    // ��1��Ԫ����data[0]. ��������
    // Ϊʲô��ȡ����ָ������, ��Ϊ GetElem �����Ѿ��з���ֵ, ֻ��ͨ��ָ��������
    for (i = 1; i <= Lb_len; ++i) {
        GetElem(Lb, i, &e);
        if (!LocateElem(*La, e))
            ListInsert(La, ++La_len, e);
    }
}

int main() {
    SqList L;
    SqList Lb;

    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("��ʼ��L��: L.length= %d \n", L.length);

    for (j = 1; j <= 5; j++) {
        // ��Ϊ�����ڵ�һ��λ�ò���Ԫ��, ���Դ�ӡʱ ��ӡ�����ǵ������
        i = ListInsert(&L,1, j);
    }
    printf("�� L �ı�ͷ���β���1--5��, L.data = ");
    ListTraverse(L);

    printf("L.length = %d \n",L.length);
    i = ListEmpty(L);
    printf("L �Ƿ�Ϊ��: i = %d(1:�� 0:��)\n",i);

    i = ClearList(&L);
    printf("��� L ��: L.length = %d\n",L.length);
    i = ListEmpty(L);
    printf("L �Ƿ�Ϊ��: i = %d(1:�� 0:��)\n",i);

    for (j = 1; j <=10; ++j) {
        ListInsert(&L,j,j);
    }
    printf("�� L �ı�β���β��� 1--10 ��, L.data = ");
    ListTraverse(L);

    printf("L.length = %d \n",L.length);

    ListInsert(&L,1,0);
    printf("�� L �ı�ͷ����0��: L.data = ");
    ListTraverse(L);
    printf("L.length = %d \n",L.length);

    // ��Ϊ L.data[i] �Ǵ�0 ��ʼ, ���Բ��ҵ� 5 ��Ԫ��ʵ���ϻ�ȡ������ L.data[4] ��ֵ
    GetElem(L,5,&e);
    printf("�� 5 ��Ԫ�ص�ֵΪ: %d\n",e);
    printf("===========================================\n");

    // ����Ԫ�� , ��λ�����
    for (j = 0; j <=11 ; ++j) {
        k=LocateElem(L,j);
        if (k)
            printf("�� %d ��Ԫ�ص�ֵΪ %d\n",k,j);
        else
            printf("û��ֵΪ %d ��Ԫ��\n",j);
    }

    printf("ɾ��ǰ,L.length = %d \n",L.length);
    k = ListLength(L);      // k Ϊ��
    //printf("%d",k);
    // j = 12 ; j >= 11 ; j--
    for (j = k +1; j >=k ; j--) {
        i = ListDelete(&L,j,&e);
        //printf("%d======\n",i);
        if (i == ERROR)
            printf("ɾ���� %d ������ʧ��\n",j);
        else
            printf("ɾ���� %d ����Ԫ��ֵΪ: %d\n",j,e);
    }
    k=ListLength(L);
    printf("ɾ����,L.length = %d \n",L.length);

    printf("�������˳��� L �е�Ԫ��: L.data = ");
    ListTraverse(L);

    j=5;
    // ɾ�� �� 5 ������
    ListDelete(&L,j,&e);
    printf("ɾ���� %d ����Ԫ��ֵΪ: %d\n",j,e);

    printf("�������˳��� L �е�Ԫ��: L.data = ");
    ListTraverse(L);

    i=InitList(&Lb);
    for (j = 6; j <= 15; ++j) {
        // ��Ϊ����, j Ӧ�ô� 1 ���ǿ�ʼ
        // ListInsert(&Lb,j,j);     ��Ϊ����
        i = ListInsert(&Lb,1,j);    // ��Ϊ������� ��������
    }
    printf("�������˳��� Lb �е�Ԫ��: Lb.data = ");
    ListTraverse(Lb);

    unionL(&L,Lb);
    printf("��������ϲ��� Lb �� L ��Ԫ��:");
    ListTraverse(L);

    return 0;
}

