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
	//(*t)��Ϊ������
	if(*t == NULL)
	{
		*t=(BSTNode*)malloc(sizeof(BSTNode));
		assert(*t != NULL);
		(*t)->data=key;
		(*t)->leftChild=NULL;
		(*t)->rightChild=NULL;
		return TRUE;
	}
	else if(key < (*t)->data)//��Ϊ����������
	{
		insertBSTree(&(*t)->leftChild,key);
		return TRUE;
	}
	else if(key > (*t)->data)//��Ϊ����������
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
	//����������������������Եõ�һ����������
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
	//����С��ֻҪһֱ����������
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
	//������ֻҪһֱ����������
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
	if(key < t->data)//ȥ����������
		return Search(t->leftChild,key);
	else//ȥ����������
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
	if(key < (*t)->data)//����������ɾ��
		return removeBST(&(*t)->leftChild,key);
	else if(key > (*t)->data)//����������ɾ��
		return removeBST(&(*t)->rightChild,key);
	else
	{
		BSTNode *p=NULL;
		if((*t)->leftChild != NULL && (*t)->rightChild != NULL)
		{
			//��t��ֵ������������������С��ֵ
			//Ȼ����t����������ɾ�����ֵ
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
	if(key < (*t)->data)//����������ɾ��
		return removeBST(&(*t)->leftChild,key);
	else if(key > (*t)->data)//����������ɾ��
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
			//��tָ������������
			p=*t;
			(*t)=(*t)->leftChild;
			free(p);
			p=NULL;
		}
		if((*t)->leftChild == NULL && (*t)->rightChild != NULL)
		{
			//��tָ������������
			p=*t;
			(*t)=(*t)->rightChild;
			free(p);
			p=NULL;
		}
		if((*t)->leftChild != NULL && (*t)->rightChild != NULL)
		{
			//��t��ֵ������������������С��ֵ
			//Ȼ����t����������ɾ�����ֵ
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