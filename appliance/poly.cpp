#include<stdio.h>
#include<malloc.h>
#include<assert.h>

typedef struct Term
{
	float coef;//系数
	int expn;//指数
	struct Term *next;
}Term,*LinkTerm;

//函数申明
int locateElem(LinkTerm p,LinkTerm s,LinkTerm &q);
void createPoly(LinkTerm &p,int m);//创建m项多项式
void printPoly(LinkTerm p);//打印多项式
int com(LinkTerm a,LinkTerm b);//比较
LinkTerm addPoly(LinkTerm pa,LinkTerm pb);//多项式相加
void caculate(LinkTerm p,float x);

void main()
{
	LinkTerm p1,p2,p3;
	int l1,l2;
	printf("请输入第一个多项式的项数：");
	scanf("%d",&l1);
	createPoly(p1,l1);
	printf("第一个多项式为：");
	printPoly(p1);
	printf("\n");
	printf("请输入第二个多项式的项数：");
	scanf("%d",&l2);
	createPoly(p2,l2);
	printf("第二个多项式为：");
	printPoly(p2);
	printf("\n");
	
	printf("p1(X)+p2(X)=");
	p3=addPoly(p1,p2);
	printPoly(p3);

	caculate(p3,2);
}

int locateElem(LinkTerm p,LinkTerm s,LinkTerm &q)
{
	//遍历p链，查找是否有与s结点指数相同的结点，如果有，q指向这个结点，并返回1
	//如果没有，根据s结点的指数大小来确定q的指向
	LinkTerm p1=p->next;
	LinkTerm p2=p;
	while(p1)
	{
		if(s->expn > p1->expn)
		{
			p1=p1->next;
			p2=p2->next;
		}
		else if(s->expn == p1->expn)//p链中有和s结点相同的结点
		{
			q=p1;
			return 1;
		}
		else//未找到,说明s结点的指数是最小的
		{
			q=p2;
			return 0;
		}
	}
	if(!p1)//说明p链表为空，q指向头结点
	{
		q=p2;
		return 0;
	}
	return -1;
}
void createPoly(LinkTerm &p,int m)
{
	//创建多项式，根据locateElem的返回值来确定多项式结点的插入位置
	LinkTerm q;
	p=(Term*)malloc(sizeof(Term));
	assert(p != NULL);
	p->next=NULL;
	for(int i=0;i<m;i++)
	{
		LinkTerm s=(Term*)malloc(sizeof(Term));
		printf("请输入%d系数和指数(空格隔开): ",i+1);
		scanf("%f %d",&s->coef,&s->expn);
		if(!locateElem(p,s,q)){//没有p链中没有和s结点指数相同的结点
			s->next=q->next;
			q->next=s;
		}else{//有相同的则指数相加
			q->coef += s->coef;
		}
	}
}
void printPoly(LinkTerm p)
{
	Term *s=p->next;
	while(s)
	{
		printf(" %.2f X^%d",s->coef,s->expn);
		s=s->next;
		if(s != NULL)
		{
			//如果s的下一结点不为负，就加上+
			if(s->coef>=0)
				printf(" +");
		}
	}
	printf("\n");
}
int com(LinkTerm a,LinkTerm b)
{
	if(a->expn < b->expn)
		return -1;
	else if(a->expn == b->expn)
		return 0;
	else
		return 1;
}
LinkTerm addPoly(LinkTerm pa,LinkTerm pb)
{
	LinkTerm a,b,c,temp;
	a=pa->next;
	b=pb->next;
	LinkTerm newLink=(Term*)malloc(sizeof(Term));
	newLink->next=NULL;
	c=newLink;
	float sum;
	while(a&&b)
	{
		switch(com(a,b))
		{
		case -1://pa指数小于pb指数,摘取pa到和链表中
			c->next=a;
			c=a;
			a=a->next;
			break;
		case 0://两个指数相等，则相加，如果系数相加后为零，则删除两个节点
			sum=a->coef+b->coef;
			if(sum==0)//系数相加为零，释放两个节点，并修改指针指向
			{
				temp=a;
				a=a->next;
				free(temp);

				temp=b;
				b=b->next;
				free(temp);
			}
			else//系数相加不为零，则修改和链表指向，删除B链的结点
			{
				a->coef=sum;
				c->next=a;
				c=a;
				a=a->next;

				temp=b;
				b=b->next;
				free(temp);
			}
			break;
		case 1://pa指数大于pb指数
			c->next=b;
			c=b;
			b=b->next;
			break;
		}
	}
	if(a != NULL)
		c->next=a;
	else
		c->next=b;
	return newLink;
}
void caculate(LinkTerm p,float x)
{
	LinkTerm q=p->next;
	float sum;
	float result=0;
	while(q)
	{
		sum=1.0;
		for(int i=1;i<=q->expn;i++)
		{
			sum=sum*x;
		}
		result+=sum*q->coef;//最后乘以系数
		q=q->next;
	}
	printf("将%.1f带入多项式中计算的结果为：%.5f\n",x,result);
}
