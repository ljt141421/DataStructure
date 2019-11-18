#include"GraphMtx.h"

//��ʼ��ͼ
void initGraph(GraphMtx *g)
{
	g->maxVertices=Default_Vertex_Size;
	g->numVertices=g->numEdeges=0;//ʵ�ʶ���=ʵ�ʱ���=0

	//Ϊ�����б��ٿռ�
	g->verticesList=(T*)malloc(sizeof(T)*(g->maxVertices));
	assert(g->verticesList != NULL);

	//���ٶ�ά����ռ�
	g->edge=(int**)malloc(sizeof(int*) * g->maxVertices);
	assert(g->edge != NULL);
	//�����пռ�
	for(int i=0;i<g->maxVertices;++i)
	{
		g->edge[i]=(int*)malloc(sizeof(int)*g->maxVertices);
	}
	//�Կ��ٵĿռ���г�ʼ��
	for(i=0;i<g->maxVertices;++i)
	{
		for(int j=0;j<g->maxVertices;++j)
		{
			g->edge[i][j]=0;
		}
	}
}
//��ʾͼ(ֻ��ʾʵ�ʶ���)
void showGraph(GraphMtx *g)
{
	printf("  ");
	for(int i=0;i<g->numVertices;++i)
	{
		printf("%c ",g->verticesList[i]);
	}
	printf("\n");
	for(i=0;i<g->numVertices;++i)
	{
		printf("%c ",g->verticesList[i]);
		for(int j=0;j<g->numVertices;++j)
		{
			printf("%d ",g->edge[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//���붥��
void insertVertex(GraphMtx *g,T v)
{
	if(g->numVertices >= g->maxVertices)
		return;
	g->verticesList[g->numVertices++]=v;
}
//��ȡ�����λ������
int getVertexPos(GraphMtx *g,T v)
{
	for(int i=0;i<g->numVertices;++i)
	{
		if(g->verticesList[i] == v)
			return i;
	}
	return -1;
}
//�����(����������֮��)
void insertEdge(GraphMtx *g,T v1,T v2,E cost)
{	
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);

	if(p1 == -1 || p2 == -1)//�ڶ����б���δ�ҵ�Ԫ��
		return;

	if(g->edge[p1][p2] != 0)//˵���Ѿ��б�
		return;

	g->edge[p1][p2]=cost;
	g->numEdeges++;
}
//�Ƴ�����(�������㸲��ǰ��Ķ��㣬����˳�򲻱�)
void removeVertex(GraphMtx *g,T v)
{
	int p=getVertexPos(g,v);
	if(p == -1)
		return;

	int numEdges=0;

	for(int i=p;i<g->numVertices-1;++i)
	{
		g->verticesList[i]=g->verticesList[i+1];//���Ƕ����б��еĶ���
	}

	for(i=0;i<g->numVertices;++i)
	{
		if(g->edge[p][i] != 0)
		{
			numEdges++;//���Ŀ�궥�������е��ڽӶ������
		}
	}

	for(i=p;i<g->numVertices-1;++i)
	{
		for(int j=0;j<g->numVertices;++j)
		{
			g->edge[i][j]=g->edge[i+1][j];//�����и���Ŀ�궥��������
		}
	}

	for(i=p;i<g->numVertices;++i)
	{
		for(int j=0;j<g->numVertices;++j)
		{
			g->edge[j][i]=g->edge[j][i+1];//�����и���Ŀ�궨��������
		}
	}

	g->numVertices--;
	g->numEdeges -= numEdges;

}
//�Ƴ���
void removeEdge(GraphMtx *g,T v1,T v2)
{
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);
	if(p1 == -1 || p2 == -1)
		return;
	if(g->edge[p1][p2]==0)//λ��Ϊ0�����Ѿ��ޱ�
		return;
	g->edge[p1][p2]=g->edge[p2][p1]=0;
	g->numEdeges--;

}
//�ݻ�ͼ
void destoryGraph(GraphMtx *g)
{
	free(g->verticesList);//�ͷŵ������б�
	g->verticesList=NULL;
	for(int i=0;i<g->numVertices;++i)
	{
		free(g->edge[i]);//�ͷŵ�ÿһ�� 
	}
	free(g->edge);//�ͷŵ���ά����
	g->edge=NULL;
	g->maxVertices=g->numEdeges=g->numVertices=0;
}
//��õ�һ���ڽӶ���
int getFirstNeighbor(GraphMtx *g,T v)
{
	int p=getVertexPos(g,v);
	if(p == -1)
		return -1;

	for(int i=0;i<g->numVertices;++i)
	{
		if(g->edge[p][i] != 0)
			return i;
	}
	return -1;
}
//��õ�һ���ڽӶ������һ���ڽӶ���
int getNextNeighbor(GraphMtx *g,T v,T w)
{
	int pv=getVertexPos(g,v);
	int pw=getVertexPos(g,w);

	if(pv == -1 || pw ==-1)
		return -1;
	for(int i=pw+1;i<g->numVertices;++i)
	{
		if(g->edge[pv][i] != 0)
			return i;
	}
	return -1;
}
//����������֮���Ȩֵ
E getWeight(GraphMtx *g,int v1,int v2)
{
	if(v1 == -1 || v2 == -1)
		return 0;
	return g->edge[v1][v2];
}
//��ͼ�Ĺؼ�·��
void criticalPath(GraphMtx *g)
{
	int n=g->numVertices;
	//���ÿ����������翪ʼʱ��
	int *ve=(int*)malloc(sizeof(int)*n);
	//���ÿ�����������ʼʱ��
	int *vl=(int*)malloc(sizeof(int)*n);
	assert(ve!=NULL && vl!=NULL);
	
	for(int i=0;i<n;++i)
	{
		//��ʼ��ÿ����������翪ʼʱ��Ϊ0
		ve[i]=0;
		//��ʼ��ÿ�����������ʼʱ��Ϊ���ֵMAX_COST
		vl[i]=MAX_COST;
	}
	
	int j,w;
	//��ÿ����������翪ʼʱ��(��Դ��˳�����)
	for(i=0;i<n;++i)
	{
		j=getFirstNeighbor(g,g->verticesList[i]);//��i�ĵ�һ���ڽӶ���
		//���������
		while(j != -1)
		{
			w=getWeight(g,i,j);
			//���һ����������翪ʼʱ�����Ȩֵ���������ڽӶ���(��Ϊÿ����������翪ʼʱ���ѳ�ʼ��Ϊ0)
			//˵���ڽӶ�������翪ʼʱ�������������
			//��ʱ����Ҫ�����ڽӶ�������翪ʼʱ��ve[j]=ve[i]+w(�������������翪ʼʱ��+Ȩֵ)
			if(ve[i]+w > ve[j])
			{	
				ve[j]=ve[i]+w;
			}
			//��i����һ���ڽӶ���
			j=getNextNeighbor(g,g->verticesList[i],g->verticesList[j]);
		}
	}


	//��ÿ�����������ʼʱ��(�ӻ������)
	vl[n-1]=ve[n-1];//��������ʼʱ������翪ʼʱ����ͬ
	//��n-2��ʼ����
	for(i=n-2;i>0;--i)
	{
		j=getFirstNeighbor(g,g->verticesList[i]);
		while(j!=-1)
		{
			w=getWeight(g,i,j);
			//���һ�����������ʼʱ����������ڽӶ����ȥ����֮���Ȩֵ(��Ϊÿ�����������ʼʱ���ѳ�ʼ��Ϊ���ֵ)
			//˵��������������ʼʱ�����������ڽӶ���
			//��ʱ����Ҫ����������������ʼʱ��Ϊvl[i]=vl[j]-w(���ڽӶ��������ʼʱ��-Ȩֵ)
			if(vl[j]-w < vl[i])
			{
				vl[i]=vl[j]-w;
			}
			j=getNextNeighbor(g,g->verticesList[i],g->verticesList[j]);
		}
	}

	int Ae,Al;
	for(i=0;i<n;++i)
	{
		j=getFirstNeighbor(g,g->verticesList[i]);
		while(j != -1)
		{
			//һ����������翪ʼʱ��
			Ae=ve[i];
			//һ�����������ʼʱ��(�ڽӶ��������ʼʱ���ȥ����֮���Ȩֵ)
			Al=vl[j]-getWeight(g,i,j);
			if(Ae == Al)//˵���ǹؼ�·��
			{
				printf("<%c,%c>�ǹؼ�·��.\n",g->verticesList[i],g->verticesList[j]);
			}
			j=getNextNeighbor(g,g->verticesList[i],g->verticesList[j]);
		}
	}

	free(ve);
	free(vl);
}
