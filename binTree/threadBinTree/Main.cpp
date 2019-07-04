#include"ThreadBinTree.h"

void main()
{
	char *str="ABC##DE##F##G#H##";
	BinTree mytree;
	initBinTree(&mytree,'#');
	createBinTree(&mytree,str);

	createInThread(&mytree);
	
	BinTreeNode *p=first(&mytree);
	
	p=last(&mytree);

	p=search(&mytree,'D');

	p=parent(&mytree,p);

	p=next(&mytree,p);

	p=prior(&mytree,p);

	inOrder(&mytree);


}