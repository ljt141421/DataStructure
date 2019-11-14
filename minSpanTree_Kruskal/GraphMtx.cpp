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
		printf("%c ",g->verticesList[i]);
	}
	printf("\n");
	for(i=0;i<g->numVertices;++i)
	{
		printf("%c ",g->verticesList[i]);
		for(int j=0;j<g->numVertices;++j)
		{
			if(g->edge[i][j]==MAX_COST)
			{
				printf("%c ",'@');//��������@���Ŵ���Ȩ�����ֵ
			}
			else
			{
				printf("%d ",g->edge[i][j]);
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

	g->edge[p1][p2]=g->edge[p2][p1]=cost;//ֱ�Ӳ��������߶�Ӧ��Ȩֵ
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
//MiniSpanTree_Prim
void MinSpanTree_Prim(GraphMtx *g,T vertex)
{
	int n=g->numVertices;
	//������lowcost���飬���ڴ���һ�����㵽���������Ȩֵ(ֵΪ˵���˶����Ѽ�����С������)
	E *lowcost=(E*)malloc(sizeof(E)*n);
	//������mst���飬ӵ�д���ÿ�������ԭ����
	int *mst=(int *)malloc(sizeof(int)*n);
	assert(lowcost != NULL && mst != NULL);

	int k=getVertexPos(g,vertex);//�����ǰ�����ڶ����б��λ��

	for(int i=0;i<n;++i)
	{
		if(i != k)
		{
			//�����ǰ��������������Ȩֵ����lowcost������
			lowcost[i]=getWeight(g,k,i);
			mst[i]=k;//�Ѹ��������ʼλ������Ϊ��һ������
		}
		else
		{
			lowcost[i]=0;//�ѵ�ǰ���������С��������
			mst[i]=0;
		}
	}

	int min,min_index;
	int begin,end;
	E cost;

	//���ʣ�µ�n-2������
	for(i=0;i<n-1;++i)
	{
		//����ֵ
		min=MAX_COST;
		min_index=-1;

		for(int j=0;j<n;j++)
		{
			//�ҳ�һ�����㣬ʹ��ǰ������Ȩֵ��С
			if(lowcost[j]!=0 && lowcost[j]<min)
			{
				min=lowcost[j];//�ҳ��Ķ��㵽��ǰ��Ȩֵ��С
				min_index=j;//�ҳ��Ķ����λ��
			}
		}
		begin=mst[min_index];//��ʼ����λ��
		end=min_index;//��������λ��
		printf("%c-->%c : %d\n",g->verticesList[begin],g->verticesList[end],min);

		//�޸Ľ���λ�ö����ȨֵΪ0������˶����Ѿ�������С������
		lowcost[min_index]=0;
		mst[min_index]=0;
		
		//�������¶��������С��������������Ҫ����lowcost�����mst����
		//1.�Խ�������Ϊ����������������������Ȩֵcost������lowcost������бȽ�
		//2.���õ���ȨֵcostС��lowcost�����ֵ�����޸�lowcost����ֵΪcost
		//3.�����ҵ���Ȩֵ��С�Ķ������ʼλ���޸�Ϊmin_index(����һ�ν����Ķ���λ��)
		for(j=0;j<n;++j)  
		{
			cost=getWeight(g,min_index,j);
			if(cost<lowcost[j])
			{
				lowcost[j]=cost;
				mst[j]=min_index;
			}
		}
	}
}

//MinSpanTree_Kruskal

//�Լ������ıȽϺ�����Ϊ��������ʹ��
int cmp(const void *a,const void *b)
{
	return (*(Edge*)a).cost - (*(Edge*)b).cost;
}
//�����������Ƿ���һ����ͨͼ��
bool Is_Same(int *father,int i,int j)
{
	//�����ǰ����ĸ����㲻������������Ѱ�Ҹ�����
	while(father[i] != i)
	{
		i=father[i];
	}
	while(father[j] != j)
	{
		j=father[j];
	}
	return i==j;
}
//����������㴦��һ����ͨͼ��
void Mark_Same(int *father,int i,int j)
{
	while(father[i] != i)
	{
		i=father[i];
	}
	while(father[j] != j)
	{
		j=father[j];
	}
	//��j����ĸ���������i��������i��j����һ����ͨͼ��
	father[j]=i;
}
void MinSpanTree_Kruskal(GraphMtx *g)
{
	int n=g->numVertices;
	//����һ������ͼ���ԣ���n���������n*(n-1)/2����
	Edge *edge=(Edge*)malloc(sizeof(Edge)*(n*(n-1)/2));
	assert(edge != NULL);
	
	int k=0;
	for(int i=0;i<n;++i)
	{
		//�����öԳƾ��󴢴�ͼ������ֻ��Ҫ�Ծ����һ����в���
		for(int j=i;j<n;++j)
		{
			//����������ı���Ϣ��������(��ʼ���㣬�������㣬Ȩֵ)
			//��ֻ����Ч������в���(�������㲻��Ȼ������������Ȩֵ��Ϊ���ֵ)
			if(g->edge[i][j]!=0 && g->edge[i][j]!=MAX_COST)
			{
				edge[k].x=i;
				edge[k].y=j;
				edge[k].cost=g->edge[i][j];
				k++;
			}
		}
	}

	int v1,v2;

	//����ϵͳ�Ŀ�������Ŀ����Ϊ�˽��Ѿ�����ı���Ϣ���д�С���������
	//��ΪKruskal��Ҫÿ��Ѱ��һ��Ȩֵ��С�ı�
	qsort(edge,k,sizeof(Edge),cmp);

	int *father=(int*)malloc(sizeof(int)*n);//����һ������ĸ�����
	assert(father != NULL);

	for(i=0;i<n;++i)
	{
		//�˴�������Ϊÿ�������Ķ���ĸ����㶼������
		father[i]=i;
	}
	
	//Kruskal�ĺ��ģ�ÿ��Ѱ��Ȩֵ��С�ıߣ��ҵ�����ߴ���һ����ͨͼ�ڣ��ͽ���������Ѱ����һ����
	for(i=0;i<n;++i)
	{
		//���һ���ߵ���������ĸ����㲻��ͬ���ͼ�����С��������(˵��û�д���һ����ͨͼ��)
		//��֮��˵�����������㴦��һ����ͨͼ�ڣ������������ߣ�Ѱ����һ����
		if(!Is_Same(father,edge[i].x,edge[i].y))
		{
			v1=edge[i].x;
			v2=edge[i].y;
			printf("%c-->%c : %d\n",g->verticesList[v1],g->verticesList[v2],edge[i].cost);
			//������С������֮�󣬽���������ĸ��ڵ�����Ϊ��ʼ����(������������㴦��һ����ͨͼ��)
			Mark_Same(father,edge[i].x,edge[i].y);
		}
	}
}