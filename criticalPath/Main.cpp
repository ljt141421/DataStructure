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
	insertVertex(&gm,'G');
	insertVertex(&gm,'H');
	insertVertex(&gm,'I');

	insertEdge(&gm,'A','B',6);
	insertEdge(&gm,'A','C',4);
	insertEdge(&gm,'A','D',5);
	insertEdge(&gm,'B','E',1);
	insertEdge(&gm,'C','E',1);
	insertEdge(&gm,'D','F',2);
	insertEdge(&gm,'E','G',9);
	insertEdge(&gm,'E','H',7);
	insertEdge(&gm,'F','H',4);
	insertEdge(&gm,'G','I',2);
	insertEdge(&gm,'H','I',6);

	showGraph(&gm);
	
	criticalPath(&gm);
	
}
