#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef int ElemType;

typedef struct
{
    ElemType data[MaxSize]; // 存储空间
    int length;             // 长度
} SqList;

// 初始化线性表
void InitList(SqList *&L)
{
    L = (SqList *)malloc(sizeof(SqList));
    L->length = 0;
}

// 销毁线性表
void DestroyList(SqList *&L)
{
    free(L);
    L = NULL;
}

// 判断是否为空
int ListEmpty(SqList *L)
{
    return (L->length == 0);
}

// 求长度
int ListLength(SqList *L)
{
    return L->length;
}

// 输出线性表
void DispList(SqList *L)
{
    int i;
    for (i = 0; i < L->length; i++)
        printf("%d ", L->data[i]);
    printf("\n");
}

// 取元素
int GetElem(SqList *L, int i, ElemType &e)
{
    if (i < 1 || i > L->length)
        return 0; // 越界
    e = L->data[i - 1];
    return 1;
}

// 按值查找
int LocateElem(SqList *L, ElemType e)
{
    int i = 0;
    while (i < L->length && L->data[i] != e)
        i++;
    if (i >= L->length)
        return 0; // 不存在
    else
        return i + 1; // 返回逻辑位置
}

// 插入
int ListInsert(SqList *&L, int i, ElemType e)
{
    int j;
    if (i < 1 || i > L->length + 1 || L->length == MaxSize)
        return 0; // 越界
    for (j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return 1;
}

// 删除
int ListDelete(SqList *&L, int i, ElemType &e)
{
    int j;
    if (i < 1 || i > L->length)
        return 0;
    e = L->data[i - 1];
    for (j = i; j < L->length; j++)
        L->data[j - 1] = L->data[j];
    L->length--;
    return 1;
}

// 求并集
void UnionList(SqList *&La, SqList *Lb)
{
    int i, la_len, lb_len;
    ElemType e;
    la_len = ListLength(La);
    lb_len = ListLength(Lb);
    for (i = 1; i <= lb_len; i++)
    {
        GetElem(Lb, i, e);
        if (!LocateElem(La, e))
            ListInsert(La, ++la_len, e);
    }
}

// 创建线性表
void CreateList(SqList *&L, ElemType a[], int n)
{
    int i;
    L = (SqList *)malloc(sizeof(SqList));
    for (i = 0; i < n; i++)
        L->data[i] = a[i];
    L->length = n;
}

int main()
{
    SqList *La, *Lb;
    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {2, 4, 8, 10};
    int n1 = 5, n2 = 4;
    CreateList(La, a1, n1);
    CreateList(Lb, a2, n2);
    printf("原La: ");
    DispList(La);
    printf("原Lb: ");
    DispList(Lb);
    UnionList(La, Lb);
    printf("并集La: ");
    DispList(La);
    DestroyList(La);
    DestroyList(Lb);
    return 0;
}
