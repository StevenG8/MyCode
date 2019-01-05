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
{//����ͼ
  graph->Dist[E->v1][E->v2] = E->weight;
  graph->Dist[E->v2][E->v1] = E->weight;
}

MGraph CreateGraph(int VertexNum,int EdgeNum)
{
  MGraph graph=(MGraph)malloc(sizeof(struct GNode));
  graph->Nv=VertexNum;
  graph->Ne=EdgeNum;

  //��ά��������
  graph->Dist=(int **)malloc(VertexNum*sizeof(int *));
  for(int i=0;i<VertexNum;i++){
    graph->Dist[i]=(int *)malloc(VertexNum*sizeof(int));
  }
  //��ά�����ʼ��
  for(int i=0;i<VertexNum;i++){
    for(int j=0;j<VertexNum;j++){
      graph->Dist[i][j]=Infinity;//Ĭ�������Ͽ�
    }
  }

  if(EdgeNum!=0){
    Edge E=(Edge)malloc(sizeof(struct ENode));
    for(int Edge=0;Edge<EdgeNum;Edge++){
      scanf("%d %d %d",&E->v1,&E->v2,&E->weight);
      E->v1--;E->v2--;//����Ǵ�1��ʼ�����ڽӾ����Ǵ�0��ʼ
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
      //��Ȼ������Ƕ�ά���飬����ά��ȴ��ȷ���ģ��Ǿ��Ƕ�����
    }
  }

  for(k=0;k<graph->Nv;k++){
    for(i=0;i<graph->Nv;i++){
      for(j=0;j<graph->Nv;j++){
        if(D[i*size+k]+D[k*size+j] < D[i*size+j]){
          D[i*size+j] = D[i*size+k]+D[k*size+j];
          // path[i][j]=k;
          // if(i==j && D[i*size+j]<0)//��ֵȦ
          //   return false;//�㷨���󣬲��ܳ��ָ�ֵ
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
  if(VertexNum==1)  flag=0;//ֻ��һֻ�������

  MGraph graph=CreateGraph(VertexNum,EdgeNum);
  WeightType D[VertexNum][VertexNum];
  Floyd(graph,&D[0][0]);//�ҳ�����Դ��������ľ���

  //�ҳ�����Դ�е����ľ��룬�Ƚϸ���Դ�е��������ҳ���С�ľ���
  int number,MaxDist;
  int MinDist=Infinity;
  for(int i=0;i<VertexNum;i++){
    MaxDist=0;
    for(int j=0;j<VertexNum;j++){//�Ҹ�Դ�е����ֵ
      if(i!=j && D[i][j]>MaxDist)
        MaxDist=D[i][j];
      if(MaxDist==Infinity){//��������һ����������ͨ��������
      	flag=0;
        break;
	    }
    }
    if(MinDist>MaxDist){//��Դ�����Сֵ
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
