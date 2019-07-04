#include"BinTree.h"

//ABC##DE##F##G#H## 以#作为停止标记
void main()
{
	char *VLR = "ABCDEFGH";
	char *LVR = "CBEDFAGH";
    char *LRV = "CEFDBHGA";

	int n=strlen(VLR);

	BinTree myTree;
	initBinTree(&myTree,'#');

	createBinTree_5(&myTree,VLR,LVR,n);

	BinTree yourTree;
	initBinTree(&yourTree,'#');

	createBinTree_6(&yourTree,LVR,LRV,n);

}


/*
void main()
{
	BinTree myTree;
	char *str="ABC##DE##F##G#H##";
	initBinTree(&myTree,'#');
	createBinTree_4(&myTree,str);

	preOrder_1(&myTree);
	printf("\n");
	inOrder_1(&myTree);
	printf("\n");

}
*/

/*
void main()
{
	BinTree myTree;
	char *str="ABC##DE##F##G#H##";
	initBinTree(&myTree,'#');
	createBinTree_4(&myTree,str);
	//createBinTree_2(&myTree);

	preOrder(&myTree);
	printf("\n");
	inOrder(&myTree);
	printf("\n");
	postOrder(&myTree);
	printf("\n");
	levelOrder(&myTree);
	printf("\n");

	printf("size = %d\n",size(&myTree));
	printf("height = %d\n",height(&myTree));
	BinTreeNode *p=search(&myTree,'E');
	BinTreeNode *father=parent(&myTree,p);

	BinTree youTree;
	initBinTree(&youTree,'#');
	copy(&youTree,&myTree);

	binTreeClear(&youTree);
}
*/
