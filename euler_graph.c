#include<stdio.h>
#include<stdlib.h>
/*
��fleury���������㷨����ŷ����· 
  Fleury�㷨��
   ��ȡv0��V(G)����P0=v0��
��Pi=v0e1v1e2��ei vi�Ѿ��б飬�����淽������ѡȡei+1��
��a��ei+1��vi�������
��b�������ޱ�ı߿ɹ��б飬����ei+1��Ӧ��ΪGi=G-{e1,e2, ��, ei}�е��ţ���ν����һ��ɾ����ʹ��ͨͼ������ͨ�ıߣ���
��c������b�������ٽ���ʱ���㷨ֹͣ�� 
*/
#define N 2 //������� 
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
	//�����ڽӱ� 
	int i=0;
	while(i<N)
	{
		adj[i].data=-1;
		int data=0;
		printf("������� %d ���ڵ�ĳ���: ",i);
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
			//��������� 
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
 	//����ڽӱ� 
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
