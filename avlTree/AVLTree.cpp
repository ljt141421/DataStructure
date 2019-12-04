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
	s->bf=0;//默认平衡因子都为0
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
			return FALSE;//不允许插入重复数据
		parent=p;
		Push(&st,parent);//把当前插入节点的父节点入栈
		if(x<p->data)
			p=p->leftChild;
		else
			p=p->rightChild;
	}
	p=buyNode(x);
	//平衡二叉树的本质还是一颗二叉排序树
	if(parent == NULL)//说明是第一个节点插入
	{
		t=p;
		return TRUE;
	}
	if(x < parent->data)
		parent->leftChild=p;//插入到左子树
	else
		parent->rightChild=p;//插入到右子树

	//插入之后需要进行调整BF(平衡因子)
	//平衡因子计算为右子树的高度-左子树的高度
	while(!IsEmpty(&st))
	{
		parent=GetTop(&st);
		Pop(&st);
		if(parent->leftChild==p)
			parent->bf--;
		else
			parent->bf++;
		if(parent->bf == 0)//父节点平衡因子为0退出循环
			break;
		if(parent->bf == -1 || parent->bf == 1)//父节点平衡因子为-1或1，则需要向上回溯调整
			p=parent;
		else//需要进行旋转化调整
		{
			int flag=(parent->bf<0)?-1:1;
			if(p->bf==flag)//平衡因子符号相同进行单旋转
			{
				if(flag==-1)//左高，进行右单旋转
					rotateR(parent);
				else		//右高，进行左单旋转
					rotateL(parent);
			}
			else			//平衡因子符号不同进行双旋转
			{
				if(flag==1)//树形为：>，进行先右后左旋转
					rotateRL(parent);
				else		//树形为：<,进行先左后右旋转
					rotateLR(parent);
			}
			break;
		}
	}
	
	//重新连接根节点
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
		Push(&st,parent);//将p之前走过的节点入栈
		if(key < p->data)
			p=p->leftChild;
		else
			p=p->rightChild;
	}
	//树中没此节点，删除失败
	if(p == NULL)
		return FALSE;

	AVLNode *q;
	int f=0;//判断左子树为空，或右子树为空

	//所删除的节点左右子树都存在
	if(p->leftChild != NULL && p->rightChild != NULL)
	{
		parent = p;
		Push(&st,parent);
		//将p的前驱节点q的值赋给p，然后在p的左子树里删除q
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
	//所删除的节点只有一个分支
	if(p->leftChild != NULL)
		q=p->leftChild;
	else
		q=p->rightChild;
	
	//要删除的为父节点
	if(parent == NULL)
		t=parent;
	else
	{
		if(parent->leftChild == p)
		{
			//把p的某个节点连接到它的父节点上
			parent->leftChild=q;
			f=0;//把左子树q给parent
		}
		else
		{
			parent->rightChild=q;
			f=1;//把右子树q给parent
		}
		int link_flag=0;// -1:leftchild ,1:rightchild,0:no_link

		//进行平衡因子的调整
		while(!IsEmpty(&st))
		{
			parent=GetTop(&st);
			Pop(&st);
			//如果删除的是右树,平衡因子减一
			if(parent->rightChild == q && f == 1)
				parent->bf--;
			else
				parent->bf++;
			
			//得到parent的父节点
			if(!IsEmpty(&st))
			{
				ppr=GetTop(&st);
				link_flag=(ppr->leftChild == parent)?-1:1;
			}
			else
			{
				link_flag=0;
			}
			//如果parent原平衡因子为0，则调整完之后不影响平衡
			if(parent->bf == -1 || parent->bf == 1)
				break;
			//parent原平衡因子不为0，则向上回溯调整
			if(parent->bf == 0)
				q=parent;
			else//进行旋转调整
			{
				int flag=0;//旋转标记
				if(parent->bf < 0)//左树高，让q指向较高的树根节点
				{
					flag=-1;
					q=parent->leftChild;
				}
				else//右树高
				{
					flag=1;
					q=parent->rightChild;
				}
				if(q->bf==0)//q的平衡因子符号为0，进行单旋转
				{
					if(flag==-1)//左高，进行右单旋转
					{
						rotateR(parent);
						parent->bf=1;
						parent->rightChild->bf=-1;
					}
					else//右高，进行左单旋转
					{
						rotateL(parent);
						parent->bf=-1;
						parent->leftChild->bf=1;
					}
					break;
				}
				if(q->bf == flag)//q的平衡因子符号和flag相同，进行单旋转
				{
					if(flag==-1)//左高，进行右单旋转
						rotateR(parent);
					else//右高，进行左单旋转
						rotateL(parent);
				}
				else//符合相反，进行双旋转
				{	
					if(flag==-1)//树形为：< 
						rotateLR(parent);
					else		//树形为：>
						rotateRL(parent);
				}
				//连接父节点
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
//单右旋
void rotateR(AVLNode *&ptr)
{
	AVLNode *subR=ptr;
	ptr=subR->leftChild;
	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;
	ptr->bf=subR->bf=0;
}
//单左旋
void rotateL(AVLNode *&ptr)
{
	AVLNode *subL=ptr;
	ptr=subL->rightChild;
	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	ptr->bf=subL->bf=0;
}
//先左后右旋转
void rotateLR(AVLNode *&ptr)
{
	AVLNode *subR=ptr;
	AVLNode *subL=subR->leftChild;
	ptr=subL->rightChild;

	//如果根有左子树与
	//就拿左子树的右子树连接根的左子树
	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	//调整平衡因子
	if(ptr->bf<=0)
		subL->bf=0;
	else
		subL->bf=-1;

	//同上
	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;

	if(ptr->bf == -1)
		subR->bf=1;
	else
		subR->bf=0;
	ptr->bf=0;
}
//先右后左旋转
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
