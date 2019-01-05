#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10
#define ERROR -1

bool Visited[Maxsize]={false};//定义图的访问标志



/***********************图****************************/

typedef struct ENode *Edge;
struct ENode{
  int V1,V2;
};

typedef struct GNode *MGraph;
struct GNode{
  int Nv;
  int Ne;
  bool G[Maxsize][Maxsize];//邻接矩阵,true表示联通,false表示断开
};

void InsertEdge(Edge E,MGraph graph)
{//无向图
  graph->G[E->V1][E->V2]=true;
  graph->G[E->V2][E->V1]=true;
}

MGraph CreateGraph(int VertexNum,int EdgeNum)
{
  MGraph graph=(MGraph)malloc(sizeof(struct GNode));
  graph->Nv = VertexNum;
  graph->Ne = EdgeNum;
  for(int i=0;i<Maxsize;i++){
    for(int j=0;j<Maxsize;j++){
      graph->G[i][j]=false;//默认全部都是不连通
    }
  }
  return graph;
}

MGraph BuildGraph(int VertexNum,int EdgeNum)
{
  MGraph graph=CreateGraph(VertexNum,EdgeNum);
  if(EdgeNum){
    Edge E=(Edge)malloc(sizeof(struct ENode));
    for(int i=0;i<EdgeNum;i++){
      scanf("%d %d",&E->V1,&E->V2);
      InsertEdge(E,graph);
    }
  }
  return graph;
}

void DFS(MGraph graph,int Vertex)
{
  int W;
  Visited[Vertex]=true;
  printf("%d ",Vertex);

  for(W=0;W<Maxsize;W++){
    if( !Visited[W] && graph->G[Vertex][W] ){
      DFS(graph,W);
    }
  }
}

void BFS(MGraph graph,int Vertex)
{
  int W,head,rear;
  head=rear=0;
  int Queue[10];
  Visited[Vertex]=true;

  Queue[rear++]=Vertex;
  printf("{ ");

  while( head!=rear ){
    Vertex=Queue[head++];
    printf("%d ",Vertex);
    for(W=0;W<Maxsize;W++){
      if( !Visited[W] && graph->G[Vertex][W]){//未被访问并且两者相通
        Visited[W]=true;
	      Queue[rear++]=W;
      }
    }
  }

  printf("}\n");
}

void ResetVisited()
{
  for(int i=0;i<Maxsize;i++)
    Visited[i]=false;
}

int main()
{
  int VertexNum,EdgeNum;
  scanf("%d %d",&VertexNum,&EdgeNum);
  MGraph graph=BuildGraph(VertexNum,EdgeNum);

  for(int Vertex=0;Vertex<VertexNum;Vertex++){
    if(Visited[Vertex]==false){
      printf("{ ");
      DFS(graph,Vertex);
      printf("}\n");
	}
  }

  ResetVisited();

  for(int Vertex=0;Vertex<VertexNum;Vertex++){
  	if(Visited[Vertex]==false)
	  BFS(graph,Vertex);
  }

  return 0;
}
