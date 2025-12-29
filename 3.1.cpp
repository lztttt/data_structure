#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LinkNode;

void CreateCircularList(LinkNode *&L, int n)
{
    L = (LinkNode *)malloc(sizeof(LinkNode));
    if (L == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    L->next = L;  
    LinkNode *r = L; 

    for (int i = 1; i <= n; i++)
    {
        LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
        if (s == NULL)
        {
            printf("内存分配失败\n");
            exit(1);
        }
        s->data = i;
        s->next = L;  
        r->next = s;  
        r = s;
    }
}

// 约瑟夫问题
void Josephus(LinkNode *&L, int n, int s, int m, int *outSeq)
{
    LinkNode *p = L;
    for (int i = 0; i < s - 1; i++)
    {
        p = p->next;
    }

    int count = 0;
    while (count < n)
    {
        
        if (p->next == p)  
        {
            break;
        }


        for (int i = 0; i < m - 1; i++)
        {
            p = p->next;
            
            if (p == L)
            {
                p = p->next;
            }
        }

        
        if (p->next == L)
        {
            p = p->next;  
        }

        LinkNode *q = p->next;
        outSeq[count++] = q->data;  
        p->next = q->next;  
        free(q);
    }
    free(L);  
    L = NULL;
}

// 销毁链表
void DestroyList(LinkNode *&L)
{
    if (L == NULL)
        return;
    LinkNode *p = L->next;
    LinkNode *q;
    while (p != L)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(L);
    L = NULL;
}

int main()
{
    int n, s, m;
    printf("请输入人数n、开始位置s和报数m: ");
    scanf("%d %d %d", &n, &s, &m);

    // 检查输入合法性
    if (n <= 0 || s < 1 || s > n || m <= 0)
    {
        printf("输入不合法\n");
        return 1;
    }

    LinkNode *L;
    CreateCircularList(L, n);

    int *outSeq = (int *)malloc(n * sizeof(int));
    if (outSeq == NULL)
    {
        printf("内存分配失败\n");
        DestroyList(L);
        return 1;
    }

    Josephus(L, n, s, m, outSeq);

    printf("出局序列为: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", outSeq[i]);
    }
    printf("\n");

    free(outSeq);
    return 0;
}