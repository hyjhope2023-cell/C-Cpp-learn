#include <stdio.h>
#include <stdlib.h>

/* 二叉链表结构定义 */
typedef struct TNode {
    char data;               /* 结点数据 */
    struct TNode *lchild;    /* 左孩子指针 */
    struct TNode *rchild;    /* 右孩子指针 */
} TNode, *BTree;

/* 核心算法：统计叶子节点个数 */
int CountLeafNodes(BTree T) {
    // 1. 如果是空树，返回0
    if (T == NULL) {
        return 0;
    }

    // 2. 如果左右孩子都为空，说明是叶子节点，返回1
    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }

    // 3. 递归统计左子树和右子树的叶子节点之和
    return CountLeafNodes(T->lchild) + CountLeafNodes(T->rchild);
}

/* 辅助函数：先序遍历建立二叉树 */
/* 输入示例：ABC##DE#G##F### (其中#表示空节点) */
BTree CreateBTree() {
    char ch;
    scanf(" %c", &ch); // 注意前面的空格，用于跳过换行符

    if (ch == '#') {
        return NULL;
    } else {
        BTree T = (BTree)malloc(sizeof(TNode));
        T->data = ch;
        T->lchild = CreateBTree(); // 递归创建左子树
        T->rchild = CreateBTree(); // 递归创建右子树
        return T;
    }
}

int main() {
    BTree T = NULL;
    printf("请按照先序遍历顺序输入二叉树节点 (用 # 代表空节点):\n");
    printf("例如输入 'A B # # C # #' 表示 A 是根，B 是左孩子，C 是右孩子\n");
    
    T = CreateBTree();

    int count = CountLeafNodes(T);
    printf("\n该二叉树的叶子节点个数为: %d\n", count);

    return 0;
}