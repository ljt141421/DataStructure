#include <stdio.h>

#define MAX_SIZE 20
#define ElemType char

typedef struct ListNode
{
	ElemType data;
	int      cur;
}ListNode;

typedef ListNode StaticList[MAX_SIZE];

//以下是函数声明
void initStaticList(StaticList &space);
int malloc_list(StaticList &space);
void insertList(StaticList &space,ElemType e);
void deleteList(StaticList &space);
void showList(StaticList &space);
void freeList(StaticList &space,int k);

void main()
{
	StaticList SL;
	initStaticList(SL);//链表初始化
	for(int i=0;i<5;++i)
	{
		insertList(SL,'A'+i);//插入数据
	}
	showList(SL);//显示链表
	deleteList(SL);//删除链表
	showList(SL);
}

//以下是链表实现
//初始化静态链表
void initStaticList(StaticList &space)
{
	for(int i=1;i<MAX_SIZE-1;++i)
	{
		//将静态链表的当前位置的游标+1
		space[i].cur=i+1;
	}
	space[MAX_SIZE-1].cur=0;//最后一位设置为0
	space[0].cur=-1;//第一位设置为-1，代表当前链表为空
}
//从静态链表中申请空间
int malloc_list(StaticList &space)
{	
	int i=space[1].cur;
	if(space[1].cur != 0)
	{
		space[1].cur=space[i].cur;//将1位置的游标设置为取走空间的游标
	}
	return i;
}
//向静态链表中插入数据
void insertList(StaticList &space,ElemType e)
{
	int i=malloc_list(space);
	if(i==0)
	{
		printf("链表空间已满，无法插入\n");
		return;
	}
	space[i].data=e;
	if(space[0].cur == -1)//当前链表为空
	{
		space[i].cur=-1;//为插入数据空间游标赋值-1，说明到此空间结束
	}
	else
	{//链表不为空
		space[i].cur=space[0].cur;//将当前空间连向0处游标
	}
	space[0].cur=i;//将0处游标指向当前空间
}
//显示链表
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
//删除链表
void deleteList(StaticList &space)
{
	int i=space[0].cur;
	space[0].cur=space[i].cur;
//	space[i].cur=space[1].cur;
//	space[1].cur=i;
	freeList(space,i);

}
//释放空间
void freeList(StaticList &space,int k)
{
	space[k].cur=space[1].cur;//将当前位置的游标设置为1处游标
	space[1].cur=k;//将1处游标设置为当前位置
}

