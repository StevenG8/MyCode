#include <stdio.h>
#include <stdlib.h>

#define Maxsize 100
#define Infinity 65535

typedef int WeightType;

typedef struct ENode *Edge;
struct ENode{
  int v1,v2;
  WeightType weight;
};

typedef struct GNode *MGraph;
struct GNode{
  int Nv,Ne;
  int **Dist;
  // int path[Maxsize][Maxsize];
};

void InsertEdge(Edge E,MGraph graph)
{//无向图
  graph->Dist[E->v1][E->v2] = E->weight;
  graph->Dist[E->v2][E->v1] = E->weight;
}

MGraph CreateGraph(int VertexNum,int EdgeNum)
{
  MGraph graph=(MGraph)malloc(sizeof(struct GNode));
  graph->Nv=VertexNum;
  graph->Ne=EdgeNum;

  //二维数组申请
  graph->Dist=(int **)malloc(VertexNum*sizeof(int *));
  for(int i=0;i<VertexNum;i++){
    graph->Dist[i]=(int *)malloc(VertexNum*sizeof(int));
  }
  //二维数组初始化
  for(int i=0;i<VertexNum;i++){
    for(int j=0;j<VertexNum;j++){
      graph->Dist[i][j]=Infinity;//默认无穷大断开
    }
  }

  if(EdgeNum!=0){
    Edge E=(Edge)malloc(sizeof(struct ENode));
    for(int Edge=0;Edge<EdgeNum;Edge++){
      scanf("%d %d %d",&E->v1,&E->v2,&E->weight);
      E->v1--;E->v2--;//编号是从1开始，而邻接矩阵是从0开始
      InsertEdge(E,graph);
    }
    free(E);
  }
  return graph;
}

void Floyd(MGraph graph,WeightType *D)
{
  int i,j,k;
  int size=graph->Nv;
  for(i=0;i<graph->Nv;i++){
    for(j=0;j<graph->Nv;j++){
      D[i*size+j] = graph->Dist[i][j];
      //虽然传入的是二维数组，但是维度却是确定的，那就是顶点数
    }
  }

  for(k=0;k<graph->Nv;k++){
    for(i=0;i<graph->Nv;i++){
      for(j=0;j<graph->Nv;j++){
        if(D[i*size+k]+D[k*size+j] < D[i*size+j]){
          D[i*size+j] = D[i*size+k]+D[k*size+j];
          // path[i][j]=k;
          // if(i==j && D[i*size+j]<0)//负值圈
          //   return false;//算法错误，不能出现负值
        }
      }
    }
  }

}

int main()
{
  bool flag=1;
  int VertexNum,EdgeNum;
  scanf("%d %d",&VertexNum,&EdgeNum);
  if(VertexNum==1)  flag=0;//只有一只动物，出错

  MGraph graph=CreateGraph(VertexNum,EdgeNum);
  WeightType D[VertexNum][VertexNum];
  Floyd(graph,&D[0][0]);//找出各个源到其他点的距离

  //找出各个源中的最大的距离，比较各个源中的最大距离找出最小的距离
  int number,MaxDist;
  int MinDist=Infinity;
  for(int i=0;i<VertexNum;i++){
    MaxDist=0;
    for(int j=0;j<VertexNum;j++){//找各源中的最大值
      if(i!=j && D[i][j]>MaxDist)
        MaxDist=D[i][j];
      if(MaxDist==Infinity){//存在另外一个独立的联通集，出错
      	flag=0;
        break;
	    }
    }
    if(MinDist>MaxDist){//找源间的最小值
      MinDist=MaxDist;
      number=Vertex+1;
    }
  }

  if(flag)
  	printf("%d %d",number,MinDist);
  else
    printf("0\n");

  return 0;
}
