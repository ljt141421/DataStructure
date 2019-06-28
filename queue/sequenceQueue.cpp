#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

#define MAX_QUEUE_SIZE 8

typedef struct Queue
{
	ElemType *base;
	int       front;
	int       rear;
}Queue;
//函数声明
void initQueue(Queue *q);
void enqueue(Queue *q,ElemType x);
void show(Queue *q);
void dequeue(Queue *q);
void getHead(Queue *q,ElemType *v);
int getLength(Queue *q);
void clear(Queue *q);
void destory(Queue *q);

void main()
{
	Queue q;
	initQueue(&q);
	int v;
	for(int i=1;i<=8;i++)
	{
		enqueue(&q,i);
	}
	show(&q);
	printf("当前队列长度为:%d \n",getLength(&q));
	getHead(&q,&v);
	printf("当前队头数据为:%d \n",v);
	dequeue(&q);
	dequeue(&q);
	printf("当前队列长度为:%d \n",getLength(&q));
	enqueue(&q,9);//此时虽然队列没有满，但仍然无法入队，为了解决这种问题，就要使用循环队列
	show(&q);
	clear(&q);
	destory(&q);
}
//初始化顺序队列
void initQueue(Queue *q)
{
	q->base=(ElemType *)malloc(sizeof(ElemType)*MAX_QUEUE_SIZE);
	assert(q->base != NULL);
	q->front=q->rear=0;
}
//入队
void enqueue(Queue *q,ElemType x)
{
	//队列满的情况下无法入队
	if(q->rear >= MAX_QUEUE_SIZE)
	{
		printf("当前队列已满，无法入队\n");
		return;
	}
	q->base[q->rear++]=x;
}
//显示队列元素
void show(Queue *q)
{
	for(int i=q->front;i<q->rear;++i)
	{
		printf("%d ",q->base[i]);
	}
	printf("\n");

}
void dequeue(Queue *q)
{
	if(q->front==q->rear)
	{
		printf("当前队列已空，无法出队\n");
		return;
	}
	q->front++;

}
//获得头部元素
void getHead(Queue *q,ElemType *v)
{
	if(q->front==q->rear)
	{
		printf("当前队列已空，无法获得头部元素\n");
		return;
	}
	*v=q->base[q->front];
	
}
int getLength(Queue *q)
{
	return (q->rear - q->front);
}
void clear(Queue *q)
{
	q->front=q->rear=0;
	printf("当前队列中数据已被清除\n");
}
void destory(Queue *q)
{
	free(q->base);
	q->base=NULL;
	printf("当前队列已被摧毁\n");
}

