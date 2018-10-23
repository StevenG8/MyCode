#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

//ȫ�ֱ���
int Altogetherlength; 

//��ջ������
#define Error 0
#define Maxsize 30
typedef int ELementType;
typedef struct SNode* Stack;
struct SNode{
	ELementType Data[Maxsize];
	int Top;//ջ��
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




//if(str=="Push")������д�Ǵ�ģ���Ϊ�ַ��������ö���������������ͣ��Ƚϵ��ǵ�ַ����������  
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
  if(OriginLength==0) //������� 
  	return;
  if(OriginLength==1){//ֻ��һ����ֱ����� 
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
