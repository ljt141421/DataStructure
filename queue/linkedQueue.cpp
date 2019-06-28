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
	QueueNode *front;//ָ���ͷ
	QueueNode *tail;//ָ���β
}LinkQueue;

//��������
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
	printf("��ǰ���г���:%d \n",getLength(&q));
	getHead(&q,&v);
	printf("��ͷ����%d ����\n",v);
	dequeue(&q);
	show(&q);
	//clear(&q);
	destory(&q);
}
//����ͷ����������
void initQueue(LinkQueue *q)
{
	QueueNode *s=(QueueNode *)malloc(sizeof(QueueNode));
	assert(s != NULL);
	q->front=q->tail=s;
	q->tail->next=NULL;
}
//��ӣ�ʹ��β��ķ�ʽ,���Ӷ�β��������
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
	printf("��ͷ> ");
	while(p != NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("<��β\n");
}
//����,�Ӷ�ͷ��ʼ����
void dequeue(LinkQueue *q)
{
	if(q->front == q->tail)
	{
		printf("��ǰ����Ϊ�գ��޷�����\n");
		return;
	}
	QueueNode *p=q->front->next;
	q->front->next=p->next;
	free(p);
	//�����ǰ����ֻ��һ���ڵ㣬Ҫ�޸�βָ��ָ��
	if(p==q->tail)
	{
		q->tail=q->front;
	}
}
//��ȡ��ͷ����
void getHead(LinkQueue *q,ElemType *v)
{
	if(q->front == q->tail)
	{
		printf("��ǰ����Ϊ�գ��޷���ö�ͷԪ��\n");
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
//�������
void clear(LinkQueue *q)
{
	if(q->front==q->tail)
	{
		printf("��ǰ�����ѿգ��������\n");
		return;
	}
	QueueNode *p=q->front->next;
	while(p != NULL)
	{
		q->front->next=p->next;
		free(p);
		p=q->front->next;
	}
	//�޸�βָ��ָ��
	q->tail=q->front;
}
//���ٶ���
void destory(LinkQueue *q)
{
	clear(q);
	free(q->front);
	q->front=q->tail=NULL;
	printf("��ǰ�����Ѵݻ�\n");
}