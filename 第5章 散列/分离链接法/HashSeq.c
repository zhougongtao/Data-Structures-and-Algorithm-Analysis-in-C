#include<stdlib.h>
#include<stdio.h>
#include"HashSeq.h"

// 结构体
struct ListNode
{
    ElementType Element;
    Position Next;
};

struct HashTbl
{
    int TableSize;
    List *TheLists;  //列表数组（指针的指针）
};

// 函数实现

HashTable InitializeTable(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = TableSize;
    H->TheLists = (Lists)malloc(sizeof(List) * TableSize);
    
    //申请哨兵节点们
    for (int i = 0; i < TableSize; i++)
    {
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        H->TheLists[i]->Next = NULL;
        H->TheLists[i]->Element = i;
    }
    return H;
}

Position Find(ElementType key, HashTable H)
{
    int i = Hash(key, H);
    List L = H->TheLists[i];
    Position P = L->Next;
    while(P != NULL && P->Element != key)
        P = P->Next;
    return P;
}   

int Hash(ElementType key, HashTable H)
{
    return key % H->TableSize;
}

void Insert(ElementType key, HashTable H)
{
    Position P = Find(key, H);
    if(P)
        printf("key is exsit in HashTable\n");
    else
    {
        int i = Hash(key, H);
        List L = H->TheLists[i];

        List TmpNode = (List)malloc(sizeof(struct ListNode));
        TmpNode->Element = key;
        TmpNode->Next = L->Next;

        L->Next = TmpNode;
    }
}

void Delete(ElementType key, HashTable H)
{
    Position P = Find(key, H);
    if(P == NULL)
        printf("key is not in HashTable\n");
    else
    {
        int i = Hash(key, H);
        List L = H->TheLists[i];

        Position P = L->Next;
        Position PP = L;
        while(P!= NULL && P->Element!=key)
        {
            P = P->Next;
            PP = PP->Next;
        }
        PP->Next = P->Next;
        free(P);
    }
}

void PrintTable(HashTable H)
{
    printf("\n");
    printf("============================\n");
    printf("  mod |  link \n");
    for (int i = 0; i < H->TableSize;i++)
    {
        printf("%4d  |", H->TheLists[i]->Element);
        Position P = H->TheLists[i]->Next;
        while(P != NULL)
        {
            printf(" => %2d", P->Element);
            P = P->Next;
        }
        printf("\n");
    }
}

int main()
{
    HashTable H = InitializeTable(10);
    for (int i = 1; i <= 10; i++)
        Insert(i * i, H);
    PrintTable(H);

    Delete(100, H);
    Delete(81, H);
    Delete(4, H);
    Delete(36, H);
    Delete(16, H);
    Delete(9, H);
    Delete(49, H);
    PrintTable(H);

    return 0;
}