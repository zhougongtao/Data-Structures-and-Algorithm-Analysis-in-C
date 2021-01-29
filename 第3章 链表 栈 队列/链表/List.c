#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// 结构体声明
struct Node
{
    ElementType Element;
    struct Node *Next;
};

/*  函数声明  */
List MakeEmpty(List L)
{
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P)
{
    return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P = L->Next;
    while (P != NULL && P->Element != X)
        P = P->Next;
    return P;
}

Position FindPrevious(ElementType X, List L)
{
    Position P = L;
    while (P->Next != NULL && P->Next->Element != X)
        P = P->Next;
    return P;
}

void PrintList(List L)
{
    while (L->Next != NULL)
    {
        L = L->Next;
        printf("-> %d ", L->Element);
    }
    printf("   over\n");
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P))
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell = (Position)malloc(sizeof(struct Node));
    if (TmpCell == NULL)
        printf("Out of space");
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    while (L->Next != NULL)
    {
        Position P = L->Next;
        L->Next = P->Next;
        free(P);
    }
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
    return P->Next;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}

int main()
{
    //代码测试
    List L;
    L = MakeEmpty(L);
    printf("%d\n", IsEmpty(L));
    printf("%d\n", IsLast(L));

    Insert(1, L, L);
    Insert(2, L, L);
    Insert(3, L, L);
    PrintList(L);

    printf("%d\n", Find(3, L));
    printf("%d\n", Find(2, L));
    printf("%d\n", FindPrevious(2, L));

    Delete(2, L);
    PrintList(L);

    DeleteList(L);
    PrintList(L);

    printf("Successful");
    return 0;
}