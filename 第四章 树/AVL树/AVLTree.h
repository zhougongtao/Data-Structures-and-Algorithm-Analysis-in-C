#ifndef _AVLTree_H
#define _AVLTree_H

struct AVLNode;                   //树节点
typedef struct AVLNode *Position; //结点指针
typedef struct AVLNode *AVLTree;  //AVL树指针
typedef int ElementType;          //数据类型

AVLTree MakeEmpty(AVLTree T);             //清空树结构
Position Find(ElementType X, AVLTree T);  //找到特定值
Position FindMin(AVLTree T);              //找到最小值
Position FindMax(AVLTree T);              //找到最大值
AVLTree Insert(ElementType X, AVLTree T); //插入操作
AVLTree Delete(ElementType X, AVLTree T); //删除操作
void PrintDot(AVLTree T);                 //输出dot文件代码
#endif