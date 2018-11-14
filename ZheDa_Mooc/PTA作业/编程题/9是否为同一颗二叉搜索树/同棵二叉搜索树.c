#include <stdio.h>
#include <stdlib.h>

#define Maxsize 10

typedef struct TreeNode* Tree;
struct TreeNode{
  Tree left;
  Tree right;
  int Data;
  int flag;
};

Tree Resetflag(Tree T)
{
  T->flag=0;

	if(T->right)
    T->right=Resetflag(T->right);
  if(T->left)
    T->left=Resetflag(T->left);
    
  return T;
}

Tree MakeEmptyNode()
{
  Tree T=(Tree)malloc(sizeof(struct TreeNode));
  T->right=T->left=NULL;
  T->flag=0;
  return T;
}

Tree Insert(Tree T,int X)//暂且默认插入的数据是不会重复的
{
  if(!T){//如果是空树
    T=MakeEmptyNode();
    T->Data=X;
  }else{
    if(X>T->Data)
      T->right=Insert(T->right,X);
    else if(X<T->Data)
      T->left=Insert(T->left,X);
  }

  return T;
}

Tree MakeTree(int* sample,int length)
{
  Tree T=MakeEmptyNode();
  T->Data=sample[0];

  int i;
  for(i=1;i<length;i++){
    T=Insert(T,sample[i]);
  }

  return T;
}

int judge(Tree T,int* X,int length)
{
  int j;
  int result=1;
  Tree head=T;

  for(j=0;j<length;j++){

	T=head;
    while(X[j]!=T->Data){
      if(X[j]>T->Data){//
        if(T->flag==1)
          T=T->right;
        else{
          result=0;
          break;
        }
      }
      else{//
        if(T->flag==1)
          T=T->left;
        else{
          result=0;
          break;
        }
      }
    }

    if(result==0)
	  break;

    else
      T->flag=1;
  }

  return result;
}

int main()
{
  int i,k,count=0;
  int length,batch;
  int output[Maxsize];

  scanf("%d",&length);
  while(length!=0){
    scanf("%d",&batch);
    int digit[length];

    for(i=0;i<length;i++)
      scanf("%d",&digit[i]);
    Tree T=MakeTree(digit,length);

    for(k=0;k<batch;k++){
      for(i=0;i<length;i++)
      	scanf("%d",&digit[i]);
      output[count++]=judge(T,digit,length);
      T=Resetflag(T);
    }

    scanf("%d",&length);
  }

  for(i=0;i<count;i++){
    if(output[i]==1)
      printf("Yes\n");
    else
      printf("No\n");
  }

  return 0;
}
