#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define ElemType int

typedef struct Node
{
	ElemType data;
	struct   Node *prior;//前驱节点
	struct   Node *next;//后继节点
}Node,*PNode;

typedef struct List
{
	PNode first;
	PNode last;
	int   size;
}List;

//函数声明
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
		printf("请输入你的选择->\n");
		scanf("%d",&select);
		
		switch(select)
		{
		case 1:
			printf("请输入你想插入的值(-1结束)：>\n");
			while(scanf("%d",&item),item!=-1)
				push_back(&myList,item);
			break;
		case 2:
			printf("请输入你想插入的值(-1结束)：>\n");
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
			printf("请输入你想插入的值：>\n");
			scanf("%d",&item);
			insert_val(&myList,item);
			break;
		case 7:
			printf("请输入你要查找的值：>\n");
			scanf("%d",&item);
			p=find(&myList,item);
			if(p==NULL){
				printf("您查找的数据不存在\n");
			}else{
				printf("您要查找的数据为：%d\n",p->data);
			}
			break;
		case 8:
			s=length(&myList);
			printf("当前表长度为%d\n",s);
			break;
		case 9:
			printf("请输入你要删除的值：");
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
			printf("链表已清除\n");
			break;
		//case 13:
		//	destory(&myList);
		case 0:
			printf("Bye!\n");
			break;
		default:
			printf("输入指令错误，请重新输入\n");
			break;
		}	
	}
	destory(&myList);
}
//以下是函数实现
//申请节点
Node* buyNode(ElemType x)
{
	Node *s =(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	s->data=x;
	s->next=s->prior=NULL;//前驱后继都为空
	return s;	
}
//初始化链表
void initSCList(List *list)
{
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	list->first=list->last=s;
	list->last->next=NULL;
	list->first->prior=NULL;
	list->size=0;
}
//尾插
void push_back(List *list,ElemType x)
{
	Node *s=buyNode(x);
	assert(s != NULL);
	s->prior=list->last;
	list->last->next=s;
	list->last=s;
	list->size++;
	
}
//显示链表
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
//头插
void push_front(List *list,ElemType x)
{
	Node *s=buyNode(x);
	//如果插入的是第一个节点
	if(list->first == list->last)
	{
		//s->prior=list->first;
		//list->first->next=s;
		list->last=s;
	}
	else//否则
	{
		s->next=list->first->next;
		s->next->prior=s;
	}
	s->prior=list->first;
	list->first->next=s;
	
	list->size++;
	
}
//尾删
void pop_back(List *list)
{
	if(list->size == 0)
	{
		printf("当前链表没有数据，无法删除\n");
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
//头删
void pop_front(List *list)
{
	if(list->size == 0)
	{
		printf("当前链表没有数据，无法删除\n");
		return;
	}
	Node *p=list->first->next;
	//如果删除的是最后一个节点
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
//按值插入(按升序插入)
void insert_val(List *list,ElemType x)
{
	Node *p=list->first;
	while(p->next != NULL && p->next->data<x)
	{
		p=p->next;
	}
	if(p->next == NULL)//此时在最后一个节点后面插入
	{
		push_back(list,x);//尾插
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
//求长度
int length(List *list)
{
	return list->size;

}
//查找
Node* find(List *list,ElemType key)
{
	Node *p=list->first->next;
	while(p != NULL && p->data != key)
	{
		p=p->next;
	}
	return p;
}
//按值删除
void delete_val(List *list,ElemType x)
{
	if(list->size == 0)
	{
		printf("当前链表中没有数据，无法进行删除\n");
		return;
	}
	Node *p=find(list,x);
	if(p == NULL)
	{
		printf("您要查找的数据不存在,无法进行删除\n");
		return;
	}
	//如果是最后一个节点
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
//排序
void sort(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前链表中的数据不足以排序\n");
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;

	//断开链表
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
		//此时若是第一个节点
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
//翻转
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前链表中的数据不足以排序\n");
		return;
	}
	Node *p=list->first->next;
	Node *q=p->next;

	//断开链表
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
		printf("当前链表中无数据，无法清空\n");
		return;
	}
	Node *p=list->first->next;
	while(p != NULL)
	{
		//如果只有一个节点
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
	printf("当前链表已被摧毁\n");
}
