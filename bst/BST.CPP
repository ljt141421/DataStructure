#include"BST.H"

void initBSTree(BST *bst)
{
	bst->root=NULL;
}
BOOL insertBSTree(BST *bst,T key)
{
	return insertBSTree(&bst->root,key);
}
BOOL insertBSTree(BSTNode **t,T key)
{
	//(*t)作为根插入
	if(*t == NULL)
	{
		*t=(BSTNode*)malloc(sizeof(BSTNode));
		assert(*t != NULL);
		(*t)->data=key;
		(*t)->leftChild=NULL;
		(*t)->rightChild=NULL;
		return TRUE;
	}
	else if(key < (*t)->data)//作为左子树插入
	{
		insertBSTree(&(*t)->leftChild,key);
		return TRUE;
	}
	else if(key > (*t)->data)//作为右子树插入
	{
		insertBSTree(&(*t)->rightChild,key);
	}
	return FALSE;
}
void Sort(BST *bst)
{
	Sort(&(bst->root));
}
void Sort(BSTNode **t)
{
	//二叉排序树用中序遍历可以得到一个有序序列
	if(*t != NULL)
	{
		Sort(&(*t)->leftChild);
		printf("%d ",(*t)->data);
		Sort(&(*t)->rightChild);
	}
}
T Min(BST *bst)
{
	assert(bst->root != NULL);
	return Min(bst->root);
}
T Min(BSTNode *t)
{
	//求最小的只要一直往左子树找
	while(t->leftChild != NULL)
		t=t->leftChild;
	return t->data;
		
}
T Max(BST *bst)
{
	assert(bst->root != NULL);
	return Max(bst->root);
}
T Max(BSTNode *t)
{
	//求最大的只要一直往右子树找
	while(t->rightChild != NULL)
		t=t->rightChild;
	return t->data;
}
BSTNode* Search(BST *bst,T key)
{
	return Search(bst->root,key);
}
BSTNode* Search(BSTNode *t,T key)
{
	if(t == NULL)
		return NULL;
	if(t->data == key)
		return t;
	if(key < t->data)//去左子树里找
		return Search(t->leftChild,key);
	else//去右子树里找
		return Search(t->rightChild,key);
}
void makeEmpty(BST *bst)
{
	makeEmpty(&(bst->root));
}
void makeEmpty(BSTNode **t)
{
	if(*t != NULL)
	{
		makeEmpty(&(*t)->leftChild);
		makeEmpty(&(*t)->rightChild);
		free(*t);
		*t=NULL;
	}
}
BOOL removeBST(BST *bst,T key)
{
	return removeBST(&(bst->root),key);
}
BOOL removeBST(BSTNode **t,T key)
{
	if(*t == NULL)
		return FALSE;
	if(key < (*t)->data)//在左子树里删除
		return removeBST(&(*t)->leftChild,key);
	else if(key > (*t)->data)//在右子树里删除
		return removeBST(&(*t)->rightChild,key);
	else
	{
		BSTNode *p=NULL;
		if((*t)->leftChild != NULL && (*t)->rightChild != NULL)
		{
			//让t的值等于他的右子树里最小的值
			//然后在t的右子树里删除这个值
			p=(*t)->rightChild;
			while(p->leftChild!=NULL)
				p=p->leftChild;
			(*t)->data=p->data;
			removeBST(&(*t)->rightChild,p->data);
		}
		else
		{
			p=*t;
			if((*t)->leftChild == NULL)
				(*t)=(*t)->rightChild;
			else
				(*t)=(*t)->leftChild;
			free(p);
			p=NULL;
		}
	}
	return TRUE;
}

/*
BOOL removeBST(BSTNode **t,T key)
{
	if(*t == NULL)
		return FALSE;
	if(key < (*t)->data)//在左子树里删除
		return removeBST(&(*t)->leftChild,key);
	else if(key > (*t)->data)//在右子树里删除
		return removeBST(&(*t)->rightChild,key);
	else
	{
		BSTNode *p=NULL;
		if((*t)->leftChild == NULL && (*t)->rightChild == NULL)
		{
			free(*t);
			t=NULL;
		}
		if((*t)->leftChild != NULL && (*t)->rightChild == NULL)
		{
			//让t指向他的左子树
			p=*t;
			(*t)=(*t)->leftChild;
			free(p);
			p=NULL;
		}
		if((*t)->leftChild == NULL && (*t)->rightChild != NULL)
		{
			//让t指向他的右子树
			p=*t;
			(*t)=(*t)->rightChild;
			free(p);
			p=NULL;
		}
		if((*t)->leftChild != NULL && (*t)->rightChild != NULL)
		{
			//让t的值等于他的右子树里最小的值
			//然后在t的右子树里删除这个值
			p=(*t)->rightChild;
			while(p->leftChild!=NULL)
				p=p->leftChild;
			(*t)->data=p->data;
			removeBST(&(*t)->rightChild,p->data);
		}

	}
	return TRUE;
}
*/