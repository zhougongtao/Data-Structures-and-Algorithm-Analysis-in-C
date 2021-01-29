#ifndef _HashQuad_H
#define _HashQuad_H

struct HashTbl;                    //哈希表
typedef struct HashTbl *HashTable; //哈希表指针
typedef int ElementType;           //属性类型
typedef int Position;              //位置索引

struct HashEntry;               //哈希表实体
typedef struct HashEntry Cell; //实体指针
typedef Cell *Cells;            //实体指针数组

HashTable InitializeTable(int);        //初始化
Position Find(ElementType, HashTable); //查找指定数字
int Hash(ElementType, HashTable);      //哈希函数
void Insert(ElementType, HashTable);   //插入数据
void Delete(ElementType, HashTable);   //删除数据
void DestoryTable(HashTable);          //清空哈希表
void PrintTable(HashTable);            //输出表格
HashTable Rehash(HashTable);           //再散列 ,设置新表，为旧表两倍大

#endif