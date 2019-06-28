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
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	s->data=x;
	s->next=s->prior=NULL;
	return s;		
}
//初始化链表
void initSCList(List *list)
{
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s != NULL);
	list->first=list->last=s;
	list->first->prior=list->last;
	list->last->next=list->first;
	list->size=0;

}
//尾插
void push_back(List *list,ElemType x)
{
	Node *s=buyNode(x);
	s->next=list->last->next;
	s->next->prior=s;
	s->prior=list->last;
	list->last->next=s;

	//修改last指针指向
	list->last=s;
	list->size++;
	
}
//显示链表
void show_list(List *list)
{
	Node *p=list->first->next;
	while(p != list->first)
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
	s->next=list->first->next;
	s->next->prior=s;
	s->prior=list->first;
	list->first->next=s;
	//如果插入的是第一个
	if(list->first==list->last)
	{
		list->last=s;
	}
	list->size++;
	
}
//尾删
void pop_back(List *list)
{
	if(list->size==0)
	{
		printf("当前表中无数据，无法进行删除\n");
		return;
	}
	Node *p=list->last;
	list->last=list->last->prior;//修改last指针指向

	p->next->prior=p->prior;
	p->prior->next=p->next;
	free(p);
	list->size--;

	
}
//头删
void pop_front(List *list)
{
	if(list->size==0)
	{
		printf("当前表中无数据，无法进行删除\n");
		return;
	}

	Node *p=list->first->next;
	p->next->prior=p->prior;
	p->prior->next=p->next;
	if(list->size==1)
	{
		list->last=list->first;
	}
	list->size--;
	
}
//按值插入(按升序插入)
void insert_val(List *list,ElemType x)
{
	Node *p=list->first;

	while(p->next != list->last && p->next->data<x)
	{
		p=p->next;
	}
	//一圈之后还是比插入值小,直接尾插
	if(p->next==list->last && p->next->data<x)
	{
		push_back(list,x);
	}
	else//否则，在p之后插入
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
	while(p != list->first && p->data != key)
	{
		p=p->next;
	}
	if(p==list->first)
	{
		return NULL;
	}
	return p;
}
//按值删除
void delete_val(List *list,ElemType x)
{
	if(list->size==0)
	{
		printf("当前表中没有数据，无法进行按值删除操作\n");
		return;
	}
	Node *p=find(list,x);
	if(p==NULL)
	{
		printf("您要删除的值不存在\n");
		return;
	}
	//如果要删除的值在最后，进行尾删
	if(p==list->last)
	{
		pop_back(list);
	}
	else
	{
		p->next->prior=p->prior;
		p->prior->next=p->next;
		free(p);
		list->size--;
	}
}
//排序
void sort(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前表中数据不足以排序\n");
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//从第一个位置后断开当前链表
	list->last->next=NULL;
	list->last=s;
	list->last->next=list->first;
	list->first->prior=list->last;

	while(q != NULL)
	{
		s=q;
		q=q->next;

		Node *p=list->first;

		while(p->next != list->last && p->next->data<s->data)
		{
			p=p->next;
		}
		//一圈之后还是比插入值小,直接尾插
		if(p->next==list->last && p->next->data<s->data)
		{
			s->next=list->last->next;
			s->next->prior=s;
			s->prior=list->last;
			list->last->next=s;
			list->last=s;
		}
		else//否则，在p之后插入
		{
			s->next=p->next;
			s->next->prior=s;
			s->prior=p;
			p->next=s;
		}
	}
}
//翻转
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前表中数据不足以排序\n");
		return;
	}
	Node *p=list->first->next;
	Node *q=p->next;
	//从第一个位置后断开当前链表
	list->last->next=NULL;
	list->last=p;
	list->last->next=list->first;
	list->first->prior=list->last;

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
//链表清除
void clear(List *list)
{
	if(list->size==0)
	{
		printf("当前链表已空，无需清除\n");
		return;
	}
	Node *p=list->first->next;
	while(p!=list->first)
	{
		p->next->prior=list->first;
		list->first->next=p->next;
		free(p);
		p=list->first->next;
	}
	list->last=list->first;
	list->size=0;

}
//链表摧毁
void destory(List *list)
{
	clear(list);
	free(list->first);
	list->first=list->last=NULL;
	printf("链表已被摧毁\n");
}
