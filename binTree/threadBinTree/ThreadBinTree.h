#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType char

typedef enum{LINK,THREAD}Tag_Type;

typedef struct BinTreeNode
{
	ElemType data;
	struct BinTreeNode *leftChild;
	struct BinTreeNode *rightChild;
	Tag_Type ltag;
	Tag_Type rtag;
}BinTreeNode;

typedef struct BinTree
{
	BinTreeNode *root;
	ElemType    refValue;//stop flag;
}BinTree;

///////////////////////////////////////////
//1线索化一棵二叉树
BinTreeNode* buyNode(ElemType x);//购买节点
void initBinTree(BinTree *bt,ElemType ref);//二叉树的初始化
void createBinTree(BinTree *bt,char *str);//创建二叉树
void createBinTree(BinTree *bt,BinTreeNode *&t,char *&str);
void createInThread(BinTree *bt);//线索化二叉树(按照中序线索化)
void createInThread(BinTreeNode *&t,BinTreeNode *&pre);

///////////////////////////////////////
//2线索化二叉树的方法
BinTreeNode* first(BinTree *bt);//第一个节点
BinTreeNode* first(BinTreeNode *t);
BinTreeNode* last(BinTree *bt);//最后一个节点
BinTreeNode* last(BinTreeNode *t);
BinTreeNode* next(BinTree *bt,BinTreeNode *cur);//查找当前节点的下一个节点
BinTreeNode* next(BinTreeNode *t,BinTreeNode *cur);
BinTreeNode* prior(BinTree *bt,BinTreeNode *cur);//查找当前节点的前一个节点
BinTreeNode* prior(BinTreeNode *t,BinTreeNode *cur);
void inOrder(BinTree *bt);//中序遍历一棵线索二叉树
void inOrder(BinTreeNode *t);
BinTreeNode* search(BinTree *bt,ElemType key);//查找数据为x的节点，返回地址
BinTreeNode* search(BinTreeNode *t,ElemType key);
BinTreeNode* parent(BinTree *bt,BinTreeNode *cur);//查找当前节点的父节点
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *cur);

