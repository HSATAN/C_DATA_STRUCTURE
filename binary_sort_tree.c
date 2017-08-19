#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
/*
���ģ���ǹ���ƽ������� 
*/
void initTree(BT *p){
	//��ʼ���� 
	(*p)->data=-1;
	(*p)->left=NULL;
	(*p)->right=NULL;
}
void createBinaryTree(BT *tree,DataType data){
	//�����в���ڵ� 
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
	//������� 
	int data=0;
	scanf("%d",&data);
	while(data !=-1){
		createBinaryTree(*tree,data);
		scanf("%d",&data);
	}
}
void printString(BT tree){
	//������� 
	if(tree){
		printf("%d  ",tree->data);
		
		printString(tree->left);
		printString(tree->right);
	}
}
BT findNode(BT tree,DataType data){
	//�ڶ����������в��� 
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
