#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100     /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100       /* 二叉树的 最大节点数 */


typedef int Status;     /* Status 是函数的类型, 其值 是函数结果状态码, 如 OK 等 */
typedef int TElemType;      /* 树节点的数据类型, 目前暂定为 整型 */
typedef TElemType SqBiTree[MAX_TREE_SIZE];      /* 0 号单元存储根节点 */

typedef struct {
    // 结点的 层, 本层序号(按 满二叉树 计算)
    int level, order;
} Position;

// 设 整型 以0 为空
TElemType Nil = 0;

Status visit(TElemType c) {
    printf("%d ", c);
    return OK;
}

// 构造空二叉树 T ,因为 T 是固定数组, 不会改变, 故不需要 &
Status InitBiTree(SqBiTree T) {
    int i;
    for (i = 0; i < MAX_TREE_SIZE; ++i) {
        // 初值 为空 , 将 树中 所有 结点值
        T[i] = Nil;
    }
    return OK;
}

// 按 层序次序 输入二叉树中结点的值(字符型 or 整型), 构造顺序存储的二叉树 T
Status CreateBiTree(SqBiTree T) {
    int i = 0;
    printf("请按层序输入结点的值(整型),0 表示空结点, 输入999结束,结点数≤ %d : \n", MAX_TREE_SIZE);
    // 重点
    while (i < 10) {
        T[i] = i + 1;
        // 此结点(不空) 无双亲 且 不是根
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            printf("出现无双亲的非根结点%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }

    while (i < MAX_TREE_SIZE) {
        // T[10] 之后的结点均为空
        // 将 空 赋值给 T 后面的结点
        T[i] = Nil;
        i++;
    }
    return OK;
}

// 在顺序存储结构中, 两函数完全一样
#define ClearBiTree InitBiTree

// 二叉树 T 存在
// 若 T 为空二叉树,则返回TRUE , 否则返回FALSE
Status BiTreeEmpty(SqBiTree T) {
    // 根节点为空, 则数为空
    if (T[0] == Nil)
        return TRUE;
    else
        return FALSE;
}

// 初始条件: 二叉树 T 存在,
// 返回 T 的深度
int BiTreeDepth(SqBiTree T) {
    int i, j = -1;
    // 找到 最后一个结点
    // 从 MAX_TREE_SIZE 开始找, 直到找到最后一个不为 0 的结点
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil)
            break;
    }
    // 因为 T[i] 从 0 开始 , 即 i 是从0 开始
    // i++ 为二叉树中 结点的个数
    i++;
    do {
        j++;
        // 计算 2 的 j 次幂
    } while (i >= pow(2, j));
    return j;
}

// 初始条件 : 二叉树 T 存在
// 当 T 不空, 用 e 返回 二叉树的根,返回 OK 否则返回 ERROR
Status Root(SqBiTree T, TElemType *e) {
    // 二叉树为空
    if (BiTreeEmpty(T))
        return ERROR;
    else {
        *e = T[0];
        return OK;
    }
}

// 初始条件: 二叉树 T 存在, e 是 T 中 某个结点(的位置)
// 操作结果: 返回 位于位置e(层, 本层序号)的结点的值
// 重点
TElemType Value(SqBiTree T, Position e) {
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

// 二叉树 T 存在, e 是T 中某个结点(的位置)
// 操作结果 : 给 处于位置e( 层, 本层序号 ) 的结点赋新值 value
Status Assign(SqBiTree T, Position e, TElemType value) {
    // 将 层, 本层 序号转为 矩阵的序号
    int i = (int) powl(2, e.level - 1) + e.order - 2;
    // 给 叶子 赋 非空值 但 双亲为空
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
        return ERROR;
        // 给 双亲 赋空值 但 有叶子(不空)
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[2 * i + 2] != Nil))
        return ERROR;
    else
        T[i] = value;
    return OK;
}

// 初始条件 : 二叉树 T 存在, e 是 T 中  某个结点
// 操作结果 : 若 e 是 T 的非根节点, 则返回它的双亲, 否则返回"空"
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

// 初始条件 : 二叉树 T 存在, e 是T 中某个结点
// 返回 e 的左孩子(LeftChild), 若 e 无左孩子, 则返回空
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i;
    // 空树
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; ++i) {
        // 找到 e
        if (T[i] == e)
            return T[2 * i + 1];
    }
    // 没找到 e
    return Nil;
}

// 初始条件 : 二叉树 T 存在. e 是T 中某个结点
// 返回 e 的右孩子(RightChild), 若 e 无右孩子,. 则返回空
TElemType RightChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i < +MAX_TREE_SIZE - 1; ++i) {
        if (T[i] == e)
            return T[2 * i + 2];
    }
    // 没找到 e
    return Nil;
}


// 初始条件: 二叉树 T 存在, e 是 T 中某个结点
// 返回 e 的左 兄弟, 若 e 是 T 的左孩子 or 无左兄弟, 返回空
TElemType LeftSibling(SqBiTree T, TElemType e) {
    int i;
    // 空树
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; ++i) {
        // 找到 e 且 序号为 偶数 (是 右孩子)
        if (T[i] == e && i % 2 == 0)
            return T[i - 1];
    }
    // 没找到 e
    return Nil;
}

// 初始条件 : 二叉树 T 存在, e 是 T 中 某个结点
// 返回 e 的右兄弟,  若 e 是 T 的右孩子 or 无右兄弟 ,返回空
TElemType RightSibling(SqBiTree T, TElemType e) {
    int i;
    // 空树
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; ++i) {
        // 找到 e 且 其序号 为 奇数(是 左孩子)
        if (T[i] == e && i % 2)
            return T[i + 1];
    }
    // 未找到
    return Nil;
}

// PreOrderTraverse(前序遍历)调用
void PreTraverse(SqBiTree T, int e) {
    visit(T[e]);
    if (T[2 * e + 1] != Nil)    // 左子树不空
        PreTraverse(T, 2 * e + 1);

    if (T[2 * e + 2] != Nil)    // 右子树不空
        PreTraverse(T, 2 * e + 2);
}

// 初始条件 : 二叉树存在
// 操作结果 : 先序遍历 T
Status PreOrderTraverse(SqBiTree T) {
    // 树不空
    if (!BiTreeEmpty(T))
        // 访问根节点
        PreTraverse(T, 0);
    printf("\n");
    return OK;
}

// InOrderTraverse(中序遍历) 调用
void InTraverse(SqBiTree T, int e) {
    // 左子树 不空
    if (T[2 * e + 1] != Nil)
        InTraverse(T, 2 * e + 1);
    visit(T[e]);
    // 右子树不空
    if (T[2 * e + 2] != Nil)
        InTraverse(T, 2 * e + 2);
}

// 初始条件 : 二叉树存在
// 操作结果 : 中序遍历 T
Status InOrderTraverse(SqBiTree T) {
    // 树不空
    if (!BiTreeEmpty(T))
        InTraverse(T, 0);
    printf("\n");
    return OK;
}

// PostTraverse(后序遍历) 调用
void PostTraverse(SqBiTree T, int e) {
    // 左子树不空
    if (T[2 * e + 1] != Nil)
        PostTraverse(T, 2 * e + 1);
    // 右子树不空
    if (T[2 * e + 2] != Nil)
        PostTraverse(T, 2 * e + 2);
    visit(T[e]);

}

// 初始条件 : 二叉树存在
// 操作结果 : 后序遍历 T
Status PostOrderTraverse(SqBiTree T) {
    // 树不空
    if (!BiTreeEmpty(T))
        PostTraverse(T, 0);
    printf("\n");
    return OK;
}

// 层序遍历 二叉树
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j;
    // 找到最后一个 非空结点 的序号
    while (T[i] != Nil)
        i--;
    for (j = 0; j <= i; ++j) {
        // 从 根节点 起, 按层序遍历二叉树
        if (T[j]!=Nil)
            // 只遍历 非空的 结点
            visit(T[j]);
    }
    printf("\n");
}

// 逐层, 按本层序号 输出 二叉树
void Print(SqBiTree T){
    int j, k;
    Position p;
    TElemType e;
    for (j = 1; j <= BiTreeDepth(T); ++j) {
        printf("第 %d 层: ", j);
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
    printf("初始化 二叉树后, 树空否? %d( 1: 是 | 0 : 否) 树的深度 = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    CreateBiTree(T);
    printf("建立 二叉树后, 树空否? %d( 1: 是 | 0 : 否) 树的深度 = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    //LevelOrderTraverse(T);

    i = Root(T, &e);
    if (i)
        printf("二叉树的根为 : %d \n", e);
    else
        printf("树空, 无根\n");

    printf("层序遍历二叉树 : \n");
    LevelOrderTraverse(T);

    printf("先序遍历二叉树 : \n");
    PreOrderTraverse(T);

    printf("中序遍历二叉树 : \n");
    InOrderTraverse(T);

    printf("后序遍历二叉树 : \n");
    PostOrderTraverse(T);

    printf("修改结点的层号3 本层序号2 \n");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    //printf("%d", e);
    // 5
    printf("待修改结点的原值为 : %d ,请输入新值: 50 ", 50);
    e = 50;
    Assign(T, p, e);

    printf("前序遍历 二叉树 : \n");
    PreOrderTraverse(T);

    printf("结点 %d 的双亲为 %d, 左右孩子分别为 : ", e, Parent(T, e));
    printf("%d ,%d ,左右兄弟 分别为: ", LeftChild(T, e), RightChild(T, e));
    printf("%d ,%d \n", LeftSibling(T, e), RightChild(T, e));

    ClearBiTree(T);
    printf("清除二叉树后, 树空否? %d( 1 : 空 | 0 : 不空), 树的深度 = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为 : %d", e);
    else
        printf("树空, 无根\n");

    printf("\n");


    return 0;

}
































