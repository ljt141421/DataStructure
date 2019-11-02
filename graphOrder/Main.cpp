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
	insertVertex(&gl,'F');
	insertVertex(&gl,'G');
	insertVertex(&gl,'H');

	insertEdge(&gl,'A','B');
	insertEdge(&gl,'A','C');
	insertEdge(&gl,'B','D');
	insertEdge(&gl,'B','E');
	insertEdge(&gl,'D','H');
	insertEdge(&gl,'E','H');
	insertEdge(&gl,'C','F');
	insertEdge(&gl,'C','G');
	insertEdge(&gl,'F','G');
	showGraph(&gl);
	
	//removeEdge(&gl,'B','C');
	//removeVertex(&gl,'C');
	//showGraph(&gl);
	
	//int v=getFirstNeighbor(&gl,'A');
	//v=getNextNeighbor(&gl,'B','C');
	//printf("the vertex is %d\n",v);
	DFS(&gl,'A');
	printf("Nul.\n");

	BFS(&gl,'A');
	printf("Nul.\n");

	components(&gl);
	printf("Nul.\n");

	destoryGraph(&gl);
}