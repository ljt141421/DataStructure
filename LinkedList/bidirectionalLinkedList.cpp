#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define ElemType int

typedef struct Node
{
	ElemType data;
	struct   Node *prior;//ǰ���ڵ�
	struct   Node *next;//��̽ڵ�
}Node,*PNode;

typedef struct List
{
	PNode first;
	PNode last;
	int   size;
}List;

//��������
void initSCList(List *list);
void push_back(List *list,ElemType x);
void show_list(List *list);
Node* buyNode(ElemType x);
void push_front(List *list,ElemType x);
void pop_back(List *list);
void pop_front(List *list);
void insert_val(List *list,ElemType x);
int length(List *list);
Node* find(List *list,ElemType key);
void delete_val(List *list,ElemType x);
void sort(List *list);
void reverse(List *list);
void clear(List *list);
void destory(List *list);
//----------------------

void main()
{
	List myList;
	initSCList(&myList);

	ElemType item;
	int select=1;
	int s;
	Node *p=NULL;
	while(select)
	{
		printf("**********************************\n");
		printf("* [1]push_back    [2]push_front  *\n");
		printf("* [3]show_list    [4]pop_back    *\n");
		printf("* [5]pop_front    [6]insert_val  *\n");
		printf("* [7]find         [8]length      *\n");
		printf("* [9]delete_val   [10]sort       *\n");
		printf("* [11]reverse     [12]clear      *\n");
		printf("* [13]destory     [0]quit _system *\n");
		printf("**********************************\n");
		printf("���������ѡ��->\n");
		scanf("%d",&select);
		
		switch(select)
		{
		case 1:
			printf("��������������ֵ(-1����)��>\n");
			while(scanf("%d",&item),item!=-1)
				push_back(&myList,item);
			break;
		case 2:
			printf("��������������ֵ(-1����)��>\n");
			while(scanf("%d",&item),item!=-1)
				push_front(&myList,item);
			break;
		case 3:
			show_list(&myList);
			break;
		case 4:
			pop_back(&myList);
			break;
		case 5:
			pop_front(&myList);
			break;
		case 6:
			printf("��������������ֵ��>\n");
			scanf("%d",&item);
			insert_val(&myList,item);
			break;
		case 7:
			printf("��������Ҫ���ҵ�ֵ��>\n");
			scanf("%d",&item);
			p=find(&myList,item);
			if(p==NULL){
				printf("�����ҵ����ݲ�����\n");
			}else{
				printf("��Ҫ���ҵ�����Ϊ��%d\n",p->data);
			}
			break;
		case 8:
			s=length(&myList);
			printf("��ǰ����Ϊ%d\n",s);
			break;
		case 9:
			printf("��������Ҫɾ����ֵ��");
			scanf("%d",&item);
			delete_val(&myList,item);
			break;
		case 10:
			sort(&myList);
			break;
		case 11:
			reverse(&myList);
			break;
		case 12:
			clear(&myList);
			printf("���������\n");
			break;
		//case 13:
		//	destory(&myList);
		case 0:
			printf("Bye!\n");
			break;
		default:
			printf("����ָ���������������\n");
			break;
		}	
	}
	destory(&myList);
}
//�����Ǻ���ʵ��
//����ڵ�
Node* buyNode(ElemType x)
{
	Node *s =(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	s->data=x;
	s->next=s->prior=NULL;//ǰ����̶�Ϊ��
	return s;	
}
//��ʼ������
void initSCList(List *list)
{
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	list->first=list->last=s;
	list->last->next=NULL;
	list->first->prior=NULL;
	list->size=0;
}
//β��
void push_back(List *list,ElemType x)
{
	Node *s=buyNode(x);
	assert(s != NULL);
	s->prior=list->last;
	list->last->next=s;
	list->last=s;
	list->size++;
	
}
//��ʾ����
void show_list(List *list)
{
	Node *p=list->first->next;
	while(p != NULL)
	{
		printf("%d-->",p->data);
		p=p->next;
	}
	printf("Nul.\n");
	
}
//ͷ��
void push_front(List *list,ElemType x)
{
	Node *s=buyNode(x);
	//���������ǵ�һ���ڵ�
	if(list->first == list->last)
	{
		//s->prior=list->first;
		//list->first->next=s;
		list->last=s;
	}
	else//����
	{
		s->next=list->first->next;
		s->next->prior=s;
	}
	s->prior=list->first;
	list->first->next=s;
	
	list->size++;
	
}
//βɾ
void pop_back(List *list)
{
	if(list->size == 0)
	{
		printf("��ǰ����û�����ݣ��޷�ɾ��\n");
		return;
	}
	Node *p=list->first;
	while(p->next != list->last)
	{
		p=p->next;
	}
	free(list->last);
	list->last=p;
	list->last->next=NULL;
	list->size--;
	
}
//ͷɾ
void pop_front(List *list)
{
	if(list->size == 0)
	{
		printf("��ǰ����û�����ݣ��޷�ɾ��\n");
		return;
	}
	Node *p=list->first->next;
	//���ɾ���������һ���ڵ�
	if(list->first->next==list->last)
	{
		list->last=list->first;
		list->last->next=NULL;
	}
	else
	{
		p->next->prior=list->first;
		list->first->next=p->next;
	}
	free(p);
	list->size--;
	
}
//��ֵ����(���������)
void insert_val(List *list,ElemType x)
{
	Node *p=list->first;
	while(p->next != NULL && p->next->data<x)
	{
		p=p->next;
	}
	if(p->next == NULL)//��ʱ�����һ���ڵ�������
	{
		push_back(list,x);//β��
	}
	else
	{
		Node *s=buyNode(x);
		s->next=p->next;
		s->next->prior=s;
		s->prior=p;
		p->next=s;
		list->size++;
	}
	
}
//�󳤶�
int length(List *list)
{
	return list->size;

}
//����
Node* find(List *list,ElemType key)
{
	Node *p=list->first->next;
	while(p != NULL && p->data != key)
	{
		p=p->next;
	}
	return p;
}
//��ֵɾ��
void delete_val(List *list,ElemType x)
{
	if(list->size == 0)
	{
		printf("��ǰ������û�����ݣ��޷�����ɾ��\n");
		return;
	}
	Node *p=find(list,x);
	if(p == NULL)
	{
		printf("��Ҫ���ҵ����ݲ�����,�޷�����ɾ��\n");
		return;
	}
	//��������һ���ڵ�
	if(p==list->last)
	{
		list->last=p->prior;
		list->last->next=NULL;
	}
	else
	{
		p->next->prior=p->prior;
		p->prior->next=p->next;
	}
	free(p);
	list->size--;

}
//����
void sort(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("��ǰ�����е����ݲ���������\n");
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;

	//�Ͽ�����
	list->last=s;
	list->last->next=NULL;

	while(q != NULL)
	{
		s=q;
		q=q->next;

		Node *p=list->first;
		while(p->next != NULL && p->next->data < s->data)
		{
			p=p->next;
		}
		//��ʱ���ǵ�һ���ڵ�
		if(p->next==NULL)
		{
			s->next=NULL;
			s->prior=list->last;
			list->last->next=s;
			list->last=s;
		}
		else
		{
			s->next=p->next;
			s->next->prior=s;
			s->prior=s;
			p->next=s;
		}
	}
}
//��ת
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("��ǰ�����е����ݲ���������\n");
		return;
	}
	Node *p=list->first->next;
	Node *q=p->next;

	//�Ͽ�����
	list->last=p;
	list->last->next=NULL;

	while(q != NULL)
	{
		p=q;
		q=q->next;

		p->next=list->first->next;
		p->next->prior=p;
		p->prior=list->first;
		list->first->next=p;
	}
}
void clear(List *list)
{
	if(list->size==0)
	{
		printf("��ǰ�����������ݣ��޷����\n");
		return;
	}
	Node *p=list->first->next;
	while(p != NULL)
	{
		//���ֻ��һ���ڵ�
		if(p==list->last)
		{
			list->last=list->first;
			list->last->next=NULL;
		}
		else
		{
			p->next->prior=list->first;
			list->first->next=p->next;
		}
		free(p);
		p=list->first->next;
	}
	list->size=0;

}
void destory(List *list)
{
	clear(list);
	free(list->first);
	list->first=list->last=NULL;
	printf("��ǰ�����ѱ��ݻ�\n");
}
