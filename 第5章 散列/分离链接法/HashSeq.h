#ifndef _HashSeq_H
#define _HashSeq_H

struct ListNode;                   //列表节点
typedef struct ListNode *List;     //列表指针
typedef List *Lists;               //列表数组
typedef struct ListNode *Position; //列表位置

struct HashTbl;                    //哈希表本体
typedef struct HashTbl *HashTable; //哈希表指针
typedef int ElementType;

HashTable InitializeTable(int);        //初始化
Position Find(ElementType, HashTable); //查找指定数字
int Hash(ElementType, HashTable);      //哈希函数
void Insert(ElementType, HashTable);   //插入数据
void Delete(ElementType, HashTable);   //删除数据
void DestoryTable(HashTable);          //清空哈希表
void PrintTable(HashTable);            //输出表格

#endif