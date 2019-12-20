#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100     /* �洢�ռ��ʼ������ */
#define MAX_TREE_SIZE 100       /* �������� ���ڵ��� */


typedef int Status;     /* Status �Ǻ���������, ��ֵ �Ǻ������״̬��, �� OK �� */
typedef int TElemType;      /* ���ڵ����������, Ŀǰ�ݶ�Ϊ ���� */
typedef TElemType SqBiTree[MAX_TREE_SIZE];      /* 0 �ŵ�Ԫ�洢���ڵ� */

typedef struct {
    // ���� ��, �������(�� �������� ����)
    int level, order;
} Position;

// �� ���� ��0 Ϊ��
TElemType Nil = 0;

Status visit(TElemType c) {
    printf("%d ", c);
    return OK;
}

// ����ն����� T ,��Ϊ T �ǹ̶�����, ����ı�, �ʲ���Ҫ &
Status InitBiTree(SqBiTree T) {
    int i;
    for (i = 0; i < MAX_TREE_SIZE; ++i) {
        // ��ֵ Ϊ�� , �� ���� ���� ���ֵ
        T[i] = Nil;
    }
    return OK;
}

// �� ������� ����������н���ֵ(�ַ��� or ����), ����˳��洢�Ķ����� T
Status CreateBiTree(SqBiTree T) {
    int i = 0;
    printf("�밴�����������ֵ(����),0 ��ʾ�ս��, ����999����,������� %d : \n", MAX_TREE_SIZE);
    // �ص�
    while (i < 10) {
        T[i] = i + 1;
        // �˽��(����) ��˫�� �� ���Ǹ�
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            printf("������˫�׵ķǸ����%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }

    while (i < MAX_TREE_SIZE) {
        // T[10] ֮��Ľ���Ϊ��
        // �� �� ��ֵ�� T ����Ľ��
        T[i] = Nil;
        i++;
    }
    return OK;
}

// ��˳��洢�ṹ��, ��������ȫһ��
#define ClearBiTree InitBiTree

// ������ T ����
// �� T Ϊ�ն�����,�򷵻�TRUE , ���򷵻�FALSE
Status BiTreeEmpty(SqBiTree T) {
    // ���ڵ�Ϊ��, ����Ϊ��
    if (T[0] == Nil)
        return TRUE;
    else
        return FALSE;
}

// ��ʼ����: ������ T ����,
// ���� T �����
int BiTreeDepth(SqBiTree T) {
    int i, j = -1;
    // �ҵ� ���һ�����
    // �� MAX_TREE_SIZE ��ʼ��, ֱ���ҵ����һ����Ϊ 0 �Ľ��
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil)
            break;
    }
    // ��Ϊ T[i] �� 0 ��ʼ , �� i �Ǵ�0 ��ʼ
    // i++ Ϊ�������� ���ĸ���
    i++;
    do {
        j++;
        // ���� 2 �� j ����
    } while (i >= pow(2, j));
    return j;
}

// ��ʼ���� : ������ T ����
// �� T ����, �� e ���� �������ĸ�,���� OK ���򷵻� ERROR
Status Root(SqBiTree T, TElemType *e) {
    // ������Ϊ��
    if (BiTreeEmpty(T))
        return ERROR;
    else {
        *e = T[0];
        return OK;
    }
}

// ��ʼ����: ������ T ����, e �� T �� ĳ�����(��λ��)
// �������: ���� λ��λ��e(��, �������)�Ľ���ֵ
// �ص�
TElemType Value(SqBiTree T, Position e) {
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

// ������ T ����, e ��T ��ĳ�����(��λ��)
// ������� : �� ����λ��e( ��, ������� ) �Ľ�㸳��ֵ value
Status Assign(SqBiTree T, Position e, TElemType value) {
    // �� ��, ���� ���תΪ ��������
    int i = (int) powl(2, e.level - 1) + e.order - 2;
    // �� Ҷ�� �� �ǿ�ֵ �� ˫��Ϊ��
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
        return ERROR;
        // �� ˫�� ����ֵ �� ��Ҷ��(����)
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[2 * i + 2] != Nil))
        return ERROR;
    else
        T[i] = value;
    return OK;
}

// ��ʼ���� : ������ T ����, e �� T ��  ĳ�����
// ������� : �� e �� T �ķǸ��ڵ�, �򷵻�����˫��, ���򷵻�"��"
TElemType Parent(SqBiTree T ,TElemType e){
    int i;
    if (T[0]==Nil)
        return Nil;
    for (i = 1; i <=MAX_TREE_SIZE-1 ; ++i) {
        if (T[i]==e)
            return T[(i + 1) / 2 - 1];
    }
    return Nil;
}

// ��ʼ���� : ������ T ����, e ��T ��ĳ�����
// ���� e ������(LeftChild), �� e ������, �򷵻ؿ�
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i;
    // ����
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; ++i) {
        // �ҵ� e
        if (T[i] == e)
            return T[2 * i + 1];
    }
    // û�ҵ� e
    return Nil;
}

// ��ʼ���� : ������ T ����. e ��T ��ĳ�����
// ���� e ���Һ���(RightChild), �� e ���Һ���,. �򷵻ؿ�
TElemType RightChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i < +MAX_TREE_SIZE - 1; ++i) {
        if (T[i] == e)
            return T[2 * i + 2];
    }
    // û�ҵ� e
    return Nil;
}


// ��ʼ����: ������ T ����, e �� T ��ĳ�����
// ���� e ���� �ֵ�, �� e �� T ������ or �����ֵ�, ���ؿ�
TElemType LeftSibling(SqBiTree T, TElemType e) {
    int i;
    // ����
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; ++i) {
        // �ҵ� e �� ���Ϊ ż�� (�� �Һ���)
        if (T[i] == e && i % 2 == 0)
            return T[i - 1];
    }
    // û�ҵ� e
    return Nil;
}

// ��ʼ���� : ������ T ����, e �� T �� ĳ�����
// ���� e �����ֵ�,  �� e �� T ���Һ��� or �����ֵ� ,���ؿ�
TElemType RightSibling(SqBiTree T, TElemType e) {
    int i;
    // ����
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; ++i) {
        // �ҵ� e �� ����� Ϊ ����(�� ����)
        if (T[i] == e && i % 2)
            return T[i + 1];
    }
    // δ�ҵ�
    return Nil;
}

// PreOrderTraverse(ǰ�����)����
void PreTraverse(SqBiTree T, int e) {
    visit(T[e]);
    if (T[2 * e + 1] != Nil)    // ����������
        PreTraverse(T, 2 * e + 1);

    if (T[2 * e + 2] != Nil)    // ����������
        PreTraverse(T, 2 * e + 2);
}

// ��ʼ���� : ����������
// ������� : ������� T
Status PreOrderTraverse(SqBiTree T) {
    // ������
    if (!BiTreeEmpty(T))
        // ���ʸ��ڵ�
        PreTraverse(T, 0);
    printf("\n");
    return OK;
}

// InOrderTraverse(�������) ����
void InTraverse(SqBiTree T, int e) {
    // ������ ����
    if (T[2 * e + 1] != Nil)
        InTraverse(T, 2 * e + 1);
    visit(T[e]);
    // ����������
    if (T[2 * e + 2] != Nil)
        InTraverse(T, 2 * e + 2);
}

// ��ʼ���� : ����������
// ������� : ������� T
Status InOrderTraverse(SqBiTree T) {
    // ������
    if (!BiTreeEmpty(T))
        InTraverse(T, 0);
    printf("\n");
    return OK;
}

// PostTraverse(�������) ����
void PostTraverse(SqBiTree T, int e) {
    // ����������
    if (T[2 * e + 1] != Nil)
        PostTraverse(T, 2 * e + 1);
    // ����������
    if (T[2 * e + 2] != Nil)
        PostTraverse(T, 2 * e + 2);
    visit(T[e]);

}

// ��ʼ���� : ����������
// ������� : ������� T
Status PostOrderTraverse(SqBiTree T) {
    // ������
    if (!BiTreeEmpty(T))
        PostTraverse(T, 0);
    printf("\n");
    return OK;
}

// ������� ������
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j;
    // �ҵ����һ�� �ǿս�� �����
    while (T[i] != Nil)
        i--;
    for (j = 0; j <= i; ++j) {
        // �� ���ڵ� ��, ���������������
        if (T[j]!=Nil)
            // ֻ���� �ǿյ� ���
            visit(T[j]);
    }
    printf("\n");
}

// ���, ��������� ��� ������
void Print(SqBiTree T){
    int j, k;
    Position p;
    TElemType e;
    for (j = 1; j <= BiTreeDepth(T); ++j) {
        printf("�� %d ��: ", j);
        for (k = 1; k <= powl(2, j - 1); ++k) {
            p.level = j;
            p.order = k;
            e = Value(T, p);
            if (e!=Nil)
                printf(" %d : %d", k, e);
        }
        printf("\n");
    }
}

int main(){
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    printf("��ʼ�� ��������, ���շ�? %d( 1: �� | 0 : ��) ������� = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    CreateBiTree(T);
    printf("���� ��������, ���շ�? %d( 1: �� | 0 : ��) ������� = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    //LevelOrderTraverse(T);

    i = Root(T, &e);
    if (i)
        printf("�������ĸ�Ϊ : %d \n", e);
    else
        printf("����, �޸�\n");

    printf("������������� : \n");
    LevelOrderTraverse(T);

    printf("������������� : \n");
    PreOrderTraverse(T);

    printf("������������� : \n");
    InOrderTraverse(T);

    printf("������������� : \n");
    PostOrderTraverse(T);

    printf("�޸Ľ��Ĳ��3 �������2 \n");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    //printf("%d", e);
    // 5
    printf("���޸Ľ���ԭֵΪ : %d ,��������ֵ: 50 ", 50);
    e = 50;
    Assign(T, p, e);

    printf("ǰ����� ������ : \n");
    PreOrderTraverse(T);

    printf("��� %d ��˫��Ϊ %d, ���Һ��ӷֱ�Ϊ : ", e, Parent(T, e));
    printf("%d ,%d ,�����ֵ� �ֱ�Ϊ: ", LeftChild(T, e), RightChild(T, e));
    printf("%d ,%d \n", LeftSibling(T, e), RightChild(T, e));

    ClearBiTree(T);
    printf("�����������, ���շ�? %d( 1 : �� | 0 : ����), ������� = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("�������ĸ�Ϊ : %d", e);
    else
        printf("����, �޸�\n");

    printf("\n");


    return 0;

}
































