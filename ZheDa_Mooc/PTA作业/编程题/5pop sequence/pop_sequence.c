#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct SNode{
	ElementType* Data;
	int top;
};
typedef struct SNode* Stack;

/*对堆栈的抽象操作*/
Stack CreatEmptyStack(int length)
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Data=(ElementType*)malloc(length*sizeof(ElementType));
	S->top=-1;
	return S;
}

int Push(Stack S,ElementType X,int MAXSIZE)
{
	if(S->top==MAXSIZE-1){
		/*printf("堆栈已满\n");*/
		return 0;
    }
	else{
	    S->Data[++(S->top)]=X;
	    return 1;
    }
}

ElementType Pop(Stack S)
{
	if(S->top==-1){
		/*printf("栈空\n");*/
		return 0;
	}else{
		return S->Data[(S->top)--];
	}
}


int judge(ElementType* digit,int length,int MAXSIZE)//对这一行进行判断
{
  int i;
  Stack S=CreatEmptyStack(length);//建立空堆栈
  for(i=1;i<=length;i++){
    if(Push(S,i,MAXSIZE)){//放入堆栈成功
      while(S->Data[S->top]==(*digit)){//检查栈顶元素是否符合
        digit=digit+1;//符合则跳到式子的下一个元素 
        Pop(S);
        /*printf("%d\n",Pop(S));*/
      }
    }else{
	  	/*printf("栈满！\n");*/
		break;//如果堆栈满了那么直接跳出
	}
  }

  if(S->top==-1){
  	free(S);
	return 1;//堆栈是空的，证明这个式子可以被堆栈表示 
  }else{
  	free(S);
  	return 0;//堆栈是满的，证明这个式子无法被堆栈表示
  }
  
}


int main()
{
  int maxsize,LengthPush,CheckNumber;
  int i,j;
  scanf("%d %d %d",&maxsize,&LengthPush,&CheckNumber);

  ElementType Temp[CheckNumber][LengthPush];
  for(j=0;j<CheckNumber;j++){
    for(i=0;i<LengthPush;i++){
      scanf("%d",&Temp[j][i]);
    }
  }
  
  for(j=0;j<CheckNumber;j++){
    if(judge(&Temp[j][0],LengthPush,maxsize)==1)
      printf("YES\n");
    else
      printf("NO\n");
  }
  
  return 0;
}
