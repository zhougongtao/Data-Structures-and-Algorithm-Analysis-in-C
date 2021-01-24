#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>

// 实现
struct SplayNode
{
    ElementType Element;
    SplayTree Left;
    SplayTree Right;
};

/*
    函数实现
*/

SplayTree Insert(ElementType X, SplayTree T)
{
    SplayTree TmpNode = (SplayTree)malloc(sizeof(struct SplayNode));
    TmpNode->Element = X;
    TmpNode->Left = NULL;
    TmpNode->Right = NULL;

    if(T == NULL)
    {
        T = TmpNode;
    }
    else
    {
        T = Splay(X, T);
        if(X < T->Element)
        {
            TmpNode->Left = T->Left;
            TmpNode->Right = T;
            T->Left = NULL;
            T = TmpNode;
        }
        else if (X > T->Element)
        {
            TmpNode->Left = T;
            TmpNode->Right = T->Right;
            T->Right = NULL;
            T = TmpNode;
        }
        else
            return T;
    }
    return T;
}

SplayTree Delete(ElementType X, SplayTree T)
{
    if(T == NULL)
    {
        printf("SplayTree is empty !!!");
        return NULL;
    }
    else
    {
        Position TmpNode = NULL;
        T = Splay(X, T);
        if(T->Left == NULL)
            TmpNode = T->Right;
        else
        {
            TmpNode = T->Left;
            TmpNode = Splay(X, TmpNode);
            TmpNode->Right = T->Right;
        }
        free(T);
        T = TmpNode;
    }
    return T;
}   

SplayTree Search(ElementType X, SplayTree T)
{
    return Splay(X, T);
}

/*
    Splay 展开
*/

SplayTree Splay(ElementType X, SplayTree T)
{
    struct SplayNode Header;
    Header.Left = Header.Right = NULL;

    Position LeftTreeMax = &Header;
    Position RightTreeMin = &Header;

    while (X != T->Element)
    {
        if (X < T->Element)
        {
            //不存在子树 退出
            if (T->Left == NULL)
                break;

            // zig-zig
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);

            //连接到右子树
            RightTreeMin->Left = T;
            RightTreeMin = T;
            T = T->Left;
        }
        else
        {
            //不存在子树 退出
            if(T->Right == NULL)
                break;

            // zag-zag
            if(X > T->Right->Element)
                T = SingleRotateWithRight(T);

            //连接到左子树
            LeftTreeMax->Right= T;
            LeftTreeMax = T;
            T = T->Right;
        }
    }
    //处理T节点剩余的子树
    LeftTreeMax->Right = T->Left;
    RightTreeMin->Left = T->Right;
    //左右子树组合
    //此处左右关系是相反的
    //因为LeftTreeMax/RightTreeMin获取子树时就是相反的方向
    T->Left = Header.Right;
    T->Right = Header.Left;
    return T;
}

SplayTree SingleRotateWithLeft(SplayTree T)
{
    SplayTree K = T->Left;
    T->Left = K->Right;
    K->Right = T;
    return K;
}

SplayTree SingleRotateWithRight(SplayTree T)
{
    SplayTree K = T->Right;
    T->Right = K->Left;
    K->Left = K;
    return K;
}

/*
    dot代码输出
*/

static void dot(SplayTree T)
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

void PrintDot(SplayTree T)
{
    printf("\n");
    printf(".dot Coding:\n");
    printf("digraph SearchTree {\n");
    dot(T);
    printf("}\n\n");
}

int main()
{
    SplayTree T = NULL;
    for (int i = 1; i <= 32; i++)
        T = Insert(i, T);

    //对应书中 4-47 ~ 4-55 Splay展开
    for (int i = 1; i <= 9;i++)
    {
        printf("\nSearch %d\n", i);
        T = Search(i, T);
        PrintDot(T);
    }

    //删除操作
    T = Delete(8, T);
    T = Delete(9, T);
    T = Delete(1, T);
    T = Delete(2, T);
    PrintDot(T);
    return 0;
}