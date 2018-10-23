typedef struct Node* PtrToNode;
typedef struct Node* Position;
struct Node{
  ElementType Data;
  PtrToNode Next;
};

typedef struct QNode* Queue;
struct QNode{
  Position Front,Rear;
  int Maxsize;
};

/*队列的函数*/
int IsEmpty(Queue Q)
{
  return (Q->Front==NULL);
}

ElementType DeleteQ(Queue Q)
{
  Position TmpCell;
  ElementType TmpElem;
  if(IsEmpty(Q)){
    printf("队列空");
    return Error;
  }else{
    TmpCell=Q->Front;
    if(Q->Front==Q->Rear)
      Q->Front=Q->Rear=NULL;
    else
      Q->Front=Q->Front->Next;
    TmpElem=TmpCell->Data;
    free(TmpCell);
    return TmpElem;
  }
}

void AddQ(Queue Q,ElementType X)
{
  PtrToNode TmpCell=(PtrToNode)malloc(sizeof(struct Node));
  TmpCell->Data=X;
  TmpCell->Next=NULL;
  if(Q->Front==NULL){
    Q->Front=Q->Rear=TmpCell;
    (Q->Rear)->Next=NULL;
  }
  else{
    (Q->Rear)->Next=TmpCell;
    Q->Rear=(Q->Rear)->Next;
  }
}

Queue MakeEmptyQueue()
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->Front=Q->Rear=NULL;
  return Q;
}
