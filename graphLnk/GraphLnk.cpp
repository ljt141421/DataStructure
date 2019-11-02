#include"GraphLnk.h"

void initGraph(GraphLnk *gl)
{
	gl->MaxVertices=Default_Vertex_Size;
	gl->NumEdges=gl->NumVertices=0;

	gl->NodeTable=(Vertex*)malloc(sizeof(Vertex)*gl->MaxVertices);
	assert(gl->NodeTable != NULL);
	//��ʼ�������б�
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
	//����������ͼ�����Զ����������㶼Ҫ���мӱ�
	//v1->v2
	s=(Edge*)malloc(sizeof(Edge));
	assert(s != NULL);
	s->dest=v2;
	//Ϊ�˷��㣬ֱ�ӽ���ͷ��
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
	//����������ͼ����ɾ����ʱҲҪ˫��ɾ��
	//v1->v2
	p=gl->NodeTable[v1].adj;
	while(p != NULL && p->dest != v2)
	{
		q=p;//q��Զָ��p��ǰ��
		p=p->link;
	}
	if(p == NULL)
		return;

	if(q==NULL)//˵����ǰ�ڽӱ���ֻ��һ���ڵ�
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
	if(q==NULL)//���ͬ��
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
	//����������ͼ����ɾ��һ���ڵ�ʱ��Ҫɾ��˫��ı�
	while(p != NULL)
	{
		k=p->dest;//kΪv�������һ�����б���Ķ����±�
		s=gl->NodeTable[k].adj;//sΪk����һ����
		while(s != NULL && s->dest !=v)//�ҵ�����k���±��v��ͬ�ı�
		{
			t=s;//t��Զָ��s��ǰ��
			s=s->link;
		}
		if(s != NULL)
		{
			if(t==NULL)//��k������ֻ��һ������
			{
				gl->NodeTable[k].adj=s->link;
			}
			else
			{
				t->link=s->link;
			}
			free(s);
		}

		gl->NodeTable[v].adj=p->link;//�޸�v�����еı�
		free(p);
		p=gl->NodeTable[v].adj;
	}

	//˫��ɾ����Ӧ�ı�֮�󣬵�������ͱߵ�ָ��
	//�����������������һ������ȥ����v����
	gl->NumVertices--;
	gl->NodeTable[v].data=gl->NodeTable[gl->NumVertices].data;//v�����data��Ϊ���һ�������data
	gl->NodeTable[v].adj=gl->NodeTable[gl->NumVertices].adj;//ͬʱ�޸ıߵ�ָ��
	
	//�ڵ����궥��ͱߵ�ָ��֮�󣬻���Ҫ����������ı��и���Ϊ���º�Ķ���
	s=gl->NodeTable[v].adj;
	while(s != NULL)
	{
		k=s->dest;//kΪv����ĵ�һ�����еĶ���
		p=gl->NodeTable[k].adj;//pΪk����ĵ�һ����
		while(p != NULL)
		{
			if(p->dest == gl->NumVertices)//��k������Ѱ�������һ�������±���ͬ�ı�
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