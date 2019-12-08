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

#define MAXSIZE 40      /* 存储空间初始分配量 */

typedef int Status;     /* Status 是 函数的类型, 其值是函数结果状态码. 如OK 等 */
typedef int ElemType;       /* ElemType 类型 根据实际情况 而定, 这里假设为 int */

typedef char String[MAXSIZE + 1];     /* 0 号 单元 存放串 的长度 */

// 生成 一个 其值等于 chars 的串 T
Status StrAssign(String T, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else {
        //串赋值的算法比较简单，把目标字符串一个个复制到数组T即可。
        // T[i] = *(chars+i-1) 这行代码是关键，字符串可以用指针访问。
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

// 由 串S 复制 得 串T
// S 为主串, T 为子串
Status StrCopy(String T, String S) {
    int i;
    for (i = 0; i <= S[0]; ++i) {
        T[i] = S[i];
    }
    return OK;
}

// 若 S 是空串, 则返回 TRUE , 否则返回 FALSE
Status StrEmpty(String S) {
    if (S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

// 主串 S 和 子串 T 均 存在
// 若 S > T. 则返回值 > 0 ; 若 S = T, 则返回值 = 0;   若S < T. 则返回值 < 0
int StrCompare(String S, String T) {
    int i;
    for (i = 0; i <= S[0] && i <= T[0]; ++i) {
        if (S[i] != T[i])
            return S[i] - T[i];
    }
    return S[0] - T[0];
}

// 返回 串 的元素个数
int StrLength(String S) {
    return S[0];
}

// 初始条件 : 串 S 存在,
// 操作结果 : 将 S 请为 空串
Status ClearString(String S) {
    // 令 串长 为0
    S[0] = 0;
    return OK;
}

// 用 T 返回 S1 和 S2 连接而成的新串, 若 未截断, 则返回TRUE 否则返回FALSE
Status Concat(String T, String S1, String S2) {
    int i;
    if (S1[0] + S2[0] <= MAXSIZE) {
        // 未截断
        for (i = 1; i <= S1[0]; ++i) {
            T[i] = S1[i];
        }
        for (i = 1; i <= S2[0]; ++i) {
            T[S1[0] + i] = S2[i];
        }
        T[0] = S1[0] + S2[0];
        return TRUE;
    } else {
        // S2 被截断
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

// 用 Sub 返回 串 S 的第 pos 个字符起 长度为 len 的子串
Status SubString(String Sub, String S, int pos, int len) {
    int i;
    // S = 10 , pos = 5, len = 5
    // pos + len = S[0]
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;
    // 从 主串中 截取 子串
    // 长度 为 len
    for (i = 1; i <= len; ++i) {
        Sub[i] = S[pos + i - 1];
    }
    Sub[0] = len;
    return OK;
}

// 返回 子串 T 在 主串 S 中 第pos 个字符之后的位置
// 若 不存在, 则函数返回值 为 0
// 朴素 匹配算法
int Index(String S, String T, int pos) {
    // i 用于 主串 S 中 当前位置 下标值, 若 pos != 1, 则 从 pos 位置开始匹配
    int i = pos;
    // j 用于 子串 T 中 当前位置 下标值
    int j = 1;
    while (i <= S[0] && j <= T[0]) {
        // 若 i < S.length && j < T.length 时 ,循环继续
        if (S[i] == T[j]) {
            ++i;
            ++j;
        } else {
            // 指针后退 重新开始匹配
            i = i - j + 2;      // i 退回到 上次 匹配首位 的下一位
            j = 1;              // j 退回到 子串T 的首位
        }
    }

    // 难点
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

// T 为 非空串, 若 主串 S 中 第pos个字符之后存在 与 T 相等的 子串
// 则返回 第一个这样的子串 在 S 中的位置, 否则返回0
int Index2(String S, String T, int pos) {
    int n, m, i;
    String sub;
    if (pos > 0) {
        n = StrLength(S);   // 得到 主串 S 的长度
        m = StrLength(T);   // 得到子串T 的长度
        i = pos;
        while (i <= n - m + 1) {
            SubString(sub, S, i, m);       // 取 主串中 第 i 个位置  长度  T 相等的子串给 sub
            if (StrCompare(sub, T) != 0) {
                // 如果两串 不相等
                ++i;
            } else
                // 如果两串相等, 则返回 i 值
                return i;
        }
    }
    return 0;       // 若 无 子串 与T相等, 返回 0
}

// 初始条件 : 主串 S 和 子串 T 同时存在
// 在 串 S  的第pos 个字符之前 插入 串T, 完全插入返回TRUE 部分插入 fanhuiFALSE
Status StrInsert(String S, int pos, String T) {
    int i;
    if (pos < 1 || pos > S[0] + 1)
        return ERROR;
    if (S[0] + T[0] <= MAXSIZE) {
        // 完全 插入
        for (i = S[0]; i >= pos; i--)
            S[i + T[0]] = S[i];
        for (i = pos; i < pos + T[0]; ++i)
            S[i] = T[i - pos + 1];

        S[0] = S[0] + T[0];
        return TRUE;
    } else {
        // 部分 插入
        for (i = MAXSIZE; i <= pos; i--)
            S[i] = S[i - T[0]];

        for (i = pos; i < pos + T[0]; ++i)
            S[i] = T[i - pos + 1];

        S[0] = MAXSIZE;
        return FALSE;
    }
}

// 串 S 存在, i <= pos <= StrLength(S) - len +1
// 从 串 S 中 删除第 pos 个字符起 长度为 len 的子串
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

// 串 S, T, V 存在 ,T 时候非空串 (此函数与串的存储结构无关)
// 用 V 替换 主串 S 中出现的所有与 T 相等的不重叠的子串
Status Replace(String S, String T, String V){
    // 从 串S 的第一个字符起开始 查找 串T
    int i = 1;
    // T 是空串
    if (StrEmpty(T))
        return ERROR;

    do {
        // 结果 i 为 从上一个 i 之后找到子串 T 的位置
        i = Index(S, T, i);
        if (i){
            // 串 S 中存在串T

            // 删除 该串T
            StrDelete(S, i, StrLength(T));
            // 在 原串 T 的位置插入串 V
            StrInsert(S, i, V);
            // 在 插入的串 V 后面继续查找串 T
            i += StrLength(V);
        }
    } while (i);
    return OK;
}

// 输出字符串T
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
    printf("请输入串s1: ");
    k = StrAssign(s1, "abcd");
    StrPrint(s1);
    if (!k) {
        printf("串长超过MAXSIZE(=%d)\n", MAXSIZE);
        exit(0);
    }

    printf("串长为 %d 串空否? %d (1 : 空 | 0 : 不为空)\n", StrLength(s1), StrEmpty(s1));

    StrCopy(s2, s1);
    printf("拷贝 s1 生成的串为: ");
    StrPrint(s2);

    printf("请输入串s2: ");
    k = StrAssign(s2, "efghijk");
    if (!k) {
        printf("串长超过MAXSIZE(%d)\n", MAXSIZE);
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
    printf("串 s1 %c s2\n", s);

    k = Concat(t, s1, s2);
    printf("串 s1 联结 串 s2 得到的串t 为: ");
    StrPrint(t);

    if (k == FALSE)
        printf("串 t 有截断\n");

    // 清空 串s1
    ClearString(s1);
    printf("将 s1 清为空串后, 串 s1 为: ");
    StrPrint(s1);
    printf("串长为 %d , 串空否? %d (1 : 空 | 0 : 不为空)\n", StrLength(s1), StrEmpty(s1));

    printf("求串 t 的子串, 请输入 子串 的起始位置, 子串长度: ");

    i = 2;
    j = 3;
    printf("%d, %d \n", i, j);

    // 截取串
    k = SubString(s2, t, i, j);
    if (k) {
        // 截取 成功
        printf("子串 s2 为 :");
        StrPrint(s2);
    }

    // 删除 字符
    // 串 t 为 a b c d e f g h i j k
    printf("从 串t 的第 pos 个字符起, 删除 len 个字符, 请输入 pos, len\n");
    i = 4;
    j = 2;
    printf("%d, %d\n", i, j);

    StrDelete(t, i, j);
    printf("删除后的串 t 为: ");
    StrPrint(t);
    printf("==================\n");
    StrPrint(s2);
    i = StrLength(s2) / 2;
    printf("%d\n", i);
    StrInsert(s2, i, t);

    printf("在串 s2 的第 %d 个字符之前插入 串 t 后, 串 s2 为: \n", i);
    // abcfghijk | bcd
    StrPrint(s2);

    printf("=============\n");
    printf("字符串s2为: ");
    StrPrint(s2);
    printf("字符串t为: ");
    StrPrint(t);
    i = Index(s2, t, 1);

    printf("s2 的第 %d 个字符起和 t 第一次匹配!\n", i);

    SubString(t, s2, 1, 3);
    StrPrint(s2);
    printf("串 t 为: ");
    StrPrint(t);

    printf("=====================\n");
    printf("串 s1 为 : ");
    StrPrint(s1);
    Concat(s1, t, t);
    printf("串 s1 为 : ");
    StrPrint(s1);

    Replace(s2, t, s1);
    printf("用串 s1 取代串 s2 中 和串 t 相同的不重叠的串后,串 s2 为:  ");
    StrPrint(s2);

}



























