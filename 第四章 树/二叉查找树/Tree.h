#ifndef _Tree_H
#define _Tree_H

struct TreeNode;                     //树节点
typedef struct TreeNode *Position;   //节点地址
typedef struct TreeNode *SearchTree; //搜索树指针
typedef int ElementType;

SearchTree MakeEmpty(SearchTree T);             //生成空树
Position Find(ElementType X, SearchTree T);     //找到指定值
Position FindMin(SearchTree T);                 //找到最小值 递归
Position FindMax(SearchTree T);                 //找到最大值 循环
SearchTree Insert(ElementType X, SearchTree T); //插入值
SearchTree Delete(ElementType X, SearchTree T); //删除值
void PrintFirst(SearchTree T);                  //先序遍历
void ToElement(Position P, SearchTree S);       //地址转数字

#endif