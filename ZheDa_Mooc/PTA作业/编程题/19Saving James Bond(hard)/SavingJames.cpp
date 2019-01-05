#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Maxsize 100
#define radius 7.5
#define SideLength 50
#define Infinity 65535

//公有变量
int range,VertexNum;
bool Visied[Maxsize]={0};
struct Site{
  int x,y;
}XY[Maxsize];

//声明
struct ShortestNode{
  float distance;
  int Vertex;
};

typedef struct LNode *PtrList;
struct LNode{
  int Vertex;
  PtrList next;
};


//快速排序-->结构体升序
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
  //读取数据
  scanf("%d %d",&range,&VertexNum);
  for(int i=0;i<VertexNum;i++){
    scanf("%d %d",&XY[i].x,&XY[i].y);
  }

  PtrList* ListHead=ConnectPoint();//连接鳄鱼点

  //计算第一次跳跃，得到距离按从小到大排序的鳄鱼点
  float distance;
  int AreFirstNodes=0;
  struct ShortestNode FirstNodes[VertexNum]={Infinity,0};//初始化为无穷大
  for(int i=0;i<VertexNum;i++){//遍历所有顶点
    distance=FirstJump( XY[i].x , XY[i].y );
    if(distance<=range)
      FirstNodes[AreFirstNodes++]={distance,i};//记录可以从岛上直接跳上的点
  }
  qsort(FirstNodes,AreFirstNodes,sizeof(struct ShortestNode),compare2keys);
  //对结构体的单个元素进行排序,得到短距离在前的标有鳄鱼下标的点的排序数组

  int MinJumpTimes=Infinity;
  int JumpTimes,FirstJumpNode;
  for(int i=0;i<AreFirstNodes;i++){
    JumpTimes=CountJump(FirstNodes[i].Vertex,ListHead);
    if( JumpTimes < MinJumpTimes ){//如果经过这一个点能跳出且跳跃次数最小
      MinJumpTimes = JumpTimes;
      FirstJumpNode = Node[i].Vertex;
    }
  }

  FindWay(FirstJumpNode);

  return 0;
}
