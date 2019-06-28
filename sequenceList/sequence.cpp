#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define SEQLIST_INIT_SIZE 8//���ʼ�ռ�
#define INC_SIZE 4//��ռ������
typedef int ElemType;
//�ṹ��
typedef struct SeqList
{
	ElemType *base; //��Ŀռ�
	int capacity;   //�������
	int size;       //��Ĵ�С
}SeqList;

//����Ϊ����������
void InitList(SeqList *list);
bool Inc(SeqList *list);
void push_back(SeqList *list,ElemType x);
void show_list(SeqList *list);
void push_front(SeqList *list,ElemType x);
void pop_back(SeqList *list);
void pop_front(SeqList *list);
void insert_pos(SeqList *list,ElemType x,int p);
int find(SeqList *list,ElemType x);
int length(SeqList *list);
void delete_pos(SeqList *list,int p);
void delete_val(SeqList *list,int x);
void sort(SeqList *list);
void reverse(SeqList *list);
void clear(SeqList *list);
void destory(SeqList *list);
void emerge(SeqList *mylist,SeqList *youlist,SeqList *list);

//��Ŀ���
void main()
{
	SeqList mylist,youlist,list;
	//��ʼ��������
	InitList(&mylist);
	InitList(&youlist);
	//β������
	push_back(&mylist,1);
	push_back(&mylist,3);
	push_back(&mylist,5);
	push_back(&mylist,7);
	push_back(&mylist,9);

	push_back(&youlist,2);
	push_back(&youlist,4);
	push_back(&youlist,6);
	push_back(&youlist,8);
	push_back(&youlist,10);
	emerge(&mylist,&youlist,&list);
	show_list(&list);
}


//�ϲ���
void emerge(SeqList *mylist,SeqList *youlist,SeqList *list)
{	//list��Ŀռ�Ϊû��list��youlist�ռ�֮��
	list->capacity=mylist->size+youlist->size;
	list->base=(ElemType*)malloc(sizeof(ElemType)*list->capacity);
	assert(list->base != NULL);
	int m=0;
	int y=0;
	int l=0;
	//��������й鲢
	while(m<mylist->size && y<youlist->size)
	{
		if(mylist->base[m]<youlist->base[y])
			list->base[l++]=mylist->base[m++];
		else
			list->base[l++]=youlist->base[y++];
	}
	//����mylist����ʣ��Ԫ��
	while(m<mylist->size)
	{
		list->base[l++]=mylist->base[m++];
	}
	//����youlist����ʣ��Ԫ��
	while(y<youlist->size)
	{
		list->base[l++]=youlist->base[y++];
	}
	//list���СΪ�����С֮��
	list->size=mylist->size+youlist->size;
}
//��ʼ��˳���
void InitList(SeqList *list)
{
	list->base=(ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
	assert(list->base != NULL);
	list->capacity=SEQLIST_INIT_SIZE;
	list->size=0;
}
//�����ռ��ڴ治�����ٷ���
bool Inc(SeqList *list)
{
	ElemType *newBase=(ElemType*)realloc(list->base,sizeof(ElemType)*(list->capacity+INC_SIZE));
	if(newBase == NULL)
	{
		printf("�ڴ�ռ䲻�㣬�޷�����ռ�\n");
		return false;
	}
	list->base=newBase;
	list->capacity+=INC_SIZE;
	return true;
}
//1:β������˳���
void push_back(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("��ռ�������%d����β������\n",x);
		return;
	}
	list->base[list->size]=x;
	list->size++;

}
//3:��ʾ˳���
void show_list(SeqList *list)
{	
	if(list->size == 0)
	{
		printf("�˱���Ŀǰû�����ݿɹ���ʾ\n");
		return;
	}
	for(int i=0;i<list->size;i++)
	{
		printf("%d ",list->base[i]);
	}
	printf("\n");
}



//������
/*
void main()
{
	SeqList mylist;
	InitList(&mylist);
	int item;
	int pos;
	int leng;
	int select=1;
	while(select)
	{
		printf("**********************************\n");
		printf("* [1]push_back    [2]push_front  *\n");
		printf("* [3]show_list    [4]pop_back    *\n");
		printf("* [5]pop_front    [6]insert_pos  *\n");
		printf("* [7]find         [8]length      *\n");
		printf("* [9]delete_pos   [10]delete_val *\n");
		printf("* [11]sort        [12]reverse    *\n");
		printf("* [13]clear       [14*]destory   *\n");
		printf("* [0]quit_system                 *\n");
		printf("**********************************\n");
		printf("���������ѡ��->");
		scanf("%d",&select);
		if(select==0)
			break;
		switch(select)
		{
			case 1:
				printf("����������Ҫ���������(-1����):\n");
				while(scanf("%d",&item),item!=-1)
				{
					push_back(&mylist,item);
				}
				break;
			case 2:
				printf("����������Ҫ���������(-1����):\n");
				while(scanf("%d",&item),item!=-1)
				{
					push_front(&mylist,item);
				}
				break;
			case 3:
				show_list(&mylist);
				break;
			case 4:
				pop_back(&mylist);
				break;
			case 5:
				pop_front(&mylist);
				break;
			case 6:
				printf("�����������������ݣ�\n");
				scanf("%d",&item);
				printf("��������������λ�ã�\n");
				scanf("%d",&pos);
				insert_pos(&mylist,item,pos);
				break;
			case 7:
				printf("������������ҵ����ݣ�\n");
				scanf("%d",&item);
				pos=find(&mylist,item);
				if(pos != -1)
					printf("����ҵ�����%d��%d�±��λ��\n",item,pos);
				else
					printf("����ҵ�����%d�ڵ�ǰ���в�����\n",item);
				break;
			case 8:
				leng=length(&mylist);
				printf("��ĳ���Ϊ��%d\n",leng);
				break;
			case 9:
				printf("����������ɾ����λ��: ");
				scanf("%d",&pos);
				delete_pos(&mylist,pos);
				break;
			case 10:
				printf("����������ɾ�������ݣ�");
				scanf("%d",&item);
				delete_val(&mylist,item);
				break;
			case 11:
				sort(&mylist);
				break;
			case 12:
				reverse(&mylist);
				break;
			case 13:
				clear(&mylist);
				break;
			default:
				printf("����������������룡\n");
				break;
		}
	}
	destory(&mylist);
}
//��ʼ��˳���
void InitList(SeqList *list)
{
	list->base=(ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
	assert(list->base != NULL);
	list->capacity=SEQLIST_INIT_SIZE;
	list->size=0;
}
//�����ռ��ڴ治�����ٷ���
bool Inc(SeqList *list)
{
	ElemType *newBase=(ElemType*)realloc(list->base,sizeof(ElemType)*(list->capacity+INC_SIZE));
	if(newBase == NULL)
	{
		printf("�ڴ�ռ䲻�㣬�޷�����ռ�\n");
		return false;
	}
	list->base=newBase;
	list->capacity+=INC_SIZE;
	return true;
}
//1:β������˳���
void push_back(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("��ռ�������%d����β������\n",x);
		return;
	}
	list->base[list->size]=x;
	list->size++;

}
//3:��ʾ˳���
void show_list(SeqList *list)
{	
	if(list->size == 0)
	{
		printf("�˱���Ŀǰû�����ݿɹ���ʾ\n");
		return;
	}
	for(int i=0;i<list->size;i++)
	{
		printf("%d ",list->base[i]);
	}
	printf("\n");
}
//2:ͷ������Ԫ��
void push_front(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("��ռ�������%d����β������",x);
		return;
	}
	for(int i=list->size;i>0;i--)
	{
		list->base[i]=list->base[i-1];
	}
	list->base[0]=x;
	list->size++;
}
//β��ɾ��Ԫ��
void pop_back(SeqList *list)
{
	if(list->size == 0)
	{
		printf("�Բ��𣬴˱��ѿգ��޷�ɾ��Ԫ��\n");
		return;
	}
	list->size--;
}
//ͷ��ɾ������ɾ
void pop_front(SeqList *list)
{
	if(list->size == 0)
	{
		printf("�Բ��𣬴˱��ѿգ��޷�ɾ��Ԫ��\n");
		return;
	}
	for(int i=0;i<list->size-1;i++)
	{
		list->base[i]=list->base[i+1];
	}
	list->size--;
}
//��λ�ò�������
void insert_pos(SeqList *list,ElemType x,int p)
{

	if(p<0 || p>list->size)
	{
		printf("����λ�÷Ƿ�,���ܲ�������");
		return;
	}
	if(list->size>list->capacity && !Inc(list))
	{
		printf("�˱�����,%d������%dλ�ò���",x,p);
		return;
	}
	
//	if(p==0)
//		push_front(list,p);
//	else if(p==list->size)
//		push_back(list,p);
//	else
//		{
	
		for(int i=list->size;i>p;i--)
		{
			list->base[i]=list->base[i-1];
		}
		list->base[p]=x;
		list->size++;
}
//��������
int find(SeqList *list,ElemType x)
{	
	for(int i=0;i<list->size;i++)
	{
		if(list->base[i]==x)
			return i;
	}
	return -1;
}
//���
int length(SeqList *list)
{
	return list->size;
}
//��λ��ɾ������
void delete_pos(SeqList *list,int p)
{
	if(p<0 || p>=list->size)
	{
		printf("�Բ���ɾ��%d��λ�÷Ƿ�\n",p);
		return;
	}
	for(int i=p;i<list->size-1;i++)
	{
		list->base[i]=list->base[i+1];
	}
	list->size--;
}
//��ֵɾ������
void delete_val(SeqList *list,int x)
{
	int pos=find(list,x);
	if(pos == -1)
	{
		printf("��Ҫɾ��������%d������\n",x);
		return;
	}
	delete_pos(list,pos);
}
//����������ʹ��ð������
void sort(SeqList *list)
{
	for(int i=0;i<list->size-1;i++)
	{
		for(int j=0;j<list->size-i-1;j++)
		{
			if(list->base[j]>list->base[j+1])
			{
				int temp=list->base[j];
				list->base[j]=list->base[j+1];
				list->base[j+1]=temp;
			}
		}
	}
}
//��ķ�ת
void reverse(SeqList *list)
{	
	if(list->size==0 || list->size==1)
	{
		printf("����û���㹻��������ת\n");
		return;
	}
	int low=0;
	int high=list->size-1;
	ElemType temp;
	while(low<high)
	{
		temp=list->base[high];
		list->base[high]=list->base[low];
		list->base[low]=temp;
		low++;
		high--;
	}
}
//������
void clear(SeqList *list)
{
	list->size=0;
	printf("���Ѿ����\n");
}
//��Ĵݻ�
void destory(SeqList *list)
{
	free(list->base);
	list->base=NULL;
	list->capacity=0;
	list->size=0;
	printf("���Ѿ��ݻ�\n");
}
*/