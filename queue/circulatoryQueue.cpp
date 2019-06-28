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
	for(int i=1;i<8;i++)
	{
		enqueue(&q,i);
	}
	show(&q);
	printf("��ǰ���г���Ϊ:%d \n",getLength(&q));
	getHead(&q,&v);
	printf("��ǰ��ͷ����Ϊ:%d \n",v);
	dequeue(&q);
	
	printf("��ǰ���г���Ϊ:%d \n",getLength(&q));
	enqueue(&q,8);
	dequeue(&q);
	enqueue(&q,9);
	dequeue(&q);
	enqueue(&q,10);
	show(&q);
	printf("��ǰ���г���Ϊ:%d \n",getLength(&q));
	
	//clear(&q);
	//destory(&q);
}
//��ʼ��ѭ������
void initQueue(Queue *q)
{
	q->base=(ElemType *)malloc(sizeof(ElemType)*MAX_QUEUE_SIZE);
	assert(q->base != NULL);
	q->front=q->rear=0;
}
//���
void enqueue(Queue *q,ElemType x)
{
	//��ָ���β��ָ�����+1��ȡģ��ȡģ��Ľ�������ָ���ͷ��ָ����ͬ
	//˵����ʱ��ǰѭ����������
	if(((q->rear + 1)%MAX_QUEUE_SIZE == q->front))
	{
		printf("��ǰ�����������޷����\n");
		return;
	}
	q->base[q->rear]=x;
	q->rear=(q->rear + 1)%MAX_QUEUE_SIZE;
}
//��ʾ����Ԫ��
void show(Queue *q)
{
	for(int i=q->front;i != q->rear;)
	{
		printf("%d ",q->base[i]);
		i=(i+1)%MAX_QUEUE_SIZE;
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
	q->front=(q->front + 1)%MAX_QUEUE_SIZE;

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
	return (q->rear - q->front + MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
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

