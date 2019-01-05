#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Maxsize 100
#define radius 7.5
#define SideLength 50
#define Infinity 65535

//���б���
int range,VertexNum;
bool Visied[Maxsize]={0};
struct Site{
  int x,y;
}XY[Maxsize];

//����
struct ShortestNode{
  float distance;
  int Vertex;
};

typedef struct LNode *PtrList;
struct LNode{
  int Vertex;
  PtrList next;
};


//��������-->�ṹ������
int compare2keys(const void *a,const void *b)
{
  int k=0;
  if((const struct ShortestNode *)a->distance > (const struct ShortestNode *)b->distance )
    k=1;
  else if( (const struct ShortestNode *)a->distance < (const struct ShortestNode *)b->distance )
    k=-1;
  return k;
}

float FirstJump(int x,int y)
{
  float distance=sqrt(pow(x,2)+pow(y,2));
  return distance-radius;
}

bool IsConnect(int i,int j)
{
  float distance=sqrt( pow( (XY[i].x-XY[j].x),2) +pow((XY[i].y-XY[j].y),2) );
  return distance<=range;
}

PtrList* ConnectPoint()
{
  int i,j;
  PtrList TempNode;
  PtrList *ListHead=(PtrList *)malloc(VertexNum*sizeof(PtrList));
  for(i=0;i<VertexNum;i++){
    ListHead[i]=(PtrList)malloc(sizeof(struct LNode));
    ListHead[i]->next = NULL;
    ListHead[i]->Vertex = i;
  }

  for(i=0;i<VertexNum;i++){
    for(j=0 ; j!=i&&j<VertexNum ; j++){
      If( IsConnect(i,j) ){
        TempNode=(PtrList)malloc(sizeof(struct LNode));
        TempNode->Vertex =j;
        TempNode->next = ListHead[i];
        ListHead[i]->next=TempNode;
        TempNode=(PtrList)malloc(sizeof(struct LNode));
        TempNode->Vertex =i;
        TempNode->next = ListHead[j];
        ListHead[j]->next=TempNode;
      }
    }
  }

  return ListHead;
}

int CountJump(int V,PtrList ListHead[])
{
  if(IsSafe(V)) return 0;
  
  PtrList TempNode;
  int i,circuit,CircuitNum,TempNum;
  Queue Q=CreateQueue();

  circuit=CircuitNum=1;
  EnQueue(V,Q);

  while( !IsEmpty(Q) ){

    for(i=0;i<CircuitNum;i++){
      V=DeQueue(Q);
      for(TempNode=ListHead[V];TempNode->Vertex != V;TempNode=TempNode->next){
        if(!Visited[TempNode-Vertex]){
          if(IsSafe(TempNode->Vertex))
            return circuit;
          EnQueue(TempNode->Vertex);
          TempNum++;
        }
      }
    }
    CircuitNum=TempNum;
    circuit++;
  }

  return ERROR;
}

void ResetVisied()
{
  for(int i=0;i<VertexNum;i++){
    Visied[i]=false;
  }
}

int main()
{
  //��ȡ����
  scanf("%d %d",&range,&VertexNum);
  for(int i=0;i<VertexNum;i++){
    scanf("%d %d",&XY[i].x,&XY[i].y);
  }

  PtrList* ListHead=ConnectPoint();//���������

  //�����һ����Ծ���õ����밴��С��������������
  float distance;
  int AreFirstNodes=0;
  struct ShortestNode FirstNodes[VertexNum]={Infinity,0};//��ʼ��Ϊ�����
  for(int i=0;i<VertexNum;i++){//�������ж���
    distance=FirstJump( XY[i].x , XY[i].y );
    if(distance<=range)
      FirstNodes[AreFirstNodes++]={distance,i};//��¼���Դӵ���ֱ�����ϵĵ�
  }
  qsort(FirstNodes,AreFirstNodes,sizeof(struct ShortestNode),compare2keys);
  //�Խṹ��ĵ���Ԫ�ؽ�������,�õ��̾�����ǰ�ı��������±�ĵ����������

  int MinJumpTimes=Infinity;
  int JumpTimes,FirstJumpNode;
  for(int i=0;i<AreFirstNodes;i++){
    JumpTimes=CountJump(FirstNodes[i].Vertex,ListHead);
    if( JumpTimes < MinJumpTimes ){//���������һ��������������Ծ������С
      MinJumpTimes = JumpTimes;
      FirstJumpNode = Node[i].Vertex;
    }
  }

  FindWay(FirstJumpNode);

  return 0;
}
