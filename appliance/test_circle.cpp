#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType char

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
void conver_8(ElemType value);
bool check(char *str);
void lineEdit();
void Printf(SeqStack *s);

void main()
{
	char a[100];
	printf("������һ���ַ�����");
	gets(a);

	int i=0,j=0;
	//���ַ����ĳ���
	while(a[i]!='\0')
		i++;
	i--;

	SeqStack ss;
	initStack(&ss);;
	//���ַ���������ջ
	for(;j<=i;j++)
	{
		push(&ss,a[j]);
	}
	while(true)
	{
		
		for(j=0;j<=i;++j)
		{
			char k;
			getTop(&ss,&k);
			pop(&ss);//��ջ
			if(k!=a[j])
			{
				printf("���ǻ���\n");
				return;
			}
			printf("�ǻ���\n");
			return;
		}
		
	}
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

//��ӡ����
void Printf(SeqStack *s)
{
	for(int i=0;i<s->top;++i)
	{
		printf("%c",s->base[i]);
	}
	printf("\n");

}
/*
void main()
{
	char a[100];
	printf("������һ���ַ�����");
	gets(a);
	int i=0,j=0;
	while(a[i]!='\0')
		i++;
	i--;
	while(j<=i)
	{
		if(a[j]!=a[i])
		{
			break;
		}
		i--;
		j++;
	}
	if(j>i)
		printf("�ǻ���\n");
	else
		printf("���ǻ���\n");
	for(;j<=i;i--,j++)
	{
		if(a[j]!=a[i])
			break;
	}
	if(j>i)
		printf("�ǻ���\n");
	else
		printf("���ǻ���\n");
	
}*/