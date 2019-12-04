#include<stdio.h>
#include<malloc.h>
#include<assert.h>

typedef struct Term
{
	float coef;//ϵ��
	int expn;//ָ��
	struct Term *next;
}Term,*LinkTerm;

//��������
int locateElem(LinkTerm p,LinkTerm s,LinkTerm &q);
void createPoly(LinkTerm &p,int m);//����m�����ʽ
void printPoly(LinkTerm p);//��ӡ����ʽ
int com(LinkTerm a,LinkTerm b);//�Ƚ�
LinkTerm addPoly(LinkTerm pa,LinkTerm pb);//����ʽ���
void caculate(LinkTerm p,float x);

void main()
{
	LinkTerm p1,p2,p3;
	int l1,l2;
	printf("�������һ������ʽ��������");
	scanf("%d",&l1);
	createPoly(p1,l1);
	printf("��һ������ʽΪ��");
	printPoly(p1);
	printf("\n");
	printf("������ڶ�������ʽ��������");
	scanf("%d",&l2);
	createPoly(p2,l2);
	printf("�ڶ�������ʽΪ��");
	printPoly(p2);
	printf("\n");
	
	printf("p1(X)+p2(X)=");
	p3=addPoly(p1,p2);
	printPoly(p3);

	caculate(p3,2);
}

int locateElem(LinkTerm p,LinkTerm s,LinkTerm &q)
{
	//����p���������Ƿ�����s���ָ����ͬ�Ľ�㣬����У�qָ�������㣬������1
	//���û�У�����s����ָ����С��ȷ��q��ָ��
	LinkTerm p1=p->next;
	LinkTerm p2=p;
	while(p1)
	{
		if(s->expn > p1->expn)
		{
			p1=p1->next;
			p2=p2->next;
		}
		else if(s->expn == p1->expn)//p�����к�s�����ͬ�Ľ��
		{
			q=p1;
			return 1;
		}
		else//δ�ҵ�,˵��s����ָ������С��
		{
			q=p2;
			return 0;
		}
	}
	if(!p1)//˵��p����Ϊ�գ�qָ��ͷ���
	{
		q=p2;
		return 0;
	}
	return -1;
}
void createPoly(LinkTerm &p,int m)
{
	//��������ʽ������locateElem�ķ���ֵ��ȷ������ʽ���Ĳ���λ��
	LinkTerm q;
	p=(Term*)malloc(sizeof(Term));
	assert(p != NULL);
	p->next=NULL;
	for(int i=0;i<m;i++)
	{
		LinkTerm s=(Term*)malloc(sizeof(Term));
		printf("������%dϵ����ָ��(�ո����): ",i+1);
		scanf("%f %d",&s->coef,&s->expn);
		if(!locateElem(p,s,q)){//û��p����û�к�s���ָ����ͬ�Ľ��
			s->next=q->next;
			q->next=s;
		}else{//����ͬ����ָ�����
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
			//���s����һ��㲻Ϊ�����ͼ���+
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
		case -1://paָ��С��pbָ��,ժȡpa����������
			c->next=a;
			c=a;
			a=a->next;
			break;
		case 0://����ָ����ȣ�����ӣ����ϵ����Ӻ�Ϊ�㣬��ɾ�������ڵ�
			sum=a->coef+b->coef;
			if(sum==0)//ϵ�����Ϊ�㣬�ͷ������ڵ㣬���޸�ָ��ָ��
			{
				temp=a;
				a=a->next;
				free(temp);

				temp=b;
				b=b->next;
				free(temp);
			}
			else//ϵ����Ӳ�Ϊ�㣬���޸ĺ�����ָ��ɾ��B���Ľ��
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
		case 1://paָ������pbָ��
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
		result+=sum*q->coef;//������ϵ��
		q=q->next;
	}
	printf("��%.1f�������ʽ�м���Ľ��Ϊ��%.5f\n",x,result);
}
