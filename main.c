
#include<stdlib.h>
#include<stdio.h>
#include"tree.h"


int main(){
	BT  tree=NULL;
	//tree=(BT*)malloc(sizeof(BT));
	//	tree->data=11;
	//	tree->left=NULL;
	//	tree->right=NULL;
//	createBinaryTree(&tree,10);
//	printString(tree);
//	addNode (&tree);
//	printString(tree);
//	BT node=findNode(tree,11);
//	if (node)
//	{
//		printf("\n≤È’“≥…π¶");
//	 } 
	init_adj();
	print_tree();
	return 0;
	
}
