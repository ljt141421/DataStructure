#pragma once 
#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Default_Vertex_Size 10//默认的顶点个数

#define T char
#define E int
#define MAX_COST 0x7FFFFFFF

typedef struct GraphMtx
{
	int maxVertices;//最大顶点个数
	int numVertices;//实际顶点个数
	int numEdeges;  //边数

	T *verticesList;//顶点列表(使用数组构造)
	int **edge;		//存储顶点矩阵(二维数组)
}GraphMtx;

void initGraph(GraphMtx *g);
void showGraph(GraphMtx *g);
void insertVertex(GraphMtx *g,T v);
int getVertexPos(GraphMtx *g,T v);
void insertEdge(GraphMtx *g,T v1,T v2,E cost);
void removeVertex(GraphMtx *g,T v);
void removeEdge(GraphMtx *g,T v1,T v2);
void destoryGraph(GraphMtx *g);
int getFirstNeighbor(GraphMtx *g,T v);
int getNextNeighbor(GraphMtx *g,T v,T w);

//MiniSpanTree_Prim
E getWeight(GraphMtx *g,int v1,int v2);
void MinSpanTree_Prim(GraphMtx *g,T vertex);