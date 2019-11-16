#pragma once

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Default_Vertex_Size 10
#define T char

//��
typedef struct Edge
{
	int dest;//�洢�����ڶ����б��е��±�
	struct Edge *link;//ָ����һ���ߵ�ָ��
}Edge;

//����
typedef struct Vertex
{
	T data;//������
	Edge *adj;//ָ���һ���ߵ�ָ��
}Vertex;

//ͼ�Ľṹ
typedef struct GraphLnk
{
	int MaxVertices;
	int NumVertices;
	int NumEdges;

	Vertex *NodeTable;//�����б�
}GraphLnk;

void initGraph(GraphLnk *gl);//��ʼ��ͼ
void showGraph(GraphLnk *gl);//��ӡͼ(���ڽӱ����ʽ)
void insertVertex(GraphLnk *gl,T v);//����һ������
void insertEdge(GraphLnk *gl,T vertex1,T vertex2);//����������֮������
int getVertexPos(GraphLnk *gl,T v);//��ȡһ�������ڶ����б��е�λ��

void removeEdge(GraphLnk *gl,T vertex1,T vertex2);//�Ƴ���������֮��ı�
void removeVertex(GraphLnk *gl,T vertex);//�Ƴ�һ������
void destoryGraph(GraphLnk *gl);//�ݻ�һ��ͼ
int getFirstNeighbor(GraphLnk *gl,T vertex);//��ȡ����ĵ�һ���ڽӶ���
int getNextNeighbor(GraphLnk *gl,T vertex1,T vertex2);//��ȡ��һ���ڽӶ���

//��������
void TopologicalSort(GraphLnk *g);

