#include"GraphMtx.h"

void main()
{
	GraphMtx gm;
	initGraph(&gm);
	insertVertex(&gm,'A');
	insertVertex(&gm,'B');
	insertVertex(&gm,'C');
	insertVertex(&gm,'D');
	insertVertex(&gm,'E');

	insertEdge(&gm,'A','B',10);
	insertEdge(&gm,'A','D',30);
	insertEdge(&gm,'A','E',100);
	insertEdge(&gm,'B','C',50);
	insertEdge(&gm,'C','E',10);
	insertEdge(&gm,'D','C',20);
	insertEdge(&gm,'D','E',60);
	showGraph(&gm);
	
	int n=gm.numVertices;

	E *dist=(E*)malloc(sizeof(E)*n);
	int *path=(int*)malloc(sizeof(int)*n);
	assert(dist!=NULL && path!=NULL);

	shortestPath(&gm,'A',dist,path);
	

	
}
