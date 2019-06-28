#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct ListNode
{
	ElemType data;
	struct ListNode *next;
}ListNode;

typedef ListNode* List;

//��ʼ������,����ͷ���ڵ�
void initList(List *head)
{	
	//ͷ���ڵ��data�򲻱�����Ϣ���߱�������ĳ��ȵ���Ϣ
	(*head)=(ListNode*)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->next=NULL;
}
//����ͷ����β������
void createList(List *head)
{	
	ListNode *p=*head;
	for(int i=1;i<=10;++i)
	{
		p=p->next=(ListNode*)malloc(sizeof(ListNode));
		assert(p !=NULL);
		p->data=i;
		p->next=NULL;
	}
}
/*
//����ͷ����ͷ������
void createList(List *head)
{
	for(int i=1;i<=10;++i)
	{
		ListNode *s=(ListNode*)malloc(sizeof(ListNode));
		s->data=i;
		s->next=(*head)->next;
		(*head)->next=s;
	}
}
*/

/*
//��������,ͷ������
void createList(List *head)
{
	//*head���ٿռ�
	(*head)=(ListNode *)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->data=1;
	(*head)->next=NULL;

	for(int i=2;i<=10;++i)
	{
		ListNode *s=(ListNode*)malloc(sizeof(ListNode));
		s->data=i;
		s->next=*head;
		*head=s;
	}
}
*/

/*
//��������,β������
void createList(List *head)//�˴�*headΪ����ָ��
{	
	//*head���ٿռ�
	(*head)=(ListNode *)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->data=1;
	(*head)->next=NULL;

	ListNode *p=*head;
	for(int i=2;i<=10;++i)
	{
		ListNode *s=(ListNode*)malloc(sizeof(ListNode));
		assert(s != NULL);
		s->data=i;
		s->next=NULL;
		p->next=s;
		p=s;
	}
}
*/
//��ʾ����
void showList(List head)
{
	ListNode *p=head->next;
	while(p !=NULL)
	{
		printf("%d->",p->data);
		p=p->next;
	}
	printf("NUL.\n");
}

void main()
{
	List mylist;
	initList(&mylist);
	createList(&mylist);
	showList(mylist);
}