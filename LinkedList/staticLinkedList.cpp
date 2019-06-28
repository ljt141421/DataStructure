#include <stdio.h>

#define MAX_SIZE 20
#define ElemType char

typedef struct ListNode
{
	ElemType data;
	int      cur;
}ListNode;

typedef ListNode StaticList[MAX_SIZE];

//�����Ǻ�������
void initStaticList(StaticList &space);
int malloc_list(StaticList &space);
void insertList(StaticList &space,ElemType e);
void deleteList(StaticList &space);
void showList(StaticList &space);
void freeList(StaticList &space,int k);

void main()
{
	StaticList SL;
	initStaticList(SL);//�����ʼ��
	for(int i=0;i<5;++i)
	{
		insertList(SL,'A'+i);//��������
	}
	showList(SL);//��ʾ����
	deleteList(SL);//ɾ������
	showList(SL);
}

//����������ʵ��
//��ʼ����̬����
void initStaticList(StaticList &space)
{
	for(int i=1;i<MAX_SIZE-1;++i)
	{
		//����̬����ĵ�ǰλ�õ��α�+1
		space[i].cur=i+1;
	}
	space[MAX_SIZE-1].cur=0;//���һλ����Ϊ0
	space[0].cur=-1;//��һλ����Ϊ-1������ǰ����Ϊ��
}
//�Ӿ�̬����������ռ�
int malloc_list(StaticList &space)
{	
	int i=space[1].cur;
	if(space[1].cur != 0)
	{
		space[1].cur=space[i].cur;//��1λ�õ��α�����Ϊȡ�߿ռ���α�
	}
	return i;
}
//��̬�����в�������
void insertList(StaticList &space,ElemType e)
{
	int i=malloc_list(space);
	if(i==0)
	{
		printf("����ռ��������޷�����\n");
		return;
	}
	space[i].data=e;
	if(space[0].cur == -1)//��ǰ����Ϊ��
	{
		space[i].cur=-1;//Ϊ�������ݿռ��α긳ֵ-1��˵�����˿ռ����
	}
	else
	{//����Ϊ��
		space[i].cur=space[0].cur;//����ǰ�ռ�����0���α�
	}
	space[0].cur=i;//��0���α�ָ��ǰ�ռ�
}
//��ʾ����
void showList(StaticList &space)
{
	int i=space[0].cur;
	while(i != -1)
	{
		printf("%c-->",space[i].data);
		i=space[i].cur;
	}
	printf("Null...\n");
}
//ɾ������
void deleteList(StaticList &space)
{
	int i=space[0].cur;
	space[0].cur=space[i].cur;
//	space[i].cur=space[1].cur;
//	space[1].cur=i;
	freeList(space,i);

}
//�ͷſռ�
void freeList(StaticList &space,int k)
{
	space[k].cur=space[1].cur;//����ǰλ�õ��α�����Ϊ1���α�
	space[1].cur=k;//��1���α�����Ϊ��ǰλ��
}

