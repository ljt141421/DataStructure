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
//1������һ�ö�����
BinTreeNode* buyNode(ElemType x);//����ڵ�
void initBinTree(BinTree *bt,ElemType ref);//�������ĳ�ʼ��
void createBinTree(BinTree *bt,char *str);//����������
void createBinTree(BinTree *bt,BinTreeNode *&t,char *&str);
void createInThread(BinTree *bt);//������������(��������������)
void createInThread(BinTreeNode *&t,BinTreeNode *&pre);

///////////////////////////////////////
//2�������������ķ���
BinTreeNode* first(BinTree *bt);//��һ���ڵ�
BinTreeNode* first(BinTreeNode *t);
BinTreeNode* last(BinTree *bt);//���һ���ڵ�
BinTreeNode* last(BinTreeNode *t);
BinTreeNode* next(BinTree *bt,BinTreeNode *cur);//���ҵ�ǰ�ڵ����һ���ڵ�
BinTreeNode* next(BinTreeNode *t,BinTreeNode *cur);
BinTreeNode* prior(BinTree *bt,BinTreeNode *cur);//���ҵ�ǰ�ڵ��ǰһ���ڵ�
BinTreeNode* prior(BinTreeNode *t,BinTreeNode *cur);
void inOrder(BinTree *bt);//�������һ������������
void inOrder(BinTreeNode *t);
BinTreeNode* search(BinTree *bt,ElemType key);//��������Ϊx�Ľڵ㣬���ص�ַ
BinTreeNode* search(BinTreeNode *t,ElemType key);
BinTreeNode* parent(BinTree *bt,BinTreeNode *cur);//���ҵ�ǰ�ڵ�ĸ��ڵ�
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *cur);

