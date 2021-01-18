#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

//函数声明

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
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

Position FindMin(SearchTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}
/*
    该插入函数返回树指针 T；对各树的子树 重新赋予指针
    
    书上使用了递归，但是显得没必要
*/
SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL) //插入空树
    {
        T = (SearchTree)malloc((sizeof(struct TreeNode)));
        T->Element = X;
        T->Left = NULL;
        T->Right = NULL;
    }
    else
    {
        if (X < T->Element)
            T->Left = Insert(X, T->Left);
        else
            T->Right = Insert(X, T->Right);
    }
    return T;
}
/*
    删除节点分为五种情况
        1. T为空 ：报错
        2. T数值较大：去左子树
        3. T数值较小：去右子树
        4. 左右都有子树
           选取一个节点进行数值的替换，将情况4 转变为情况5
           要保证二叉树的结构，有两种选择
           ->左子树中最大的数字 a
           ->右子树中最小的数字 b（默认方案）
           原因：对树T所有节点进行排序后，
                大小关系如下：* * a X b * *（*代表其他数字）
        5. 没有或仅有一个子树
           没有子树：直接free
           一个子树：指针指向子树，释放 T
*/   

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;
    if (T == NULL)
        printf("Element not found");    //为空
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);   //T数值较大
    else if (X > T->Element)
        T->Right = Delete(X, T->Right); //T数值较小
    else if (T->Left && T->Right)       //左右都有子树
    {                                
        TmpCell = FindMin(T->Right);    
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else                                //没有或仅有一个子树
    {
        TmpCell = T;
        if (T->Left = NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}

void PrintFirst(SearchTree T)
{
    if (T != NULL)
    {
        printf(" %d ", T->Element);
        PrintFirst(T->Left);
        PrintFirst(T->Right);
    }
}

void ToElement(Position P, SearchTree T)
{
    if (T == NULL)
        return;
    else if (T == P)
    {
        printf(" %d\n", T->Element);
    }
    else
    {
        ToElement(P, T->Left);
        ToElement(P, T->Right);
    }
}

int main()
{
    SearchTree T = NULL;

    T = Insert(3, T);
    T = Insert(2, T);
    T = Insert(1, T);
    T = Insert(5, T);
    T = Insert(4, T);
    PrintFirst(T);

    printf("Max:");
    ToElement(FindMax(T), T);
    printf("Min:");
    ToElement(FindMin(T), T);

    Delete(1, T);
    PrintFirst(T);
    printf("\n");

    Delete(3, T);
    PrintFirst(T);
    printf("\n");

    return 0;
}