#include"BinTree.h"
#include"Queue.h"
#include"Stack.h"

//��ʼ��������
void initBinTree(BinTree *bt,ElemType ref)
{
	bt->root=NULL;
	bt->refValue=ref;
}
//1:�������Ĵ�����ʽ
//��¶�ӿ�
void createBinTree_1(BinTree *bt)
{
	createBinTree_1(bt,&(bt->root));
}
//ʵ�ʴ�������,�˴�**tΪ����ָ�룬��ΪҪ�Զ������ĸ��ڵ�bt->root���в���
void createBinTree_1(BinTree *bt,BinTreeNode **t)
{
	ElemType item;
	scanf("%c",&item);
	if(item == bt->refValue)
		(*t)=NULL;
	else
	{
		(*t)=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert((*t)!=NULL);
		(*t)->data=item;
		//�ݹ鴴����������������
		createBinTree_1(bt,&((*t)->leftChild));
		createBinTree_1(bt,&((*t)->rightChild));
	}

}
void createBinTree_2(BinTree *bt)
{
	createBinTree_2(bt,bt->root);
}
void createBinTree_2(BinTree *bt,BinTreeNode *&t)
{
	ElemType item;
	scanf("%c",&item);
	if(item==bt->refValue)
		t=NULL;
	else
	{
		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t!=NULL);
		t->data=item;
		createBinTree_2(bt,t->leftChild);
		createBinTree_2(bt,t->rightChild);
	}
}
void createBinTree_3(BinTree *bt)
{
	bt->root=createBinTree_3_(bt);
}
BinTreeNode* createBinTree_3_(BinTree *bt)
{
	ElemType item;
	scanf("%c",&item);
	if(item==bt->refValue)
		return NULL;
	else
	{	
		BinTreeNode *t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data=item;
		t->leftChild=createBinTree_3_(bt);
		t->rightChild=createBinTree_3_(bt);
		return t;
	}
}
void createBinTree_4(BinTree *bt,char *str)
{
	createBinTree_4(bt,bt->root,str);
}
void createBinTree_4(BinTree *bt,BinTreeNode *&t,char *&str)
{
	if(*str == bt->refValue)
		t=NULL;
	else
	{
		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t!=NULL);
		t->data=*str;
		createBinTree_4(bt,t->leftChild,++str);
		createBinTree_4(bt,t->rightChild,++str);
	}
}

////////////////////////////
//2
void preOrder(BinTree *bt)
{
	preOrder(bt->root);
}
void preOrder(BinTreeNode *t)
{
	if(t != NULL)
	{
		printf("%c ",t->data);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}
//�������
void inOrder(BinTree *bt)
{
	inOrder(bt->root);
}
void inOrder(BinTreeNode *t)
{
	if(t != NULL)
	{
		inOrder(t->leftChild);
		printf("%c ",t->data);
		inOrder(t->rightChild);
	}
}
//�������
void postOrder(BinTree *bt)
{
	postOrder(bt->root);
}
void postOrder(BinTreeNode *t)
{
	if(t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		printf("%c ",t->data);
	}
}
//��α���(��Ҫ��������)
void levelOrder(BinTree *bt)
{
	levelOrder(bt->root);
}
void levelOrder(BinTreeNode *t)
{
	if(t != NULL)//tΪָ��ͷ���ָ��
	{
		BinTreeNode *v;
		LinkQueue q;
		InitQueue(&q);
		EnQueue(&q,t);//��ͷ������
		while(!QueueIsEmpty(&q))//�����в�Ϊ��
		{
			GetHead(&q,&v);//ȡͷ���
			DeQueue(&q);//����
			printf("%c ",v->data);
			if(v->leftChild != NULL)
				EnQueue(&q,v->leftChild);//���������գ��������
			if(v->rightChild != NULL)
				EnQueue(&q,v->rightChild);//���������գ��������
		}
	}
}

////////////////////////////////////
//3
int size(BinTree *bt)
{
	return size(bt->root);
}
int size(BinTreeNode *t)
{
	if(t == NULL)
		return 0;
	else
		return size(t->leftChild)+size(t->rightChild)+1;
}
int height(BinTree *bt)
{
	return height(bt->root);
}
int height(BinTreeNode *t)
{
	if(t == NULL)
		return 0;
	else
	{
		int leftHeight=height(t->leftChild);
		int rightHeight=height(t->rightChild);
		return (leftHeight > rightHeight ? leftHeight : rightHeight)+1;
	}
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

	BinTreeNode *p=search(t->leftChild,key);//����������Ѱ��
	if(p != NULL)
		return p;
	return search(t->rightChild,key);
}
BinTreeNode* parent(BinTree *bt,BinTreeNode *p)
{
	return parent(bt->root,p);
}
BinTreeNode* parent(BinTreeNode *t,BinTreeNode *p)
{
	if(t== NULL || p==NULL)
		return NULL;
	if(t->leftChild==p || t->rightChild==p)
		return t;

	BinTreeNode *q=parent(t->leftChild,p);
	if(q != NULL)
		return q;
	return parent(t->rightChild,p);
}
BinTreeNode* leftChild(BinTreeNode *p)
{
	if(p != NULL)
		return p->leftChild;
	return NULL;
}
BinTreeNode* rightChild(BinTreeNode *p)
{
	if(p != NULL)
		return p->rightChild;
	return NULL;
}
bool binTreeEmpty(BinTree *bt)
{
	return bt->root==NULL;
}
void copy(BinTree *bt1,BinTree *bt2)
{
	copy(bt1->root,bt2->root);
}
void copy(BinTreeNode *&t1,BinTreeNode *t2)
{
	if(t2 == NULL)
		t1=NULL;
	else
	{
		t1=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t1 != NULL);
		t1->data=t2->data;
		copy(t1->leftChild,t2->leftChild);
		copy(t1->rightChild,t2->rightChild);
	}
}
void binTreeClear(BinTree *bt)
{
	binTreeClear(bt->root);
}
void binTreeClear(BinTreeNode *&t)
{
	if(t != NULL)
	{
		binTreeClear(t->leftChild);
		binTreeClear(t->rightChild);
		free(t);
		t=NULL;
	}
}
////////////////////////////////////
//4�ǵݹ����
void preOrder_1(BinTree *bt)
{
	preOrder_1(bt->root);
}
void preOrder_1(BinTreeNode *t)
{
	if(t != NULL)
	{
		SeqStack st;
		InitStack(&st);
		BinTreeNode *p;
		Push(&st,t);
		while(!IsEmpty(&st))
		{
			GetTop(&st,&p);
			Pop(&st);
			printf("%c ",p->data);
			if(p->rightChild != NULL)
				Push(&st,p->rightChild);
			if(p->leftChild != NULL)
				Push(&st,p->leftChild);
		}
	}
}
void inOrder_1(BinTree *bt)
{
	inOrder_1(bt->root);
}
void inOrder_1(BinTreeNode *t)
{
	if(t != NULL)
	{
		SeqStack st;
		InitStack(&st);
		BinTreeNode *p;
		Push(&st,t);
		while(!IsEmpty(&st))
		{
			while(t != NULL && t->leftChild != NULL)
			{
				Push(&st,t->leftChild);
				t=t->leftChild;
			}
			GetTop(&st,&p);
			Pop(&st);
			printf("%c ",p->data);

			if(p->rightChild != NULL)
			{
				t=p->rightChild;
				if(t != NULL)
					Push(&st,t);
			}

		}
	}
}
/////////////////////////////////
//5
void createBinTree_5(BinTree *bt,char *VLR,char *LVR,int n)
{
	createBinTree_5(bt->root,VLR,LVR,n);
}
void createBinTree_5(BinTreeNode *&t,char *VLR,char *LVR,int n)
{
	if(n==0)
		t=NULL;
	else
	{
		int k=0;
		while(VLR[0] != LVR[k])
			k++;

		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data=LVR[k];

		createBinTree_5(t->leftChild,VLR+1,LVR,k);
		createBinTree_5(t->rightChild,VLR+k+1,LVR+k+1,n-k-1);
	}
}
void createBinTree_6(BinTree *bt,char *LVR,char *LRV,int n)
{
	createBinTree_6(bt->root,LVR,LRV,n);
}
void createBinTree_6(BinTreeNode *&t,char *LVR,char *LRV,int n)
{
	if(n==0)
		t=NULL;
	else
	{
		int k=0;
		while(LRV[n-1] != LVR[k])
			k++;

		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data=LVR[k];

		createBinTree_6(t->rightChild,LVR+k+1,LRV+k,n-k-1);
		createBinTree_6(t->leftChild,LVR,LRV,k);
	}
}