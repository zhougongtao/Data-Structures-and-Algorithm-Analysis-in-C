#ifndef _Splay_H
#define _Splay_H

struct SplayNode;                    //树节点
typedef struct SplayNode *SplayTree; //树指针
typedef struct SplayNode *Position;  //位置指针
typedef int ElementType;

SplayTree MakeEmpty(SplayTree);
SplayTree Find(ElementType, SplayTree); //找到指定数字
SplayTree FindMax(SplayTree);           //找到最大值
SplayTree FindMin(SplayTree);           //找到最小值

SplayTree Insert(ElementType, SplayTree);   //插入函数
SplayTree Delete(ElementType, SplayTree);   //删除函数
SplayTree Search(ElementType, SplayTree);  //查找数值

SplayTree Splay(ElementType, SplayTree);       //展开
SplayTree SplaySimple(ElementType, SplayTree); //简化版展开
SplayTree SingleRotateWithLeft(SplayTree);     //左侧单旋转
SplayTree SingleRotateWithRight(SplayTree);    //右侧单旋转

void PrintDot(SplayTree); //输出树格式 .dot

#endif