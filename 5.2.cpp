#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 100 // 定义队列最大容量

// 定义任务
typedef struct
{
    char name[20];
    int time; // 剩余处理时间
} Task;

typedef Task ElemType;

// 循环队列
typedef struct
{
    ElemType data[MaxSize];
    int front;
    int rear;
} SqQueue;

// 初始化
void InitQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

// 入队
void EnQueue(SqQueue &Q, ElemType e)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
    {
        printf("队列已满\n");
        return;
    }
    Q.data[Q.rear] = e; // 任务入队
    Q.rear = (Q.rear + 1) % MaxSize;
}

// 出队
void DeQueue(SqQueue &Q, ElemType &e)
{
    if (Q.front == Q.rear)
    {
        printf("队列为空\n");
        return;
    }
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
}

// 销毁
void DestroyQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

// 判空
bool QueueEmpty(SqQueue &Q)
{
    return Q.front == Q.rear;
}

// 队列长度
int QueueLength(SqQueue &Q)
{
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}

int main()
{
    SqQueue q;
    InitQueue(q);

    int n, q_time;
    printf("请输入任务数量n和时间片q\n");
    scanf("%d %d", &n, &q_time);

    // 输入n个任务并加入队列
    ElemType task;
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d个任务的名称和处理时间\n", i + 1);
        scanf("%s %d", task.name, &task.time);
        EnQueue(q, task);
    }

    int total_time = 0;
    ElemType current;

    while (!QueueEmpty(q))
    {
        DeQueue(q, current);

        int process = (current.time > q_time) ? q_time : current.time;
        total_time += process;
        current.time -= process;

        if (current.time == 0)
        {
            printf("任务%s完成时间：%d ms\n", current.name, total_time);
        }
        else
        {
            EnQueue(q, current);
        }
    }
    DestroyQueue(q);
    return 0;
}