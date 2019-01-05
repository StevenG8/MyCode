#include <stdio.h>
#include <stdlib.h>


/**********队列的声明************/
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


/********队列函数*********/
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



/**********图的声明************/
typedef struct ENode *Edge ;//边
struct ENode{
  int v1;
  int v2;
};

typedef struct Lnode *LNode ;//链表元素
struct Lnode{
  int v;
  LNode next;
};

typedef struct GNode *LGraph ;//图
struct GNode{
  int v;
  int e;
  LNode *Node;//表头,下标表示第几个人，链表元素表示认识的人
};

/********图函数*********/
LGraph CreateGraph(int people,int connect)
{
  LGraph graph=(LGraph)malloc(sizeof(struct GNode));
  graph->v=people;
  graph->e=connect;
  graph->Node=(LNode *)malloc(people*sizeof(LNode));//指针的数组申请
  for(int i=1;i<people;i++){
  	graph->Node[i] = (LNode)malloc(sizeof(struct Lnode));//指针数组中的每个元素的申请
    graph->Node[i]->v = i;//表头自身
	  graph->Node[i]->next = NULL;
  }
  return graph;
}

void InsertEdge(LGraph graph,Edge E)
{//无向图
//  printf("建立边\n");
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

  Visited[Vertex]=true;//标示结点已访问

  LNode LN;
  int TotalNum,CirculateNum,TempNum,layer;

  TotalNum=layer=0;//认识的人数和人际交往层数
  CirculateNum=1;//初始只有自己一个交际圈
  Queue Q=CreateQueue();//生成空队列
  InQueue(Vertex,Q);

  while( !IsEmpty(Q) && layer<6 ){

//	printf("进入%d层的遍历\n",layer+1);
    TempNum=0;//记录当前层有多少个结点

    for(int i=0;i<CirculateNum;i++){//对当前的交际圈（一层）的全遍历

      Vertex=DeQueue(Q);
      LN = graph->Node[Vertex];

      while( LN->v != Vertex  ){//是认识的人
    		if( !Visited[LN->v] ){
    		  Visited [LN->v]=true;
    		  TempNum++;
          InQueue(LN->v,Q);//不认识的人添加标志并且入列
    		}
		    LN=LN->next;
      }

    }

    layer++;//这一层遍历完毕进入下一层
    CirculateNum=TempNum;//下一层要遍历够这么多个结点才能进去下一层
    TotalNum=TotalNum+CirculateNum;//全部认识的人数
//    printf("这一层认识了%d人\n",CirculateNum);
//    printf("总共认识了%d人\n",TotalNum);

  }

  return TotalNum;
}



int main()
{
  int people,connect;
  scanf("%d %d",&people,&connect);
  bool Visited[people+1]={0};    // +1是为了跟数据统一从1开始,后面的循环全部从1开始
  LGraph graph=CreateGraph(people+1,connect);
//  printf("初始化图完毕\n");

  if(connect!=0){
    Edge E=(Edge)malloc(sizeof(struct ENode));
    for(int i=0;i<connect;i++){
      scanf("%d %d",&E->v1,&E->v2);
      InsertEdge(graph,E);
    }
    free(E);//释放边结点空间
  }

  int num;
  for(int i=1;i<people+1;i++){
    num=BFS(i,graph,Visited);
    printf("%d: %.2f%%\n",i,(num+1)/people*100.0);
    for(int i=1;i<people+1;i++){//将已访问的标志去掉
	    Visited[i]=false;
	  }
  }

  return 0;
}
