#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

#define ElemType char

//二叉树单个节点
typedef struct BinTreeNode
{
	ElemType data;//数据域
	struct BinTreeNode *leftChild;//左子树指针
	struct BinTreeNode *rightChild;//右子树指针
}BinTreeNode;

//二叉树头结点
typedef struct BinTree
{
	BinTreeNode *root;//根部指针
	ElemType    refValue;//停止标记
}BinTree;

void initBinTree(BinTree *bt,ElemType ref);
///////////////////////////////////////////
//1创建
//使用地址
void createBinTree_1(BinTree *bt);
void createBinTree_1(BinTree *bt,BinTreeNode **t);
//使用引用
void createBinTree_2(BinTree *bt);
void createBinTree_2(BinTree *bt,BinTreeNode *&t);
//返回节点
void createBinTree_3(BinTree *bt);
BinTreeNode* createBinTree_3_(BinTree *bt);
//直接传入字符串
void createBinTree_4(BinTree *bt,char *str);
void createBinTree_4(BinTree *bt,BinTreeNode *&t,char *&str);

//////////////////////////////////////////////
//2递归遍历
//先序遍历
void preOrder(BinTree *bt);
void preOrder(BinTreeNode *t);
//中序遍历
void inOrder(BinTree *bt);
void inOrder(BinTreeNode *t);
//后序遍历
void postOrder(BinTree *bt);
void postOrder(BinTreeNode *t);
//层次遍历(需要借助队列)
void levelOrder(BinTree *bt);
void levelOrder(BinTreeNode *t);

//////////////////////////////////////////////////
//3方法
int size(BinTree *bt);//求节点个数
int size(BinTreeNode *t);
int height(BinTree *bt);//求树的深度
int height(BinTreeNode *t);
BinTreeNode* search(BinTree *bt,ElemType key);//查找节点,若找到返回地址,反之返回NULL
BinTreeNode* search(BinTreeNode *t,ElemType key);
BinTreeNode* parent(BinTree *bt,BinTreeNode *p);//求节点的父节点
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *p);
BinTreeNode* leftChild(BinTreeNode *p);//求左子树
BinTreeNode* rightChild(BinTreeNode *p);//求右子树
bool binTreeEmpty(BinTree *bt);//判断是否为空
void copy(BinTree *bt1,BinTree *bt2);//复制一棵二叉树
void copy(BinTreeNode *&t1,BinTreeNode *t2);
void binTreeClear(BinTree *bt);//清除一棵二叉树
void binTreeClear(BinTreeNode *&t);

///////////////////////////////////
//4非递归遍历(需要借助栈)
void preOrder_1(BinTree *bt);
void preOrder_1(BinTreeNode *t);
void inOrder_1(BinTree *bt);
void inOrder_1(BinTreeNode *t);
//后序遍历单独建一个工程实现
void postOrder_1(BinTree *bt);
void postOrder_1(BinTreeNode *t);

////////////////////////////////////////////
//5二叉树的恢复实现
void createBinTree_5(BinTree *bt,char *VLR,char *LVR,int n);//前序和中序
void createBinTree_5(BinTreeNode *&t,char *VLR,char *LVR,int n);
void createBinTree_6(BinTree *bt,char *LVR,char *LRV,int n);//中序和后序
void createBinTree_6(BinTreeNode *&t,char *LVR,char *LRV,int n);




