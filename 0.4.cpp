#include <stdio.h>
#include <stdlib.h>
#define Max_size 10
typedef struct
{
    int data[Max_size];
    int length;
} SeqList;

void InitList(SeqList *L)
{
    L->length = 0;
} // 初始化

int List_insert(SeqList *L, int i, int e)
{
    if (i < 1 || i > L->length + 1)
        return 0; // 合法性检查
    if (L->length >= Max_size)
        return 0; // 表满
    for (int j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return 1;
} // 插入

int printList(SeqList L)
{
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.data[i]);
    }
    printf("\n");
    return 1; // 打印
}

int main()
{
    SeqList L;
    InitList(&L);
    int input;
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &input);
        List_insert(&L, i + 1, input);
    } // 输入
    printList(L);
    printf("长度: %d\n", L.length);
    return 0;
}