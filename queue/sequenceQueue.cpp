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
//��������
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
	printf("��ǰ���г���Ϊ:%d \n",getLength(&q));
	getHead(&q,&v);
	printf("��ǰ��ͷ����Ϊ:%d \n",v);
	dequeue(&q);
	dequeue(&q);
	printf("��ǰ���г���Ϊ:%d \n",getLength(&q));
	enqueue(&q,9);//��ʱ��Ȼ����û����������Ȼ�޷���ӣ�Ϊ�˽���������⣬��Ҫʹ��ѭ������
	show(&q);
	clear(&q);
	destory(&q);
}
//��ʼ��˳�����
void initQueue(Queue *q)
{
	q->base=(ElemType *)malloc(sizeof(ElemType)*MAX_QUEUE_SIZE);
	assert(q->base != NULL);
	q->front=q->rear=0;
}
//���
void enqueue(Queue *q,ElemType x)
{
	//��������������޷����
	if(q->rear >= MAX_QUEUE_SIZE)
	{
		printf("��ǰ�����������޷����\n");
		return;
	}
	q->base[q->rear++]=x;
}
//��ʾ����Ԫ��
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
		printf("��ǰ�����ѿգ��޷�����\n");
		return;
	}
	q->front++;

}
//���ͷ��Ԫ��
void getHead(Queue *q,ElemType *v)
{
	if(q->front==q->rear)
	{
		printf("��ǰ�����ѿգ��޷����ͷ��Ԫ��\n");
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
	printf("��ǰ�����������ѱ����\n");
}
void destory(Queue *q)
{
	free(q->base);
	q->base=NULL;
	printf("��ǰ�����ѱ��ݻ�\n");
}

