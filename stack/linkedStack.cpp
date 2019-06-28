#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct StackNode
{
	ElemType data;//������
	struct StackNode *next;//ָ����һ���ڵ�ָ����
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
//��ʼ��ջ
void initStack(LinkStack *s)//�˴���*s�൱��һ������ָ��,��ΪLinkStack����һ��StackNodeָ��
{
	*s=NULL;
}
//ֻ��ʹ��ͷ��ķ�ʽ���Ȳ������������棬ֻ�������ŷ���ջ�Ƚ����������
void push(LinkStack *s,ElemType x)
{
	StackNode *t=(StackNode*)malloc(sizeof(StackNode));
	assert(t != NULL);
	t->data=x;
	
	//�����ʱ�ǵ�һ��Ԫ��
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
//��ʾջԪ��
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
//��ջ,ֻ�ܴ�ͷ����ջ��ֻ�������ŷ���ջ�Ƚ����������
void pop(LinkStack *s)
{
	StackNode *p=*s;
	printf("%d ��ջ\n",p->data);
	*s=p->next;
	free(p);
	p=NULL;
}