//rearָ��ָ����Ƕ��������е�ǰ��һ����ЧԪ�ص��±�
//frontָ��ָ����Ƕ��������е�ǰ��һ����ЧԪ�ص��±�
typedef int ELementType;
typedef int Position;
struct QNode{
  ELementType *Data;
  Position Front,Rear;
  int Maxsize;
}
typedef struct QNode* Queue;

//�����ն���
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
    printf("��������\n");
    return flase;
  }else{
    Q->Rear=(Q->Rear+1)%(Q->MaxSize);
    Q->Data[Q->Rear]=X;
  }
}

bool ELementType DeleteQ(Queue PtrQ)
{
  
}
