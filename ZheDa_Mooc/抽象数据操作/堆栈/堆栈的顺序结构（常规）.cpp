#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
#define Error NULL
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data[MAXSIZE];
	int Top;//栈顶
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
		printf("堆栈满");
	else
		S->Data[++(S->Top)]=X;
}

ELementType Pop(Stack S)
{
	if(S->Top==-1){
		printf("栈空");
		return Error;
	}else{
		return S->Data[(S->Top)--];
	}
}

int main()
{
	Stack PtrS=CreatEmptyStack();
	printf("当前堆栈状态，1为空，0为非空。 %d\n",IfEmpty(PtrS));
	Push(PtrS,1);Push(PtrS,2);Push(PtrS,3);
	printf("当前堆栈状态，1为空，0为非空。 %d\n",IfEmpty(PtrS));
	printf("出栈%d\n",Pop(PtrS));
	printf("出栈%d\n",Pop(PtrS));
	printf("出栈%d\n",Pop(PtrS));
	printf("当前堆栈状态，1为空，0为非空。 %d\n",IfEmpty(PtrS));
	return 0;
}
