/*
����Ӧ���Ƕ��г����˶δ�����Ϊ����һ���ɹ��İ汾�ҳ����ü��׵������滻����ɹ���
������֣������������Ҳ��װ10�����ݣ��ɹ��İ汾�ļ�������Ҳ��װʮ�����ݡ�
������������һ������ѭ�����еĺ��������֤����������ǿ������е�,������װʮ������
*/

//�ܽ᣺�ܲ��ø��ӵ����ݽṹ�Ͳ��ã�����

#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10
#define ERROR -1

bool Visited[Maxsize]={false};//����ͼ�ķ��ʱ�־

/***********************����****************************/
typedef struct QNode *Queue;
struct QNode{
  int Data[Maxsize+1];
  int head;
  int rear;//rear��end,Ҳ����βָ�뵫�����ָ��ָ��ĵط����޸�ֵ�ڵȴ���ֵ��
};

Queue CreateQueue()
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->head = Q->rear =0;//��ǰͷ��β���±�
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
  if(Q->rear == Maxsize){//���������β��,Ҫ��ͷ��ʼ
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
  if(Q->head == Maxsize){//���������β��,Ҫ��ͷ��ʼ
    ReturnVal=Q->Data[Maxsize];
    Q->head=0;
  }else{
    ReturnVal=Q->Data[Q->head++];
  }
  return ReturnVal;
}


/***********************ͼ****************************/

typedef struct ENode *Edge;
struct ENode{
  int V1,V2;
};

typedef struct GNode *MGraph;
struct GNode{
  int Nv;
  int Ne;
  bool G[Maxsize][Maxsize];//�ڽӾ���,true��ʾ��ͨ,false��ʾ�Ͽ�
};

void InsertEdge(Edge E,MGraph graph)
{//����ͼ
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
      graph->G[i][j]=false;//Ĭ��ȫ�����ǲ���ͨ
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
      if( !Visited[W] && graph->G[Vertex][W]){//δ�����ʲ���������ͨ
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

  EnQueue(2,Q);//��������ȷ��
  DeQueue(Q);
  printf("Q->head=%d\n",Q->head);
  EnQueue(1,Q);
  printf("Q->rear=%d\n",Q->rear);

  for(int i=0;i<10;i++){
  	DeQueue(Q);
  	printf("Q->head=%d\n",Q->head);
  }

  DeQueue(Q);//��������ȷ��

  printf("�պÿ���װ10��\n");
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
