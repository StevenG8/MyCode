#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10 
#define Error NULL
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data[MAXSIZE];
	int Top1;
	int Top2; 
};

Stack CreatEmptyStack()
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Top1=-1;
	S->Top2=MAXSIZE;
	return S;
} 

bool IfEmpty(Stack S)
{
	if(S->Top1==-1||S->Top2==MAXSIZE)
		return true;
	else 
		return false;
}

void Push(Stack S,ELementType X,int Tag)
{
	if(S->Top1==S->Top2-1){
		printf("��ջ��");
	}else{
		if(Tag==1)
			S->Data[++(S->Top1)]=X; 
		else
			S->Data[--(S->Top2)]=X;
	}
}

ELementType Pop(Stack S,int Tag)
{
	if(Tag==1){
		if(S->Top1==-1){
			printf("ջ��");
			return Error;
		}else{
			return S->Data[(S->Top1)--];
		}	
	}else{
		if(S->Top2==MAXSIZE){
			printf("ջ��");
			return Error;
		}else{
			return S->Data[(S->Top2)++];
		}	
	}
}

int main()
{
	Stack PtrS=CreatEmptyStack();
	for(int i=0;i<MAXSIZE;i++){
		PtrS->Data[i]=i;
		printf("PtrS->Data[%d]=%d\n",i,PtrS->Data[i]);
	}
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	Push(PtrS,1,1);Push(PtrS,0,1);
	Push(PtrS,8,2);Push(PtrS,9,2);
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	for(int i=0;i<MAXSIZE;i++){
		printf("PtrS->Data[%d]=%d\n",i,PtrS->Data[i]);
	}
	printf("��ջ%d\n",Pop(PtrS,1)); 
	printf("��ջ%d\n",Pop(PtrS,1));
	printf("��ջ%d\n",Pop(PtrS,2));
	printf("��ջ%d\n",Pop(PtrS,2));
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	return 0;	
}
