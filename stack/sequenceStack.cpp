#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

#define STACK_INIT_SIZE 8
#define STACK_INCR_SIZE 3

typedef struct SeqStack
{
	ElemType *base;//�洢�ռ����ַ
	int      top;//��ǰλ��ָ��
	int      capacity;//������С
}SeqStack;

//��������
void initStack(SeqStack *s);
bool inc(SeqStack *s);
bool isFull(SeqStack *s);
bool isEmpty(SeqStack *s);
void push(SeqStack *s,ElemType x);
void show(SeqStack *s);
void pop(SeqStack *s);
bool getTop(SeqStack *s,ElemType *v);
void clear(SeqStack *s);
void destory(SeqStack *s);
int getLength(SeqStack *s);


void main()
{
	SeqStack st;
	initStack(&st);
	ElemType v;
	for(int i=1;i<=10;++i)
	{
		push(&st,i);
	}
	printf("��ǰջ����:%d \n",getLength(&st));
	show(&st);
	getTop(&st,&v);
	printf("%d ��ջ\n",v);
	pop(&st);
	show(&st);
	clear(&st);
	destory(&st);
}

//����ʵ��
void initStack(SeqStack *s)
{
	s->base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);//���������Ĵ洢�ռ�
	assert(s->base != NULL);
	s->capacity=STACK_INIT_SIZE;
	s->top=0;//top��0��ʼ
}
//��������
bool inc(SeqStack *s)
{
	ElemType *newBase=(ElemType *)realloc(s->base,sizeof(ElemType)*(s->capacity+STACK_INCR_SIZE));
	if(newBase == NULL)
	{
		printf("��ǰϵͳ�ڴ治�㣬�޷�����ռ�.\n");
		return false;
	}
	s->base=newBase;
	s->capacity+=STACK_INCR_SIZE;
	return true;
}
//�жϵ�ǰջ�ռ��Ƿ���
bool isFull(SeqStack *s)
{
	return s->top>=s->capacity;
}
//�жϵ�ǰջ�Ƿ��
bool isEmpty(SeqStack *s)
{
	return s->top==0;
}
//��ջ
void push(SeqStack *s,ElemType x)
{
	if(isFull(s) && !inc(s))
	{
		printf("��ǰջ�ռ�������%d �޷���ջ\n",x);
		return;
	}
	s->base[s->top++]=x;
	//s->top++;
}
//��ʾ
void show(SeqStack *s)
{
	for(int i=s->top-1;i>=0;--i)
	{
		printf("%d\n",s->base[i]);
	}
	printf("\n");
}
//��ջ
void pop(SeqStack *s)
{
	if(isEmpty(s))
	{
		printf("��ǰջ�������ݣ��޷���ջ\n");
		return;
	}
	s->top--;
}
//���ջ��Ԫ��
bool getTop(SeqStack *s,ElemType *v)
{
	if(isEmpty(s))
	{
		printf("��ǰջ�������ݣ��޷���ջ\n");
		return false;
	}
	*v=s->base[s->top-1];//������--s->top;
	return true;
}
//���ջ�ĳ���
int getLength(SeqStack *s)
{
	return s->top;
}
//���ջ
void clear(SeqStack *s)
{
	s->top=0;
	printf("��ǰջ�����\n");
}
//����ջ
void destory(SeqStack *s)
{
	free(s->base);
	s->base=NULL;
	s->capacity=s->top=0;
	printf("��ǰջ������\n");
}