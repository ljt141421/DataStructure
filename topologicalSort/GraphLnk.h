#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Default_Vertex_Size 10
#define T char

//边
typedef struct Edge
{
	int dest;//存储顶点在顶点列表中的下标
	struct Edge *link;//指向下一条边的指针
}Edge;

//顶点
typedef struct Vertex
{
	T data;//顶点名
	Edge *adj;//指向第一条边的指针
}Vertex;

//图的结构
typedef struct GraphLnk
{
	int MaxVertices;
	int NumVertices;
	int NumEdges;

	Vertex *NodeTable;//顶点列表，
}GraphLnk;

void initGraph(GraphLnk *gl);//初始化图
void showGraph(GraphLnk *gl);//打印图(以邻接表的形式)
void insertVertex(GraphLnk *gl,T v);//插入一个顶点
void insertEdge(GraphLnk *gl,T vertex1,T vertex2);//在两个顶点之间插入边
int getVertexPos(GraphLnk *gl,T v);//获取一个顶点在顶点列表中的位置

void removeEdge(GraphLnk *gl,T vertex1,T vertex2);//移除两个顶点之间的边
void removeVertex(GraphLnk *gl,T vertex);//移除一个顶点
void destoryGraph(GraphLnk *gl);//摧毁一个图
int getFirstNeighbor(GraphLnk *gl,T vertex);//获取顶点的第一个邻接顶点
int getNextNeighbor(GraphLnk *gl,T vertex1,T vertex2);//获取下一个邻接顶点

//拓扑排序
void TopologicalSort(GraphLnk *g);

