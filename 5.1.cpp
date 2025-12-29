#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

typedef int ElemType;
typedef struct
{
    ElemType data[MaxSize];
    int front;
    int rear;
} SqQueue;

void InitQueue(SqQueue &Q) // 初始化
{
    Q.front = 0;
    Q.rear = 0;
}

void EnQueue(SqQueue &Q, ElemType e) // 进队
{
    if ((Q.rear + 1) % MaxSize == Q.front)
    {
        printf("队列满\n");
        return;
    }
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MaxSize;
}

void DeQueue(SqQueue &Q, ElemType &e) // 出队
{
    if (Q.front == Q.rear)
    {
        printf("队列空\n");
        return;
    }
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
}

void DestroyQueue(SqQueue &Q) // 销毁队列
{
    Q.front = 0;
    Q.rear = 0;
}

bool QueueEmpty(SqQueue &Q) // 判空
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

int QueueLength(SqQueue &Q) // 队列长度
{
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}

int main()
{
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);
    EnQueue(Q, 6);
    ElemType e;
    DeQueue(Q, e);
    printf("出队元素: %d\n", e);
    DeQueue(Q, e);
    printf("出队元素: %d\n", e);
    printf("当前队列长度: %d\n", QueueLength(Q));
    DestroyQueue(Q);
    return 0;
}