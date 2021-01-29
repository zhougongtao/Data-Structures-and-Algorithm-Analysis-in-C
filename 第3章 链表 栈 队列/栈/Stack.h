#ifndef _Stack_H
#define _Stack_H

struct Node;
typedef struct Node *PtrToNode; // 节点指针
typedef PtrToNode Stack;        // 指向栈
typedef int ElementType;        // 内容类型

int IsEmpty(Stack S);              //是否为空
Stack CreateStack(void);           //创建栈
void DisposeStack(Stack S);        //销毁栈 释放哨兵节点
void MakeEmpty(Stack S);           // 清空栈 清空内容
void Push(ElementType X, Stack S); //压入栈
void Pop(Stack S);                 // 弹出栈
ElementType Top(Stack S);          //顶层内容

#endif