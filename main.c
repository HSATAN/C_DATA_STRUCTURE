#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX_VER_NUM 11//����������
#define MAX_ARC_NUM 22//�ߵ������
typedef char VertexType;
typedef int Status;
typedef struct EdgeInfo
{
    VertexType v1;
    VertexType v2;
    int weight;
}EdgeInfo;
typedef struct ArcBox//������������Ϣ
{
    int iver;
    struct ArcBox *ilink;
    int jver;
    struct ArcBox *jlink;
    int weight;//Ȩֵ
    int mark;
    char *info;
}ArcBox;
typedef struct VerBox//��������������Ϣ
{
    VertexType data;//����ֵ
    ArcBox *firstedge;//ָ���ڽӵ㣨������������Ϣ��
}VerBox;
typedef struct Graph
{
    int vernum;//�����ܸ���
    int arcnum;//�ߵ��ܸ���
    VerBox vertexs[MAX_VER_NUM];//������Ϣ
}Graph;
typedef struct StackData//ջ�пɴ�ŵ�����
{
    VertexType data;
    int lenght;
    struct StackData *pnext;
}StackData;
typedef struct Stack//ջ���ڴ���ѷ��ʹ��Ķ���
{
    struct StackData *ptop;
    struct StackData *pbottom;    
}STNODE;
typedef struct Stack_Arc//�淽�ѷ��ʹ��ı߼�����
{
    ArcBox *p[MAX_ARC_NUM];
    int v_num[MAX_ARC_NUM];
}SANode;
int Visited[MAX_VER_NUM];//��Ƕ����Ƿ񱻷��ʹ�
EdgeInfo Data[MAX_ARC_NUM]={{'A','B',324},{'A','J',419},{'A','K',328},{'A','D',241},{'A','C',556},{'A','F',703},{'A','G',521},{'B','G',391},{'B','H',230},{'B','I',356},{'B','J',220},{'C','F',642},{'C','E',337},{'D','F',829},{'D','K',334},{'E','F',581},{'E','G',1254},{'F','G',887},{'G','H',242},{'H','I',249},{'I','J',713},{'J','K',398}};//�߼�Ȩֵ
int Count=0;//�ǿ��߱ߵ�����
STNODE Stack;//����ѷ��ʹ�
SANode Store_Arc_Ver;//��Ż�����Ϣ��������Ϣ
int LAV=-1,ALL=0;
int Short_Len=1000000,Short_Load=0;//��������·��
void CreateGraph(Graph **G);//����ͼ
int LocateVer(Graph G,VertexType v);//���Ҷ���v��ͼ�е�λ��
void ShowAdjInfo(Graph *G);//�鿴�ڽӵ���Ϣ
int FirstAdjVer(Graph *G,int v,ArcBox **u);//��һ�ڽӵ�
int NextAdjVer(Graph *G,int v,int w,ArcBox **u);//��һ�ڽӵ�
void NAV(ArcBox *p,int *n,int v,int w,ArcBox **u);//�ݹ������һ�ڽӵ�
void InitArcBox_mark(ArcBox *p);//��ʼ��mark��ֵ
void DFSTraverse(Graph *G);//������ȱ���ͼ
void DFST(Graph *G,int v);//���������ȱ���
void InitStack(void);//��ʼ��ջ
void Push(VertexType c);//���ݽ�ջ
void Pop(void);//��ջ
Status IsAdj(int *len,VertexType v);//�ж�ջ���ĵ��Ƿ���AΪ�ڽӵ�
int main()
{
    Graph *G=NULL;
    CreateGraph(&G);
    printf("������ڽӱ�\n");
    ShowAdjInfo(G);printf("\n\n");
    printf("����·�����:\n");
    DFSTraverse(G);printf("\n");
    printf("����·������:%d�������·��Ϊ:·��%d������Ϊ:%d\n\n",ALL,Short_Load,Short_Len);
    return 0;
}
void CreateGraph(Graph **G)//����ͼ
{
    int i,j,k,w;
    char v1,v2;
    ArcBox *pnew;
    (*G)=(Graph *)malloc(1*sizeof(Graph));
    if((*G)==NULL)
    {
        printf("��̬�ڴ����ʧ�ܣ�������ֹ��\n");
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
                printf("��̬�ڴ����ʧ�ܣ�������ֹ��\n");
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
            printf("ע�⣺*****����%c�����ڣ�*****\n",i<0?v1:v2);
        }
    }
    return;
}
int LocateVer(Graph G,VertexType v)//���Ҷ���v��ͼ�е�λ��
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
void ShowAdjInfo(Graph *G)//�鿴�ڽӵ���Ϣ
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
int FirstAdjVer(Graph *G,int v,ArcBox **u)//��һ�ڽӵ�
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
int NextAdjVer(Graph *G,int v,int w,ArcBox **u)//��һ�ڽӵ�
{
    int n=-1;
    ArcBox *p;
    (*u)=NULL;
    p=G->vertexs[v].firstedge;
    NAV(p,&n,v,w,&(*u));
    return n;
 
}
void NAV(ArcBox *p,int *n,int v,int w,ArcBox **u)//�ݹ������һ�ڽӵ�
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
        else printf("��һ�ڽӵ����ݳ������飡\n");
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
void InitArcBox_mark(ArcBox *p)//��ʼ��mark��ֵ
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
void DFSTraverse(Graph *G)//������ȱ���ͼ
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
void DFST(Graph *G,int v)//���������ȱ���
{
    int w=-1,flag=1,i=0,enter=1,len=0;
    ArcBox *u;//�ڽӵ�
    StackData *p;
    Visited[v]=TRUE;
    Count++;
    Push(G->vertexs[v].data);
    if(Count==11&&IsAdj(&len,Stack.ptop->data)==1) 
    {        
        ALL++;
        printf("·��%-2d��",ALL);
        printf("A");
        p=Stack.ptop;
        len=len+p->lenght;
        if(Short_Len>len) Short_Load=ALL,Short_Len=len;        
        while(p!=Stack.pbottom)
        {
            printf("->%c",p->data);
            p=p->pnext;
        }
        printf(" �ܳ���Ϊ��%d",len);
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
    for(LAV;Store_Arc_Ver.v_num[LAV]==v&&LAV>=0;)//��ԭ��ǰ����ߵ�״̬����ջ
    {
        Store_Arc_Ver.p[LAV]->mark=FALSE;
        Store_Arc_Ver.p[LAV]=NULL;
        LAV--;
    }
}
void InitStack(void)//��ʼ��ջ
{
    Stack.pbottom=Stack.ptop=(StackData *)malloc(1*sizeof(StackData));
    Stack.pbottom->pnext=NULL;
    return;
}
void Push(VertexType c)//���ݽ�ջ
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
Status IsAdj(int *len,VertexType v)//�ж���ջ���ĵ��Ƿ���AΪ�ڽӵ�
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
