#include <stdio.h>
#include <stdlib.h>

/*树的声明*/
#define Maxsize 10
#define Null -1
typedef int child;
typedef int ElementType;
struct TreeNode{
  child left;
  child right;
};
struct TreeNode T[Maxsize];

int Max(int a,int b)
{
  if(a>b) return a;
  else return b;
}

/*树*/
int BuildTree()
{
  int num,root;
  scanf("%d",&num);
  if(num){
    int i,j;
    int check[num];
    char tl,tr;
    for(j=0;j<num;j++) check[j]=0;
    for(i=0;i<num;i++){
      scanf(" %c %c",&tl,&tr);
      if(tl!='-'){
        T[i].left=tl-'0';
        check[T[i].left]=1;
      }else
        T[i].left=Null;
      if(tr!='-'){
        T[i].right=tr-'0';
        check[T[i].right]=1;
      }else
        T[i].right=Null;
    }
    for(j=0;j<num;j++)
	  if(check[j]==0) break;
    root=j;
	return root;
  }else return Null; 
}

int layer(int root)
{
  if(root==Null)  return 0;
  if(T[root].left==Null&&T[root].right==Null)
    return 1;
  if(T[root].left==Null&&T[root].right!=Null)
    return layer(T[root].right)+1;
  if(T[root].left!=Null&&T[root].right==Null)
    return layer(T[root].left)+1;
  if(T[root].left!=Null&&T[root].right!=Null)
    return Max(layer(T[root].left),layer(T[root].right))+1;
}

ElementType LeftElem(int root)
{
  //基准 
  if( (T[root].left==Null) && (T[root].right==Null) )
  	return root;
  	
  if( (T[root].left!=Null)) 
  	return LeftElem(T[root].left);
  if( (T[root].left==Null) && (T[root].right!=Null) )
  	return LeftElem(T[root].right);
}

ElementType RightElem(int root)
{
  //基准 
  if( (T[root].left==Null) && (T[root].right==Null) )
  	return root;
  	
  if( (T[root].right!=Null)) 
  	return RightElem(T[root].right);
  if( (T[root].right==Null) && (T[root].left!=Null) )
  	return RightElem(T[root].left);
}

int main()
{
  int root;
  root=BuildTree();
  printf("%d %d %d",layer(root),LeftElem(root),RightElem(root));
  return 0;
}
