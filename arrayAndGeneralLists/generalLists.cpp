#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

#define AtomType int
typedef enum{HEAD,ATOM,CHILDLIST}ElemTag;//head==0 atom,childlist==1

typedef struct GLNode
{
	ElemTag tag;//公共部分，用于区分原子和表结点
	union{
		AtomType atom;//如果是原子则存储原子
		struct GLNode *hp;//指向表头指针，如果存储表，则指向下一个表
	};
	struct GLNode *tp;//指向表尾指针
}GLNode;

typedef GLNode* GenList;

void initGenList(GenList &gl);
void createGenList(GenList &gl,char *str);
bool sever(char *sub,char *hsub);

void showGenList(GenList &gl);
bool genListEmpty(GenList &gl,char *str);
int genListLength(GenList &gl);
int genListDepth(GenList &gl);

void main()
{
	GenList gl;
	initGenList(gl);

	char *ga = "(1,2,3)";
	char *gb = "(1,(2,3))";
	char *gc = "(1,(2,3),4)";
	char *gd = "((1,2),3)";
	char *ge = "((1,2,3))";
	char *gf = "()";
	char *gg = "(1,(2,(3,(10,20),4),5),6)";
	
	createGenList(gl,gc);
	showGenList(gl);
	printf("\n");

	int length=genListLength(gl);
	printf("length=%d\n",length);

	int depth=genListDepth(gl);
	printf("depth=%d\n",depth);
}
//初始化广义表
void initGenList(GenList &gl)
{
	gl=NULL;
}
void createGenList(GenList &gl,char *str)
{
	int n=strlen(str);
	char *sub=(char *)malloc(sizeof(char)*(n-2));
	char *hsub=(char *)malloc(sizeof(char)*(n-2));
	assert(sub !=NULL && hsub !=NULL);

	//"1,2,3"
	strncpy(sub,str+1,n-2);//进行脱括号
	sub[n-2]='\0';

	if(gl==NULL)
	{
		gl=(GLNode*)malloc(sizeof(GLNode));
		assert(gl !=NULL);
		gl->tag=HEAD;//设置为头结点
		gl->hp=gl->tp=NULL;
	}

	GLNode *p=gl;
	while(strlen(sub)!=0)
	{
		p=p->tp=(GLNode*)malloc(sizeof(GLNode)); //创建节点并重新指向
		assert(p !=NULL);
		p->hp=p->tp=NULL;

		//"1,2,3" --> hsub="1" sub="2,3";
		//"(1,2),3,4" --> hsub="(1,2)" sub="3,4"
		if(sever(sub,hsub))//分离出头结点和尾结点
		{
			if(hsub[0]=='(')//说明头结点也是一个表
			{
				p->tag=CHILDLIST;
				createGenList(p->hp,hsub);//递归创建子表
			}
			else//头结点是一个原子
			{
				p->tag=ATOM;
				p->atom=atoi(hsub);//把字符串转为整数
			}

		}
	}

}

//"1,2,3"  ==>    hsub="1", sub="2,3";
//"(1,2),3,4" ==> hsub="(1,2)" sub="3,4"

//"" "()"

//"(1,2)"  ==> hsub ="(1,2)"  sub = ""
//分离hsub和sub函数
bool sever(char *sub,char *hsub)
{
	if(*sub=='\0' || strcmp(sub,"()")==0)//如果为空表或者是()的情况
	{
		hsub[0]='\0';
		return true;
	}

	int n=strlen(sub);
	int i=0;
	char ch=sub[0];
	int k=0;
	while(i<n && (ch != ',' || k!=0 ))
	{
		if(ch=='(')
		{
			k++;
		}
		else if(ch==')')
		{
			k--;
		}
		i++;
		ch=sub[i];
	}
	if(i < n)
	{
		sub[i]='\0';//在i处截断
		strcpy(hsub,sub);//拷贝字符到hsub
		strcpy(sub,sub+i+1);//重新对sub进行拷贝赋值
	}
	else if(k != 0)//出现错误
	{
		return false;
	}
	else//"(1,2)"  ==> hsub ="(1,2)"  sub = ""
	{
		strcpy(hsub,sub);
		sub[0]='\0';
	}
	return true;
}
//显示
void showGenList(GenList &gl)
{
	GLNode *p=gl->tp;
	printf("(");
	while(p != NULL)
	{
		if(p->tag==ATOM)
		{
			printf("%d",p->atom);
			if(p->tp != NULL)
			{
				printf(",");
			}
			p=p->tp;
		}
		else if(p->tag==CHILDLIST)//此时还是一个表
		{
			showGenList(p->hp);//递归打印
			p=p->tp;
		}
	}
	printf("),");
}
//判断表是否为空
bool genListEmpty(GenList &gl,char *str)
{
	return gl->tp==NULL;
}
//求表的长度
int genListLength(GenList &gl)
{
	int length=0;
	GLNode *p=gl->tp;
	while(p != NULL)
	{
		length++;
		p=p->tp;
	}
	return length;
}
//求表的深度
int genListDepth(GenList &gl)
{
	if(gl->tp == NULL)
	{
		return 1;
	}
	GLNode *p=gl->tp;
	int maxDepth=0;
	int dep;
	while(p != NULL)
	{
		if(p->tag==CHILDLIST)
		{
			dep=genListDepth(p->hp->tp);
			if(dep>maxDepth)
			{
				maxDepth=dep;
			}
		}
		p=p->tp;
	}
	return maxDepth+1;
}
