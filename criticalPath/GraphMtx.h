#pragma once 
#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Default_Vertex_Size 10//Ĭ�ϵĶ������

#define T char
#define E int

#define MAX_COST 0xFFFFFFF

typedef struct GraphMtx
{
	int maxVertices;//��󶥵����
	int numVertices;//ʵ�ʶ������
	int numEdeges;  //����

	T *verticesList;//�����б�(ʹ�����鹹��)
	int **edge;		//�洢�������(��ά����)
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

//��ͼ�Ĺؼ�·��
E getWeight(GraphMtx *g,int v1,int v2);
void criticalPath(GraphMtx *g);