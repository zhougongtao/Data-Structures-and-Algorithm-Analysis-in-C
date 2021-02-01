#ifndef _BinHeap_H
#define _BinHeap_H

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(int MaxElements);   //初始化
int IsEmpty(PriorityQueue H);                //是否为空
int IsFull(PriorityQueue H);                 //是否已满
void Insert(ElementType X, PriorityQueue H); //插入
ElementType DeleteMin(PriorityQueue H);      //删除最小值
ElementType FindMin(PriorityQueue H);        //找到最大值
void PrintDot(PriorityQueue T);              //输出dot文件代码

#endif
