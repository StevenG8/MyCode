#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
#define Error NULL
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data[MAXSIZE];
	int Top;//ջ��
};

Stack CreatEmptyStack()
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Top=-1;
	return S;
}

bool IfEmpty(Stack S)
{
	if(S->Top==-1)
		return true;
	else
		return false;
}

void Push(Stack S,ELementType X)
{
	if(S->Top==MAXSIZE-1)
		printf("��ջ��");
	else
		S->Data[++(S->Top)]=X;
}

ELementType Pop(Stack S)
{
	if(S->Top==-1){
		printf("ջ��");
		return Error;
	}else{
		return S->Data[(S->Top)--];
	}
}

int main()
{
	Stack PtrS=CreatEmptyStack();
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	Push(PtrS,1);Push(PtrS,2);Push(PtrS,3);
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	printf("��ջ%d\n",Pop(PtrS));
	printf("��ջ%d\n",Pop(PtrS));
	printf("��ջ%d\n",Pop(PtrS));
	printf("��ǰ��ջ״̬��1Ϊ�գ�0Ϊ�ǿա� %d\n",IfEmpty(PtrS));
	return 0;
}
