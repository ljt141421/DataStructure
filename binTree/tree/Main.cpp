#include"Tree.h"

void main()
{
	char *str = "RAD#E##B#CFG#H#K#####";//将数转为二叉树之后的结构
	Tree tree;
	initTree(&tree,'#');
	createTree(&tree,str);

	TreeNode *r=root(&tree);

	TreeNode *p=find(&tree,'E');
	TreeNode *par=parent(&tree,p);

}