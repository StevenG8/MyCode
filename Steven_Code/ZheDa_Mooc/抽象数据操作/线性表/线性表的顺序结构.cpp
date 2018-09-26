#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10 

typedef int ElementType;
typedef struct LNode* List;
struct LNode{
	ElementType Data[Maxsize];
	int last;//存放线性表中的最后一个元素的下标 
}; 

List MakeEmpty()
{
	List PtrL;
	PtrL=(List)malloc(sizeof(struct LNode));
	//malloc函数是申请一块空间并返回该空间的地址
	PtrL->last=-1;//空表
	return PtrL; 
} 

int FindPosition(ElementType X,List PtrL)
{
	int i=0;
	while(PtrL->last>=i){
		if(PtrL->Data[i]==X)
			break;
		i++;
	}
	if(i>PtrL->last)
		return -1;//没有找到 
	else 
		return i;
}

int Insert(ElementType X,int position,List PtrL)
{
	if(position>PtrL->last||position<0){
		printf("位置不合法\n");
		return -1; 
	}
	if(PtrL->last==Maxsize-1){
		printf("表满\n");
		return -1; 
	} 
	int i;
	//数组插入数值要把从该位置起的全部数字往后挪一位，从最大的下标开始 
	for(i=PtrL->last;i>=position;i--) 
		PtrL->Data[i+1]=PtrL->Data[i];
	PtrL->Data[position]=X;
	PtrL->last++;
	return 1;
} 

int Delete(int position,List PtrL)
{
	if(position>PtrL->last||position<0){
		printf("位置不合法\n");
		return -1;
	}
	int i;
	//数组删除数值要把从该位置起的全部数字往前挪一位，从最小的下标开始 
	for(i=position;i<=PtrL->last;i++)
		PtrL->Data[i]=PtrL->Data[i+1];
	PtrL->last--;
	return 1;
} 

int main()
{
	List L;
	L=MakeEmpty();
	printf("L->last=%d,L->Data[0]=%d\n",L->last,L->Data[0]);

	L->last=0;//使其从空表变为有一个元素的实表 
	Insert(1,0,L);
	Insert(2,1,L);
	Insert(3,2,L);
	printf("L->last=%d,L->Data[0]=%d,L->Data[1]=%d,L->Data[2]=%d,L->Data[3]=%d\n",L->last,L->Data[0],L->Data[1],L->Data[2],L->Data[3]);
	Insert(4,-1,L);//位置不合法 
	printf("元素1的位置为%d\n",FindPosition(1,L));
	Delete(1,L);
	printf("L->last=%d,L->Data[0]=%d,L->Data[1]=%d,L->Data[2]=%d,L->Data[3]=%d\n",L->last,L->Data[0],L->Data[1],L->Data[2],L->Data[3]);
	return 0;
}
