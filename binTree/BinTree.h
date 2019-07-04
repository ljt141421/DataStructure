#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

#define ElemType char

//�����������ڵ�
typedef struct BinTreeNode
{
	ElemType data;//������
	struct BinTreeNode *leftChild;//������ָ��
	struct BinTreeNode *rightChild;//������ָ��
}BinTreeNode;

//������ͷ���
typedef struct BinTree
{
	BinTreeNode *root;//����ָ��
	ElemType    refValue;//ֹͣ���
}BinTree;

void initBinTree(BinTree *bt,ElemType ref);
///////////////////////////////////////////
//1����
//ʹ�õ�ַ
void createBinTree_1(BinTree *bt);
void createBinTree_1(BinTree *bt,BinTreeNode **t);
//ʹ������
void createBinTree_2(BinTree *bt);
void createBinTree_2(BinTree *bt,BinTreeNode *&t);
//���ؽڵ�
void createBinTree_3(BinTree *bt);
BinTreeNode* createBinTree_3_(BinTree *bt);
//ֱ�Ӵ����ַ���
void createBinTree_4(BinTree *bt,char *str);
void createBinTree_4(BinTree *bt,BinTreeNode *&t,char *&str);

//////////////////////////////////////////////
//2�ݹ����
//�������
void preOrder(BinTree *bt);
void preOrder(BinTreeNode *t);
//�������
void inOrder(BinTree *bt);
void inOrder(BinTreeNode *t);
//�������
void postOrder(BinTree *bt);
void postOrder(BinTreeNode *t);
//��α���(��Ҫ��������)
void levelOrder(BinTree *bt);
void levelOrder(BinTreeNode *t);

//////////////////////////////////////////////////
//3����
int size(BinTree *bt);//��ڵ����
int size(BinTreeNode *t);
int height(BinTree *bt);//���������
int height(BinTreeNode *t);
BinTreeNode* search(BinTree *bt,ElemType key);//���ҽڵ�,���ҵ����ص�ַ,��֮����NULL
BinTreeNode* search(BinTreeNode *t,ElemType key);
BinTreeNode* parent(BinTree *bt,BinTreeNode *p);//��ڵ�ĸ��ڵ�
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *p);
BinTreeNode* leftChild(BinTreeNode *p);//��������
BinTreeNode* rightChild(BinTreeNode *p);//��������
bool binTreeEmpty(BinTree *bt);//�ж��Ƿ�Ϊ��
void copy(BinTree *bt1,BinTree *bt2);//����һ�ö�����
void copy(BinTreeNode *&t1,BinTreeNode *t2);
void binTreeClear(BinTree *bt);//���һ�ö�����
void binTreeClear(BinTreeNode *&t);

///////////////////////////////////
//4�ǵݹ����(��Ҫ����ջ)
void preOrder_1(BinTree *bt);
void preOrder_1(BinTreeNode *t);
void inOrder_1(BinTree *bt);
void inOrder_1(BinTreeNode *t);
//�������������һ������ʵ��
void postOrder_1(BinTree *bt);
void postOrder_1(BinTreeNode *t);

////////////////////////////////////////////
//5�������Ļָ�ʵ��
void createBinTree_5(BinTree *bt,char *VLR,char *LVR,int n);//ǰ�������
void createBinTree_5(BinTreeNode *&t,char *VLR,char *LVR,int n);
void createBinTree_6(BinTree *bt,char *LVR,char *LRV,int n);//����ͺ���
void createBinTree_6(BinTreeNode *&t,char *LVR,char *LRV,int n);




