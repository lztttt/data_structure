#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 队列结构
typedef struct QueueNode {
    BiTree data;
    struct QueueNode *next;
} QueueNode;
typedef struct {
    QueueNode *front, *rear;
} LinkQueue;

// 初始化队列
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode));
    Q->front->next = NULL;
}

// 入队
void EnQueue(LinkQueue *Q, BiTree T) {
    QueueNode *p = (QueueNode*)malloc(sizeof(QueueNode));
    p->data = T;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

// 出队
int DeQueue(LinkQueue *Q, BiTree *T) {
    if (Q->front == Q->rear) return 0;
    QueueNode *p = Q->front->next;
    *T = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) Q->rear = Q->front;
    free(p);
    return 1;
}

// 4. 判断队列空
int QueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}

// 先序创建二叉树
void CreateBTree(BiTree *T) {
    char ch;
    while ((ch = getchar()) == ' ' || ch == '\n');
    if (ch == '#') *T = NULL;
    else {
        *T = (BiTNode*)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBTree(&((*T)->lchild));
        CreateBTree(&((*T)->rchild));
    }
}

// 先序遍历
void PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 中序遍历
void InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild);
        printf("%c", T->data);
        InOrderTraverse(T->rchild);
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c", T->data);
    }
}

// 统计叶子结点数
int CountLeaf(BiTree T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

// 统计度为1的结点数
int CountDegree1(BiTree T) {
    if (!T) return 0;
    if ((T->lchild && !T->rchild) || (!T->lchild && T->rchild))
        return 1 + CountDegree1(T->lchild) + CountDegree1(T->rchild);
    return CountDegree1(T->lchild) + CountDegree1(T->rchild);
}

// 统计度为2的结点数
int CountDegree2(BiTree T) {
    if (!T) return 0;
    if (T->lchild && T->rchild)
        return 1 + CountDegree2(T->lchild) + CountDegree2(T->rchild);
    return CountDegree2(T->lchild) + CountDegree2(T->rchild);
}

// 树的深度
int TreeDepth(BiTree T) {
    if (!T) return 0;
    int ldepth = TreeDepth(T->lchild);
    int rdepth = TreeDepth(T->rchild);
    return (ldepth > rdepth ? ldepth : rdepth) + 1;
}

// 树的宽度
int TreeWidth(BiTree T) {
    if (!T) return 0;
    LinkQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    int width = 0, levelSize = 0;
    while (!QueueEmpty(Q)) {
        levelSize = 0;
        // 统计当前层结点数
        QueueNode *p = Q.front->next;
        while (p) { levelSize++; p = p->next; }
        if (levelSize > width) width = levelSize;
        // 层序遍历，出队当前层，入队下一层
        for (int i = 0; i < levelSize; i++) {
            BiTree node;
            DeQueue(&Q, &node);
            if (node->lchild) EnQueue(&Q, node->lchild);
            if (node->rchild) EnQueue(&Q, node->rchild);
        }
    }
    return width;
}

// 查询结点层次
void LocateNode(BiTree T, char c, int l, int *level) {
    if (!T || *level != 0) return;
    l++;
    if (T->data == c) { *level = l; return; }
    LocateNode(T->lchild, c, l, level);
    LocateNode(T->rchild, c, l, level);
}

// 找结点最大值
TElemType MaxElem(BiTree T) {
    if (!T) return '\0';
    TElemType max = T->data;
    TElemType lmax = MaxElem(T->lchild);
    TElemType rmax = MaxElem(T->rchild);
    if (lmax > max) max = lmax;
    if (rmax > max) max = rmax;
    return max;
}

// 交换所有结点的左右子树
void SwapChildren(BiTree T) {
    if (!T) return;
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    SwapChildren(T->lchild);
    SwapChildren(T->rchild);
}

// 收集叶子结点
void CollectLeaves(BiTree T, char *leaves, int *idx) {
    if (!T) return;
    if (!T->lchild && !T->rchild) {
        leaves[(*idx)++] = T->data;
        return;
    }
    CollectLeaves(T->lchild, leaves, idx);
    CollectLeaves(T->rchild, leaves, idx);
}

// 删除所有叶子结点
void DeleteLeaves(BiTree *T) {
    if (!*T) return;
    if (!(*T)->lchild && !(*T)->rchild) {
        free(*T);
        *T = NULL;
        return;
    }
    DeleteLeaves(&((*T)->lchild));
    DeleteLeaves(&((*T)->rchild));
}


int main() {
    BiTree T = NULL;
    char leaves[20] = {0};
    int idx = 0, level = 0;
    char queryNode;

    printf("请按先序序列输入二叉树中结点的值（每个结点一个字符，#表示空树）：\n");
    CreateBTree(&T);
    printf("先序遍历序列为：");
    PreOrderTraverse(T);
    printf("\n中序遍历序列为：");
    InOrderTraverse(T);
    printf("\n后序遍历序列为：");
    PostOrderTraverse(T);
    printf("\n");

    printf("叶子结点个数为：%d\n", CountLeaf(T));
    printf("度为1的结点个数为：%d\n", CountDegree1(T));
    printf("度为2的结点个数为：%d\n", CountDegree2(T));
    printf("树的深度为：%d\n", TreeDepth(T));
    printf("树的宽度为：%d\n", TreeWidth(T));

    printf("\n请输入要查询的结点：\n");
    while ((queryNode = getchar()) == ' ' || queryNode == '\n');
    LocateNode(T, queryNode, 0, &level);
    printf("结点%c在第%d层\n", queryNode, level);

    printf("值最大的结点为：%c\n", MaxElem(T));

    SwapChildren(T);
    printf("交换每个结点的左右子树后先序遍历序列为：");
    PreOrderTraverse(T);
    printf("\n");

    CollectLeaves(T, leaves, &idx);
    DeleteLeaves(&T);
    printf("删除的叶子结点为：");
    for (int i = 0; i < idx; i++) printf("%c ", leaves[i]);
    printf("\n");

    return 0;
}