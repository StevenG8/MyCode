#include <stdio.h>
#include <stdlib.h>


/**********���е�����************/
typedef struct Qnode *QNode ;
struct Qnode{
  int v;
  QNode next;
};

typedef struct queue *Queue ;
struct queue{
  QNode head;
  QNode rear;
};


/********���к���*********/
Queue CreateQueue()
{
  Queue Q=(Queue)malloc(sizeof(struct queue));
  Q->head=Q->rear=NULL;
  return Q;
}

bool IsEmpty(Queue Q)
{
  return (Q->head)==NULL;
}

void InQueue(int Vertex,Queue Q)
{
  if(IsEmpty(Q)){
    Q->head = (QNode)malloc(sizeof(struct Qnode));
    Q->head->v = Vertex;
    Q->head->next = NULL;
    Q->rear = Q->head;
  }
  else{
    QNode QN= (QNode)malloc(sizeof(struct Qnode));
    QN->v = Vertex;
    QN->next = NULL;
    Q->rear->next=QN;
    Q->rear=QN;
  }
}

int DeQueue(Queue Q)
{
  int Vertex=Q->head->v;
  QNode QN=Q->head;
  if(Q->head == Q->rear)
    Q->head = Q->rear = NULL;
  else{
    Q->head = Q->head->next;
  }
  free(QN);
  return Vertex;
}



/**********ͼ������************/
typedef struct ENode *Edge ;//��
struct ENode{
  int v1;
  int v2;
};

typedef struct Lnode *LNode ;//����Ԫ��
struct Lnode{
  int v;
  LNode next;
};

typedef struct GNode *LGraph ;//ͼ
struct GNode{
  int v;
  int e;
  LNode *Node;//��ͷ,�±��ʾ�ڼ����ˣ�����Ԫ�ر�ʾ��ʶ����
};

/********ͼ����*********/
LGraph CreateGraph(int people,int connect)
{
  LGraph graph=(LGraph)malloc(sizeof(struct GNode));
  graph->v=people;
  graph->e=connect;
  graph->Node=(LNode *)malloc(people*sizeof(LNode));//ָ�����������
  for(int i=1;i<people;i++){
  	graph->Node[i] = (LNode)malloc(sizeof(struct Lnode));//ָ�������е�ÿ��Ԫ�ص�����
    graph->Node[i]->v = i;//��ͷ����
	  graph->Node[i]->next = NULL;
  }
  return graph;
}

void InsertEdge(LGraph graph,Edge E)
{//����ͼ
//  printf("������\n");
  LNode Cell=(LNode)malloc(sizeof(struct Lnode));
  Cell->v = E->v2;
  Cell->next = graph->Node[E->v1];
  graph->Node[E->v1] = Cell;

  Cell=(LNode)malloc(sizeof(struct Lnode));
  Cell->v = E->v1;
  Cell->next = graph->Node[E->v2];
  graph->Node[E->v2] = Cell;
}



int BFS(int Vertex,LGraph graph,bool *Visited)
{

  Visited[Vertex]=true;//��ʾ����ѷ���

  LNode LN;
  int TotalNum,CirculateNum,TempNum,layer;

  TotalNum=layer=0;//��ʶ���������˼ʽ�������
  CirculateNum=1;//��ʼֻ���Լ�һ������Ȧ
  Queue Q=CreateQueue();//���ɿն���
  InQueue(Vertex,Q);

  while( !IsEmpty(Q) && layer<6 ){

//	printf("����%d��ı���\n",layer+1);
    TempNum=0;//��¼��ǰ���ж��ٸ����

    for(int i=0;i<CirculateNum;i++){//�Ե�ǰ�Ľ���Ȧ��һ�㣩��ȫ����

      Vertex=DeQueue(Q);
      LN = graph->Node[Vertex];

      while( LN->v != Vertex  ){//����ʶ����
    		if( !Visited[LN->v] ){
    		  Visited [LN->v]=true;
    		  TempNum++;
          InQueue(LN->v,Q);//����ʶ������ӱ�־��������
    		}
		    LN=LN->next;
      }

    }

    layer++;//��һ�������Ͻ�����һ��
    CirculateNum=TempNum;//��һ��Ҫ��������ô��������ܽ�ȥ��һ��
    TotalNum=TotalNum+CirculateNum;//ȫ����ʶ������
//    printf("��һ����ʶ��%d��\n",CirculateNum);
//    printf("�ܹ���ʶ��%d��\n",TotalNum);

  }

  return TotalNum;
}



int main()
{
  int people,connect;
  scanf("%d %d",&people,&connect);
  bool Visited[people+1]={0};    // +1��Ϊ�˸�����ͳһ��1��ʼ,�����ѭ��ȫ����1��ʼ
  LGraph graph=CreateGraph(people+1,connect);
//  printf("��ʼ��ͼ���\n");

  if(connect!=0){
    Edge E=(Edge)malloc(sizeof(struct ENode));
    for(int i=0;i<connect;i++){
      scanf("%d %d",&E->v1,&E->v2);
      InsertEdge(graph,E);
    }
    free(E);//�ͷű߽��ռ�
  }

  int num;
  for(int i=1;i<people+1;i++){
    num=BFS(i,graph,Visited);
    printf("%d: %.2f%%\n",i,(num+1)/people*100.0);
    for(int i=1;i<people+1;i++){//���ѷ��ʵı�־ȥ��
	    Visited[i]=false;
	  }
  }

  return 0;
}
