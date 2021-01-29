#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

// 函数声明

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack(void)
{
    Stack S = (Stack)malloc(sizeof(struct Node));
    if(S == NULL)
        printf("Out of space");
    S->Next = NULL;
    return S;
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
        printf("Stack is NULL");
    else
        while(!IsEmpty(S))
            Pop(S);
}

void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;
    TmpCell = (PtrToNode)malloc(sizeof(struct Node));
    if(TmpCell == NULL)
        printf("Out of space ");
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

void Pop(Stack S)
{
    PtrToNode FirstCell;
    if(IsEmpty(S))
        printf("Empty Stack");
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
    
}

ElementType Top(Stack S)
{
    if(!IsEmpty(S))
        return S->Next->Element;
    printf("Empty Stack ");
    return -1;
}

int main()
{
    Stack S = CreateStack();
    Push(1, S);
    Push(2, S);
    Push(3, S);
    printf("%d\n", Top(S));
    Pop(S);
    printf("%d\n", Top(S));
    MakeEmpty(S);
    printf("%d\n", Top(S));

    return 0;
}