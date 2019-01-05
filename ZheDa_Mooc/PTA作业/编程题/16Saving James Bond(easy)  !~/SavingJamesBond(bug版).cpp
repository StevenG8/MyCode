#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define radius 7.5
#define SideLength 50

//结构体声明，指针声明
typedef int Vertex;//顶点下标
typedef int WeightType;

typedef struct CoordinateNode{//坐标
  int x,y;
}Coordinate;

typedef struct ENode *Edge;//边
struct ENode{
  Vertex v1,v2;
  WeightType weight;
};

typedef struct AdjVNode *PtrToAdjVNode;//结点的邻接点(边上的点)
struct AdjVNode{
  Vertex v;
  WeightType weight;
  PtrToAdjVNode next;
};

typedef struct VNode{//表头
  PtrToAdjVNode FirstEdge;
  Coordinate XY;//顶点数据
}AdjList;

typedef struct GNode *LGraph;//图
struct GNode{
  int nv,ne;
  AdjList *VList;
};


//定义全局变量
bool flag=0;
bool Visited[101]={0};


/******************函数******************/

LGraph CreateGraph(Vertex V,Coordinate Site[])//建立初始化图
{
  LGraph graph=(LGraph)malloc(sizeof(struct GNode));
  graph->nv=V;
  graph->ne=0;
  //申请表头的邻接表,注意还有一个原点坐标
  graph->VList=(AdjList*)malloc( V * sizeof(struct VNode));

  for(int i=0;i<V;i++){//结点初始化
    graph->VList[i].FirstEdge=NULL;
    graph->VList[i].XY=Site[i];//赋予初始坐标
  }

  return graph;
}

void InsertEdge(Edge E,LGraph graph)
{
  PtrToAdjVNode temp = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
  temp->v = E->v2;
  temp->weight = E->weight;
  temp->next = graph->VList[E->v1].FirstEdge;
  graph->VList[E->v1].FirstEdge = temp;

  //无向图
  temp = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
  temp->v = E->v1;
  temp->weight = E->weight;
  temp->next = graph->VList[E->v2].FirstEdge;
  graph->VList[E->v2].FirstEdge = temp;

}

//计算两条鳄鱼点之间的距离
float CalculateDistance(int x1,int y1,int x2,int y2)
{
  float distance = sqrt( pow(x2-x1,2)+pow(y2-y1,2) );
  return distance;
}

//计算岛屿到鳄鱼的距离（因为岛屿是一块地而不是一个点）
float FirstStep(int x,int y)
{
  float distance=sqrt( pow(x,2)+pow(y,2) );
  distance=distance-radius;
  return distance;
}

void BuildGraph(LGraph graph,Coordinate Site[],int DotNum,int range)
{
  int i,j;
  float distance;
  Edge E=(Edge)malloc(sizeof(struct ENode));

  //岛到鳄鱼的联通
  for(i=1;i<DotNum;i++){
    distance=FirstStep(Site[i].x,Site[i].y);
    if(distance<=range){//可以从岛上直接跳到鳄鱼身上
	  E->v1=0;
      E->v2=i;
      E->weight=(WeightType)distance;
      InsertEdge(E,graph);
    }
  }

  //鳄鱼之间的连通
  for(i=1;i<DotNum;i++){
    if( (Site[i].x)!=0 && (Site[i].y)!=0 ){//不是异常点才进行检查联通
      for(j=i+1;j<DotNum;j++){//遍历每个鳄鱼结点建立联系
          distance=CalculateDistance(Site[i].x, Site[i].y, Site[j].x, Site[j].y);
          if(distance<range){
            E->v1=i;
            E->v2=j;
            E->weight=(WeightType)distance;
            InsertEdge(E,graph);
    //        printf("在%d与%d之间建立边\n",i,j);
          }
      }
    }
  }
}

bool JudgeJump(int x,int y,int range)
{
  int absx=abs(x);
  int absy=abs(y);
  return ((absx+range)>=SideLength) || ((absy+range)>=SideLength);
}

void DFS(LGraph graph,Vertex V,int range)//V是从哪个顶点出发
{
  if( JudgeJump(graph->VList[V].XY.x, graph->VList[V].XY.y, range) ){//计算该鳄鱼点是否可以直接跳到岸上
  	flag=1;//该点可以直接跳到岸上
  	return;
  }

  Visited[V]=true;//这个顶点已经搜索过了。如果是可以通，则每一个遍历到该顶点都可通；不可通，则每一个遍历到该顶点都不可通
  PtrToAdjVNode W = graph->VList[V].FirstEdge;//V这个顶点所连接的第一个结点

  while(W != NULL){//对该顶点的每一条边（每一个邻接点）进行深搜
  	if(Visited[W->v] != true)//如果该邻接点不曾被访问过,访问该邻接点；同时防止了回访这样的死循环。
      DFS(graph,W->v,range);
    if(flag==1)//找到点可以直接跳到岸上，结束搜索
      break;
  	W=W->next;//下一个邻接点
  }
}



int main()
{
  int Vnum,range;
  scanf("%d %d",&Vnum,&range);

  Coordinate XY[Vnum+1];//横坐标和纵坐标,加上一个原点坐标
  XY[0].x=0;//规定零点坐标
  XY[0].y=0;
  for(int i=1;i<Vnum+1;i++){//读取除零点外的坐标
    scanf("%d %d",&XY[i].x,&XY[i].y);
  }

  LGraph graph=CreateGraph(Vnum+1,XY);//建立初始化图
  BuildGraph(graph,XY,Vnum+1,range);//建立图的连接
  DFS(graph,0,range);//从岛屿出发开始跳到鳄鱼上

  if(flag==1)	  printf("Yes\n");
  else 			  printf("No\n");

  return 0;
}
