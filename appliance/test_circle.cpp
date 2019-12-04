#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType char

#define STACK_INIT_SIZE 8
#define STACK_INCR_SIZE 3

typedef struct SeqStack
{
	ElemType *base;//存储空间基地址
	int      top;//当前位置指针
	int      capacity;//容量大小
}SeqStack;

//函数声明
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
	printf("请输入一个字符串：");
	gets(a);

	int i=0,j=0;
	//求字符串的长度
	while(a[i]!='\0')
		i++;
	i--;

	SeqStack ss;
	initStack(&ss);;
	//对字符串进行入栈
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
			pop(&ss);//出栈
			if(k!=a[j])
			{
				printf("不是回文\n");
				return;
			}
			printf("是回文\n");
			return;
		}
		
	}
}


//函数实现
void initStack(SeqStack *s)
{
	s->base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);//分配连续的存储空间
	assert(s->base != NULL);
	s->capacity=STACK_INIT_SIZE;
	s->top=0;//top从0开始
}
//增加容量
bool inc(SeqStack *s)
{
	ElemType *newBase=(ElemType *)realloc(s->base,sizeof(ElemType)*(s->capacity+STACK_INCR_SIZE));
	if(newBase == NULL)
	{
		printf("当前系统内存不足，无法申请空间.\n");
		return false;
	}
	s->base=newBase;
	s->capacity+=STACK_INCR_SIZE;
	return true;
}
//判断当前栈空间是否满
bool isFull(SeqStack *s)
{
	return s->top>=s->capacity;
}
//判断当前栈是否空
bool isEmpty(SeqStack *s)
{
	return s->top==0;
}
//入栈
void push(SeqStack *s,ElemType x)
{
	if(isFull(s) && !inc(s))
	{
		printf("当前栈空间已满，%d 无法入栈\n",x);
		return;
	}
	s->base[s->top++]=x;
	//s->top++;
}
//显示
void show(SeqStack *s)
{
	for(int i=s->top-1;i>=0;--i)
	{
		printf("%d\n",s->base[i]);
	}
	printf("\n");
}
//弹栈
void pop(SeqStack *s)
{
	if(isEmpty(s))
	{
		printf("当前栈中无数据，无法弹栈\n");
		return;
	}
	s->top--;
}
//获得栈顶元素
bool getTop(SeqStack *s,ElemType *v)
{
	if(isEmpty(s))
	{
		printf("当前栈中无数据，无法出栈\n");
		return false;
	}
	*v=s->base[s->top-1];//不能是--s->top;
	return true;
}
//获得栈的长度
int getLength(SeqStack *s)
{
	return s->top;
}
//清空栈
void clear(SeqStack *s)
{
	s->top=0;
	printf("当前栈已清空\n");
}
//销毁栈
void destory(SeqStack *s)
{
	free(s->base);
	s->base=NULL;
	s->capacity=s->top=0;
	printf("当前栈已销毁\n");
}

//打印函数
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
	printf("请输入一个字符串：");
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
		printf("是回文\n");
	else
		printf("不是回文\n");
	for(;j<=i;i--,j++)
	{
		if(a[j]!=a[i])
			break;
	}
	if(j>i)
		printf("是回文\n");
	else
		printf("不是回文\n");
	
}*/