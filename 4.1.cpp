#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
typedef int ElemType;

typedef struct
{
    ElemType data[MaxSize];
    int top;
} SqStack;

// 栈初始化
void InitSqStack(SqStack *&s)
{
    s = (SqStack *)malloc(sizeof(SqStack));
    if (s == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    s->top = -1;
}

// 判空
bool IsSqStackEmpty(SqStack *s)
{
    return s->top == -1;
}

// 进栈
bool PushSqStack(SqStack *&s, ElemType e)
{
    if (s->top == MaxSize - 1)
    {
        printf("栈满\n");
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}

// 出栈
bool PopSqStack(SqStack *&s, ElemType &e)
{
    if (IsSqStackEmpty(s))
    {
        printf("栈空\n");
        return false;
    }
    e = s->data[s->top];
    s->top--;
    return true;
}

// 销毁栈
void DestroySqStack(SqStack *&s)
{
    free(s);
    s = NULL;
}

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkList;

void InitLinkList(LinkList *&L)
{
    L = (LinkList *)malloc(sizeof(LinkList));
    if (L == NULL)
    {
        printf("内存分配失败\n");
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

// 遍历输出单链表
void PrintLinkList(LinkList *L)
{
    LinkList *p = L->next;
    if (p == NULL)
    {
        printf("单链表为空！\n");
        return;
    }
    printf("原单链表元素：");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void ReverseOutputBySqStack(LinkList *L)
{
    SqStack *s;
    InitSqStack(s);

    LinkList *p = L->next;
    while (p != NULL)
    {
        PushSqStack(s, p->data);
        p = p->next;
    }

    printf("栈逆向输出：");
    ElemType e;
    while (!IsSqStackEmpty(s))
    {
        PopSqStack(s, e);
        printf("%d ", e);
    }
    printf("\n");

    DestroySqStack(s);
}

int main()
{
    ElemType testArr[] = {10, 20, 30, 40, 50};
    int n = sizeof(testArr) / sizeof(ElemType);
    LinkList *L;
    CreateLinkList(L, testArr, n);
    PrintLinkList(L);
    ReverseOutputBySqStack(L);
    LinkList *p = L, *q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    return 0;
}
