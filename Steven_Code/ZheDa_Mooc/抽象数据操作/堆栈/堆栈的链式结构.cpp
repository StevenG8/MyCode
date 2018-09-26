#include <stdio.h>
#include <stdlib.h>
#define Error NULL
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data;
	Stack Next;
};

Stack CreatEmptyStack()
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Next=NULL;
	return S;
} 

int IfEmpty(Stack S)//返回1就是空 
{
	return (S->Next==NULL);
}

//头指针作为保留不做数据存储
//不然栈空的时候被free掉就没了，整个栈都删除了找不到入口 
void Push(Stack PtrS,ELementType X) 
{
	//这里其实就是链表的第二个位置插入 
	Stack FirstCell=CreatEmptyStack();
	FirstCell->Next=PtrS->Next;
	FirstCell->Data=X;
	PtrS->Next=FirstCell;
}

ELementType Pop(Stack PtrS)
{
	//这里其实就是链表的第二个位置的删除 
	if(IfEmpty(PtrS)){
		printf("Error");
		return Error;
	}
	Stack FirstCell=PtrS->Next;
	ELementType CellValue=FirstCell->Data;
	PtrS->Next=FirstCell->Next; 
	free(FirstCell);
	return CellValue;
}

int main()
{
	Stack S=CreatEmptyStack();
	printf("空表为1，非空表为0 %d\n",IfEmpty(S));
	Push(S,0);Push(S,1);Push(S,2);
	
	Stack temp=S;
	temp=temp->Next;
	while(temp!=NULL){
		printf("%d\n",temp->Data);
		temp=temp->Next;
	}	
	
	printf("弹出\n");
	printf("%d\n",Pop(S));
	printf("%d\n",Pop(S));
	printf("%d\n",Pop(S));
	printf("空表为1，非空表为0 %d\n",IfEmpty(S));
	return 0;
}
