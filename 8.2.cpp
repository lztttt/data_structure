#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct node
{
    KeyType key;
    struct node *lchild;
    struct node *rchild;
} BSTNode;

// 二叉排序树插入
int InsertBST(BSTNode *&p, KeyType k)
{
    if (p == NULL)
    {
        p = (BSTNode *)malloc(sizeof(BSTNode));
        p->key = k;
        p->lchild = p->rchild = NULL;
        return 1;
    }
    else if (k == p->key)
    {
        return 0; // 已存在
    }
    else if (k < p->key)
    {
        return InsertBST(p->lchild, k);
    }
    else
    {
        return InsertBST(p->rchild, k);
    }
}

// 构造二叉排序树
BSTNode *CreatBST(KeyType A[], int n)
{
    BSTNode *bt = NULL;
    for (int i = 0; i < n; i++)
    {
        InsertBST(bt, A[i]);
    }
    return bt;
}

// 中序遍历
void InOrder(BSTNode *bt)
{
    if (bt != NULL)
    {
        InOrder(bt->lchild);
        printf("%d ", bt->key);
        InOrder(bt->rchild);
    }
}

// 查找关键字的父结点
BSTNode *FindParent(BSTNode *bt, KeyType k)
{
    if (bt == NULL || bt->key == k)
        return NULL;
    BSTNode *parent = NULL;
    while (bt != NULL)
    {
        if (bt->key == k)
            return parent;
        parent = bt;
        if (k < bt->key)
            bt = bt->lchild;
        else
            bt = bt->rchild;
    }
    return NULL;
}

// 二叉排序树删除
void Delete(BSTNode *&p)
{
    BSTNode *q, *r;
    if (p->rchild == NULL)
    {
        q = p;
        p = p->lchild;
        free(q);
    }
    else if (p->lchild == NULL)
    {
        q = p;
        p = p->rchild;
        free(q);
    }
    else
    {
        q = p;
        r = p->lchild;
        while (r->rchild != NULL)
        {
            q = r;
            r = r->rchild;
        }
        p->key = r->key;
        if (q == p)
            q->lchild = r->lchild;
        else
            q->rchild = r->lchild;
        free(r);
    }
}
void PrintBST(BSTNode *bt)
{
    if (bt == NULL)
        return;
    printf("%d", bt->key);
    if (bt->lchild != NULL || bt->rchild != NULL)
    {
        printf("(");
        PrintBST(bt->lchild);
        if (bt->rchild != NULL)
        {
            printf(",");
            PrintBST(bt->rchild);
        }
        printf(")");
    }
}

int DeleteBST(BSTNode *&bt, KeyType k)
{
    if (bt == NULL)
        return 0;
    BSTNode *p = bt;
    BSTNode *parent = FindParent(bt, k);
    while (p != NULL && p->key != k)
    {
        if (k < p->key)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (p == NULL)
        return 0;
    if (parent == NULL)
    {
        Delete(bt);
    }
    else if (parent->lchild == p)
    {
        Delete(parent->lchild);
    }
    else
    {
        Delete(parent->rchild);
    }
    return 1;
}

// 层序遍历
void LevelOrder(BSTNode *bt)
{
    if (bt == NULL)
        return;
    BSTNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = bt;
    printf("二叉排序树结构：");
    while (front < rear)
    {
        BSTNode *p = queue[front++];
        printf("%d ", p->key);
        if (p->lchild != NULL)
            queue[rear++] = p->lchild;
        if (p->rchild != NULL)
            queue[rear++] = p->rchild;
    }
    printf("\n");
}

int main() {
    KeyType A[] = {12, 7, 17, 11, 16, 2, 13, 9, 21, 4};
    int n = sizeof(A) / sizeof(KeyType);
    BSTNode *bt = CreatBST(A, n);
    printf("二叉排序树为：");
    PrintBST(bt);
    printf("\n");
    //中序序列
    printf("中序序列为：");
    InOrder(bt);
    printf("\n");
    // 删除11
    printf("删除11\n");
    DeleteBST(bt, 11);
    printf("二叉排序树为：");
    PrintBST(bt);
    printf("\n中序序列为：");
    InOrder(bt);
    printf("\n");
    // 删除17
    printf("删除17\n");
    DeleteBST(bt, 17);
    printf("二叉排序树为：");
    PrintBST(bt);
    printf("\n中序序列：");
    InOrder(bt);
    printf("\n");
    return 0;
}