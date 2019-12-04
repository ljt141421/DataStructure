#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
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

//表达式求值
ElemType _getTop(SeqStack *s);
void _pop(SeqStack *s,ElemType *e);
bool in(ElemType c);//判断是否为操作字符
char operate(ElemType a,ElemType e,ElemType b);
ElemType precede(ElemType a,ElemType b);//判断操作符优先级
ElemType evaluateExpression();//表达式主要逻辑

void main()
{
	printf("请输入一段表达式(运算数介于0和9之间)：\n");
	ElemType e=evaluateExpression();
	printf("The result of expression is %d\n",e-48);
}

bool in(ElemType c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='#' || c=='(' || c==')' || c=='[' || c==']')
		return true;
	return false;
}
/*
ElemType operate(ElemType a,ElemType e,ElemType b)
{
	ElemType c;
	switch (e){
      case '+':
          c=a+b;
			break;
      case '-':
          c=a-b;
		  break;
      case '*':
          c=a*b;
		  break;
      case '/':
          c=a/b;
		  break;
	}
	return c;
}
*/
ElemType operate(ElemType a,ElemType e,ElemType b)
{
	ElemType c;
	a=a-48;
	b=b-48;
	switch (e){
      case '+':
          c=a+b+48;
			break;
      case '-':
          c=a-b+48;
		  break;
      case '*':
          c=a*b+48;
		  break;
      case '/':
          c=a/b+48;
		  break;
	}
	return c;
}
ElemType precede(ElemType a,ElemType b)
{
	//判断逻辑见书本53页
	if(a=='+' || a=='-')
	{
		if(b=='+' || b=='-' || b==')' || b==']' || b=='#')
			return '>';
		else
			return '<';
	}
	if(a=='*' || a=='/')
	{
		if(b=='(' || b=='[')
			return '<';
		else
			return '>';
	}
	if(a=='(')
	{
		if(b==')')
			return '=';
		else
			return '<';
	}
	if(a=='[')
	{
		if(b==']')
			return '=';
		else
			return '<';
	}
	if(a=='#')
	{
		if(b=='#')
			return '=';
		else
			return '<';
	}
	return '>';
}
ElemType evaluateExpression()
{
	SeqStack optr,opnd;//设optr为运算符操作栈，opnd为运算数栈
	initStack(&optr);
	push(&optr,'#');
	initStack(&opnd);

	char c=getchar();
	char e,a,b;
	while(c!='#' || _getTop(&optr)!='#')
	{
		if(!in(c))//不是操作运算符就进栈
		{
			if(c>='0' && c<='9')
				push(&opnd,c);
			c=getchar();
		}
		else
			switch(precede(_getTop(&optr),c))
			{
				//栈顶元素优先级低
			case '<':
				push(&optr,c);
				c=getchar();
				break;
			case '='://脱去括号并接收下一字符
				_pop(&optr,&e);
				c=getchar();
				break;
			case '>'://退栈并将运算结果入栈
				_pop(&optr,&e);
				_pop(&opnd,&b);
				_pop(&opnd,&a);
				push(&opnd,operate(a,e,b));
				break;
			}
	}
	return _getTop(&opnd);
	/*
	char x,a,b,c[100];
	gets(c);
	int i=0;
	while(c[i]!='#' || _getTop(&optr)!='#')
	{
		if(!in(c[i]))//不是操作运算符就进栈
		{
			if(i>0 && (c[i-1]>'0'&& c[i-1]<='9')){
                 _pop(&opnd,&x);
				 printf("x->%d \n",x);
				 printf("exp->%d\n",10*x + c[i] - '0');
                 push(&opnd, 10*x + c[i] - '0');
             }
             else push(&opnd, c[i] - '0');
			 printf("exp2->%d\n",c[i] - '0');
             i++;
		}
		else
			switch(precede(_getTop(&optr),c[i]))
			{
				//栈顶元素优先级低
			case '<':
				push(&optr,c[i]);
				i++;
				break;
			case '='://脱去括号并接收下一字符
				_pop(&optr,&x);
				i++;
				break;
			case '>'://退栈并将运算结果入栈
				_pop(&optr,&x);
				_pop(&opnd,&b);
				_pop(&opnd,&a);
				push(&opnd,operate(a,x,b));
				break;
			}
	}
	return _getTop(&opnd);
	*/
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
void _pop(SeqStack *s,ElemType *e)
{
	if(isEmpty(s))
	{
		printf("当前栈中无数据，无法弹栈\n");
		return ;
	} 
	*e=s->base[s->top-1];
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
	printf("%c \n",*v);
	return true;
}
//返回栈顶元素
ElemType _getTop(SeqStack *s)
{
	if(isEmpty(s))
	{
		printf("当前栈中无数据，无法出栈\n");
		return false;
	}
	return s->base[s->top-1];
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