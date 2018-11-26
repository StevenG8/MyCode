#include <stdio.h>
#include <stdlib.h>

#define MinNum -10001//哨兵
#define Maxsize 1001 //因为堆的数组0下标是哨兵

typedef int ElementType;
typedef struct MinHeap *MinH;
struct MinHeap{
  ElementType *Data;
  int size;
  int capacity;
};

MinH MinHeapCreate();
int IsEmpty(MinH H);//空的时候返回0
int IsFull(MinH H);
void Insert(MinH H,ElementType X);
//ElementType DeleteMin(MinH H);
void PrintRouteNode(MinH H);

int IsEmpty(MinH H)//空的时候返回0
{
  return H->size;
}

int IsFull(MinH H)//满的时候返回1
{
  return (H->capacity)==(H->size);
}

MinH MinHeapCreate()
{
  MinH H=(MinH)malloc(sizeof(struct MinHeap));
  H->size=0;
  H->Data=(ElementType *)malloc(Maxsize*sizeof(ElementType));
  H->Data[0]=MinNum;//设置哨兵
  H->capacity=Maxsize;
  return H;
}

void Insert(MinH H,ElementType X)
{
  if(IsFull(H)){
    printf("Full!\n");
    return;
  }

  int parent;
  for(parent=++H->size; X < H->Data[parent/2] ;parent/=2){
    H->Data[parent]=H->Data[parent/2];
  }
  H->Data[parent]=X;
}

//ElementType DeleteMin(MinH H)
//{
//  if(!IsEmpty(H)){
//    printf("Empty\n");
//    return H->Data[0];
//  }
//
//  int parent,child;
//  ElementType result=H->Data[1];
//  ElementType DeleteNum=H->Data[H->size--];
//
//  for(parent=1 ; parent*2 < H->size ; parent=child){
//    child=parent*2;
//    if( child!=H->size && H->Data[child+1] < H->Data[child] )
//      child++;
//    if(DeleteNum < H->Data[child])
//      break;
//    else
//      H->Data[parent]=H->Data[child];
//  }
//  H->Data[parent]=DeleteNum;
//
//  return result;
//}

void PrintRouteNode(MinH H,int position)
{
  while(position/2!=0){//执行到其父亲结点是哨兵就停止，也就是在数组下标为1的时候跳出循环
    printf("%d ",H->Data[position]);
    position/=2;
  }
  printf("%d\n",H->Data[position]);
}

int main()
{
  int i;

  //数据输入
  int DataNum,CheckNum;
  scanf("%d %d",&DataNum,&CheckNum);

  ElementType Data[DataNum];
  for(i=0;i<DataNum;i++)
    scanf("%d",&Data[i]);

  int CheckPosition[CheckNum];
  for(i=0;i<CheckNum;i++)
    scanf("%d",&CheckPosition[i]);

  //建立堆
  MinH H=MinHeapCreate();
  for(i=0;i<DataNum;i++){
    Insert(H,Data[i]);
  }

  //输出
  for(i=0;i<CheckNum;i++){
    PrintRouteNode(H,CheckPosition[i]);
  }

  return 0;
}
