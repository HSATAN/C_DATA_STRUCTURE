#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
/*
这个模块是构建平衡二叉树 
*/
void initTree(BT *p){
	//初始化树 
	(*p)->data=-1;
	(*p)->left=NULL;
	(*p)->right=NULL;
}
void createBinaryTree(BT *tree,DataType data){
	//向树中插入节点 
	if (*tree==NULL)
	{
		BT initNode=(BT)malloc(sizeof(BT));
		initNode->data=data;
		initNode->left=NULL;
		initNode->right=NULL;
		*tree=initNode;
		return;
	}
	
	BT p=*tree;
	BT pre=*tree;
	while(p){
		pre=p;
		if(data>p->data){
			p=p->right;
		}
		else{
			p=p->left;
		}
		
	}
	BT new=(BT )malloc(sizeof(BT));
	if(data>pre->data){
		new->data=data;
		new->left=NULL;
		new->right=NULL;
		pre->right=new;
		
	}
	else{
		new->data=data;
		new->left=NULL;
		new->right=NULL;
		pre->left=new;
		
	}

}
void addNode (BT *tree){
	//添加数据 
	int data=0;
	scanf("%d",&data);
	while(data !=-1){
		createBinaryTree(*tree,data);
		scanf("%d",&data);
	}
}
void printString(BT tree){
	//先序输出 
	if(tree){
		printf("%d  ",tree->data);
		
		printString(tree->left);
		printString(tree->right);
	}
}
BT findNode(BT tree,DataType data){
	//在二叉排序树中查找 
	if(tree==NULL)
	{
		return NULL;
	}
	if(tree->data==data)
	{
		return tree;
	}
	else if(tree->data>data)
	{
		findNode(tree->right,data);
	}
	else if(tree->data<data)
	{
		findNode(tree->left,data);
	}
}
