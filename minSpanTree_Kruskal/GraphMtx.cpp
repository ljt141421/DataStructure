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
				printf("%c ",'@');//在这里用@符号代表权的最大值
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

	g->edge[p1][p2]=g->edge[p2][p1]=cost;//直接插入两条边对应的权值
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
//MiniSpanTree_Prim
void MinSpanTree_Prim(GraphMtx *g,T vertex)
{
	int n=g->numVertices;
	//构建出lowcost数组，用于储存一个顶点到其他顶点的权值(值为说明此顶点已加入最小生成树)
	E *lowcost=(E*)malloc(sizeof(E)*n);
	//构建出mst数组，拥有储存每个顶点的原顶点
	int *mst=(int *)malloc(sizeof(int)*n);
	assert(lowcost != NULL && mst != NULL);

	int k=getVertexPos(g,vertex);//求出当前顶点在顶点列表的位置

	for(int i=0;i<n;++i)
	{
		if(i != k)
		{
			//算出当前顶点和其他顶点的权值放入lowcost数组中
			lowcost[i]=getWeight(g,k,i);
			mst[i]=k;//把各顶点的起始位置设置为第一个顶点
		}
		else
		{
			lowcost[i]=0;//把当前顶点放入最小生成树中
			mst[i]=0;
		}
	}

	int min,min_index;
	int begin,end;
	E cost;

	//求出剩下的n-2个顶点
	for(i=0;i<n-1;++i)
	{
		//赋初值
		min=MAX_COST;
		min_index=-1;

		for(int j=0;j<n;j++)
		{
			//找出一个顶点，使当前到它的权值最小
			if(lowcost[j]!=0 && lowcost[j]<min)
			{
				min=lowcost[j];//找出的顶点到当前的权值最小
				min_index=j;//找出的顶点的位置
			}
		}
		begin=mst[min_index];//起始顶点位置
		end=min_index;//结束顶点位置
		printf("%c-->%c : %d\n",g->verticesList[begin],g->verticesList[end],min);

		//修改结束位置顶点的权值为0，代表此顶点已经加入最小生成树
		lowcost[min_index]=0;
		mst[min_index]=0;
		
		//由于有新顶点加入最小生成树，所以需要更新lowcost数组和mst数组
		//1.以结束顶点为基础，算出其与其他顶点的权值cost，并与lowcost数组进行比较
		//2.若得到的权值cost小于lowcost数组的值，就修改lowcost数组值为cost
		//3.并把找到的权值最小的顶点的起始位置修改为min_index(即上一次结束的顶点位置)
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

//自己创建的比较函数，为快速排序使用
int cmp(const void *a,const void *b)
{
	return (*(Edge*)a).cost - (*(Edge*)b).cost;
}
//看两个顶点是否处于一个连通图中
bool Is_Same(int *father,int i,int j)
{
	//如果当前顶点的父顶点不是自身，就向上寻找父顶点
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
//标记两个顶点处于一个连通图中
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
	//将j顶点的父顶点设置i，即代表i和j处于一个连通图内
	father[j]=i;
}
void MinSpanTree_Kruskal(GraphMtx *g)
{
	int n=g->numVertices;
	//对于一个无向图而言，有n个顶点就有n*(n-1)/2条边
	Edge *edge=(Edge*)malloc(sizeof(Edge)*(n*(n-1)/2));
	assert(edge != NULL);
	
	int k=0;
	for(int i=0;i<n;++i)
	{
		//由于用对称矩阵储存图，所以只需要对矩阵的一半进行操作
		for(int j=i;j<n;++j)
		{
			//把两个顶点的边信息储存起来(起始顶点，结束顶点，权值)
			//且只对有效顶点进行操作(两个顶点不相等或者两个顶点的权值不为最大值)
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

	//调用系统的快速排序，目的是为了将已经储存的边信息进行从小到大的排序
	//因为Kruskal需要每次寻找一条权值最小的边
	qsort(edge,k,sizeof(Edge),cmp);

	int *father=(int*)malloc(sizeof(int)*n);//储存一个顶点的父顶点
	assert(father != NULL);

	for(i=0;i<n;++i)
	{
		//此处我们认为每个独立的顶点的父顶点都是自身
		father[i]=i;
	}
	
	//Kruskal的核心：每次寻找权值最小的边，且当这个边处于一个连通图内，就进行舍弃，寻找下一条边
	for(i=0;i<n;++i)
	{
		//如果一条边的两个顶点的父顶点不相同，就加入最小生成树中(说明没有处于一个连通图内)
		//反之，说明这两个顶点处于一个连通图内，就舍弃这条边，寻找下一条边
		if(!Is_Same(father,edge[i].x,edge[i].y))
		{
			v1=edge[i].x;
			v2=edge[i].y;
			printf("%c-->%c : %d\n",g->verticesList[v1],g->verticesList[v2],edge[i].cost);
			//加入最小生成树之后，将结束顶点的父节点设置为起始顶点(即标记两个顶点处于一个连通图中)
			Mark_Same(father,edge[i].x,edge[i].y);
		}
	}
}