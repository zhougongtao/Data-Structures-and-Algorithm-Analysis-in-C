#include "HashQuad.h"
#include <stdio.h>
#include <stdlib.h>

// 结构体
enum KindOfEntry
{
    Legitimate, //有数字
    Empty,      //为空
    Deleted     //被删除
};

/* Deleted: 由于使用平方探测法，在被删除的数据之后可能还存在其他数字，不能用empty代替*/

struct HashEntry
{
    ElementType Element;
    enum KindOfEntry Info;
};

struct HashTbl
{
    int TableSize;
    Cell *TheCells; //列表数组（指针的指针）
};

// 函数实现

HashTable InitializeTable(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = TableSize;
    H->TheCells = (Cells)malloc(sizeof(Cell) * TableSize);
    for (int i = 0; i < TableSize; i++)
        H->TheCells[i].Info = Empty;
    return H;
}

Position Find(ElementType key, HashTable H)
{
    Position P = Hash(key, H);
    int CollisionNum = 0;
    while (H->TheCells[P].Info != Empty && H->TheCells[P].Element != key)
    {
        //平方列加的迭代式
        //F(i) = F(i-1) + 2i - 1
        P += 2 * (++CollisionNum) - 1;
        if (P > H->TableSize)
            P -= H->TableSize;
    }
    return P;
}

int Hash(ElementType key, HashTable H)
{
    return key % H->TableSize;
}

void Insert(ElementType key, HashTable H)
{
    Position P = Find(key, H);
    if (H->TheCells[P].Info == Legitimate)
        printf("key is exsit in HashTable\n");
    else
    {
        H->TheCells[P].Info = Legitimate;
        H->TheCells[P].Element = key;
    }
}

void Delete(ElementType key, HashTable H)
{
    Position P = Find(key, H);
    if (H->TheCells[P].Info == Empty)
        printf("key is not in HashTable\n");
    else
        H->TheCells[P].Info = Deleted;
}

void PrintTable(HashTable H)
{
    printf("\n");
    printf("==============================\n");
    printf("  mod |  value     | Kind \n");
    printf("------------------------------\n");
    for (int i = 0; i < H->TableSize; i++)
    {
        printf("%4d  |", i);
        printf("%11d | ", H->TheCells[i].Element);
        switch (H->TheCells[i].Info)
        {
        case 0:
            printf("Legitimate");
            break;
        case 1:
            printf("Empty");
            break;
        case 2:
            printf("Deleted");
            break;
        default:
            break;
        }
        printf("\n");
    }
}

static int NextPrime(int k)
{
    for (k = k + 1;; k++)
    {
        int flag = 1;
        for (int j = 2; j < k / 2; j++)
            if (k % j == 0)
                flag = 0;
        if(flag)
            break;
    }
    printf("\nnew Size: %d ", k);
    return k;
}

HashTable Rehash(HashTable H)
{
    Cell *OldCells = H->TheCells;
    int OldSize = H->TableSize;

    int newSize = NextPrime(2 * OldSize);
    H = InitializeTable(newSize);
    for (int i = 0; i < OldSize; i++)
        if (OldCells[i].Info == Legitimate)
            Insert(OldCells[i].Element, H);
        
    free(OldCells);
    return H;
}

int main()
{
    HashTable H = InitializeTable(17);

    printf("\ninsert");
    for (int i = 1; i <= 10; i++)
        Insert(i * i, H);
    PrintTable(H);

    printf("\ndelete");
    Delete(100, H);
    Delete(81, H);
    Delete(4, H);
    Delete(36, H);
    Delete(16, H);
    Delete(9, H);
    Delete(49, H);
    PrintTable(H);

    printf("\ninsert same");
    Insert(16, H);
    Insert(9, H);
    Insert(49, H);
    PrintTable(H);

    printf("\nrehash");
    H = Rehash(H);
    PrintTable(H);

    return 0;
}