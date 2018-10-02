//rear指针指向的是队列数组中当前第一个无效元素的下标
//front指针指向的是队列数组中当前第一个有效元素的下标
typedef int ELementType;
typedef int Position;
struct QNode{
  ELementType *Data;
  Position Front,Rear;
  int Maxsize;
}
typedef struct QNode* Queue;

//创建空队列
Queue CreateQueue(int Maxsize)
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->Data=(ELementType*)malloc(sizeof(MaxSize*ELementType))
  Q->Front=Q->Rear=0;
  Q->Maxsize=Maxsize;
  return Q;
}

bool IsFull(Queue Q)
{
  return ((Q->Rear+1)%(Q->Maxsize)==Q->Front);
}

bool AddQ(Queue Q,ELementType X)
{
  if(IsFull(Q)){
    printf("队列已满\n");
    return flase;
  }else{
    Q->Rear=(Q->Rear+1)%(Q->MaxSize);
    Q->Data[Q->Rear]=X;
  }
}

bool ELementType DeleteQ(Queue PtrQ)
{
  
}
