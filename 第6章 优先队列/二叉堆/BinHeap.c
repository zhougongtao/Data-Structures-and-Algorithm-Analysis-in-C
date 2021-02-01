#include "BinHeap.h"
#include <stdio.h>
#include <stdlib.h>
#define MinData -1e9 //宏定义最小值
struct HeapStruct
{
    int Capacity;          //容量
    int Size;              //当前大小
    ElementType *Elements; //数组队列
};

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;
    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType *)malloc((MaxElements + 1) * sizeof(ElementType));
    H->Elements[0] = MinData;
    H->Capacity = MaxElements;
    H->Size = 0;
    return H;
}

int IsFull(PriorityQueue H)
{
    return H->Capacity == H->Size ? 1 : 0;
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0 ? 1 : 0;
}

void Insert(ElementType X, PriorityQueue H)
{
    if (IsFull(H))
    {
        printf("PriotityQueue is empty !!! \n");
        return;
    }
    int num = ++H->Size;
    while (X < H->Elements[num / 2])
    {
        H->Elements[num] = H->Elements[num / 2];
        num /= 2;
    }
    H->Elements[num] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    if (IsEmpty(H))
    {
        printf("PriorityQueue is empty !!! \n");
        return H->Elements[0];
    }
    int MinElement = H->Elements[1];        //最小的数字
    int LastElement = H->Elements[H->Size]; //最后一位数字
    H->Size--;

    int num = 1;
    while (num * 2 <= H->Size)
    {
        num *= 2;
        if ((num + 1) <= H->Size && H->Elements[num + 1] < H->Elements[num])
            num++;
        if (LastElement > H->Elements[num])
            H->Elements[num / 2] = H->Elements[num];
        else
            break;
    }
    H->Elements[num / 2] = LastElement;
    return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
    if (IsEmpty(H))
    {
        printf("PriorityQueue is empty !!! \n");
        return H->Elements[0];
    }
    else
        return H->Elements[1];
}

static void dot(PriorityQueue H)
{
    if (H == NULL)
        return;
    for (int i = 1; i <= H->Size / 2; i++)
    {
        if (i * 2 <= H->Size)
            printf("    %d->%d;\n", H->Elements[i], H->Elements[i * 2]);
        if (i * 2 + 1 <= H->Size)
            printf("    %d->%d;\n", H->Elements[i], H->Elements[i * 2 + 1]);
    }
}

void PrintDot(PriorityQueue H)
{
    printf("\n");
    printf(".dot Coding:\n");
    printf("digraph Heap {\n");
    dot(H);
    printf("}\n\n");
}

int main()
{
    PriorityQueue H = Initialize(64);
    for (int i = 10; i >= 0; i--)
        Insert(i, H);
    printf("delete: %d\n", DeleteMin(H));
    printf("delete: %d\n", DeleteMin(H));
    PrintDot(H);

    return 0;
}