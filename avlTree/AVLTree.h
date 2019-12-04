#ifndef _AVLTREE_H
#define _AVLTREE_H

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Type int
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct AVLNode
{
	Type     data;
	AVLNode *leftChild;
	AVLNode *rightChild;
	int      bf;
}AVLNode;

typedef struct AVLTree
{
	AVLNode *root;
}AVLTree;

////////////////////////////////////////////////////////
void initAVLTree(AVLTree *avl);
AVLNode* buyNode(Type x);

BOOL insertAVL(AVLTree *avl, Type x);
BOOL insertAVL(AVLNode *&t , Type x);

BOOL removeAVL(AVLTree *avl, Type key);
BOOL removeAVL(AVLNode *&t, Type key);

void rotateR(AVLNode *&ptr);
void rotateL(AVLNode *&ptr);
void rotateLR(AVLNode *&ptr);
void rotateRL(AVLNode *&ptr);



#endif