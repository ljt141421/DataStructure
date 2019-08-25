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

	insertEdge(&gm,'A','B');
	insertEdge(&gm,'A','D');
	insertEdge(&gm,'B','C');
	insertEdge(&gm,'B','E');
	insertEdge(&gm,'C','E');
	insertEdge(&gm,'C','D');
	showGraph(&gm);

	int p=getFirstNeighbor(&gm,'D');
	printf("%d \n",p);

	int q=getNextNeighbor(&gm,'D','C');
	printf("%d \n",q);

	removeEdge(&gm,'B','C');
	showGraph(&gm);

	removeVertex(&gm,'C');
	showGraph(&gm);

	destoryGraph(&gm);
}
