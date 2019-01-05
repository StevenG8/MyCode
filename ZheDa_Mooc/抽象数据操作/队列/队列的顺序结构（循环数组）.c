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
//rearָ��ָ����Ƕ��������е�ǰ��һ����ЧԪ�ص��±�
//frontָ��ָ����Ƕ��������е�ǰ��һ����ЧԪ�ص��±�

//�����ն���
Queue CreateQueue(int Maxsize)
{
  Queue Q=(Queue)malloc(sizeof(struct QNode));
  Q->Data=(ElementType*)malloc(Maxsize*sizeof(ElementType));
  Q->Front=Q->Rear=0;
  Q->Maxsize=Maxsize;
  return Q;
}

//����ճ������һ��λ�ã���Ȼfront==rear��ʱ��ȿ��ܿ�Ҳ������
int IsFull(Queue Q)
{
  return ((Q->Rear+1)%(Q->Maxsize)==Q->Front);
}
int AddQ(Queue Q,ElementType X)
{
  if(IsFull(Q)){
    printf("��������\n");
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
    printf("���п�");
    return 0;
  }else{
    Q->Front=(Q->Front+1)%(Q->Maxsize);
    return Q->Data[Q->Front];
  }
}



/**********�Լ�д��**************/
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
