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
			g->edge[i][j]=0;
		}
	}
}
//显示图(只显示实际顶点)
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
void insertEdge(GraphMtx *g,T v1,T v2)
{	
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);

	if(p1 == -1 || p2 == -1)//在顶点列表中未找到元素
		return;

	if(g->edge[p1][p2] != 0)//说明已经有边
		return;
	g->edge[p1][p2]=g->edge[p2][p1]=1;//由于是无向图，所以要对称
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
