
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

//直接使用原来的节点，那么也就是改变这些节点的指向
//头结点是无法被使用的，因为在后面的输出是要变成NULL
//我们应该申请两个结点把传入的两个链表的头节点拷贝，把它们的后续结点接上，再把原有的那--
//--两个头结点的后续变为NULL
//头节点拿出来之后就很简单了，就是把指针的next改动即可
List Merge(List L1,List L2)
{
  List L;
  List l1=(List)malloc(sizeof(struct Node));
  List l2=(List)malloc(sizeof(struct Node));
  l1->Data=L1->Data;
  l1->Next=L1->Next;
  l2->Data=L2->Data;
  l2->Next=L2->Next;
  L1=NULL;L2=NULL;

  if((l1->Data)<(l2->Data)){
    L=l1;
    l1=l1->Next;
  }
  else if((l2->Data)<(l1->Data)){
    L=l2;
    l2=l2->Next;
  }else{
    L=l1;
    l1=l1->Next;
    l2=l2->Next;
  }

  while(l1&&l2){
    if((l1->Data)<(l2->Data)){
      L->Next=l1;
      l1=l1->Next;
    }else if((l2->Data)<(l1->Data)){
      L->Next=l2;
      l2=l2->Next;
    }else{
      L->Next=l1;
      l1=l1->Next;
      l2=l2->Next;
    }
  }
  for(;l1;l1=l1->Next)
    L->Next=l1;
  for(;l2;l2=l2->Next)
    L->Next=l2;

  return L;
}
