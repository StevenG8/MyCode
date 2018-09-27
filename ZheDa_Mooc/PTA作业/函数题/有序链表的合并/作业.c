
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* ϸ���ڴ˲��� */
void Print( List L ); /* ϸ���ڴ˲������������NULL */

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

//ֱ��ʹ��ԭ���Ľڵ㣬��ôҲ���Ǹı���Щ�ڵ��ָ��
//ͷ������޷���ʹ�õģ���Ϊ�ں���������Ҫ���NULL
//����Ӧ�������������Ѵ�������������ͷ�ڵ㿽���������ǵĺ��������ϣ��ٰ�ԭ�е���--
//--����ͷ���ĺ�����ΪNULL
//ͷ�ڵ��ó���֮��ͺܼ��ˣ����ǰ�ָ���next�Ķ�����
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
