#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<assert.h>

#define ElemType int
#define MAXSIZE 100

typedef struct Triple
{
	int i;//����Ԫ�����±�
	int j;//����Ԫ�����±�
	int e;//����Ԫ����
}Triple;

typedef struct SMatrix
{
	Triple data[MAXSIZE];
	int mu;//����
	int nu;//����
	int tu;//����Ԫ�ĸ���
}SMatrix;

//��������
void createMatrix(SMatrix *m);
void printMatrix(SMatrix  *m);
void copy(SMatrix *m,SMatrix *t);
void addMatrix(SMatrix *M, SMatrix *N, SMatrix *T); //M N
void subMatrix(SMatrix *M, SMatrix *N, SMatrix *T);
void mulMatrix(SMatrix *M, SMatrix *N, SMatrix *T); //M (m,n) N(x,y)
void transposeMatrix(SMatrix *m,SMatrix *t);
void fastTransposeMatrix(SMatrix *m,SMatrix *t);

void main()
{
	SMatrix sm,sm1;
	memset(&sm,0,sizeof(sm));
	createMatrix(&sm);
	printMatrix(&sm);
	fastTransposeMatrix(&sm,&sm1);
	printMatrix(&sm1);
}
//����ϡ�����
void createMatrix(SMatrix *m)
{
	FILE *fp = fopen("Matrix.txt","r");
	if(fp == NULL)
		exit(1);

	fscanf(fp,"%d %d",&m->mu,&m->nu);

	int value;
	int k=0;
	for(int i=0;i<m->mu;++i)
	{
		for(int j=0;j<m->nu;++j)
		{
			fscanf(fp,"%d",&value);
			if(value != 0)
			{
				m->data[k].e=value;
				m->data[k].i=i;
				m->data[k].j=j;
				k++;
			}
		}
	}
	m->tu=k;
	fclose(fp);
}
//��ӡϡ�����
void printMatrix(SMatrix  *m)
{
	printf("row=%d, col=%d\n",m->mu,m->nu);
	for(int i=0;i<m->tu;++i)
	{
		printf("(%d,%d,%d)\n",m->data[i].i,m->data[i].j,m->data[i].e);
	}
}
void copy(SMatrix *m,SMatrix *t)
{
	t->mu=m->mu;
	t->nu=m->nu;
	t->tu=m->tu;
	for(int i=0;i<m->tu;++i)
	{
		t->data[i].i = m->data[i].i;
		t->data[i].j = m->data[i].j;
		t->data[i].e = m->data[i].e;
	}
}
void addMatrix(SMatrix *M, SMatrix *N, SMatrix *T){}//M N
void subMatrix(SMatrix *M, SMatrix *N, SMatrix *T){}
void mulMatrix(SMatrix *M, SMatrix *N, SMatrix *T){} //M (m,n) N(x,y)
//����ת�ã�m��n��-->n��m��,ͬʱԭ������ÿһ��������Ϊ�¾����ÿһ������
void transposeMatrix(SMatrix *m,SMatrix *t)
{
	t->mu=m->nu;
	t->nu=m->mu;
	t->tu=m->tu;

	int k=0;
	if(m->nu != 0)
	{
		//colָm������
		for(int col=0;col<m->nu;++col)
		{
			for(int q=0;q<m->tu;++q)//qָm�з���Ԫ�ĸ���
			{
				if(m->data[q].j==col)//���m�е�ǰ��q���ķ���Ԫ�����뵱ǰ����ͬ
				{//�����û�
					t->data[k].i=m->data[q].j;
					t->data[k].j=m->data[q].i;
					t->data[k].e=m->data[q].e;
					k++;
				}
			}
		}
	}
}
//����ת��
void fastTransposeMatrix(SMatrix *m,SMatrix *t)
{
	t->mu=m->nu;
	t->nu=m->mu;
	t->tu=m->tu;

	int *num=(int *)malloc(sizeof(int)*m->nu);
	assert(num != NULL);
	int *cpot=(int *)malloc(sizeof(int)*m->nu);
	assert(cpot != NULL);

	if(t->tu != 0)
	{
		for(int col=0;col<m->nu;++col)
		{
			num[col]=0;//��ʼ��ÿ���з���Ԫ�ĸ���Ϊ��
		}
		for(int t=0;t<m->tu;++t)
		{
			num[m->data[t].j]++;//�����ÿ���з���Ԫ�ĸ���������num��
		}
		cpot[0]=0;//���õ�һ���е�һ������Ԫ��������ʼ��Ϊ0
		for(col=1;col<m->tu;++col)
		{
			//��ǰ����Ԫ��������ʼ������һ�е�һ���������ʼ��+��һ�з���Ԫ�ĸ���
			cpot[col]=cpot[col-1]+num[col-1];
		}
		int q=0;//�������
		for(int p=0;p<m->tu;++p)
		{
			col=m->data[p].j;//��ǰ����Ԫ����
			q=cpot[col];//��ǰ����Ԫ�����λ�õ�����
			t->data[q].i = m->data[p].j;
			t->data[q].j = m->data[p].i;
			t->data[q].e = m->data[p].e;
			cpot[col]++;//��ͬ��Ԫ�ش�ź�һ��λ��
		}
	}
	free(num);
	free(cpot);
}
