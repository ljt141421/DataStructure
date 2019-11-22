#include"GraphMtx.h"

//初始化图
void initGraph(GraphMtx *g)
{
	g->maxVertices=Default_Vertex_Size;
	g->numVertices=g->numEdeges=0;//实际顶点=实际边数=0

	//为顶点列表开辟空间
	g->verticesList=(T*)malloc(sizeof(T)*(g->maxVertices));
	assert(g->verticesList != NULL);

	//开辟二维数组空间
	g->edge=(int**)malloc(sizeof(int*) * g->maxVertices);
	assert(g->edge != NULL);
	//开辟行空间
	for(int i=0;i<g->maxVertices;++i)
	{
		g->edge[i]=(int*)malloc(sizeof(int)*g->maxVertices);
	}
	//对开辟的空间进行初始化
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
//显示图(只显示实际顶点)
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
				printf("%2c ",'@');//在这里用@符号代表权的最大值
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
//插入顶点
void insertVertex(GraphMtx *g,T v)
{
	if(g->numVertices >= g->maxVertices)
		return;
	g->verticesList[g->numVertices++]=v;
}
//获取顶点的位置坐标
int getVertexPos(GraphMtx *g,T v)
{
	for(int i=0;i<g->numVertices;++i)
	{
		if(g->verticesList[i] == v)
			return i;
	}
	return -1;
}
//插入边(在两个顶点之间)
void insertEdge(GraphMtx *g,T v1,T v2,E cost)
{	
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);

	if(p1 == -1 || p2 == -1)//在顶点列表中未找到元素
		return;
	g->edge[p1][p2]=cost;
	g->numEdeges++;
}
//移除顶点(后续顶点覆盖前面的顶点，但是顺序不变)
void removeVertex(GraphMtx *g,T v)
{
	int p=getVertexPos(g,v);
	if(p == -1)
		return;

	int numEdges=0;

	for(int i=p;i<g->numVertices-1;++i)
	{
		g->verticesList[i]=g->verticesList[i+1];//覆盖顶点列表中的顶点
	}

	for(i=0;i<g->numVertices;++i)
	{
		if(g->edge[p][i] != 0)
		{
			numEdges++;//获得目标顶点所在行的邻接顶点边数
		}
	}

	for(i=p;i<g->numVertices-1;++i)
	{
		for(int j=0;j<g->numVertices;++j)
		{
			g->edge[i][j]=g->edge[i+1][j];//后续行覆盖目标顶点所在行
		}
	}

	for(i=p;i<g->numVertices;++i)
	{
		for(int j=0;j<g->numVertices;++j)
		{
			g->edge[j][i]=g->edge[j][i+1];//后序列覆盖目标定点所在列
		}
	}

	g->numVertices--;
	g->numEdeges -= numEdges;

}
//移除边
void removeEdge(GraphMtx *g,T v1,T v2)
{
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);
	if(p1 == -1 || p2 == -1)
		return;
	if(g->edge[p1][p2]==0)//位置为0代表已经无边
		return;
	g->edge[p1][p2]=g->edge[p2][p1]=0;
	g->numEdeges--;

}
//摧毁图
void destoryGraph(GraphMtx *g)
{
	free(g->verticesList);//释放掉顶点列表
	g->verticesList=NULL;
	for(int i=0;i<g->numVertices;++i)
	{
		free(g->edge[i]);//释放掉每一行 
	}
	free(g->edge);//释放掉二维数组
	g->edge=NULL;
	g->maxVertices=g->numEdeges=g->numVertices=0;
}
//获得第一个邻接顶点
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
//获得第一个邻接顶点的下一个邻接顶点
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
//获得两条边对应的权值
E getWeight(GraphMtx *g,int v1,int v2)
{
	if(v1 == -1 || v2 == -1)
		return MAX_COST;
	return g->edge[v1][v2];
}

void shortestPath(GraphMtx *g,T vertex,E dist[],int path[])
{
	int n=g->numVertices;
	//设置一个数组，用来标识是否已经求过最短路径
	bool *s=(bool*)malloc(sizeof(bool)*n);
	assert(s!=NULL);
	int v=getVertexPos(g,vertex);

	for(int i=0;i<n;++i)
	{
		//求出顶点v到各顶点的权值,若两个顶点不能直接到达则权值为MAX_COST
		dist[i]=getWeight(g,v,i);
		s[i]=false;
		if(i!=v && dist[i]<MAX_COST)
		{
			//将权值小于MAX_COST的顶点起始位置设置为v
			path[i]=v;
		}
		else
		{
			//将v自身以及权值为MAX_COST的顶点起始位置设置为-1
			path[i]=-1;
		}
	}

	s[v]=true;//代表v自身已经加入最短路径集合中
	int min;
	int w;
	//求出剩下的n-1个顶点的最短路径
	for(i=0;i<n-1;++i)
	{
		min=MAX_COST;
		int u=v;
		for(int j=0;j<n;++j)
		{
			//找出一个权值最短的顶点，u记录这个顶点的位置
			if(!s[j] && dist[j]<min)
			{
				u=j;
				min=dist[j];
			}
		}
		s[u]=true;//将顶点u加入最短路径的集合中
			
		for(int k=0;k<n;++k)
		{
			//求出以顶点u到各顶点的权值
			w=getWeight(g,u,k);
			//如果一个顶点没有加入最短路径集合中
			//且u到这个顶点的权值小于MAX_COST
			//且 u到v的权值 加上 u到这个顶点的权值 小于 这个顶点到v的权值
			//就把 这个顶点到v的权值 设置为 u到v的权值 加上 u到这个顶点的权值
			//并且修改这个顶点的起始位置为u
			if(!s[k] && w<MAX_COST && dist[u]+w<dist[k])
			{
				dist[k]=dist[u]+w;
				path[k]=u;
			}
		}
	}



}