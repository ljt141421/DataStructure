#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct Node{
	ElemType data;//数据域
	struct Node *next;//指向下一个节点的next指针
}Node,*ListNode;

//创建一个顺序表用于指向单链表
typedef struct List{
	ListNode first;//指向单链表的头结点
	ListNode last; //指向单链表的尾结点
	size_t   size; //单链表的表长度
	//ElemType size;
}List;

//一下是函数声明
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
		printf("请输入你的选择->\n");
		scanf("%d",&select);
		switch(select)
		{
		case 1:
			printf("请输入你想插入的值(-1结束)：>\n");
			while(scanf("%d",&item),item!=-1)
				push_back(&mylist,item);
			break;
		case 2:
			printf("请输入你想插入的值(-1结束)：>\n");
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
			printf("请输入你想插入的值：>\n");
			scanf("%d",&item);
			insert_val(&mylist,item);
			break;
		case 7:
			printf("请输入你要查找的值：>\n");
			scanf("%d",&item);
			p=find(&mylist,item);
			if(p==NULL){
				printf("您查找的数据不存在\n");
			}else{
				printf("您要查找的数据为：%d\n",p->data);
			}
			break;
		case 8:
			s=length(&mylist);
			printf("当前表长度为%d\n",s);
			break;
		case 9:
			printf("请输入你要删除的值：");
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
			printf("链表已清除\n");
			break;
		case 13:
			destory(&mylist);
		case 0:
			printf("Bye!\n");
			break;
		default:
			printf("输入指令错误，请重新输入\n");
			break;
		}
	}

}
//链表的初始化
void InitList(List *list)
{
	list->first=list->last=(Node*)malloc(sizeof(Node));
	assert(list->first !=NULL);
	list->first->next=NULL;
	list->size=0;
}
//尾插
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
//头插
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

	//如果插入的为第一个
	if(list->size==0)
	{
		list->last=s;	
	}

	s->next=list->first->next;
	list->first->next=s;
	list->size++;
}
*/
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
//尾删
void pop_back(List *list)
{
	if(list->size==0)
	{
		printf("表已空，无法删除\n");
		return;
	}
	Node *p=list->first;
	//循环判断p->next是否等于list->last
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
	if(list->size==0)
	{
		printf("表已空，无法删除\n");
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
//按值插入
void insert_val(List *list,ElemType x)
{
	//Node *s=(Node *)malloc(sizeof(Node));
	//assert(s !=NULL);
	//s->data=x;
	//s->next=NULL;
	Node *s=buyNode(x);


	Node *p=list->first;
	//判断p->next->data是否<x
	while(p->next!=NULL && p->next->data < x)
	{
		p=p->next;
	}
	//如果p-next==null，则把数据插入之后还有把list->last指向s
	if(p->next==NULL)
	{
		list->last=s;
	}
	s->next=p->next;
	p->next=s;
	list->size++;
}
//查找
Node* find(List *list,ElemType key)
{
	Node *p=list->first;
	while(p!=NULL && p->data!=key)
	{
		p=p->next;
	}
	return p;
}
//求长度
int length(List *list)
{
	return list->size;
}
//按值删除
void delete_val(List *list,ElemType x)
{
	if(list->size==0)
	{
		return;
	}
	Node *p=find(list,x);
	if(p==NULL)
	{
		printf("数据不存在,无法删除\n");
		return;
	}
	
	if(p==list->last)
	{
		pop_back(list);
	}
	else
	{
		Node *q=p->next;
		//把q->data的值拷贝给p->data
		p->data=q->data;
		//p->next重新指向q->next
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
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//断开链表
	list->last=s;
	list->last->next=NULL;
	while(q!=NULL)
	{
		s=q;
		q=q->next;

		Node *p=list->first;
		//判断p->next->data是否<x
		while(p->next!=NULL && p->next->data < s->data)
		{
			p=p->next;
		}
		//如果p-next==null，则把数据插入之后还有把list->last指向s
		if(p->next==NULL)
		{
			list->last=s;
		}
		s->next=p->next;
		p->next=s;

	}
}
//翻转排序
void reverse(List *list)
{
	if(list->size==0 || list->size==1)
	{
		return;
	}
	Node *s=list->first->next;
	Node *q=s->next;
	//断开链表
	list->last=s;
	list->last->next=NULL;
	while(q!=NULL)
	{
		s=q;
		q=q->next;
		//头插
		s->next=list->first->next;
		list->first->next=s;
	}
}
//清除链表
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
//摧毁链表
void destory(List *list)
{
	clear(list);
	free(list->first);
	list->first=list->last=NULL;
	printf("链表已摧毁\n");
}
//购买节点
Node* buyNode(ElemType x)
{
	Node *s=(Node *)malloc(sizeof(Node));
	assert(s!=NULL);
	s->data=x;
	s->next=NULL;
	return s;
}
//对代码进行改进
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
