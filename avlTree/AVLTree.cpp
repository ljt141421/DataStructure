#include"AVLTree.h"
#include"Stack.h"

void initAVLTree(AVLTree *avl)
{
	avl->root=NULL;
}
AVLNode* buyNode(Type x)
{
	AVLNode *s=(AVLNode*)malloc(sizeof(AVLNode));
	assert(s!=NULL);
	s->data=x;
	s->leftChild=s->rightChild=NULL;
	s->bf=0;//Ĭ��ƽ�����Ӷ�Ϊ0
	return s;
}
BOOL insertAVL(AVLTree *avl, Type x)
{
	return insertAVL(avl->root,x);
}
BOOL insertAVL(AVLNode *&t , Type x)
{
	AVLNode *p=t;
	AVLNode *parent=NULL;

	Stack st;
	InitStack(&st);

	while(p != NULL)
	{
		if(x == p->data)
			return FALSE;//����������ظ�����
		parent=p;
		Push(&st,parent);//�ѵ�ǰ����ڵ�ĸ��ڵ���ջ
		if(x<p->data)
			p=p->leftChild;
		else
			p=p->rightChild;
	}
	p=buyNode(x);
	//ƽ��������ı��ʻ���һ�Ŷ���������
	if(parent == NULL)//˵���ǵ�һ���ڵ����
	{
		t=p;
		return TRUE;
	}
	if(x < parent->data)
		parent->leftChild=p;//���뵽������
	else
		parent->rightChild=p;//���뵽������

	//����֮����Ҫ���е���BF(ƽ������)
	//ƽ�����Ӽ���Ϊ�������ĸ߶�-�������ĸ߶�
	while(!IsEmpty(&st))
	{
		parent=GetTop(&st);
		Pop(&st);
		if(parent->leftChild==p)
			parent->bf--;
		else
			parent->bf++;
		if(parent->bf == 0)//���ڵ�ƽ������Ϊ0�˳�ѭ��
			break;
		if(parent->bf == -1 || parent->bf == 1)//���ڵ�ƽ������Ϊ-1��1������Ҫ���ϻ��ݵ���
			p=parent;
		else//��Ҫ������ת������
		{
			int flag=(parent->bf<0)?-1:1;
			if(p->bf==flag)//ƽ�����ӷ�����ͬ���е���ת
			{
				if(flag==-1)//��ߣ������ҵ���ת
					rotateR(parent);
				else		//�Ҹߣ���������ת
					rotateL(parent);
			}
			else			//ƽ�����ӷ��Ų�ͬ����˫��ת
			{
				if(flag==1)//����Ϊ��>���������Һ�����ת
					rotateRL(parent);
				else		//����Ϊ��<,�������������ת
					rotateLR(parent);
			}
			break;
		}
	}
	
	//�������Ӹ��ڵ�
	if(IsEmpty(&st))
		t=parent;
	else
	{
		AVLNode *q=GetTop(&st);
		if(q->data > parent->data)
			q->leftChild=parent;
		else
			q->rightChild=parent;
	}
	
	return TRUE;
}

BOOL removeAVL(AVLTree *avl, Type key)
{
	return removeAVL(avl->root,key);
}
BOOL removeAVL(AVLNode *&t, Type key)
{
	AVLNode *ppr=NULL;
	AVLNode *parent=NULL;
	AVLNode *p=t;
	Stack st;
	InitStack(&st);
	while(p != NULL)
	{
		if(p->data == key)
			break;
		parent=p;
		Push(&st,parent);//��p֮ǰ�߹��Ľڵ���ջ
		if(key < p->data)
			p=p->leftChild;
		else
			p=p->rightChild;
	}
	//����û�˽ڵ㣬ɾ��ʧ��
	if(p == NULL)
		return FALSE;

	AVLNode *q;
	int f=0;//�ж�������Ϊ�գ���������Ϊ��

	//��ɾ���Ľڵ���������������
	if(p->leftChild != NULL && p->rightChild != NULL)
	{
		parent = p;
		Push(&st,parent);
		//��p��ǰ���ڵ�q��ֵ����p��Ȼ����p����������ɾ��q
		q=p->leftChild;
		while(q->rightChild != NULL)
		{
			parent = q;
			Push(&st,parent);
			q=q->rightChild;
		}
		p->data=q->data;
		p=q;
	}
	//��ɾ���Ľڵ�ֻ��һ����֧
	if(p->leftChild != NULL)
		q=p->leftChild;
	else
		q=p->rightChild;
	
	//Ҫɾ����Ϊ���ڵ�
	if(parent == NULL)
		t=parent;
	else
	{
		if(parent->leftChild == p)
		{
			//��p��ĳ���ڵ����ӵ����ĸ��ڵ���
			parent->leftChild=q;
			f=0;//��������q��parent
		}
		else
		{
			parent->rightChild=q;
			f=1;//��������q��parent
		}
		int link_flag=0;// -1:leftchild ,1:rightchild,0:no_link

		//����ƽ�����ӵĵ���
		while(!IsEmpty(&st))
		{
			parent=GetTop(&st);
			Pop(&st);
			//���ɾ����������,ƽ�����Ӽ�һ
			if(parent->rightChild == q && f == 1)
				parent->bf--;
			else
				parent->bf++;
			
			//�õ�parent�ĸ��ڵ�
			if(!IsEmpty(&st))
			{
				ppr=GetTop(&st);
				link_flag=(ppr->leftChild == parent)?-1:1;
			}
			else
			{
				link_flag=0;
			}
			//���parentԭƽ������Ϊ0���������֮��Ӱ��ƽ��
			if(parent->bf == -1 || parent->bf == 1)
				break;
			//parentԭƽ�����Ӳ�Ϊ0�������ϻ��ݵ���
			if(parent->bf == 0)
				q=parent;
			else//������ת����
			{
				int flag=0;//��ת���
				if(parent->bf < 0)//�����ߣ���qָ��ϸߵ������ڵ�
				{
					flag=-1;
					q=parent->leftChild;
				}
				else//������
				{
					flag=1;
					q=parent->rightChild;
				}
				if(q->bf==0)//q��ƽ�����ӷ���Ϊ0�����е���ת
				{
					if(flag==-1)//��ߣ������ҵ���ת
					{
						rotateR(parent);
						parent->bf=1;
						parent->rightChild->bf=-1;
					}
					else//�Ҹߣ���������ת
					{
						rotateL(parent);
						parent->bf=-1;
						parent->leftChild->bf=1;
					}
					break;
				}
				if(q->bf == flag)//q��ƽ�����ӷ��ź�flag��ͬ�����е���ת
				{
					if(flag==-1)//��ߣ������ҵ���ת
						rotateR(parent);
					else//�Ҹߣ���������ת
						rotateL(parent);
				}
				else//�����෴������˫��ת
				{	
					if(flag==-1)//����Ϊ��< 
						rotateLR(parent);
					else		//����Ϊ��>
						rotateRL(parent);
				}
				//���Ӹ��ڵ�
				if(link_flag==1)
					ppr->rightChild=parent;
				else if(link_flag==-1)
					ppr->leftChild=parent;
			}
		}
		if(IsEmpty(&st))
			t=parent;
	}
	free(p);
	return TRUE;
}
//������
void rotateR(AVLNode *&ptr)
{
	AVLNode *subR=ptr;
	ptr=subR->leftChild;
	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;
	ptr->bf=subR->bf=0;
}
//������
void rotateL(AVLNode *&ptr)
{
	AVLNode *subL=ptr;
	ptr=subL->rightChild;
	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	ptr->bf=subL->bf=0;
}
//���������ת
void rotateLR(AVLNode *&ptr)
{
	AVLNode *subR=ptr;
	AVLNode *subL=subR->leftChild;
	ptr=subL->rightChild;

	//���������������
	//���������������������Ӹ���������
	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	//����ƽ������
	if(ptr->bf<=0)
		subL->bf=0;
	else
		subL->bf=-1;

	//ͬ��
	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;

	if(ptr->bf == -1)
		subR->bf=1;
	else
		subR->bf=0;
	ptr->bf=0;
}
//���Һ�����ת
void rotateRL(AVLNode *&ptr)
{
	AVLNode *subL=ptr;
	AVLNode *subR=subL->rightChild;
	ptr=subR->leftChild;

	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;
	if(ptr->bf >= 0)
		subR->bf=0;
	else
		subR->bf=1;

	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	if(ptr->bf == 1)
		subL->bf=-1;
	else
		subL->bf=0;
	ptr->bf=0;
}
