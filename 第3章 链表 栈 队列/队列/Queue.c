#include"Queue.h"
#include<stdio.h>
#include<stdlib.h>

struct Node{
    ElementType Element;
    PtrToNode Pre;
    PtrToNode Next;
};

struct QueueRecord{
    PtrToNode Front;
    PtrToNode Rear;
};

// 函数声明
int IsEmpty(Queue Q)
{
    return Q->Front->Next == Q->Rear;
}

Queue CreateQueue(void)
{
    Queue TmpQueue = (Queue)malloc(sizeof(struct QueueRecord));
    PtrToNode fnode = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode rnode = (PtrToNode)malloc(sizeof(struct Node));
    TmpQueue->Front = fnode;
    TmpQueue->Rear = rnode;
    TmpQueue->Front->Next = TmpQueue->Rear;
    TmpQueue->Front->Pre = NULL;
    TmpQueue->Rear->Next = NULL;
    TmpQueue->Rear->Pre = TmpQueue->Front;
    return TmpQueue;
}

void MakeEmpty(Queue Q)
{
    while(!IsEmpty(Q))
    {
        PtrToNode TmpNode = Q->Front->Next;
        Q->Front->Next = TmpNode->Next;
        free(TmpNode);
    }
}

void Enqueue(ElementType X, Queue Q)
{
    PtrToNode TmpNode = (PtrToNode)malloc(sizeof(struct Node));
    TmpNode->Element = X;
    TmpNode->Next = Q->Rear;
    TmpNode->Pre = Q->Rear->Pre;
    Q->Rear->Pre->Next = TmpNode;
    Q->Rear->Pre = TmpNode;
}

void Dequeue(Queue Q)
{
    PtrToNode TmpNode = Q->Front->Next;
    TmpNode->Next->Pre = Q->Front;
    Q->Front->Next = TmpNode->Next;
    free(TmpNode);
}

void PrintQueue(Queue Q)
{
    PtrToNode P = Q->Front;
    while(P->Next != Q->Rear)
    {
        P = P->Next;
        printf("-> %d ", P->Element);
    }
    printf("\n");
}

ElementType Front(Queue Q)
{
    return Q->Front->Next->Element;
}

int main(){
    Queue Q = CreateQueue();
    printf("%d\n", IsEmpty(Q));

    Enqueue(1, Q);
    Enqueue(2, Q);
    Enqueue(3, Q);
    PrintQueue(Q);

    Dequeue(Q);
    PrintQueue(Q);
    Dequeue(Q);
    PrintQueue(Q);

    Enqueue(1, Q);
    Enqueue(2, Q);
    PrintQueue(Q);

    MakeEmpty(Q);
    PrintQueue(Q);

    return 0;
}