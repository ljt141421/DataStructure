#include"Stack.h"

void InitStack(Stack *s)
{
	*s = NULL;
}

void Push(Stack *s, ElemType x)
{
	StackNode *t = (StackNode*)malloc(sizeof(StackNode));
	assert(t != NULL);
	t->data = x;

	if(*s == NULL)
	{
		*s = t;
		t->next = NULL;
	}
	else
	{
		t->next = *s;
		*s = t;
	}
}

void Show(Stack *s)
{
	StackNode *p = *s;
	while(p != NULL)
	{
		printf("%d\n",p->data);
		p = p->next;
	}
	printf("\n");
}

void Pop(Stack *s)
{
	StackNode *p = *s;
	*s = p->next;
	free(p);
	p = NULL;
}

bool IsEmpty(Stack *s)
{
	return *s == NULL;
}

ElemType GetTop(Stack *s)
{
	StackNode *p = *s;
	assert(p != NULL);
	return p->data;
}