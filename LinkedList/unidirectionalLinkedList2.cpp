#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct Node{
	ElemType data;//������
	struct Node *next;//ָ����һ���ڵ��nextָ��
}Node,*ListNode;

//����һ��˳�������ָ������
typedef struct List{
	ListNode first;//ָ�������ͷ���
	ListNode last; //ָ�������β���
	size_t   size; //������ı���
	//ElemType size;
}List;

//һ���Ǻ�������
void InitList(List *list);
void push_back(List *list,ElemType x);
void show_list(List *list);
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
//---------------------
Node* buyNode(ElemType x);
typedef Node* It;
It begin(List *list);
It end(List *list);
void insert(List *list,It pos,ElemType x);


void main()
{
	List mylist;
	InitList(&mylist);
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
				push_back(&mylist,item);
			break;
		case 2:
			printf("��������������ֵ(-1����)��>\n");
			while(scanf("%d",&item),item!=-1)
				push_front(&mylist,item);
			break;
		case 3:
			show_list(&mylist);
			break;
		case 4:
			pop_back(&mylist);
			break;
		case 5:
			pop_front(&mylist);
			break;
		case 6:
			printf("��������������ֵ��>\n");
			scanf("%d",&item);
			insert_val(&mylist,item);
			break;
		case 7:
			printf("��������Ҫ���ҵ�ֵ��>\n");
			scanf("%d",&item);
			p=find(&mylist,item);
			if(p==NULL){
				printf("�����ҵ����ݲ�����\n");
			}else{
				printf("��Ҫ���ҵ�����Ϊ��%d\n",p->data);
			}
			break;
		case 8:
			s=length(&mylist);
			printf("��ǰ����Ϊ%d\n",s);
			break;
		case 9:
			printf("��������Ҫɾ����ֵ��");
			scanf("%d",&item);
			delete_val(&mylist,item);
			break;
		case 10:
			sort(&mylist);
			break;
		case 11:
			reverse(&mylist);
			break;
		case 12:
			clear(&mylist);
			printf("���������\n");
			break;
		case 13:
			destory(&mylist);
		case 0:
			printf("Bye!\n");
			break;
		default:
			printf("����ָ���������������\n");
			break;
		}
	}

}
//����ĳ�ʼ��
void InitList(List *list)
{
	list->first=list->last=(Node*)malloc(sizeof(Node));
	assert(list->first !=NULL);
	list->first->next=NULL;
	list->size=0;
}
//β��
void push_back(List *list,ElemType x)
{
	insert(list,end(list),x);
}
/*
void push_back(List *list,ElemType x)
{
	//Node *s=(Node *)malloc(sizeof(Node));
	//assert(s!=NULL); 
	//s->data=x;
	//s->next=NULL;
	Node *s=buyNode(x);
	list->last->next=s;
	list->last=s;
	list->size++;
}
*/
//ͷ��
void push_front(List *list,ElemType x)
{
	insert(list,begin(list),x);
}
/*
void push_front(List *list,ElemType x)
{
	//Node *s=(Node *)malloc(sizeof(Node));
	//assert(s!=NULL);
	//s->data=x;
	//s->next=NULL;
	Node *s=buyNode(x);

	//��������Ϊ��һ��
	if(list->size==0)
	{
		list->last=s;	
	}

	s->next=list->first->next;
	list->first->next=s;
	list->size++;
}
*/
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
//βɾ
void pop_back(List *list)
{
	if(list->size==0)
	{
		printf("���ѿգ��޷�ɾ��\n");
		return;
	}
	Node *p=list->first;
	//ѭ���ж�p->next�Ƿ����list->last
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
	if(list->size==0)
	{
		printf("���ѿգ��޷�ɾ��\n");
		return;
	}
	Node *p=list->first->next;
	list->first->next=p->next;
	free(p);
	if(list->size==1)
	{
		list->last=list->first;
	}
	list->size--;

}
//��ֵ����
void insert_val(List *list,ElemType x)
{
	//Node *s=(Node *)malloc(sizeof(Node));
	//assert(s !=NULL);
	//s->data=x;
	//s->next=NULL;
	Node *s=buyNode(x);


	Node *p=list->first;
	//�ж�p->next->data�Ƿ�<x
	while(p->next!=NULL && p->next->data < x)
	{
		p=p->next;
	}
	//���p-next==null��������ݲ���֮���а�list->lastָ��s
	if(p->next==NULL)
	{
		list->last=s;
	}
	s->next=p->next;
	p->next=s;
	list->size++;
}
//����
Node* find(List *list,ElemType key)
{
	Node *p=list->first;
	while(p!=NULL && p->data!=key)
	{
		p=p->next;
	}
	return p;
}
//�󳤶�
int length(List *list)
{
	return list->size;
}
//��ֵɾ��
void delete_val(List *list,ElemType x)
{
	if(list->size==0)
	{
		return;
	}
	Node *p=find(list,x);
	if(p==NULL)
	{
		printf("���ݲ�����,�޷�ɾ��\n");
		return;
	}
	
	if(p==list->last)
	{
		pop_back(list);
	}
	else
	{
		Node *q=p->next;
		//��q->data��ֵ������p->data
		p->data=q->data;
		//p->next����ָ��q->next
		p->next=q->next;
		free(q);
		list->size--;
	}

}
//����
void sort(List *list)
{
	if(list->size==0 || list->size==1)
	{
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//�Ͽ�����
	list->last=s;
	list->last->next=NULL;
	while(q!=NULL)
	{
		s=q;
		q=q->next;

		Node *p=list->first;
		//�ж�p->next->data�Ƿ�<x
		while(p->next!=NULL && p->next->data < s->data)
		{
			p=p->next;
		}
		//���p-next==null��������ݲ���֮���а�list->lastָ��s
		if(p->next==NULL)
		{
			list->last=s;
		}
		s->next=p->next;
		p->next=s;

	}
}
//��ת����
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//�Ͽ�����
	list->last=s;
	list->last->next=NULL;
	while(q!=NULL)
	{
		s=q;
		q=q->next;
		//ͷ��
		s->next=list->first->next;
		list->first->next=s;
	}
}
//�������
void clear(List *list)
{
	if(list->size==0)
	{
		return;
	}
	Node *p=list->first->next;
	while(p!=NULL)
	{
		list->first->next=p->next;
		free(p);
		p=list->first->next;
	}

	list->last=list->first;
	list->size=0;
	
}
//�ݻ�����
void destory(List *list)
{
	clear(list);
	free(list->first);
	list->first=list->last=NULL;
	printf("�����Ѵݻ�\n");
}
//����ڵ�
Node* buyNode(ElemType x)
{
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s!=NULL);
	s->data=x;
	s->next=NULL;
	return s;
}
//�Դ�����иĽ�
It begin(List *list)
{
	return list->first->next;
}
It end(List *list)
{
	return list->last->next;
}
void insert(List *list,It pos,ElemType x)
{	
	Node *p=list->first;
	while(p->next!=pos)
	{
		p=p->next;
	}
	Node *s=buyNode(x);
	s->next=p->next;
	p->next=s;
	if(pos==NULL)
	{
		list->last=s;
	}
	list->size++;

}
