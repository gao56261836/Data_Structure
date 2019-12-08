#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40      /* �洢�ռ��ʼ������ */

typedef int Status;     /* Status �� ����������, ��ֵ�Ǻ������״̬��. ��OK �� */
typedef int ElemType;       /* ElemType ���� ����ʵ����� ����, �������Ϊ int */

typedef char String[MAXSIZE + 1];     /* 0 �� ��Ԫ ��Ŵ� �ĳ��� */

// ���� һ�� ��ֵ���� chars �Ĵ� T
Status StrAssign(String T, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else {
        //����ֵ���㷨�Ƚϼ򵥣���Ŀ���ַ���һ�������Ƶ�����T���ɡ�
        // T[i] = *(chars+i-1) ���д����ǹؼ����ַ���������ָ����ʡ�
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; ++i) {
            // T[1] = *(chars + 1 -1);
            // T[2] = *(chars + 1);
            // T[3] = *(chars + 2);
            // T[4] = *(chars + 3);
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}

// �� ��S ���� �� ��T
// S Ϊ����, T Ϊ�Ӵ�
Status StrCopy(String T, String S) {
    int i;
    for (i = 0; i <= S[0]; ++i) {
        T[i] = S[i];
    }
    return OK;
}

// �� S �ǿմ�, �򷵻� TRUE , ���򷵻� FALSE
Status StrEmpty(String S) {
    if (S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

// ���� S �� �Ӵ� T �� ����
// �� S > T. �򷵻�ֵ > 0 ; �� S = T, �򷵻�ֵ = 0;   ��S < T. �򷵻�ֵ < 0
int StrCompare(String S, String T) {
    int i;
    for (i = 0; i <= S[0] && i <= T[0]; ++i) {
        if (S[i] != T[i])
            return S[i] - T[i];
    }
    return S[0] - T[0];
}

// ���� �� ��Ԫ�ظ���
int StrLength(String S) {
    return S[0];
}

// ��ʼ���� : �� S ����,
// ������� : �� S ��Ϊ �մ�
Status ClearString(String S) {
    // �� ���� Ϊ0
    S[0] = 0;
    return OK;
}

// �� T ���� S1 �� S2 ���Ӷ��ɵ��´�, �� δ�ض�, �򷵻�TRUE ���򷵻�FALSE
Status Concat(String T, String S1, String S2) {
    int i;
    if (S1[0] + S2[0] <= MAXSIZE) {
        // δ�ض�
        for (i = 1; i <= S1[0]; ++i) {
            T[i] = S1[i];
        }
        for (i = 1; i <= S2[0]; ++i) {
            T[S1[0] + i] = S2[i];
        }
        T[0] = S1[0] + S2[0];
        return TRUE;
    } else {
        // S2 ���ض�
        for (i = 1; i <= S1[0]; ++i) {
            T[i] = S1[i];
        }
        for (i = 1; i <= MAXSIZE - S1[0]; ++i) {
            T[S1[0] + i] = S2[i];
        }
        T[0] = MAXSIZE;
    }
    return FALSE;
}

// �� Sub ���� �� S �ĵ� pos ���ַ��� ����Ϊ len ���Ӵ�
Status SubString(String Sub, String S, int pos, int len) {
    int i;
    // S = 10 , pos = 5, len = 5
    // pos + len = S[0]
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;
    // �� ������ ��ȡ �Ӵ�
    // ���� Ϊ len
    for (i = 1; i <= len; ++i) {
        Sub[i] = S[pos + i - 1];
    }
    Sub[0] = len;
    return OK;
}

// ���� �Ӵ� T �� ���� S �� ��pos ���ַ�֮���λ��
// �� ������, ��������ֵ Ϊ 0
// ���� ƥ���㷨
int Index(String S, String T, int pos) {
    // i ���� ���� S �� ��ǰλ�� �±�ֵ, �� pos != 1, �� �� pos λ�ÿ�ʼƥ��
    int i = pos;
    // j ���� �Ӵ� T �� ��ǰλ�� �±�ֵ
    int j = 1;
    while (i <= S[0] && j <= T[0]) {
        // �� i < S.length && j < T.length ʱ ,ѭ������
        if (S[i] == T[j]) {
            ++i;
            ++j;
        } else {
            // ָ����� ���¿�ʼƥ��
            i = i - j + 2;      // i �˻ص� �ϴ� ƥ����λ ����һλ
            j = 1;              // j �˻ص� �Ӵ�T ����λ
        }
    }

    // �ѵ�
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

// T Ϊ �ǿմ�, �� ���� S �� ��pos���ַ�֮����� �� T ��ȵ� �Ӵ�
// �򷵻� ��һ���������Ӵ� �� S �е�λ��, ���򷵻�0
int Index2(String S, String T, int pos) {
    int n, m, i;
    String sub;
    if (pos > 0) {
        n = StrLength(S);   // �õ� ���� S �ĳ���
        m = StrLength(T);   // �õ��Ӵ�T �ĳ���
        i = pos;
        while (i <= n - m + 1) {
            SubString(sub, S, i, m);       // ȡ ������ �� i ��λ��  ����  T ��ȵ��Ӵ��� sub
            if (StrCompare(sub, T) != 0) {
                // ������� �����
                ++i;
            } else
                // ����������, �򷵻� i ֵ
                return i;
        }
    }
    return 0;       // �� �� �Ӵ� ��T���, ���� 0
}

// ��ʼ���� : ���� S �� �Ӵ� T ͬʱ����
// �� �� S  �ĵ�pos ���ַ�֮ǰ ���� ��T, ��ȫ���뷵��TRUE ���ֲ��� fanhuiFALSE
Status StrInsert(String S, int pos, String T) {
    int i;
    if (pos < 1 || pos > S[0] + 1)
        return ERROR;
    if (S[0] + T[0] <= MAXSIZE) {
        // ��ȫ ����
        for (i = S[0]; i >= pos; i--)
            S[i + T[0]] = S[i];
        for (i = pos; i < pos + T[0]; ++i)
            S[i] = T[i - pos + 1];

        S[0] = S[0] + T[0];
        return TRUE;
    } else {
        // ���� ����
        for (i = MAXSIZE; i <= pos; i--)
            S[i] = S[i - T[0]];

        for (i = pos; i < pos + T[0]; ++i)
            S[i] = T[i - pos + 1];

        S[0] = MAXSIZE;
        return FALSE;
    }
}

// �� S ����, i <= pos <= StrLength(S) - len +1
// �� �� S �� ɾ���� pos ���ַ��� ����Ϊ len ���Ӵ�
Status StrDelete(String S , int pos, int len){
    int i;
    if (pos < 1 || pos > S[0] - len + 1 || len < 0)
        return ERROR;

    for (i = pos+len; i <=S[0] ; ++i) {
        S[i - len] = S[i];
    }
    S[0] -= len;
    return OK;
}

// �� S, T, V ���� ,T ʱ��ǿմ� (�˺����봮�Ĵ洢�ṹ�޹�)
// �� V �滻 ���� S �г��ֵ������� T ��ȵĲ��ص����Ӵ�
Status Replace(String S, String T, String V){
    // �� ��S �ĵ�һ���ַ���ʼ ���� ��T
    int i = 1;
    // T �ǿմ�
    if (StrEmpty(T))
        return ERROR;

    do {
        // ��� i Ϊ ����һ�� i ֮���ҵ��Ӵ� T ��λ��
        i = Index(S, T, i);
        if (i){
            // �� S �д��ڴ�T

            // ɾ�� �ô�T
            StrDelete(S, i, StrLength(T));
            // �� ԭ�� T ��λ�ò��봮 V
            StrInsert(S, i, V);
            // �� ����Ĵ� V ����������Ҵ� T
            i += StrLength(V);
        }
    } while (i);
    return OK;
}

// ����ַ���T
void StrPrint(String T){
    int i;
    for (i = 1; i <= T[0]; ++i) {
        printf("%c", T[i]);
    }
    printf("\n");
}

int main(){
    int i, j;
    Status k;
    char s;
    String t, s1, s2;
    printf("�����봮s1: ");
    k = StrAssign(s1, "abcd");
    StrPrint(s1);
    if (!k) {
        printf("��������MAXSIZE(=%d)\n", MAXSIZE);
        exit(0);
    }

    printf("����Ϊ %d ���շ�? %d (1 : �� | 0 : ��Ϊ��)\n", StrLength(s1), StrEmpty(s1));

    StrCopy(s2, s1);
    printf("���� s1 ���ɵĴ�Ϊ: ");
    StrPrint(s2);

    printf("�����봮s2: ");
    k = StrAssign(s2, "efghijk");
    if (!k) {
        printf("��������MAXSIZE(%d)\n", MAXSIZE);
        exit(0);
    }
    StrPrint(s2);

    // s1 = "abcd"
    // s2 = "efghijk"
    i = StrCompare(s1, s2);
    if (i < 0) {
        s = '<';
    } else if (i == 0){
        s = '=';
    }else{
        s = '<';
    }
    printf("�� s1 %c s2\n", s);

    k = Concat(t, s1, s2);
    printf("�� s1 ���� �� s2 �õ��Ĵ�t Ϊ: ");
    StrPrint(t);

    if (k == FALSE)
        printf("�� t �нض�\n");

    // ��� ��s1
    ClearString(s1);
    printf("�� s1 ��Ϊ�մ���, �� s1 Ϊ: ");
    StrPrint(s1);
    printf("����Ϊ %d , ���շ�? %d (1 : �� | 0 : ��Ϊ��)\n", StrLength(s1), StrEmpty(s1));

    printf("�� t ���Ӵ�, ������ �Ӵ� ����ʼλ��, �Ӵ�����: ");

    i = 2;
    j = 3;
    printf("%d, %d \n", i, j);

    // ��ȡ��
    k = SubString(s2, t, i, j);
    if (k) {
        // ��ȡ �ɹ�
        printf("�Ӵ� s2 Ϊ :");
        StrPrint(s2);
    }

    // ɾ�� �ַ�
    // �� t Ϊ a b c d e f g h i j k
    printf("�� ��t �ĵ� pos ���ַ���, ɾ�� len ���ַ�, ������ pos, len\n");
    i = 4;
    j = 2;
    printf("%d, %d\n", i, j);

    StrDelete(t, i, j);
    printf("ɾ����Ĵ� t Ϊ: ");
    StrPrint(t);
    printf("==================\n");
    StrPrint(s2);
    i = StrLength(s2) / 2;
    printf("%d\n", i);
    StrInsert(s2, i, t);

    printf("�ڴ� s2 �ĵ� %d ���ַ�֮ǰ���� �� t ��, �� s2 Ϊ: \n", i);
    // abcfghijk | bcd
    StrPrint(s2);

    printf("=============\n");
    printf("�ַ���s2Ϊ: ");
    StrPrint(s2);
    printf("�ַ���tΪ: ");
    StrPrint(t);
    i = Index(s2, t, 1);

    printf("s2 �ĵ� %d ���ַ���� t ��һ��ƥ��!\n", i);

    SubString(t, s2, 1, 3);
    StrPrint(s2);
    printf("�� t Ϊ: ");
    StrPrint(t);

    printf("=====================\n");
    printf("�� s1 Ϊ : ");
    StrPrint(s1);
    Concat(s1, t, t);
    printf("�� s1 Ϊ : ");
    StrPrint(s1);

    Replace(s2, t, s1);
    printf("�ô� s1 ȡ���� s2 �� �ʹ� t ��ͬ�Ĳ��ص��Ĵ���,�� s2 Ϊ:  ");
    StrPrint(s2);

}



























