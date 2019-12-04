#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
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

//���ʽ��ֵ
ElemType _getTop(SeqStack *s);
void _pop(SeqStack *s,ElemType *e);
bool in(ElemType c);//�ж��Ƿ�Ϊ�����ַ�
char operate(ElemType a,ElemType e,ElemType b);
ElemType precede(ElemType a,ElemType b);//�жϲ��������ȼ�
ElemType evaluateExpression();//���ʽ��Ҫ�߼�

void main()
{
	printf("������һ�α��ʽ(����������0��9֮��)��\n");
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
	//�ж��߼����鱾53ҳ
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
	SeqStack optr,opnd;//��optrΪ���������ջ��opndΪ������ջ
	initStack(&optr);
	push(&optr,'#');
	initStack(&opnd);

	char c=getchar();
	char e,a,b;
	while(c!='#' || _getTop(&optr)!='#')
	{
		if(!in(c))//���ǲ���������ͽ�ջ
		{
			if(c>='0' && c<='9')
				push(&opnd,c);
			c=getchar();
		}
		else
			switch(precede(_getTop(&optr),c))
			{
				//ջ��Ԫ�����ȼ���
			case '<':
				push(&optr,c);
				c=getchar();
				break;
			case '='://��ȥ���Ų�������һ�ַ�
				_pop(&optr,&e);
				c=getchar();
				break;
			case '>'://��ջ������������ջ
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
		if(!in(c[i]))//���ǲ���������ͽ�ջ
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
				//ջ��Ԫ�����ȼ���
			case '<':
				push(&optr,c[i]);
				i++;
				break;
			case '='://��ȥ���Ų�������һ�ַ�
				_pop(&optr,&x);
				i++;
				break;
			case '>'://��ջ������������ջ
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
void _pop(SeqStack *s,ElemType *e)
{
	if(isEmpty(s))
	{
		printf("��ǰջ�������ݣ��޷���ջ\n");
		return ;
	} 
	*e=s->base[s->top-1];
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
	printf("%c \n",*v);
	return true;
}
//����ջ��Ԫ��
ElemType _getTop(SeqStack *s)
{
	if(isEmpty(s))
	{
		printf("��ǰջ�������ݣ��޷���ջ\n");
		return false;
	}
	return s->base[s->top-1];
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