#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef int Position;
struct QNode{
  ElementType *Data;
  Position Front,Rear;
  int Maxsize;
};
typedef struct QNode* Queue;
//rear指针指向的是队列数组中当前第一个无效元素的下标
//front指针指向的是队列数组中当前第一个有效元素的下标

//创建空队列
Queue CreateQueue(int Maxsize)
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->Data=(ElementType*)malloc(Maxsize*sizeof(ElementType));
  Q->Front=Q->Rear=0;
  Q->Maxsize=Maxsize;
  return Q;
}

//这里空出数组的一个位置，不然front==rear的时候既可能空也可能满
int IsFull(Queue Q)
{
  return ((Q->Rear+1)%(Q->Maxsize)==Q->Front);
}
int AddQ(Queue Q,ElementType X)
{
  if(IsFull(Q)){
    printf("队列已满\n");
    return 0;
  }else{
    Q->Rear=(Q->Rear+1)%(Q->Maxsize);
    Q->Data[Q->Rear]=X;
    return 1;
  }
}

int IsEmpty(Queue Q)
{
  return (Q->Front==Q->Rear);
}

int DeleteQ(Queue Q)
{
  if(IsEmpty(Q)){
    printf("队列空");
    return 0;
  }else{
    Q->Front=(Q->Front+1)%(Q->Maxsize);
    return Q->Data[Q->Front];
  }
}
