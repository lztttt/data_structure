#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkList;

// 初始化单链表
void InitLinkList(LinkList *&L)
{
    L = NULL;
}

// 创建单链表
void CreateLinkList(LinkList *&L, ElemType arr[], int n)
{
    InitLinkList(L);
    LinkList *p = NULL;
    for (int i = 0; i < n; i++)
    {
        LinkList *newNode = (LinkList *)malloc(sizeof(LinkList));
        newNode->data = arr[i];
        newNode->next = NULL;

        if (L == NULL)
        {
            L = newNode;
            p = newNode;
        }
        else
        {
            p->next = newNode;
            p = newNode;
        }
    }
}

// 遍历输出单链表
void PrintLinkList(LinkList *L)
{
    if (L == NULL)
    {
        printf("链表为空\n");
        return;
    }
    printf("原单链表元素：");
    LinkList *p = L;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void RecursiveReverseOutput(LinkList *L)
{
    if (L == NULL)
    {
        return;
    }
    RecursiveReverseOutput(L->next);
    printf("%d ", L->data);
}

int main()
{
    ElemType testArr[] = {1, 3, 5, 7, 9};
    int n = sizeof(testArr) / sizeof(ElemType);

    LinkList *L;
    CreateLinkList(L, testArr, n);
    PrintLinkList(L);

    printf("递归逆序输出：");
    RecursiveReverseOutput(L);
    printf("\n");

    LinkList *p = L, *q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    return 0;
}