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
			if(i==j)
			{
				g->edge[i][j]=0;
			}
			else
			{
				g->edge[i][j]=MAX_COST;
			}
		}
	}
}
//��ʾͼ(ֻ��ʾʵ�ʶ���)
void showGraph(GraphMtx *g)
{
	printf("  ");
	for(int i=0;i<g->numVertices;++i)
	{
		printf("%2c ",g->verticesList[i]);
	}
	printf("\n");
	for(i=0;i<g->numVertices;++i)
	{
		printf("%c ",g->verticesList[i]);
		for(int j=0;j<g->numVertices;++j)
		{
			if(g->edge[i][j]==MAX_COST)
			{
				printf("%2c ",'@');//��������@���Ŵ���Ȩ�����ֵ
			}
			else
			{
				printf("%2d ",g->edge[i][j]);
			}
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
		if(g->edge[p][i] == 1)
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
		if(g->edge[pv][i] == 1)
			return i;
	}
	return -1;
}
//��������߶�Ӧ��Ȩֵ
E getWeight(GraphMtx *g,int v1,int v2)
{
	if(v1 == -1 || v2 == -1)
		return MAX_COST;
	return g->edge[v1][v2];
}

void shortestPath(GraphMtx *g,T vertex,E dist[],int path[])
{
	int n=g->numVertices;
	//����һ�����飬������ʶ�Ƿ��Ѿ�������·��
	bool *s=(bool*)malloc(sizeof(bool)*n);
	assert(s!=NULL);
	int v=getVertexPos(g,vertex);

	for(int i=0;i<n;++i)
	{
		//�������v���������Ȩֵ,���������㲻��ֱ�ӵ�����ȨֵΪMAX_COST
		dist[i]=getWeight(g,v,i);
		s[i]=false;
		if(i!=v && dist[i]<MAX_COST)
		{
			//��ȨֵС��MAX_COST�Ķ�����ʼλ������Ϊv
			path[i]=v;
		}
		else
		{
			//��v�����Լ�ȨֵΪMAX_COST�Ķ�����ʼλ������Ϊ-1
			path[i]=-1;
		}
	}

	s[v]=true;//����v�����Ѿ��������·��������
	int min;
	int w;
	//���ʣ�µ�n-1����������·��
	for(i=0;i<n-1;++i)
	{
		min=MAX_COST;
		int u=v;
		for(int j=0;j<n;++j)
		{
			//�ҳ�һ��Ȩֵ��̵Ķ��㣬u��¼��������λ��
			if(!s[j] && dist[j]<min)
			{
				u=j;
				min=dist[j];
			}
		}
		s[u]=true;//������u�������·���ļ�����
			
		for(int k=0;k<n;++k)
		{
			//����Զ���u���������Ȩֵ
			w=getWeight(g,u,k);
			//���һ������û�м������·��������
			//��u����������ȨֵС��MAX_COST
			//�� u��v��Ȩֵ ���� u����������Ȩֵ С�� ������㵽v��Ȩֵ
			//�Ͱ� ������㵽v��Ȩֵ ����Ϊ u��v��Ȩֵ ���� u����������Ȩֵ
			//�����޸�����������ʼλ��Ϊu
			if(!s[k] && w<MAX_COST && dist[u]+w<dist[k])
			{
				dist[k]=dist[u]+w;
				path[k]=u;
			}
		}
	}



}