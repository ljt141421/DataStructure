#include"Tree.h"

void initTree(Tree *tree,ElemType ref)
{
	tree->root=NULL;
	tree->refValue=ref;
}
void createTree(Tree *tree,char *str)
{
	createTree(tree,tree->root,str);
}
void createTree(Tree *tree,TreeNode *&t,char *&str)
{
	if(*str == tree->refValue)
		t=NULL;
	else
	{
		t=(TreeNode*)malloc(sizeof(TreeNode));
		assert(t != NULL);
		t->data=*str;
		createTree(tree,t->firstChild,++str);
		createTree(tree,t->nextSibling,++str);
	}
}


TreeNode* root(Tree *tree)
{
	return tree->root;
}
TreeNode* firstChild(Tree *tree)
{
	return firstChild(tree->root);
}
TreeNode* firstChild(TreeNode *t)
{
	if(t == NULL)
		return NULL;
	return t->firstChild;
}
TreeNode* nextSibling(Tree *tree)
{
	return nextSibling(tree->root);
}
TreeNode* nextSibling(TreeNode *t)
{
	if(t == NULL)
		return NULL;
	return t->nextSibling;
}
TreeNode* find(Tree *tree,ElemType key)
{
	return find(tree->root,key);
}
TreeNode* find(TreeNode *t,ElemType key)
{
	if(t == NULL)
		return NULL;
	if(t->data == key)
		return t;
	TreeNode *p=find(t->firstChild,key);
	if(p != NULL)
		return p;
	return find(t->nextSibling,key);
}
TreeNode* parent(Tree *tree,TreeNode *p)
{
	return parent(tree->root,p);
}
TreeNode* parent(TreeNode *t,TreeNode *p)
{
	if(t == NULL || p == NULL)
		return NULL;
	TreeNode *q=t->firstChild;
	TreeNode *par;//parent
	while(q != NULL && q != p)
	{
		par=parent(q,p);
		if(par != NULL)
			return par;
		q=q->nextSibling;
	}

	if(q != NULL && q==p)
		return t;
	return NULL;
}