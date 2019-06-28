#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define SEQLIST_INIT_SIZE 8//表初始空间
#define INC_SIZE 4//表空间的增量
typedef int ElemType;
//结构体
typedef struct SeqList
{
	ElemType *base; //表的空间
	int capacity;   //表的容量
	int size;       //表的大小
}SeqList;

//以下为函数的声明
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

//表的拷贝
void main()
{
	SeqList mylist,youlist,list;
	//初始化两个表
	InitList(&mylist);
	InitList(&youlist);
	//尾插数据
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


//合并表
void emerge(SeqList *mylist,SeqList *youlist,SeqList *list)
{	//list表的空间为没有list和youlist空间之和
	list->capacity=mylist->size+youlist->size;
	list->base=(ElemType*)malloc(sizeof(ElemType)*list->capacity);
	assert(list->base != NULL);
	int m=0;
	int y=0;
	int l=0;
	//对两表进行归并
	while(m<mylist->size && y<youlist->size)
	{
		if(mylist->base[m]<youlist->base[y])
			list->base[l++]=mylist->base[m++];
		else
			list->base[l++]=youlist->base[y++];
	}
	//插入mylist表中剩余元素
	while(m<mylist->size)
	{
		list->base[l++]=mylist->base[m++];
	}
	//插入youlist表中剩余元素
	while(y<youlist->size)
	{
		list->base[l++]=youlist->base[y++];
	}
	//list表大小为两表大小之和
	list->size=mylist->size+youlist->size;
}
//初始化顺序表
void InitList(SeqList *list)
{
	list->base=(ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
	assert(list->base != NULL);
	list->capacity=SEQLIST_INIT_SIZE;
	list->size=0;
}
//如果表空间内存不够，再分配
bool Inc(SeqList *list)
{
	ElemType *newBase=(ElemType*)realloc(list->base,sizeof(ElemType)*(list->capacity+INC_SIZE));
	if(newBase == NULL)
	{
		printf("内存空间不足，无法增配空间\n");
		return false;
	}
	list->base=newBase;
	list->capacity+=INC_SIZE;
	return true;
}
//1:尾部插入顺序表
void push_back(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("表空间已满，%d不能尾部插入\n",x);
		return;
	}
	list->base[list->size]=x;
	list->size++;

}
//3:显示顺序表
void show_list(SeqList *list)
{	
	if(list->size == 0)
	{
		printf("此表中目前没有数据可供显示\n");
		return;
	}
	for(int i=0;i<list->size;i++)
	{
		printf("%d ",list->base[i]);
	}
	printf("\n");
}



//主函数
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
		printf("请输入你的选择->");
		scanf("%d",&select);
		if(select==0)
			break;
		switch(select)
		{
			case 1:
				printf("请输入你想要插入的数据(-1结束):\n");
				while(scanf("%d",&item),item!=-1)
				{
					push_back(&mylist,item);
				}
				break;
			case 2:
				printf("请输入你想要插入的数据(-1结束):\n");
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
				printf("请输入你想插入的数据：\n");
				scanf("%d",&item);
				printf("请输入你想插入的位置：\n");
				scanf("%d",&pos);
				insert_pos(&mylist,item,pos);
				break;
			case 7:
				printf("请输入你想查找的数据：\n");
				scanf("%d",&item);
				pos=find(&mylist,item);
				if(pos != -1)
					printf("你查找的数据%d在%d下标的位置\n",item,pos);
				else
					printf("你查找的数据%d在当前表中不存在\n",item);
				break;
			case 8:
				leng=length(&mylist);
				printf("表的长度为：%d\n",leng);
				break;
			case 9:
				printf("请输入你想删除的位置: ");
				scanf("%d",&pos);
				delete_pos(&mylist,pos);
				break;
			case 10:
				printf("请输入你想删除的数据：");
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
				printf("输入错误，请重新输入！\n");
				break;
		}
	}
	destory(&mylist);
}
//初始化顺序表
void InitList(SeqList *list)
{
	list->base=(ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
	assert(list->base != NULL);
	list->capacity=SEQLIST_INIT_SIZE;
	list->size=0;
}
//如果表空间内存不够，再分配
bool Inc(SeqList *list)
{
	ElemType *newBase=(ElemType*)realloc(list->base,sizeof(ElemType)*(list->capacity+INC_SIZE));
	if(newBase == NULL)
	{
		printf("内存空间不足，无法增配空间\n");
		return false;
	}
	list->base=newBase;
	list->capacity+=INC_SIZE;
	return true;
}
//1:尾部插入顺序表
void push_back(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("表空间已满，%d不能尾部插入\n",x);
		return;
	}
	list->base[list->size]=x;
	list->size++;

}
//3:显示顺序表
void show_list(SeqList *list)
{	
	if(list->size == 0)
	{
		printf("此表中目前没有数据可供显示\n");
		return;
	}
	for(int i=0;i<list->size;i++)
	{
		printf("%d ",list->base[i]);
	}
	printf("\n");
}
//2:头部插入元素
void push_front(SeqList *list,ElemType x)
{
	if(list->size >= list->capacity && !Inc(list))
	{
		printf("表空间已满，%d不能尾部插入",x);
		return;
	}
	for(int i=list->size;i>0;i--)
	{
		list->base[i]=list->base[i-1];
	}
	list->base[0]=x;
	list->size++;
}
//尾部删除元素
void pop_back(SeqList *list)
{
	if(list->size == 0)
	{
		printf("对不起，此表已空，无法删除元素\n");
		return;
	}
	list->size--;
}
//头部删除数据删
void pop_front(SeqList *list)
{
	if(list->size == 0)
	{
		printf("对不起，此表已空，无法删除元素\n");
		return;
	}
	for(int i=0;i<list->size-1;i++)
	{
		list->base[i]=list->base[i+1];
	}
	list->size--;
}
//按位置插入数据
void insert_pos(SeqList *list,ElemType x,int p)
{

	if(p<0 || p>list->size)
	{
		printf("插入位置非法,不能插入数据");
		return;
	}
	if(list->size>list->capacity && !Inc(list))
	{
		printf("此表已满,%d不能在%d位置插入",x,p);
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
//查找数据
int find(SeqList *list,ElemType x)
{	
	for(int i=0;i<list->size;i++)
	{
		if(list->base[i]==x)
			return i;
	}
	return -1;
}
//求表长
int length(SeqList *list)
{
	return list->size;
}
//按位置删除数据
void delete_pos(SeqList *list,int p)
{
	if(p<0 || p>=list->size)
	{
		printf("对不起，删除%d的位置非法\n",p);
		return;
	}
	for(int i=p;i<list->size-1;i++)
	{
		list->base[i]=list->base[i+1];
	}
	list->size--;
}
//按值删除数据
void delete_val(SeqList *list,int x)
{
	int pos=find(list,x);
	if(pos == -1)
	{
		printf("你要删除的数据%d不存在\n",x);
		return;
	}
	delete_pos(list,pos);
}
//表排序，这里使用冒泡排序
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
//表的翻转
void reverse(SeqList *list)
{	
	if(list->size==0 || list->size==1)
	{
		printf("表中没有足够数据来翻转\n");
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
//表的清空
void clear(SeqList *list)
{
	list->size=0;
	printf("表已经清空\n");
}
//表的摧毁
void destory(SeqList *list)
{
	free(list->base);
	list->base=NULL;
	list->capacity=0;
	list->size=0;
	printf("表已经摧毁\n");
}
*/