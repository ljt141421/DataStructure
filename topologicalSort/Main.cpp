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

	insertEdge(&gl,'A','B');
	insertEdge(&gl,'A','C');
	insertEdge(&gl,'A','D');
	insertEdge(&gl,'C','B');
	insertEdge(&gl,'C','E');
	insertEdge(&gl,'D','E');
	insertEdge(&gl,'F','D');
	insertEdge(&gl,'F','E');
	showGraph(&gl);
	
	TopologicalSort(&gl);
	
}