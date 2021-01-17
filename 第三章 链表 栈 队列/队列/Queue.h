#ifndef _Queue_H
#define _Queue_H

struct Node;
struct QueueRecord;                //队列本体
typedef struct Node *PtrToNode;    //节点指针
typedef struct QueueRecord *Queue; //队列指针
typedef int ElementType;           //内容类型

int IsEmpty(Queue Q);                 //是否为空
Queue CreateQueue(void);              //创建队列
void DisposeQueue(Queue Q);           //销毁队列 释放哨兵节点
void MakeEmpty(Queue Q);              //清空队列 清空内容
void Enqueue(ElementType X, Queue Q); //进队
void Dequeue(Queue Q);                //出队
void PrintQueue(Queue Q);             //打印队列
ElementType Front(Queue Q);           //队首

#endif