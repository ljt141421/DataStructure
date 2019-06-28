#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<assert.h>

#define ElemType int
#define MAXSIZE 100

typedef struct Triple
{
	int i;//非零元的行下标
	int j;//非零元的列下标
	int e;//非零元数据
}Triple;

typedef struct SMatrix
{
	Triple data[MAXSIZE];
	int mu;//行数
	int nu;//列数
	int tu;//非零元的个数
}SMatrix;

//函数声明
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
//创建稀疏矩阵
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
//打印稀疏矩阵
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
//矩阵转置：m行n列-->n行m列,同时原矩阵中每一列数据作为新矩阵的每一行数据
void transposeMatrix(SMatrix *m,SMatrix *t)
{
	t->mu=m->nu;
	t->nu=m->mu;
	t->tu=m->tu;

	int k=0;
	if(m->nu != 0)
	{
		//col指m中列数
		for(int col=0;col<m->nu;++col)
		{
			for(int q=0;q<m->tu;++q)//q指m中非零元的个数
			{
				if(m->data[q].j==col)//如果m中当前第q个的非零元的列与当前列相同
				{//进行置换
					t->data[k].i=m->data[q].j;
					t->data[k].j=m->data[q].i;
					t->data[k].e=m->data[q].e;
					k++;
				}
			}
		}
	}
}
//快速转置
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
			num[col]=0;//初始化每列中非零元的个数为零
		}
		for(int t=0;t<m->tu;++t)
		{
			num[m->data[t].j]++;//计算出每列中非零元的个数，放入num中
		}
		cpot[0]=0;//设置第一列中第一个非零元的坐标起始点为0
		for(col=1;col<m->tu;++col)
		{
			//当前非零元的坐标起始点是上一列第一个坐标表起始点+上一列非零元的个数
			cpot[col]=cpot[col-1]+num[col-1];
		}
		int q=0;//存放坐标
		for(int p=0;p<m->tu;++p)
		{
			col=m->data[p].j;//当前非零元的列
			q=cpot[col];//当前非零元所存放位置的坐标
			t->data[q].i = m->data[p].j;
			t->data[q].j = m->data[p].i;
			t->data[q].e = m->data[p].e;
			cpot[col]++;//相同列元素存放后一个位置
		}
	}
	free(num);
	free(cpot);
}
