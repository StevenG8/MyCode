#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define radius 7.5
#define SideLength 50

//�ṹ��������ָ������
typedef int Vertex;//�����±�
typedef int WeightType;

typedef struct CoordinateNode{//����
  int x,y;
}Coordinate;

typedef struct ENode *Edge;//��
struct ENode{
  Vertex v1,v2;
  WeightType weight;
};

typedef struct AdjVNode *PtrToAdjVNode;//�����ڽӵ�(���ϵĵ�)
struct AdjVNode{
  Vertex v;
  WeightType weight;
  PtrToAdjVNode next;
};

typedef struct VNode{//��ͷ
  PtrToAdjVNode FirstEdge;
  Coordinate XY;//��������
}AdjList;

typedef struct GNode *LGraph;//ͼ
struct GNode{
  int nv,ne;
  AdjList *VList;
};


//����ȫ�ֱ���
bool flag=0;
bool Visited[101]={0};


/******************����******************/

LGraph CreateGraph(Vertex V,Coordinate Site[])//������ʼ��ͼ
{
  LGraph graph=(LGraph)malloc(sizeof(struct GNode));
  graph->nv=V;
  graph->ne=0;
  //�����ͷ���ڽӱ�,ע�⻹��һ��ԭ������
  graph->VList=(AdjList*)malloc( V * sizeof(struct VNode));

  for(int i=0;i<V;i++){//����ʼ��
    graph->VList[i].FirstEdge=NULL;
    graph->VList[i].XY=Site[i];//�����ʼ����
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

  //����ͼ
  temp = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
  temp->v = E->v1;
  temp->weight = E->weight;
  temp->next = graph->VList[E->v2].FirstEdge;
  graph->VList[E->v2].FirstEdge = temp;

}

//�������������֮��ľ���
float CalculateDistance(int x1,int y1,int x2,int y2)
{
  float distance = sqrt( pow(x2-x1,2)+pow(y2-y1,2) );
  return distance;
}

//���㵺�쵽����ľ��루��Ϊ������һ��ض�����һ���㣩
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

  //�����������ͨ
  for(i=1;i<DotNum;i++){
    distance=FirstStep(Site[i].x,Site[i].y);
    if(distance<=range){//���Դӵ���ֱ��������������
	  E->v1=0;
      E->v2=i;
      E->weight=(WeightType)distance;
      InsertEdge(E,graph);
    }
  }

  //����֮�����ͨ
  for(i=1;i<DotNum;i++){
    if( (Site[i].x)!=0 && (Site[i].y)!=0 ){//�����쳣��Ž��м����ͨ
      for(j=i+1;j<DotNum;j++){//����ÿ�������㽨����ϵ
          distance=CalculateDistance(Site[i].x, Site[i].y, Site[j].x, Site[j].y);
          if(distance<range){
            E->v1=i;
            E->v2=j;
            E->weight=(WeightType)distance;
            InsertEdge(E,graph);
    //        printf("��%d��%d֮�佨����\n",i,j);
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

void DFS(LGraph graph,Vertex V,int range)//V�Ǵ��ĸ��������
{
  if( JudgeJump(graph->VList[V].XY.x, graph->VList[V].XY.y, range) ){//�����������Ƿ����ֱ����������
  	flag=1;//�õ����ֱ����������
  	return;
  }

  Visited[V]=true;//��������Ѿ��������ˡ�����ǿ���ͨ����ÿһ���������ö��㶼��ͨ������ͨ����ÿһ���������ö��㶼����ͨ
  PtrToAdjVNode W = graph->VList[V].FirstEdge;//V������������ӵĵ�һ�����

  while(W != NULL){//�Ըö����ÿһ���ߣ�ÿһ���ڽӵ㣩��������
  	if(Visited[W->v] != true)//������ڽӵ㲻�������ʹ�,���ʸ��ڽӵ㣻ͬʱ��ֹ�˻ط���������ѭ����
      DFS(graph,W->v,range);
    if(flag==1)//�ҵ������ֱ���������ϣ���������
      break;
  	W=W->next;//��һ���ڽӵ�
  }
}



int main()
{
  int Vnum,range;
  scanf("%d %d",&Vnum,&range);

  Coordinate XY[Vnum+1];//�������������,����һ��ԭ������
  XY[0].x=0;//�涨�������
  XY[0].y=0;
  for(int i=1;i<Vnum+1;i++){//��ȡ������������
    scanf("%d %d",&XY[i].x,&XY[i].y);
  }

  LGraph graph=CreateGraph(Vnum+1,XY);//������ʼ��ͼ
  BuildGraph(graph,XY,Vnum+1,range);//����ͼ������
  DFS(graph,0,range);//�ӵ��������ʼ����������

  if(flag==1)	  printf("Yes\n");
  else 			  printf("No\n");

  return 0;
}
