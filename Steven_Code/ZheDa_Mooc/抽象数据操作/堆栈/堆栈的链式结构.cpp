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

int IfEmpty(Stack S)//����1���ǿ� 
{
	return (S->Next==NULL);
}

//ͷָ����Ϊ�����������ݴ洢
//��Ȼջ�յ�ʱ��free����û�ˣ�����ջ��ɾ�����Ҳ������ 
void Push(Stack PtrS,ELementType X) 
{
	//������ʵ��������ĵڶ���λ�ò��� 
	Stack FirstCell=CreatEmptyStack();
	FirstCell->Next=PtrS->Next;
	FirstCell->Data=X;
	PtrS->Next=FirstCell;
}

ELementType Pop(Stack PtrS)
{
	//������ʵ��������ĵڶ���λ�õ�ɾ�� 
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
	printf("�ձ�Ϊ1���ǿձ�Ϊ0 %d\n",IfEmpty(S));
	Push(S,0);Push(S,1);Push(S,2);
	
	Stack temp=S;
	temp=temp->Next;
	while(temp!=NULL){
		printf("%d\n",temp->Data);
		temp=temp->Next;
	}	
	
	printf("����\n");
	printf("%d\n",Pop(S));
	printf("%d\n",Pop(S));
	printf("%d\n",Pop(S));
	printf("�ձ�Ϊ1���ǿձ�Ϊ0 %d\n",IfEmpty(S));
	return 0;
}
