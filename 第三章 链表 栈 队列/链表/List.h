/*
    宏定义
    #ifndef *** //if not define  
    #define ***
    #endif
    当多个文件引用.c文件时，导致文件多次编译
    通过条件编译避免该情况发生

*/
#ifndef _List_H
#define _List_H

struct Node;
typedef int ElementType;
typedef struct Node *PtrToNode; //node指针
typedef PtrToNode List;         //指向表头Header，该指针代表这个表
typedef PtrToNode Position;     //指向表中任意位置

List MakeEmpty(List L);                         //生成哨兵节点
int IsEmpty(List L);                            //是否为空
int IsLast(Position P);                         //当前位置是否是末尾
Position Find(ElementType X, List L);           //查找
Position FindPrevious(ElementType X, List L);   //查找前一位
void PrintList(List L);                         //数据输出
void Delete(ElementType X, List L);             //指定数据删除
void Insert(ElementType X, Position P, List L); //数据插入
void DeleteList(List L);                        //数据删除
Position Header(List L);                        //哨兵节点
Position First(List L);                         //首节点
Position Advance(Position P);                   //下一个节点
ElementType Retrieve(Position P);               //返回值

#endif