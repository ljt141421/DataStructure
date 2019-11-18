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
void insertEdge(GraphMtx *g,T v1,T v2,E cost)
{	
	int p1=getVertexPos(g,v1);
	int p2=getVertexPos(g,v2);

	if(p1 == -1 || p2 == -1)//在顶点列表中未找到元素
		return;

	if(g->edge[p1][p2] != 0)//说明已经有边
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
		if(g->edge[p][i] != 0)
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
		if(g->edge[pv][i] != 0)
			return i;
	}
	return -1;
}
//求两个顶点之间的权值
E getWeight(GraphMtx *g,int v1,int v2)
{
	if(v1 == -1 || v2 == -1)
		return 0;
	return g->edge[v1][v2];
}
//求图的关键路径
void criticalPath(GraphMtx *g)
{
	int n=g->numVertices;
	//存放每个顶点的最早开始时间
	int *ve=(int*)malloc(sizeof(int)*n);
	//存放每个顶点的最晚开始时间
	int *vl=(int*)malloc(sizeof(int)*n);
	assert(ve!=NULL && vl!=NULL);
	
	for(int i=0;i<n;++i)
	{
		//初始化每个顶点的最早开始时间为0
		ve[i]=0;
		//初始化每个顶点的最晚开始时间为最大值MAX_COST
		vl[i]=MAX_COST;
	}
	
	int j,w;
	//求每个顶点的最早开始时间(从源点顺序递推)
	for(i=0;i<n;++i)
	{
		j=getFirstNeighbor(g,g->verticesList[i]);//求i的第一个邻接顶点
		//当顶点存在
		while(j != -1)
		{
			w=getWeight(g,i,j);
			//如果一个顶点的最早开始时间加上权值大于它的邻接顶点(因为每个顶点的最早开始时间已初始化为0)
			//说明邻接顶点的最早开始时间晚于这个顶点
			//此时就需要更改邻接顶点的最早开始时间ve[j]=ve[i]+w(即这个顶点的最早开始时间+权值)
			if(ve[i]+w > ve[j])
			{	
				ve[j]=ve[i]+w;
			}
			//求i的下一个邻接顶点
			j=getNextNeighbor(g,g->verticesList[i],g->verticesList[j]);
		}
	}


	//求每个顶点的最晚开始时间(从汇点逆推)
	vl[n-1]=ve[n-1];//汇点的最晚开始时间和最早开始时间相同
	//从n-2开始逆推
	for(i=n-2;i>0;--i)
	{
		j=getFirstNeighbor(g,g->verticesList[i]);
		while(j!=-1)
		{
			w=getWeight(g,i,j);
			//如果一个顶点的最晚开始时间大于它的邻接顶点减去他们之间的权值(因为每个顶点的最晚开始时间已初始化为最大值)
			//说明这个顶点的最晚开始时间早于它的邻接顶点
			//此时就需要更改这个顶点的最晚开始时间为vl[i]=vl[j]-w(即邻接顶点的最晚开始时间-权值)
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
			//一个顶点的最早开始时间
			Ae=ve[i];
			//一个顶点的最晚开始时间(邻接顶点的最晚开始时间减去他们之间的权值)
			Al=vl[j]-getWeight(g,i,j);
			if(Ae == Al)//说明是关键路径
			{
				printf("<%c,%c>是关键路径.\n",g->verticesList[i],g->verticesList[j]);
			}
			j=getNextNeighbor(g,g->verticesList[i],g->verticesList[j]);
		}
	}

	free(ve);
	free(vl);
}
