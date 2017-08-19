#include<stdio.h>
#include<stdlib.h>
/*
用fleury（弗罗来算法）找欧拉回路 
  Fleury算法：
   任取v0∈V(G)，令P0=v0；
设Pi=v0e1v1e2…ei vi已经行遍，按下面方法从中选取ei+1：
（a）ei+1与vi相关联；
（b）除非无别的边可供行遍，否则ei+1不应该为Gi=G-{e1,e2, …, ei}中的桥（所谓桥是一条删除后使连通图不再连通的边）；
（c）当（b）不能再进行时，算法停止。 
*/
#define N 2 //矩阵的行 
typedef struct DataNode
{
	struct DataNode *next;
	int data;
}DN;
typedef struct HeadNode
{
	struct DataNode * first;
	int degree;
	int data;
}HD;
HD adj[N]; 
void init_adj()
{
	//生成邻接表 
	int i=0;
	while(i<N)
	{
		adj[i].data=-1;
		int data=0;
		printf("请输入第 %d 个节点的出度: ",i);
		scanf("%d",&data);
		
		if (data>0)
		{
			
			adj[i].degree=data;
			adj[i].first=NULL;
		}
		else
		{
			i++;
			continue;
		}
		int j=0;
		while(j<data)
		{
			//输入表数据 
			DN *dn=(DN*)malloc(sizeof(DN*));
			
			int node_data=0;
			scanf("%d",&node_data);
			dn->data=node_data;
			dn->next=adj[i].first;
			adj[i].first=dn;
			j++;
		}
		//scanf("%d",&data);
	
		i++;
	}
 } 
 
 void print_tree()
 {
 	//输出邻接表 
 	int i=0;
 	while(i<N)
 	{
 		DN *p=adj[i].first;
 		while(p)
 		{
 			printf(" %d",p->data);
 			p=p->next;
		 }
 		
 		i++;
	 }
  } 
