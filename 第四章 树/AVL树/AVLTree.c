#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>

struct AVLNode
{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

//函数声明

static int Height(Position P) //返回高度，空树为-1
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

AVLTree MakeEmpty(AVLTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, AVLTree T)
{
    if (T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

Position FindMin(AVLTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

Position FindMax(AVLTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

/* 
    插入函数 4种情况：
        1. 插入左儿子的左子树 左侧单旋转
        2. 插入左儿子的右子树 左侧双旋转
        3. 插入右儿子的左子树 右侧双旋转
        4. 插入右儿子的右子树 右侧单旋转

*/
static Position SingleRotateWithLeft(Position K2) //左侧单旋转
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = __max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = __max(Height(K1->Left), Height(K1->Right)) + 1;
    return K1;
}

static Position SingleRotateWithRight(Position K1) //右侧单旋转
{
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K2->Height = __max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = __max(Height(K1->Left), Height(K1->Right)) + 1;
    return K2;
}

static Position DoubleRotateWithLeft(Position K3) //左侧双旋转
{
    K3->Left = SingleRotateWithRight(K3->Left);
    return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight(Position K1)
{
    K1->Right = SingleRotateWithLeft(K1->Right);
    return SingleRotateWithRight(K1);
}

AVLTree Insert(ElementType X, AVLTree T) //插入函数
{
    if (T == NULL) //该树为空时
    {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Left = NULL;
        T->Right = NULL;
    }
    else if (X < T->Element) //X偏小
    {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->Element) //X偏大
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
        {
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    T->Height = __max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

Position Delete(ElementType X, AVLTree T)
{
    Position TmpCell;
    if (T == NULL)
        printf("T is NULL");
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right)
    {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else
    {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }

    //平衡调整
    if (T == NULL)
        return T;
    if (Height(T->Left) - Height(T->Right) == 2)
    {
        if (X < T->Left->Element)
            T = SingleRotateWithLeft(T);
        else
            T = DoubleRotateWithLeft(T);
    }
    if (Height(T->Right) - Height(T->Left) == 2)
    {
        if (X > T->Right->Element)
            T = SingleRotateWithRight(T);
        else
            T = DoubleRotateWithRight(T);
    }
    T->Height = __max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

/*
    dot代码输出
*/
static void dot(AVLTree T)
{
    if (T == NULL)
        return;
    if (T->Left != NULL)
    {
        printf("    %d->%d;\n", T->Element, T->Left->Element);
        dot(T->Left);
    }
    if (T->Right != NULL)
    {
        printf("    %d->%d;\n", T->Element, T->Right->Element);
        dot(T->Right);
    }
}

void PrintDot(AVLTree T)
{
    printf("\n");
    printf(".dot Coding:\n");
    printf("digraph SearchTree {\n");
    dot(T);
    printf("}\n\n");
}

int main()
{
    AVLTree T = NULL;
    for (int i = 0; i <= 10; i++)
    {
        T = Insert(i, T);
        //PrintDot(T);
    }
    T = Delete(2, T);
    T = Delete(0, T);
    PrintDot(T);
    return 0;
}