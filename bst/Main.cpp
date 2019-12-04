#include"BST.H"

void main()
{	
	T ar[] = {45,12,53,3,37,100,24,61,90,78};
	int n=sizeof(ar)/sizeof(int);
	BST bs;
	initBSTree(&bs);
	for(int i=0;i<n;++i)
	{
		insertBSTree(&bs,ar[i]);
	}
	
	T min=Min(&bs);
	T max=Max(&bs);
	printf("min=%d,max=%d\n",min,max);
	Sort(&bs);
	printf("\n");
	removeBST(&bs,12);

	Sort(&bs);
	printf("\n");
}