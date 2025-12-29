#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct linknode
{
    ElemType data;
    struct linknode *next;
} LinkStNode;

// 初始化链栈
void InitLinkStack(LinkStNode *&s)
{
    s = (LinkStNode *)malloc(sizeof(LinkStNode));
    if (s == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    s->next = NULL;
}

// 链栈判空
bool IsLinkStackEmpty(LinkStNode *s)
{
    return s->next == NULL;
}

// 链栈进栈
void PushLinkStack(LinkStNode *&s, ElemType e)
{
    LinkStNode *newNode = (LinkStNode *)malloc(sizeof(LinkStNode));
    newNode->data = e;
    newNode->next = s->next;
    s->next = newNode;      
}

// 链栈出栈
bool PopLinkStack(LinkStNode *&s, ElemType &e)
{
    if (IsLinkStackEmpty(s))
    {
        printf("链栈为空，无法出栈！\n");
        return false;
    }
    LinkStNode *p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    return true;
}

// 销毁链栈
void DestroyLinkStack(LinkStNode *&s)
{
    LinkStNode *p = s, *q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    s = NULL;
}

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkList;

// 初始化的单链表
void InitLinkList(LinkList *&L)
{
    L = (LinkList *)malloc(sizeof(LinkList));
    if (L == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    L->next = NULL;
}

// 创建单链表
void CreateLinkList(LinkList *&L, ElemType arr[], int n)
{
    InitLinkList(L);
    LinkList *p = L;
    for (int i = 0; i < n; i++)
    {
        LinkList *newNode = (LinkList *)malloc(sizeof(LinkList));
        newNode->data = arr[i];
        newNode->next = NULL;
        p->next = newNode;
        p = newNode;
    }
}

// 遍历输出链表
void PrintLinkList(LinkList *L)
{
    LinkList *p = L->next;
    if (p == NULL)
    {
        printf("单链表为空！\n");
        return;
    }
    printf("单链表元素：");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 链栈逆置单链表
void ReverseLinkListByLinkStack(LinkList *&L)
{
    LinkStNode *s;
    InitLinkStack(s);

    LinkList *p = L->next;
    L->next = NULL;
    while (p != NULL)
    {
        PushLinkStack(s, p->data);
        LinkList *q = p;
        p = p->next;
        free(q);
    }
    LinkList *q = L;

    ElemType e;
    while (!IsLinkStackEmpty(s))
    {
        PopLinkStack(s, e);
        LinkList *newNode = (LinkList *)malloc(sizeof(LinkList));
        newNode->data = e;
        newNode->next = NULL;
        q->next = newNode;
        q = newNode;
    }

    DestroyLinkStack(s);
}

int main()
{
    ElemType testArr[] = {2, 4, 6, 8, 10};
    int n = sizeof(testArr) / sizeof(ElemType);

    LinkList *L;
    CreateLinkList(L, testArr, n);
    printf("逆置前：");
    PrintLinkList(L);

    ReverseLinkListByLinkStack(L);
    printf("逆置后：");
    PrintLinkList(L);
    LinkList *p = L, *r;
    while (p != NULL)
    {
        r = p->next;
        free(p);
        p = r;
    }

    return 0;
}