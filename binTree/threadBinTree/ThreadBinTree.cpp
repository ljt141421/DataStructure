#include"ThreadBinTree.h"

//1
BinTreeNode* buyNode(ElemType x)
{
	BinTreeNode *s=(BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(s != NULL);
	s->data=x;
	s->leftChild=s->rightChild=NULL;
	s->ltag=s->rtag=LINK;
	return s;

}
void initBinTree(BinTree *bt,ElemType ref)
{
	bt->root=NULL;
	bt->refValue=ref;
}
void createBinTree(BinTree *bt,char *str)
{
	createBinTree(bt,bt->root,str);
}
void createBinTree(BinTree *bt,BinTreeNode *&t,char *&str)
{
	if(*str == bt->refValue)
		t=NULL;
	else
	{
		t=buyNode(*str);
		createBinTree(bt,t->leftChild,++str);
		createBinTree(bt,t->rightChild,++str);
	}
}
void createInThread(BinTree *bt)
{
	BinTreeNode *pre=NULL;
	createInThread(bt->root,pre);
	pre->rightChild=NULL;
	pre->rtag=THREAD;

}
void createInThread(BinTreeNode *&t,BinTreeNode *&pre)
{
	if(t == NULL)
		return;
	createInThread(t->leftChild,pre);
	if(t->leftChild == NULL)
	{
		t->ltag=THREAD;
		t->leftChild=pre;
	}
	if(pre != NULL && pre->rightChild == NULL)
	{
		pre->rtag=THREAD;
		pre->rightChild=t;
	}
	pre=t;
	createInThread(t->rightChild,pre);
}
//2
BinTreeNode* first(BinTree *bt)
{
	return first(bt->root);
}
BinTreeNode* first(BinTreeNode *t)
{
	if(t == NULL)
		return NULL;
	BinTreeNode *p=t;
	while(p->ltag == LINK)
		p=p->leftChild;
	return p;
}
BinTreeNode* last(BinTree *bt)
{
	return last(bt->root);
}
BinTreeNode* last(BinTreeNode *t)
{
	if(t == NULL)
		return NULL;
	BinTreeNode *p=t;
	while(p->rtag == LINK)
		p=p->rightChild;
	return p;
}
BinTreeNode* next(BinTree *bt,BinTreeNode *cur)
{
	return next(bt->root,cur);
}
BinTreeNode* next(BinTreeNode *t,BinTreeNode *cur)
{
	if(t == NULL || cur == NULL)
		return NULL;
	if(cur->rtag == THREAD)
		return cur->rightChild;
	return first(cur->rightChild);//否则，返回当前节点的右子树的第一个节点
}
BinTreeNode* prior(BinTree *bt,BinTreeNode *cur)
{
	return prior(bt->root,cur);
}
BinTreeNode* prior(BinTreeNode *t,BinTreeNode *cur)
{
	if(t == NULL || cur == NULL)
		return NULL;
	if(cur->ltag == THREAD)
		return cur->leftChild;
	return last(cur->leftChild);//否则，返回当前节点的左子树的最后一个节点
}
void inOrder(BinTree *bt)
{
	inOrder(bt->root);
}
void inOrder(BinTreeNode *t)
{
	BinTreeNode *p;
	for(p=first(t);p != NULL;p=next(t,p))
	{
		printf("%c ",p->data);
	}
	printf("\n");
}
BinTreeNode* search(BinTree *bt,ElemType key)
{
	return search(bt->root,key);
}
BinTreeNode* search(BinTreeNode *t,ElemType key)
{
	if(t == NULL)
		return NULL;
	if(t->data == key)
		return t;
	BinTreeNode *p;
	for(p=first(t);p != NULL;p=next(t,p))
	{
		if(p->data == key)
			return p;
	}
	return NULL;

}
BinTreeNode* parent(BinTree *bt,BinTreeNode *cur)
{
	return parent(bt->root,cur);
}
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *cur)
{
	if(t == NULL || cur == NULL)
		return NULL;
	if(t == cur)//当前节点为根节点
		return NULL;
	BinTreeNode *p;
	if(cur->ltag == THREAD)
	{
		p=cur->leftChild;
		if(p->rightChild == cur)
			return p;
	}
	if(cur->rtag == THREAD)
	{
		p=cur->rightChild;
		if(p->leftChild == cur)
			return p;
	}
	p=first(cur->leftChild);//查找前驱
	p=p->leftChild;
	if(p != NULL && p->rightChild == cur)
		return p;

	p=last(cur->rightChild);//前驱查找失败的情况下查找后继
	return p->rightChild;
}
