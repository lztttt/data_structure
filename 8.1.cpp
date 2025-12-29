#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct
{
    KeyType key;
} RecType;

// 顺序查找
int SeqSearch(RecType R[], int n, KeyType k)
{
    int i = 0;
    R[n].key = k;
    printf("顺序查找：\n");
    while (R[i].key != k)
    {
        printf("第%d次：%d\n", i + 1, R[i].key);
        i++;
    }
    printf("第%d次：%d\n", i + 1, R[i].key);
    if (i == n)
    {
        printf("\n顺序查找结果：元素不存在\n");
        return 0;
    }
    else
    {
        printf("\n顺序查找成功，其逻辑位序为：%d\n", i + 1);
        return i + 1;
    }
}

// 二分查找
int BinSearch(RecType R[], int n, KeyType k)
{
    int low = 0, high = n - 1, mid;
    printf("二分查找：\n");
    int count = 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("第%d次：%d\n", count, R[mid].key);
        count++;
        if (R[mid].key == k)
        {
            printf("\n二分查找成功，其逻辑位序为：%d\n", mid + 1);
            return mid + 1;
        }
        else if (k < R[mid].key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    printf("\n元素不存在\n");
    return 0;
}
int main()
{
    KeyType keys[] = {3, 4, 5, 7, 24, 30, 42, 54, 63, 72, 87, 95};
    int n = sizeof(keys) / sizeof(KeyType);
    RecType R[n + 1];

    for (int i = 0; i < n; i++)
    {
        R[i].key = keys[i];
    }
    scanf("%d", &R[n].key);
    KeyType target = R[n].key;
    printf("查找元素：%d\n", target);
    
    SeqSearch(R, n, target);

    BinSearch(R, n, target);
    return 0;
}