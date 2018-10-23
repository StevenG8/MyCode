#include <stdio.h>
#include <stdlib.h>

#define Maxsize 10
#define Null -1
typedef int child;
typedef int ElementType;

/*��������*/
struct TreeNode{
  child left;
  child right;
};
//ȫ�ֱ���
struct TreeNode T[Maxsize];

/*���ĺ���*/
int BuildTree()
{
  int num,root;
  scanf("%d",&num);
  if(num){
    int i,j;
    int check[num];
    char tl,tr;
    for(j=0;j<num;j++) check[j]=0;
    for(i=0;i<num;i++){
      scanf(" %c %c",&tl,&tr);
      if(tl!='-'){
        T[i].left=tl-'0';
        check[T[i].left]=1;
      }else
        T[i].left=Null;
      if(tr!='-'){
        T[i].right=tr-'0';
        check[T[i].right]=1;
      }else
        T[i].right=Null;
    }
    for(j=0;j<num;j++)
	  if(check[j]==0) break;
    root=j;
	return root;
  }else return Null;
}



//���е�����
typedef struct Node* PtrToNode;
typedef struct Node* Position;
struct Node{
  ElementType Data;
  PtrToNode Next;
};

typedef struct QNode* Queue;
struct QNode{
  Position Front,Rear;
};

/*���еĺ���*/
int IsEmpty(Queue Q)
{
  return (Q->Front==NULL);
}

ElementType DeleteQ(Queue Q)
{
  Position TmpCell;
  ElementType TmpElem;
  if(IsEmpty(Q)){
    printf("���п�");
    return;
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




void FindLeaves(int root)
{
  int i=0;
  ElementType temp;
  Queue Q=MakeEmptyQueue();
  AddQ(Q,root);
  while(!IsEmpty(Q)){
    temp=DeleteQ(Q);
    if(T[temp].left!=Null)  AddQ(Q,T[temp].left);
    if(T[temp].right!=Null) AddQ(Q,T[temp].right);
    if((T[temp].left==Null)&&(T[temp].right==Null)){
      if(i)
        printf(" ");
      printf("%d",temp);
      i=1;
    }
  }
}

int main()
{
  int root;
  root=BuildTree();
  FindLeaves(root);  
  return 0;
}


//���������û������ģ�����û�а취���������������������
//void FindLeaves(int root)
//{
//  //��׼
//  if((T[root].left==Null)&&(T[root].right==Null)){
//    printf("%d ",root);
//    return ;
//  }
//
//  if((T[root].left!=Null)&&(T[root].right!=Null)){
//    FindLeaves(T[root].left);
//    FindLeaves(T[root].right);
//  }
//  if(T[root].left==Null){
//    FindLeaves(T[root].right);
//  }
//  if(T[root].right==Null){
//    FindLeaves(T[root].left);
//  }
//}
