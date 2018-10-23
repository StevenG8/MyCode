#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

//全局变量
int Altogetherlength; 

//堆栈的声明
#define Error 0
#define Maxsize 30
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data[Maxsize];
	int Top;//栈顶
};

Stack CreatEmptyStack()
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Top=-1;
	return S;
}

int IfEmpty(Stack S)
{
	if(S->Top==-1)	return 1;
	else            return 0;
}

void Push(Stack S,ELementType X)
{
	if(S->Top==Maxsize-1)
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




//if(str=="Push")这样子写是错的，因为字符串是引用对象而不是数据类型，比较的是地址而不是内容  
int ReadData(int* Pre,int* In)
{
  char str[5];
  int i,j,cnt,num;
  ELementType elem;

  scanf("%d",&num);
  if(num){
    i=j=0;
    Stack S=CreatEmptyStack();
    for(cnt=0;cnt<2*num;cnt++){
      scanf("%s",&str);
      if(strcmp(str,"Push")==0){
        scanf("%d",&elem);
        Push(S,elem);
        Pre[j++]=elem;
      }else{
        elem=Pop(S);
        In[i++]=elem;
      }
    }
  }
  return num;
}

void PostTraversal(int* Pre,int* In,int OriginLength)
{ 
  if(OriginLength==0) //空树情况 
  	return;
  if(OriginLength==1){//只有一个根直接输出 
  	if(Altogetherlength==1)	 
	  printf("%d",Pre[0]);
  	else
	  printf("%d ",Pre[0]);
  	return;
  }
  
  int root=Pre[0];
  int Sublength=0;
  while(root!=In[Sublength]){
  	Sublength++;	
  }
  
  //left
  PostTraversal(&Pre[1],In,Sublength);
  //right
  PostTraversal(&Pre[Sublength+1],&In[Sublength+1],OriginLength-Sublength-1);
  //root
  if(Altogetherlength==OriginLength)
  	printf("%d",Pre[0]);	
  else 
  	printf("%d ",Pre[0]); 
}

int main()
{
  int Pre[Maxsize],In[Maxsize];
  int length=Altogetherlength=ReadData(Pre,In);
  PostTraversal(Pre,In,length);
  return 0;
}
