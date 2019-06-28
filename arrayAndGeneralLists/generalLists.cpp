#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

#define AtomType int
typedef enum{HEAD,ATOM,CHILDLIST}ElemTag;//head==0 atom,childlist==1

typedef struct GLNode
{
	ElemTag tag;//�������֣���������ԭ�Ӻͱ���
	union{
		AtomType atom;//�����ԭ����洢ԭ��
		struct GLNode *hp;//ָ���ͷָ�룬����洢����ָ����һ����
	};
	struct GLNode *tp;//ָ���βָ��
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
//��ʼ�������
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
	strncpy(sub,str+1,n-2);//����������
	sub[n-2]='\0';

	if(gl==NULL)
	{
		gl=(GLNode*)malloc(sizeof(GLNode));
		assert(gl !=NULL);
		gl->tag=HEAD;//����Ϊͷ���
		gl->hp=gl->tp=NULL;
	}

	GLNode *p=gl;
	while(strlen(sub)!=0)
	{
		p=p->tp=(GLNode*)malloc(sizeof(GLNode)); //�����ڵ㲢����ָ��
		assert(p !=NULL);
		p->hp=p->tp=NULL;

		//"1,2,3" --> hsub="1" sub="2,3";
		//"(1,2),3,4" --> hsub="(1,2)" sub="3,4"
		if(sever(sub,hsub))//�����ͷ����β���
		{
			if(hsub[0]=='(')//˵��ͷ���Ҳ��һ����
			{
				p->tag=CHILDLIST;
				createGenList(p->hp,hsub);//�ݹ鴴���ӱ�
			}
			else//ͷ�����һ��ԭ��
			{
				p->tag=ATOM;
				p->atom=atoi(hsub);//���ַ���תΪ����
			}

		}
	}

}

//"1,2,3"  ==>    hsub="1", sub="2,3";
//"(1,2),3,4" ==> hsub="(1,2)" sub="3,4"

//"" "()"

//"(1,2)"  ==> hsub ="(1,2)"  sub = ""
//����hsub��sub����
bool sever(char *sub,char *hsub)
{
	if(*sub=='\0' || strcmp(sub,"()")==0)//���Ϊ�ձ������()�����
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
		sub[i]='\0';//��i���ض�
		strcpy(hsub,sub);//�����ַ���hsub
		strcpy(sub,sub+i+1);//���¶�sub���п�����ֵ
	}
	else if(k != 0)//���ִ���
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
//��ʾ
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
		else if(p->tag==CHILDLIST)//��ʱ����һ����
		{
			showGenList(p->hp);//�ݹ��ӡ
			p=p->tp;
		}
	}
	printf("),");
}
//�жϱ��Ƿ�Ϊ��
bool genListEmpty(GenList &gl,char *str)
{
	return gl->tp==NULL;
}
//���ĳ���
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
//�������
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
