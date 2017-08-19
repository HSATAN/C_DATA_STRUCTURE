#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX_VER_NUM 11//顶点的最大数
#define MAX_ARC_NUM 22//边的最大数
typedef char VertexType;
typedef int Status;
typedef struct EdgeInfo
{
    VertexType v1;
    VertexType v2;
    int weight;
}EdgeInfo;
typedef struct ArcBox//边所包含的信息
{
    int iver;
    struct ArcBox *ilink;
    int jver;
    struct ArcBox *jlink;
    int weight;//权值
    int mark;
    char *info;
}ArcBox;
typedef struct VerBox//顶点所包含的信息
{
    VertexType data;//顶点值
    ArcBox *firstedge;//指向邻接点（边所包含的信息）
}VerBox;
typedef struct Graph
{
    int vernum;//顶点总个数
    int arcnum;//边的总个数
    VerBox vertexs[MAX_VER_NUM];//顶点信息
}Graph;
typedef struct StackData//栈中可存放的数据
{
    VertexType data;
    int lenght;
    struct StackData *pnext;
}StackData;
typedef struct Stack//栈用于存放已访问过的顶点
{
    struct StackData *ptop;
    struct StackData *pbottom;    
}STNODE;
typedef struct Stack_Arc//存方已访问过的边及顶点
{
    ArcBox *p[MAX_ARC_NUM];
    int v_num[MAX_ARC_NUM];
}SANode;
int Visited[MAX_VER_NUM];//标记顶点是否被访问过
EdgeInfo Data[MAX_ARC_NUM]={{'A','B',324},{'A','J',419},{'A','K',328},{'A','D',241},{'A','C',556},{'A','F',703},{'A','G',521},{'B','G',391},{'B','H',230},{'B','I',356},{'B','J',220},{'C','F',642},{'C','E',337},{'D','F',829},{'D','K',334},{'E','F',581},{'E','G',1254},{'F','G',887},{'G','H',242},{'H','I',249},{'I','J',713},{'J','K',398}};//边及权值
int Count=0;//记可走边的总数
STNODE Stack;//存放已访问过
SANode Store_Arc_Ver;//存放弧的信息及顶点信息
int LAV=-1,ALL=0;
int Short_Len=1000000,Short_Load=0;//存放最断最路经
void CreateGraph(Graph **G);//创建图
int LocateVer(Graph G,VertexType v);//查找顶点v在图中的位置
void ShowAdjInfo(Graph *G);//查看邻接点信息
int FirstAdjVer(Graph *G,int v,ArcBox **u);//第一邻接点
int NextAdjVer(Graph *G,int v,int w,ArcBox **u);//下一邻接点
void NAV(ArcBox *p,int *n,int v,int w,ArcBox **u);//递归查找下一邻接点
void InitArcBox_mark(ArcBox *p);//初始化mark的值
void DFSTraverse(Graph *G);//深度优先遍历图
void DFST(Graph *G,int v);//剃归深度优先遍历
void InitStack(void);//初始化栈
void Push(VertexType c);//数据进栈
void Pop(void);//出栈
Status IsAdj(int *len,VertexType v);//判断栈顶的点是否与A为邻接点
int main()
{
    Graph *G=NULL;
    CreateGraph(&G);
    printf("顶点的邻接表：\n");
    ShowAdjInfo(G);printf("\n\n");
    printf("可走路径结果:\n");
    DFSTraverse(G);printf("\n");
    printf("可走路径总数:%d条；最短路径为:路径%d，长度为:%d\n\n",ALL,Short_Load,Short_Len);
    return 0;
}
void CreateGraph(Graph **G)//创建图
{
    int i,j,k,w;
    char v1,v2;
    ArcBox *pnew;
    (*G)=(Graph *)malloc(1*sizeof(Graph));
    if((*G)==NULL)
    {
        printf("动态内存分配失败，程序终止！\n");
        exit(-1);
    }
    (*G)->arcnum=MAX_ARC_NUM;
    (*G)->vernum=MAX_VER_NUM;
    for(i=0;i<(*G)->vernum;i++)
    {
        (*G)->vertexs[i].data='A'+i;
        (*G)->vertexs[i].firstedge=NULL;
    }
    for(k=0;k<(*G)->arcnum;k++)
    {
        v1=Data[k].v1;
        v2=Data[k].v2;
        w=Data[k].weight;
        i=LocateVer((**G),v1);
        j=LocateVer((**G),v2);
        if(i>=0&&j>=0)
        {
            pnew=(ArcBox *)malloc(1*sizeof(ArcBox));
            if(pnew==NULL)
            {
                printf("动态内存分配失败，程序终止！\n");
                exit(-1);
            }            
            pnew->iver=i;
            pnew->jver=j;
            pnew->weight=w;
            pnew->mark=FALSE;
            pnew->ilink=(*G)->vertexs[i].firstedge;
            pnew->jlink=(*G)->vertexs[j].firstedge;
            (*G)->vertexs[i].firstedge=pnew;
            (*G)->vertexs[j].firstedge=pnew;
        }
        else
        {
            printf("注意：*****顶点%c不存在！*****\n",i<0?v1:v2);
        }
    }
    return;
}
int LocateVer(Graph G,VertexType v)//查找顶点v在图中的位置
{
    int i,result=-1;
    for(i=0;i<MAX_VER_NUM;i++)
    {
        if(G.vertexs[i].data==v)
        {
            result=i;
            break;        
        }
    }
    return result;
}
void ShowAdjInfo(Graph *G)//查看邻接点信息
{
    int v,w;
    ArcBox *u;
    for(v=0;v<G->vernum;v++)
    {
        printf("[%d|%c]",v,G->vertexs[v].data);
        for(w=FirstAdjVer(G,v,&u);w>=0;w=NextAdjVer(G,v,w,&u))
        {
            printf("->[%d|%c|%d]",w,G->vertexs[w].data,u->weight);
        }
        InitArcBox_mark(G->vertexs[v].firstedge);
        printf("\n");
    }
}
int FirstAdjVer(Graph *G,int v,ArcBox **u)//第一邻接点
{
    int w=-1;
    ArcBox *p;
    p=G->vertexs[v].firstedge;
    (*u)=p;
    if(v==p->iver)
    {
        w=p->jver;
        p->mark=TRUE;
    }
    else if(v==p->jver)
    {
        w=p->iver;
        p->mark=TRUE;
    }
    return w;
}
int NextAdjVer(Graph *G,int v,int w,ArcBox **u)//下一邻接点
{
    int n=-1;
    ArcBox *p;
    (*u)=NULL;
    p=G->vertexs[v].firstedge;
    NAV(p,&n,v,w,&(*u));
    return n;
 
}
void NAV(ArcBox *p,int *n,int v,int w,ArcBox **u)//递归查找下一邻接点
{
    if(p->mark==FALSE && (p->iver==v ||p->jver==v))
    {
        (*u)=p;
        if(p->iver==v)
        {
            *n=p->jver;p->mark=TRUE;
        }
        else if(p->jver==v)
        {
            *n=p->iver;p->mark=TRUE;
        }
        else printf("下一邻接点数据出错，请检查！\n");
    }
    else
    {
        if(p->ilink!=NULL && *n==-1)
        {
            NAV(p->ilink,n,v,w,&(*u));
        }
        if(p->jlink!=NULL && *n==-1)
        {
            NAV(p->jlink,n,v,w,&(*u));
        }
    }
    return;
}
void InitArcBox_mark(ArcBox *p)//初始化mark的值
{
    p->mark=FALSE;
    if(p->ilink!=NULL)
    {
        InitArcBox_mark(p->ilink);
    }
    if(p->jlink!=NULL)
    {
        InitArcBox_mark(p->jlink);
    }
    return;
}
void DFSTraverse(Graph *G)//深度优先遍历图
{
    int v;
    for(v=0;v<G->vernum;v++)
    {
        Visited[v]=FALSE;
        InitArcBox_mark(G->vertexs[v].firstedge);
    }
    InitStack();
    DFST(G,0);        
    return;
}
void DFST(Graph *G,int v)//剃归深度优先遍历
{
    int w=-1,flag=1,i=0,enter=1,len=0;
    ArcBox *u;//邻接点
    StackData *p;
    Visited[v]=TRUE;
    Count++;
    Push(G->vertexs[v].data);
    if(Count==11&&IsAdj(&len,Stack.ptop->data)==1) 
    {        
        ALL++;
        printf("路径%-2d：",ALL);
        printf("A");
        p=Stack.ptop;
        len=len+p->lenght;
        if(Short_Len>len) Short_Load=ALL,Short_Len=len;        
        while(p!=Stack.pbottom)
        {
            printf("->%c",p->data);
            p=p->pnext;
        }
        printf(" 总长度为：%d",len);
        printf("\n");
    }
    for(w=FirstAdjVer(G,v,&u);w>=0;w=NextAdjVer(G,v,w,&u))
    {
        enter=1;
        for(i=0;i<=LAV;i++)
        {
            if(Store_Arc_Ver.p[i]==u)
            {
                enter=0;
                break;
            }
        }
        if(enter==1)
        {
            Store_Arc_Ver.p[++LAV]=u;
            Store_Arc_Ver.v_num[LAV]=v;
        }
        if(Visited[w]==FALSE)
        {    
            DFST(G,w);
            Visited[w]=FALSE;
            Count--;
            Pop();
        }
    }
    for(LAV;Store_Arc_Ver.v_num[LAV]==v&&LAV>=0;)//还原当前顶点边的状态并出栈
    {
        Store_Arc_Ver.p[LAV]->mark=FALSE;
        Store_Arc_Ver.p[LAV]=NULL;
        LAV--;
    }
}
void InitStack(void)//初始化栈
{
    Stack.pbottom=Stack.ptop=(StackData *)malloc(1*sizeof(StackData));
    Stack.pbottom->pnext=NULL;
    return;
}
void Push(VertexType c)//数据进栈
{
    StackData *pnew;
    char v1,v2;
    int i;
    pnew=(StackData *)malloc(1*sizeof(StackData));
    pnew->data=c;
    if(c=='A')
    {
        pnew->lenght=0;
    }
    else
    {
        v1=c;
        v2=Stack.ptop->data;
        for(i=0;i<MAX_ARC_NUM;i++)
        {
            if((v1==Data[i].v1 || v1==Data[i].v2) && (v2==Data[i].v1 || v2==Data[i].v2))
            {    
                pnew->lenght=Stack.ptop->lenght+Data[i].weight;
            }
        }
    }
    pnew->pnext=Stack.ptop;
    Stack.ptop=pnew;
    return;
}
void Pop(void)
{
    StackData *p;
    p=Stack.ptop;
    Stack.ptop=p->pnext;
    free(p);
}
Status IsAdj(int *len,VertexType v)//判断是栈顶的点是否与A为邻接点
{
    int i;
    for(i=0;i<MAX_ARC_NUM;i++)
    {
        if((Data[i].v1==v&&Data[i].v2=='A')||(Data[i].v1=='A'&&Data[i].v2==v))
        {
            *len=Data[i].weight;
            return TRUE;
            break;
        }
    }
        system("pause");
    return FALSE;
}
