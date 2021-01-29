#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>

// 实现
struct SplayNode
{
    ElementType Element;
    SplayTree Parent;
    SplayTree Left;
    SplayTree Right;
};

// 函数实现

/*
    查找函数
        如果找到指定数值，返回特定位置
        如果没有找到，返回父亲的位置（用于Insert使用）
*/
SplayTree Find(ElementType X, SplayTree T)
{
    if (T->Element > X) //如果X较小 去左侧寻找
    {
        if (T->Left)
            return Find(X, T->Left);
        else
            return T;
    }
    else if (T->Element < X) //如果X较大 去右侧寻找
    {
        if (T->Right)
            return Find(X, T->Right);
        else
            return T;
    }
    else 
        return T;
}

SplayTree FindMax(SplayTree T)
{
    Position P = NULL;
    if(T == NULL)
        return NULL;
    else
    {
        P = T;
        while(P->Right)
            P = P->Right;
        Splay(P->Element, P);
    }
    return T;
}

SplayTree FindMin(SplayTree T)
{
    Position P = NULL;
    if(T == NULL)
        return NULL;
    else
    {
        P = T;
        while(P->Left)
            P = P->Left;
        Splay(P->Element, P);
    }
    return T;
}

SplayTree Insert(ElementType X, SplayTree T)
{
    SplayTree TmpNode = (SplayTree)malloc(sizeof(struct SplayNode));
    TmpNode->Right = TmpNode->Left = TmpNode->Parent = NULL;
    TmpNode->Element = X;

    // 作为初始的空树时
    if (T == NULL)
    {
        T = TmpNode;
    }
    // 当树不为空时
    else
    {
        Position P = Find(X, T); //找到父亲节点
        TmpNode->Parent = P;
        if (P->Element > X)
            P->Left = TmpNode;
        else
            P->Right = TmpNode;
        Splay(X, TmpNode);
    }
    return TmpNode; //返回调整到根的结点指针
}

SplayTree Delete(ElementType X, SplayTree T)
{
    if(T == NULL)
        printf("SplayTree is empty\n");

    T = Search(X, T);  //检索 X

    if(T == NULL)
    {
        printf("X is not exist\n");
        return T;
    }
    else
    {
        if (T->Left && T->Right)   //左右子树都存在
        {
            SplayTree L = T->Left;
            SplayTree R = T->Right;

            L->Parent = NULL;
            R->Parent = NULL;

            free(T);

            L = FindMax(L);

            L->Right = R;
            R->Parent = L;
            return L;
        }
        else if(T->Left == NULL) //左子树不存在
        {
            SplayTree TmpCell = T->Right;
            TmpCell->Parent = NULL;
            free(T);
            return TmpCell;
        }
        else if(T->Right == NULL) //右子树不存在
        {
            SplayTree TmpCell = T->Left;
            TmpCell->Parent = NULL;
            free(T);
            return TmpCell;
        }
        else  //不存在子树
        {
            free(T);
            return NULL;
        }        
    }
}

SplayTree Search(ElementType X, SplayTree T)
{
    if (T == NULL)
        return NULL;
    if (T->Element == X)
        return Splay(X, T);
    else if (T->Element > X)
        return Search(X, T->Left);
    else
        return Search(X, T->Right);
}

/*
    伸展树展开
*/

SplayTree Splay(ElementType X, SplayTree T)
{
    while ((T->Parent) != NULL)
    {
        Position P = T->Parent; //父亲节点
        Position G = P->Parent; //祖父节点

        if (P->Left == T)
        {
            if (G == NULL)
            {
                SingleRotateWithLeft(P);
            }
            else if (G->Left == P)
            {
                SingleRotateWithLeft(G);
                SingleRotateWithLeft(P);
            }
            else if (G->Right == P)
            {
                SingleRotateWithLeft(P);
                SingleRotateWithRight(G);
            }
        }
        else if (P->Right == T)
        {
            if (G == NULL)
            {
                SingleRotateWithRight(P);
            }
            else if (G->Left == P)
            {
                SingleRotateWithRight(P);
                SingleRotateWithLeft(G);
            }
            else if (G->Right == P)
            {
                SingleRotateWithRight(G);
                SingleRotateWithRight(P);
            }
        }
    } 

    return T;
}

/* 
    zig-zag 相当于两次不同方向的 zig 
    SingleRotateWithLeft/Right(P);是共同部分
    可对展开进行简化
*/

SplayTree SplaySimple(ElementType X, SplayTree T)
{
    Position P = T->Parent;
    Position G = P->Parent;

    do
    {
        if (P->Left == T)
        {
            if (G->Left == P)
                SingleRotateWithLeft(G);
            SingleRotateWithLeft(P);
        }
        else
        {
            if (G->Right == P)
                SingleRotateWithRight(G);
            SingleRotateWithRight(P);
        }

    } while ((T->Parent) != NULL);

    return T;
}

SplayTree SingleRotateWithLeft(SplayTree T)
{
    SplayTree P = T->Parent;
    SplayTree K = T->Left;

    if (K->Right) //不存在右子树，不不能设置父亲节点
        K->Right->Parent = T;
    T->Left = K->Right;
    T->Parent = K;

    K->Right = T;
    K->Parent = P;

    if (P)
    { //zig情况时，P == NULL
        if (P->Left == T)
            P->Left = K;
        else
            P->Right = K;
    }
    return T;
}

SplayTree SingleRotateWithRight(SplayTree T)
{
    SplayTree P = T->Parent;
    SplayTree K = T->Right;

    if (K->Left)
        K->Left->Parent = T;
    T->Right = K->Left;
    T->Parent = K;

    K->Left = T;
    K->Parent = P;

    if (P)
    {
        if (P->Left == T)
            P->Left = T;
        else
            P->Right = T;
    }
    return T;
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