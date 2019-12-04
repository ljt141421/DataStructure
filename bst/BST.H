#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define T int
#define TRUE 1
#define FALSE 0
#define BOOL int

typedef struct BSTNode
{
	T data;
	struct BSTNode *leftChild;
	struct BSTNode *rightChild;
}BSTNode;

typedef struct BST
{
	BSTNode *root;
}BST;

void initBSTree(BST *bst);
BOOL insertBSTree(BST *bst,T key);
BOOL insertBSTree(BSTNode **t,T key);

T Min(BST *bst);
T Min(BSTNode *t);
T Max(BST *bst);
T Max(BSTNode *t);

void Sort(BST *bst);
void Sort(BSTNode **t);

BSTNode* Search(BST *bst,T key);
BSTNode* Search(BSTNode *t,T key);

void makeEmpty(BST *bst);
void makeEmpty(BSTNode **t);

BOOL removeBST(BST *bst,T key);
BOOL removeBST(BSTNode **t,T key);