#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef struct AVLNode *Position;
struct AVLNode{
  AVLTree left,right;
  ElementType Data;
  int height;
};

int Max(int a,int b);
int GetHeight(AVLTree T);
AVLTree MakeEmptyNode();
AVLTree Insert(ElementType X,AVLTree T);
AVLTree SingleLeftRotation(AVLTree T);
AVLTree SingleRightRotation(AVLTree T);
AVLTree DoubleLeftRightRotation(AVLTree T);
AVLTree DoubleRightLeftRotation(AVLTree T);


AVLTree SingleLeftRotation(AVLTree A)
{
  AVLTree B=A->left;
  A->left=B->right;
  B->right=A;
  A->height=Max(GetHeight(A->left),GetHeight(A->right))+1;
  B->height=Max(GetHeight(B->left),A->height)+1;
  return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
  A->left=SingleRightRotation(A->left);
  return SingleLeftRotation(A);
}

AVLTree SingleRightRotation(AVLTree A)
{
  AVLTree B=A->right;
  A->right=B->left;
  B->left=A;
  A->height=Max(GetHeight(A->left),GetHeight(A->right))+1;
  B->height=Max(GetHeight(B->right),A->height)+1;
  return B;
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
  A->right=SingleLeftRotation(A->right);
  return SingleRightRotation(A);
}

//int GetHeight(AVLTree T)
//{
//  if(T)
//    return Max(GetHeight(T->left),GetHeight(T->right))+1;
//  return -1;
//}

int GetHeight(AVLTree T)
{
  if(T)	return T->height;
  else  return -1;
}

int Max(int a,int b)
{
  return a>b? a:b;
}

AVLTree Insert(ElementType X,AVLTree T)
{
  if(!T){
    T=MakeEmptyNode();
    T->Data=X;
  }

  else if(X>T->Data){
    T->right=Insert(X,T->right);
    if(GetHeight(T->right)-GetHeight(T->left)==2){
      if((T->right->Data)<X)
        T=SingleRightRotation(T);
      else
        T=DoubleRightLeftRotation(T);
    }
  }

  else if(X<T->Data){
    T->left=Insert(X,T->left);
    if(GetHeight(T->left)-GetHeight(T->right)==2){
      if((T->left->Data)>X)
      	T=SingleLeftRotation(T);
	  else
	    T=DoubleLeftRightRotation(T);
    }
  }
  //注意这里一定要+1更新树高。从递归的基本情况反过来增加树高。
  T->height=Max(GetHeight(T->left),GetHeight(T->right))+1;
  return T;
}

AVLTree MakeEmptyNode()
{
  AVLTree T=(AVLTree)malloc(sizeof(struct AVLNode));
  T->height=0;
  T->left=T->right=NULL;
  return T;
}


int main()
{
  AVLTree T=NULL;
  int num,i;
  ElementType digit;

  scanf("%d",&num);
  for(i=0;i<num;i++){
    scanf("%d",&digit);
    T=Insert(digit,T);
  }

  if(T)
    printf("%d",T->Data);//输出根节点的数值

  return 0;
}
