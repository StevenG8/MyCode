#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Maxsize 1000
typedef int ElementType; 
ElementType T[Maxsize];//定义全局变量

int LogaB(int a,int b);

int getleftNum(int num);
void CompleteBinaryTree(ElementType A[],int num,int root);

int compare(const void*a,const void* b);

//下面这个是老师给的建立完全二叉树的代码
/*
  //初始传入应该这样子写：CompleteBinaryTree(0,num-1,0);

  //传入数据数组A的左下标，右下标，二叉树数组T的根节点下标
  void CompleteBinaryTree(int Aleft,int Aright,int Troot)
  {
    int num=Aright-Aleft+1;//算出数组长度
    if(num==0)  return;//递归的基准
    int leftNum=getleftNum(num);//求出这个总数目下左子树的结点个数（因为完全二叉树的形状是固定的）
    T[Troot]=A[Aleft+leftNum];//将数据数组A的根节点的值存放到二叉树数组T的相应根节点位置
    int leftroot=Troot*2+1;//算出这个结点下左结点在二叉树数组T的下标值
    int rightroot=leftroot+1;
    CompleteBinaryTree(Aleft,Aleft+leftNum-1,leftroot);//递归
    CompleteBinaryTree(Aleft+LeftNum+1,Aright,rightroot);
  }
*/

//二叉树的数组是按顺序存放的，0是根节点。最终生成的数组按顺序输出就是一个层遍历
void CompleteBinaryTree(ElementType A[],int num,int root)
{
  if(num==0)  return;
  int leftNum=getleftNum(num);
  T[root]=A[leftNum];
  CompleteBinaryTree(A,leftNum,root*2+1);
  CompleteBinaryTree(&A[leftNum+1],num-leftNum-1,root*2+2);
}

int getleftNum(int num)
{
  //算出这颗完全二叉树有多少层，层数从1开始累加算起
  //注意这里要num+1，举个例子，4层的二叉树总共是15个结点，3层则为7个结点
  //在当前的layer层内都是完美二叉树（全都是满的）
  int layer=LogaB(2,num+1);

  //低层-->二叉树图像的最下方-->数目的高层；这里统一底层表示的意思是二叉树图像的最下方，也就是数目的最高层
  int MaxleftNum=pow(2,layer-1);//根节点的左子树的最低层最多能挂多少个结点
  int FullNum=pow(2,layer)-1;//算出这颗完全二叉树的高层满二叉树的结点个数
  int leftNum=num-FullNum;//算出最底层的结点个数
  if(leftNum>MaxleftNum)
    leftNum=MaxleftNum;//实际的根节点的左子树最底层的结点个数

  return leftNum+(FullNum-1)/2;//“(FullNum-1)/2”是除去最底层的根节点的左子树的总个数
}

int LogaB(int a,int b)
{
  return log(b)/log(a);
}

int compare(const void*a,const void* b)
{
  return (*(int *)a-*(int *)b); 
}


int main()
{
  int num,i;
  scanf("%d",&num);
  int Data[num];
  for(i=0;i<num;i++){
    scanf("%d",&Data[i]);
  }
  qsort(Data,num,sizeof(ElementType),compare);//使用快速排序将其从小到大排序
  
  CompleteBinaryTree(Data,num,0);//建立完全二叉树 
  
  for(i=0;i<num-1;i++){
    printf("%d ",T[i]);
  }
  printf("%d",T[num-1]);
  
  return 0;
}
