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
	s->next=NULL;
	return s;
}
//初始化链表
void initSCList(List *list)
{
	Node *s = (Node *)malloc(sizeof(Node));//创建出头结点
	assert(s != NULL);
	list->first=list->last=s;
	list->last->next=list->first;//进行手尾循环
	list->size=0;
}
//尾插
void push_back(List *list,ElemType x)
{
	Node *s = buyNode(x);
	list->last->next=s;
	list->last=s;
	list->last->next=list->first;//s->list-first 构建首尾循环
	list->size++;
}
//显示链表
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
//头插
void push_front(List *list,ElemType x)
{
	Node *s=buyNode(x);
	s->next=list->first->next;//让第一个节点next指向头结点，构建循环
	list->first->next=s;
	//判断是否是第一个节点
	if(list->first==list->last)
	{
		list->last=s;//如果是，则让last指向第一个节点
	}
	list->size++;
}
//尾删
void pop_back(List *list)
{
	if(list->size == 0)
	{
		printf("当前链表中没有数据无法进行删除操作\n");
		return;
	}
	Node *p=list->first;
	while(p->next != list->last)
	{
		p=p->next;
	}
	free(list->last);
	list->last=p;
	list->last->next=list->first;//p->next=list->first 最后一个节点指向头结点 构建循环条件
	list->size--;
}
//头删
void pop_front(List *list)
{
	if(list->size == 0)
	{
		printf("当前链表中没有数据无法进行删除操作\n");
		return;
	}
	Node *p=list->first->next;
	list->first->next=p->next;
	free(p);
	//如果只有一个节点
	if(list->size==1)
	{
		list->last=list->first;//把last指向first 构建循环
	}
	list->size--;
}
//按值插入
void insert_val(List *list,ElemType x)
{
	Node *p=list->first;
	//首先进行查找，判断条件是：p->next != list->last 同时 p->next-data < x(默认按升序进行插入)
	while(p->next != list->last && p->next->data < x)
	{
		p=p->next;
	}
	//如果最后一个节点data值小于x,直接进行尾插
	if(p->next == list->last && p->next->data < x)
	{
		push_back(list,x);
	}
	else
	{
		//否则直接进行插入
		Node *s = buyNode(x);
		s->next=p->next;
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
	if(list->size == 0)
	{
		printf("当前链表中没有数据无法进行查找\n");
		return NULL;
	}
	Node *p=list->first->next;
	//进行查找，判断条件为 p != list->first 同时 p->data != key
	while(p != list->first && p->data != key)
	{
		p=p->next;
	}
	//p=list->first 说明走了一个循环没有找到数据
	if(p==list->first)
	{
		return NULL;
	}
	return p;
}
//按值删除
void delete_val(List *list,ElemType x)
{
	if(list->size == 0)
	{
		printf("当前链表中没有数据无法进行删除\n");
		return;
	}
	Node *p=find(list,x);
	if(p == NULL)
	{
		printf("要删除的数据不存在\n");
		return;
	}
	//查找到的位置在最后一个节点，直接尾删
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
//排序
void sort(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前链表中数据不足排序\n");
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//断开链表
	list->last->next=NULL;
	list->last=s;//指向第一个节点
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
		//如果只有一个节点并且当前节点值小于s节点值,进行尾部插入
		if(p->next == list->last && p->next->data < s->data)
		{
			s->next=list->last->next;//插入节点执行list->last->next即list->first
			list->last->next=s;//第一个节点next指向s节点
			list->last=s;//last节点指向正在插入节点s
		}
		else
		{
			s->next=p->next;
			p->next=s;
		}
	}
}
//翻转
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		printf("当前链表中数据不足翻转\n");
		return;
	}
	Node *p=list->first->next;
	Node *q=p->next;

	//断开链表
	list->last->next=NULL;
	list->last=p;
	list->last->next=list->first;//p->next=list->first;

	while(q != NULL)
	{
		p=q;
		q=q->next;
		//类似头插
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
	list->last=list->first;//first和last都指向头结点
	list->last->next=list->first;//last->next指向头结点 构成循环
	list->size=0;//链表空间清零

}
void destory(List *list)
{
	clear(list);//先清除链表
	free(list->first);//释放掉节点指针
	list->first=list->last=NULL;
	printf("链表已摧毁\n");
}
