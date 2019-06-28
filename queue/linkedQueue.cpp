#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct QueueNode
{
	ElemType data;
	struct QueueNode *next;
}QueueNode;

typedef struct LinkQueue
{
	QueueNode *front;//指向队头
	QueueNode *tail;//指向对尾
}LinkQueue;

//函数声明
void initQueue(LinkQueue *q);
void enqueue(LinkQueue *q,ElemType x);
void show(LinkQueue *q);
void dequeue(LinkQueue *q);
void getHead(LinkQueue *q,ElemType *v);
int getLength(LinkQueue *q);
void clear(LinkQueue *q);
void destory(LinkQueue *q);

void main()
{
	LinkQueue q;
	initQueue(&q);
	int v;
	for(int i=1;i<=8;++i)
	{
		enqueue(&q,i);
	}
	show(&q);
	printf("当前队列长度:%d \n",getLength(&q));
	getHead(&q,&v);
	printf("队头数据%d 出队\n",v);
	dequeue(&q);
	show(&q);
	//clear(&q);
	destory(&q);
}
//带有头结点的链队列
void initQueue(LinkQueue *q)
{
	QueueNode *s=(QueueNode *)malloc(sizeof(QueueNode));
	assert(s != NULL);
	q->front=q->tail=s;
	q->tail->next=NULL;
}
//入队，使用尾插的方式,即从对尾进行入列
void enqueue(LinkQueue *q,ElemType x)
{
	QueueNode *s=(QueueNode *)malloc(sizeof(QueueNode));
	assert(s != NULL);
	s->data=x;
	s->next=NULL;

	q->tail->next=s;
	q->tail=s;
}
void show(LinkQueue *q)
{
	QueueNode *p=q->front->next;
	printf("队头> ");
	while(p != NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("<队尾\n");
}
//出队,从队头开始出队
void dequeue(LinkQueue *q)
{
	if(q->front == q->tail)
	{
		printf("当前队列为空，无法出队\n");
		return;
	}
	QueueNode *p=q->front->next;
	q->front->next=p->next;
	free(p);
	//如果当前队列只有一个节点，要修改尾指针指向
	if(p==q->tail)
	{
		q->tail=q->front;
	}
}
//获取队头数据
void getHead(LinkQueue *q,ElemType *v)
{
	if(q->front == q->tail)
	{
		printf("当前队列为空，无法获得队头元素\n");
		return;
	}
	QueueNode *p=q->front->next;
	*v=p->data;
}
int getLength(LinkQueue *q)
{
	int length=0;
	QueueNode *p=q->front->next;
	while(p != NULL)
	{
		length++;
		p=p->next;
	}
	return length;
}
//清除队列
void clear(LinkQueue *q)
{
	if(q->front==q->tail)
	{
		printf("当前队列已空，无需清空\n");
		return;
	}
	QueueNode *p=q->front->next;
	while(p != NULL)
	{
		q->front->next=p->next;
		free(p);
		p=q->front->next;
	}
	//修改尾指针指向
	q->tail=q->front;
}
//销毁队列
void destory(LinkQueue *q)
{
	clear(q);
	free(q->front);
	q->front=q->tail=NULL;
	printf("当前队列已摧毁\n");
}