#include"GraphLnk.h"

void main()
{
	GraphLnk gl;
	initGraph(&gl);
	insertVertex(&gl,'A');
	insertVertex(&gl,'B');
	insertVertex(&gl,'C');
	insertVertex(&gl,'D');
	insertVertex(&gl,'E');

	insertEdge(&gl,'A','B');
	insertEdge(&gl,'A','D');
	insertEdge(&gl,'B','C');
	insertEdge(&gl,'B','E');
	insertEdge(&gl,'C','D');
	insertEdge(&gl,'C','E');
	showGraph(&gl);
	
	//removeEdge(&gl,'B','C');
	//removeVertex(&gl,'C');
	//showGraph(&gl);
	
	int v=getFirstNeighbor(&gl,'A');
	v=getNextNeighbor(&gl,'B','C');
	printf("the vertex is %d\n",v);
}