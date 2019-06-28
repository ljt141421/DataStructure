#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct StackNode
{
	ElemType data;//数据域
	struct StackNode *next;//指向下一个节点指针域
}StackNode;

typedef StackNode* LinkStack;

void initStack(LinkStack *s);
void push(LinkStack *s,ElemType x);
void show(LinkStack *s);
void pop(LinkStack *s);

void main()
{
	LinkStack st;
	initStack(&st);

	for(int i=1;i<=5;++i)
	{
		push(&st,i);
	}
	show(&st);
	pop(&st);
	show(&st);
}
//初始化栈
void initStack(LinkStack *s)//此处的*s相当于一个二级指针,因为LinkStack就是一个StackNode指针
{
	*s=NULL;
}
//只能使用头插的方式，先插入的排在最后面，只有这样才符合栈先进后出的性质
void push(LinkStack *s,ElemType x)
{
	StackNode *t=(StackNode*)malloc(sizeof(StackNode));
	assert(t != NULL);
	t->data=x;
	
	//如果此时是第一个元素
	if(*s == NULL)
	{
		*s=t;
		t->next=NULL;
	}
	else
	{
		t->next=*s;
		*s=t;
	}
}
//显示栈元素
void show(LinkStack *s)
{
	StackNode *p=*s;
	while(p != NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	printf("\n");
}
//弹栈,只能从头部弹栈，只有这样才符合栈先进后出的性质
void pop(LinkStack *s)
{
	StackNode *p=*s;
	printf("%d 出栈\n",p->data);
	*s=p->next;
	free(p);
	p=NULL;
}