#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */
List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
	L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

// 函数的参数全部都是形参,就算是传入指针,也只是传入其地址
// 只能通过地址去修改值的大小,修改链表的顺序
List Merge(List L1,List L2)
{
  List L=(List)malloc(sizeof(struct Node));
  List PtrL1,PtrL2,PtrL;
  PtrL=L;
  PtrL1=L1->Next;
  PtrL2=L2->Next;//原链表带头节点
  while(PtrL1&&PtrL2){
    if((PtrL1->Data)<=(PtrL2->Data)){
      PtrL->Next=PtrL1;
      PtrL1=PtrL1->Next;
      PtrL=PtrL->Next;
    }else{
      PtrL->Next=PtrL2;
      PtrL2=PtrL2->Next;
      PtrL=PtrL->Next;
    }
  }
  PtrL->Next=PtrL1?PtrL1:PtrL2;
  //跳出while循环就只有一个链表完了,另外一个链表还存在且是有顺序的！
  L1->Next=NULL;//带头节点的链表，如此就完成了“空表”
  L2->Next=NULL;
  return L;
}

List Read()
{
  int size;
  scanf("%d",&size);
  if(size==0){
  	printf("Error!");
  	return NULL;
  }

  List Node,Head,temp;
  Head=Node=(List)malloc(sizeof(struct Node));
  while(size--){
  	temp=(List)malloc(sizeof(struct Node));
    scanf("%d",&temp->Data);
    Node->Next=temp;
    Node=Node->Next;
  }
  Node->Next=NULL;
  return Head;
}

void Print(List L)
{
  while(L){
    printf("%d ",L->Data);
    L=L->Next;
  }
  printf("\n");
}
