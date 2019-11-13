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
	insertVertex(&gm,'F');

	insertEdge(&gm,'A','B',6);
	insertEdge(&gm,'A','C',1);
	insertEdge(&gm,'A','D',5);
	insertEdge(&gm,'B','C',5);
	insertEdge(&gm,'B','E',3);
	insertEdge(&gm,'C','D',5);
	insertEdge(&gm,'C','E',6);
	insertEdge(&gm,'C','F',4);
	insertEdge(&gm,'D','F',2);
	insertEdge(&gm,'E','F',6);
	showGraph(&gm);

	MinSpanTree_Prim(&gm,'E');

	/*
	int p=getFirstNeighbor(&gm,'D');
	printf("%d \n",p);

	int q=getNextNeighbor(&gm,'D','C');
	printf("%d \n",q);

	removeEdge(&gm,'B','C');
	showGraph(&gm);

	removeVertex(&gm,'C');
	showGraph(&gm);
	destoryGraph(&gm);
	*/
}
