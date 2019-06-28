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

//初始化链表,带有头部节点
void initList(List *head)
{	
	//头部节点的data域不保存信息或者保存链表的长度等信息
	(*head)=(ListNode*)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->next=NULL;
}
//带有头结点的尾部插入
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
//带有头结点的头部插入
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
//创建链表,头部插入
void createList(List *head)
{
	//*head开辟空间
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
//创建链表,尾部插入
void createList(List *head)//此处*head为二级指针
{	
	//*head开辟空间
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
//显示链表
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