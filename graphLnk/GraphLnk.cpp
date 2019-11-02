#include"GraphLnk.h"

void initGraph(GraphLnk *gl)
{
	gl->MaxVertices=Default_Vertex_Size;
	gl->NumEdges=gl->NumVertices=0;

	gl->NodeTable=(Vertex*)malloc(sizeof(Vertex)*gl->MaxVertices);
	assert(gl->NodeTable != NULL);
	//初始化顶点列表
	for(int i=0;i<gl->MaxVertices;++i)
	{
		gl->NodeTable[i].adj=NULL;
	}
}
void showGraph(GraphLnk *gl)
{
	Edge *p;
	for(int i=0;i<gl->NumVertices;++i)
	{
		printf("%d %c:>",i,gl->NodeTable[i].data);
		p=gl->NodeTable[i].adj;
		while(p != NULL)
		{
			printf("%d-->",p->dest);
			p=p->link;
		}
		printf("Nul.\n");
	}
	printf("\n");
}
void insertVertex(GraphLnk *gl,T v)
{
	if(gl->NumVertices >= gl->MaxVertices)
		return;
	gl->NodeTable[gl->NumVertices++].data=v;
}
void insertEdge(GraphLnk *gl,T vertex1,T vertex2)
{
	int v1=getVertexPos(gl,vertex1);
	int v2=getVertexPos(gl,vertex2);

	if(v1==-1 || v2==-1)
		return;

	Edge *s;
	//由于是无向图，所以对于两个顶点都要进行加边
	//v1->v2
	s=(Edge*)malloc(sizeof(Edge));
	assert(s != NULL);
	s->dest=v2;
	//为了方便，直接进行头插
	s->link=gl->NodeTable[v1].adj;
	gl->NodeTable[v1].adj=s;

	//v2->v1
	s=(Edge*)malloc(sizeof(Edge));
	assert(s != NULL);
	s->dest=v1;
	s->link=gl->NodeTable[v2].adj;
	gl->NodeTable[v2].adj=s;

	gl->NumEdges++;
}
int getVertexPos(GraphLnk *gl,T v)
{
	for(int i=0;i<gl->NumVertices;++i)
	{
		if(gl->NodeTable[i].data==v)
			return i;
	}
	return -1;
}

void removeEdge(GraphLnk *gl,T vertex1,T vertex2)
{
	int v1=getVertexPos(gl,vertex1);
	int v2=getVertexPos(gl,vertex2);

	if(v1==-1 || v2==-1)
		return;

	Edge *q=NULL;
	Edge *p;
	//由于是无向图，在删除边时也要双向删除
	//v1->v2
	p=gl->NodeTable[v1].adj;
	while(p != NULL && p->dest != v2)
	{
		q=p;//q永远指向p的前驱
		p=p->link;
	}
	if(p == NULL)
		return;

	if(q==NULL)//说明当前邻接表中只有一个节点
	{
		gl->NodeTable[v1].adj=p->link;
	}
	else
	{
		q->link=p->link;
	}
	free(p);

	//v2->v1
	q=NULL;
	p=gl->NodeTable[v2].adj;
	while(p->dest != v1)
	{
		q=p;
		p=p->link;
	}
	if(q==NULL)//情况同上
	{
		gl->NodeTable[v2].adj=p->link;
	}
	else
	{
		q->link=p->link;
	}
	free(p);
	gl->NumEdges--;
}
void removeVertex(GraphLnk *gl,T vertex)
{
	int v=getVertexPos(gl,vertex);
	if(v == -1)
		return;

	Edge *p=gl->NodeTable[v].adj;

	int k;
	Edge *t=NULL;
	Edge *s;
	//由于是无向图，在删除一个节点时，要删除双向的边
	while(p != NULL)
	{
		k=p->dest;//k为v顶点的下一条边中保存的顶点下标
		s=gl->NodeTable[k].adj;//s为k的下一条边
		while(s != NULL && s->dest !=v)//找到顶点k中下标和v相同的边
		{
			t=s;//t永远指向s的前驱
			s=s->link;
		}
		if(s != NULL)
		{
			if(t==NULL)//在k顶点中只有一个顶点
			{
				gl->NodeTable[k].adj=s->link;
			}
			else
			{
				t->link=s->link;
			}
			free(s);
		}

		gl->NodeTable[v].adj=p->link;//修改v顶点中的边
		free(p);
		p=gl->NodeTable[v].adj;
	}

	//双向删除对应的边之后，调整顶点和边的指向
	//在这里做的是拿最后一个顶点去覆盖v顶点
	gl->NumVertices--;
	gl->NodeTable[v].data=gl->NodeTable[gl->NumVertices].data;//v顶点的data改为最后一个顶点的data
	gl->NodeTable[v].adj=gl->NodeTable[gl->NumVertices].adj;//同时修改边的指向
	
	//在调整完顶点和边的指向之后，还需要在其他顶点的边中更改为更新后的顶点
	s=gl->NodeTable[v].adj;
	while(s != NULL)
	{
		k=s->dest;//k为v顶点的第一条边中的顶点
		p=gl->NodeTable[k].adj;//p为k顶点的第一条边
		while(p != NULL)
		{
			if(p->dest == gl->NumVertices)//在k顶点中寻找与最后一个顶点下标相同的边
			{
				p->dest=v;
				break;
			}
			p=p->link;
		}
		s=s->link;
	}
}
void destoryGraph(GraphLnk *gl)
{
	Edge *p;
	for(int i=0;i<gl->NumVertices;++i)
	{
		p=gl->NodeTable[i].adj;
		while(p != NULL)
		{
			gl->NodeTable[i].adj=p->link;
			free(p);
			p=gl->NodeTable[i].adj;
		}
	}
	free(gl->NodeTable);
	gl->NodeTable=NULL;
	gl->MaxVertices=gl->NumEdges=gl->NumVertices=0;
}	
int getFirstNeighbor(GraphLnk *gl,T vertex)
{
	int v=getVertexPos(gl,vertex);
	if(v == -1)
		return -1;
	Edge *p=gl->NodeTable[v].adj;
	if(p != NULL)
		return p->dest;
	return -1;
}
int getNextNeighbor(GraphLnk *gl,T vertex1,T vertex2)
{
	int v1=getVertexPos(gl,vertex1);
	int v2=getVertexPos(gl,vertex2);

	if(v1 == -1 || v2 == -1)
		return -1;

	Edge *p=gl->NodeTable[v1].adj;
	while(p != NULL && p->dest != v2)
		p=p->link;
	if(p != NULL && p->link != NULL)
		return p->link->dest;
	return -1;
}