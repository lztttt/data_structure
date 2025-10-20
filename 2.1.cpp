#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode
{
    int data;
    struct LNode *next; // 指向后结点
} LinkNode;

void CreateList(LinkNode *&L) // 创建单链表
{
    LinkNode *s, *r; // s新结点指针 r尾指针
    int x, n, i;    
    L = (LinkNode *)malloc(sizeof(LinkNode)); // 创建头结点
    if (L == NULL)
    { 
        printf("内存分配失败\n");
        exit(1);
    }
    L->next = NULL; 
    r = L;          // 指向头结点

    printf("数列的元素个数：");
    scanf("%d", &n);

    if (n <= 0) 
    {
        printf("元素个数需为正整数\n");
        return;
    }

    printf("请输入%d个整数：", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);

        // 创建新结点并赋值
        s = (LinkNode *)malloc(sizeof(LinkNode));
        if (s == NULL)
        {
            printf("内存分配失败\n");
            exit(1);
        }
        s->data = x;
        s->next = NULL;

        // 尾插：将新结点插入尾部
        r->next = s;
        r = s; // 尾指针更新为新结点
    }
}

// 输出链表结点
void DispList(LinkNode *L)
{
    LinkNode *p = L->next; // 首结点
    if (p == NULL)
    { // 空链表判断
        printf("链表为空\n");
        return;
    }
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 链表长度
int ListLength(LinkNode *L)
{
    int len = 0;
    LinkNode *p = L->next;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

// 查找第i个位置元素
bool GetElem(LinkNode *L, int i, int &e)
{
    int j = 1;             // 当前结点逻辑位序
    LinkNode *p = L->next; 

    // 判断合法性
    if (i < 1 || i > ListLength(L))
    {
        return false;
    }

    while (j < i && p != NULL)
    {
        j++;
        p = p->next;
    }

    e = p->data;
    return true;
}

// 插入元素
bool ListInsert(LinkNode *&L, int i, int x)
{
    int j = 0;           
    LinkNode *p = L, *s; //s新结点

    // 判断合法性
    if (i < 1 || i > ListLength(L) + 1)
    {
        return false;
    }

    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }

    //创建新结点
    s = (LinkNode *)malloc(sizeof(LinkNode));
    if (s == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    s->data = x;

    //插入新结点
    s->next = p->next;
    p->next = s;

    return true;
}

// 删除元素
bool ListDelete(LinkNode *&L, int i, int &e)
{
    int j = 0;          
    LinkNode *p = L, *q; // q：待删除结点

    // 判断合法性
    if (i < 1 || i > ListLength(L))
    {
        return false;
    }

    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }

    q = p->next;
    if (q == NULL)
    {
        return false;
    }

    // 删除结点释放内存
    e = q->data;       
    p->next = q->next; 
    free(q);          

    return true;
}

// 逆置单链表
void ReverseList(LinkNode *&L)
{
    LinkNode *pre = NULL;  
    LinkNode *p = L->next;
    LinkNode *next = NULL; 

    // 遍历链表，逐个反转指针方向
    while (p != NULL)
    {
        next = p->next;
        p->next = pre; 
        pre = p;        
        p = next;       
    }

    L->next = pre;
}

// 释放链表
void DestroyList(LinkNode *&L)
{
    LinkNode *pre = L;     
    LinkNode *p = L->next; 

    while (p != NULL)
    {
        free(pre);    
        pre = p;      
        p = pre->next; 
    }
    free(pre); 
    L = NULL; 
}

int main()
{
    LinkNode *L;
    int i, e, x;
    bool flag;

    // 1. 创建单链表
    CreateList(L);

    // 2. 输出链表
    printf("当前链表结点：");
    DispList(L);

    // 3. 查找第i个位置元素
    printf("请输入要查找的位置i:");
    scanf("%d", &i);
    flag = GetElem(L, i, e);
    if (flag)
    {
        printf("第%d个位置的元素值为:%d\n", i, e);
    }
    else
    {
        printf("位置i不合法\n");
    }

    // 4. 插入元素到第i个位置
    printf("请输入要插入的位置i和元素x:");
    scanf("%d %d", &i, &x);
    flag = ListInsert(L, i, x);
    if (flag)
    {
        printf("插入后链表：");
        DispList(L);
    }
    else
    {
        printf("位置i不合法\n", ListLength(L) + 1);
    }

    // 5. 删除第i个结点
    printf("请输入要删除的位置i：");
    scanf("%d", &i);
    flag = ListDelete(L, i, e);
    if (flag)
    {
        printf("删除的元素为：%d\n", e);
        printf("删除后链表：");
        DispList(L);
    }
    else
    {
        printf("位置i不合法\n", ListLength(L));
    }

    // 6. 逆置单链表
    ReverseList(L);
    printf("逆置后链表：");
    DispList(L);

    // 7. 释放全部结点空间
    DestroyList(L);
    return 0;
}