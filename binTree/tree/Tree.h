#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType char

typedef struct TreeNode
{
	ElemType data;
	struct TreeNode *firstChild;
	struct TreeNode *nextSibling;
}TreeNode;

typedef struct Tree
{
	TreeNode *root;
	ElemType refValue;
}Tree;

void initTree(Tree *tree,ElemType ref);
void createTree(Tree *tree,char *str);
void createTree(Tree *tree,TreeNode *&t,char *&str);

TreeNode* root(Tree *tree);
TreeNode* firstChild(Tree *tree);
TreeNode* firstChild(TreeNode *t);
TreeNode* nextSibling(Tree *tree);
TreeNode* nextSibling(TreeNode *t);
TreeNode* find(Tree *tree,ElemType key);
TreeNode* find(TreeNode *t,ElemType key);
TreeNode* parent(Tree *tree,TreeNode *p);
TreeNode* parent(TreeNode *t,TreeNode *p);