#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define ElemType int

typedef struct Node
{
	ElemType data;
	struct   Node *next;
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
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	s->data=x;
	s->next=NULL;
	return s;
}
//��ʼ������
void initSCList(List *list)
{
	Node *s = (Node *)malloc(sizeof(Node));//������ͷ���
	assert(s != NULL);
	list->first=list->last=s;
	list->last->next=list->first;//������βѭ��
	list->size=0;
}
//β��
void push_back(List *list,ElemType x)
{
	Node *s = buyNode(x);
	list->last->next=s;
	list->last=s;
	list->last->next=list->first;//s->list-first ������βѭ��
	list->size++;
}
//��ʾ����
void show_list(List *list)
{
	Node *p = list->first->next;
	while(p != list->first)
	{
		printf("%d-->",p->data);
		p=p->next;
	}
	printf("NULL.\n");
}
//ͷ��
void push_front(List *list,ElemType x)
{
	Node *s=buyNode(x);
	s->next=list->first->next;//�õ�һ���ڵ�nextָ��ͷ��㣬����ѭ��
	list->first->next=s;
	//�ж��Ƿ��ǵ�һ���ڵ�
	if(list->first==list->last)
	{
		list->last=s;//����ǣ�����lastָ���һ���ڵ�
	}
	list->size++;
}
//βɾ
void pop_back(List *list)
{
	if(list->size == 0)
	{
		printf("��ǰ������û�������޷�����ɾ������\n");
		return;
	}
	Node *p=list->first;
	while(p->next != list->last)
	{
		p=p->next;
	}
	free(list->last);
	list->last=p;
	list->last->next=list->first;//p->next=list->first ���һ���ڵ�ָ��ͷ��� ����ѭ������
	list->size--;
}
//ͷɾ
void pop_front(List *list)
{
	if(list->size == 0)
	{
		printf("��ǰ������û�������޷�����ɾ������\n");
		return;
	}
	Node *p=list->first->next;
	list->first->next=p->next;
	free(p);
	//���ֻ��һ���ڵ�
	if(list->size==1)
	{
		list->last=list->first;//��lastָ��first ����ѭ��
	}
	list->size--;
}
//��ֵ����
void insert_val(List *list,ElemType x)
{
	Node *p=list->first;
	//���Ƚ��в��ң��ж������ǣ�p->next != list->last ͬʱ p->next-data < x(Ĭ�ϰ�������в���)
	while(p->next != list->last && p->next->data < x)
	{
		p=p->next;
	}
	//������һ���ڵ�dataֵС��x,ֱ�ӽ���β��
	if(p->next == list->last && p->next->data < x)
	{
		push_back(list,x);
	}
	else
	{
		//����ֱ�ӽ��в���
		Node *s = buyNode(x);
		s->next=p->next;
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
	if(list->size == 0)
	{
		printf("��ǰ������û�������޷����в���\n");
		return NULL;
	}
	Node *p=list->first->next;
	//���в��ң��ж�����Ϊ p != list->first ͬʱ p->data != key
	while(p != list->first && p->data != key)
	{
		p=p->next;
	}
	//p=list->first ˵������һ��ѭ��û���ҵ�����
	if(p==list->first)
	{
		return NULL;
	}
	return p;
}
//��ֵɾ��
void delete_val(List *list,ElemType x)
{
	if(list->size == 0)
	{
		printf("��ǰ������û�������޷�����ɾ��\n");
		return;
	}
	Node *p=find(list,x);
	if(p == NULL)
	{
		printf("Ҫɾ�������ݲ�����\n");
		return;
	}
	//���ҵ���λ�������һ���ڵ㣬ֱ��βɾ
	if(p==list->last)
	{
		pop_back(list);
	}
	else
	{
		Node *q=p->next;
		p->data=q->data;
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
		printf("��ǰ���������ݲ�������\n");
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//�Ͽ�����
	list->last->next=NULL;
	list->last=s;//ָ���һ���ڵ�
	list->last->next=list->first;
	
	while(q != NULL)
	{
		s=q;
		q=q->next;
		Node *p=list->first;
		while(p->next != list->last && p->next->data < s->data)
		{
			p=p->next;
		}
		//���ֻ��һ���ڵ㲢�ҵ�ǰ�ڵ�ֵС��s�ڵ�ֵ,����β������
		if(p->next == list->last && p->next->data < s->data)
		{
			s->next=list->last->next;//����ڵ�ִ��list->last->next��list->first
			list->last->next=s;//��һ���ڵ�nextָ��s�ڵ�
			list->last=s;//last�ڵ�ָ�����ڲ���ڵ�s
		}
		else
		{
			s->next=p->next;
			p->next=s;
		}
	}
}
//��ת
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("��ǰ���������ݲ��㷭ת\n");
		return;
	}
	Node *p=list->first->next;
	Node *q=p->next;

	//�Ͽ�����
	list->last->next=NULL;
	list->last=p;
	list->last->next=list->first;//p->next=list->first;

	while(q != NULL)
	{
		p=q;
		q=q->next;
		//����ͷ��
		p->next=list->first->next;
		list->first->next=p;
	}

}
void clear(List *list)
{
	Node *p=list->first->next;
	while(p != list->first)
	{
		list->first->next=p->next;
		free(p);
		p=list->first->next;
	}
	list->last=list->first;//first��last��ָ��ͷ���
	list->last->next=list->first;//last->nextָ��ͷ��� ����ѭ��
	list->size=0;//����ռ�����

}
void destory(List *list)
{
	clear(list);//���������
	free(list->first);//�ͷŵ��ڵ�ָ��
	list->first=list->last=NULL;
	printf("�����Ѵݻ�\n");
}
