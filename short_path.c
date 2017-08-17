#include<stdio.h>
#include<stdlib.h>

#define N 4
#define MAX 999999
#define MIN 0
typedef struct Map{
	int map[N][N];
}AdjMap;

typedef struct maxmin{
	int max;
	int min;
} MAXMIN;
AdjMap map;

void initMap() {
	map.map[0][1]=2;
map.map[0][2]=6;
map.map[0][3]=4;
map.map[1][0]=-1;
map.map[1][1]=0;
map.map[1][2]=3;
map.map[1][3]=-1;
map.map[2][0]=7;
map.map[2][1]=-1;
map.map[2][2]=0;
map.map[2][3]=1;
map.map[3][0]=5;
map.map[3][1]=-1;
map.map[3][2]=12;
map.map[3][3]=0;
}


MAXMIN max(AdjMap);
void multi_short_path();


int main(){
	initMap();
	int i=0,j=0;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++){
		if(i==j){
			map.map[i][j]=0;
		}
	}
	for(i=0;i<N;i++)
	for(j=0;j<N;j++){
		
		printf("%d ",map.map[i][j]);
		if ((j+1)%N==0 && j>0)
			printf("\n");
	}
	MAXMIN max_min=max(map) ;
	printf("min=%d  max=%d \n",max_min.min,max_min.max);
	multi_short_path();
	for(i=0;i<N;i++)
	for(j=0;j<N;j++){
		
		printf("%d ",map.map[i][j]);
		if ((j+1)%N==0 && j>0)
			printf("\n");
	}
	return 0;
}
MAXMIN max(AdjMap map){
	/*
	这个函数找出图中的最大值和最小值 
	返回一个包含最大值和最小值的结构体 
	*/
	int i=0,j=0;
	int max=MIN;
	int min=MAX;
	for (i=0;i<N;i++)
	for (j=0;j<N;j++){
		if (map.map[i][j]>max){
			max=map.map[i][j];
		}
		if (map.map[i][j]<min && map.map[i][j]>0){
			min=map.map[i][j];
		}
	
	}
	
	MAXMIN temp;
	temp.max=max;
	temp.min=min;
	
	return temp;
}

void multi_short_path(){
	int i=0,j=0,k=0;
	for(k=0;k<N;k++)
	for (i=0;i<N;i++)
	for (j=0;j<N;j++){
		if (map.map[i][k]>=0 && map.map[k][j]>=0)
		if (map.map[i][k]+map.map[k][j]<map.map[i][j] || map.map[i][j]==-1){
			map.map[i][j]=map.map[i][k]+map.map[k][j];
					}
	}
}

