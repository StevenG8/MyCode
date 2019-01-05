/*
这里应该是队列出现了段错误，因为在另一个成功的版本我尝试用简易的数组替换结果成功了
但很奇怪，这个队列数组也是装10个数据，成功的版本的简易数组也是装十个数据。
而我特意做了一个测试循环队列的函数，结果证明这个队列是可以运行的,就是能装十个数据
*/

//总结：能不用复杂的数据结构就不用！！！

#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10
#define ERROR -1

bool Visited[Maxsize]={false};//定义图的访问标志

/***********************队列****************************/
typedef struct QNode *Queue;
struct QNode{
  int Data[Maxsize+1];
  int head;
  int rear;//rear是end,也就是尾指针但是这个指针指向的地方是无赋值在等待赋值的
};

Queue CreateQueue()
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->head = Q->rear =0;//当前头和尾的下标
}

bool IsEmpty(Queue Q)
{
  return Q->head == Q->rear;
}

bool IsFull(Queue Q)
{
  return (Q->rear+1)%(Maxsize+1)==Q->head;
}

void EnQueue(int Vertex,Queue Q)
{
  if(IsFull(Q)){
    printf("ERROR\n");
    return;
  }
  if(Q->rear == Maxsize){//队列数组的尾巴,要从头开始
    Q->Data[Maxsize]=Vertex;
    Q->rear=0;
  }else{
    Q->Data[Q->rear++]=Vertex;
  }
}

int DeQueue(Queue Q)
{
  int ReturnVal;
  if(IsEmpty(Q)){
    printf("ERROR\n");
    return ERROR;
  }
  if(Q->head == Maxsize){//队列数组的尾巴,要从头开始
    ReturnVal=Q->Data[Maxsize];
    Q->head=0;
  }else{
    ReturnVal=Q->Data[Q->head++];
  }
  return ReturnVal;
}


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
  int W;
  Visited[Vertex]=true;

  Queue Q=CreateQueue();
  EnQueue(Vertex,Q);
  printf("{ ");

  while( !IsEmpty(Q) ){
    Vertex=DeQueue(Q);
    printf("%d ",Vertex);
    for(W=0;W<Maxsize;W++){
      if( !Visited[W] && graph->G[Vertex][W]){//未被访问并且两者相通
        Visited[W]=true;
    		EnQueue(W,Q);
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

void TestQueue()
{
  Queue Q=CreateQueue();

  for(int i=0;i<10;i++){
	EnQueue(1,Q);
	printf("Q->rear=%d\n",Q->rear);
  }

  EnQueue(2,Q);//报错是正确的
  DeQueue(Q);
  printf("Q->head=%d\n",Q->head);
  EnQueue(1,Q);
  printf("Q->rear=%d\n",Q->rear);

  for(int i=0;i<10;i++){
  	DeQueue(Q);
  	printf("Q->head=%d\n",Q->head);
  }

  DeQueue(Q);//报错是正确的

  printf("刚好可以装10个\n");
}

int main()
{
//  TestQueue();

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
