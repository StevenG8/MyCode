#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef int SetName;
typedef int Settype;

//这里采取将元素映射到数组下标,数组存放的数据是该元素的集合头
//这样就无需采用结构体,直接用数组就可以实现

SetName FindRoot(Settype A[],ElementType X);
void Connect(Settype A[],SetName a,SetName b);
SetName DiminishFindRoot(Settype A[],ElementType X);


SetName FindRoot(Settype A[],ElementType X)
{
  //A[x]是它的集合头,如果集合头外还有集合头,那么更新基准继续搜索
  for(;A[X]>=0;X=A[X]);
  return X;//返回集合头,即数组下标
}

void Connect(Settype A[],SetName Root1,SetName Root2)
{
  // SetName Root1=FindRoot(A,a);
  // SetName Root2=FindRoot(A,b);

  if(Root1!=Root2){//如果两个不属于同个集合
    if(A[Root1]<A[Root2]){//如果根1上的节点数更多,根2连接到根1上
      A[Root1]=A[Root1]+A[Root2];//更新根1的总结点数
      A[Root2]=Root1;
    }
    else{
      A[Root2]+=A[Root1];
      A[Root1]=Root2;
    }
  }
}


int main()
{
  int num;
  scanf("%d\n",&num);
  Settype Data[num+1];//这里的0下标是没有被使用的,为了跟题目1-N相对应
  for(int i=1;i<num+1;i++){
    Data[i]=-1;//初始化,默认都是单个结点为一个集合
  }

  char c;
  ElementType a,b;
  SetName root1,root2;
  while(1){

    scanf("%c",&c);
    if(c!='S'){
      scanf("%d %d",&a,&b);
      root1=FindRoot(Data,a);
      root2=FindRoot(Data,b);
      if(c=='C'){//检查这两个元素是否属于同个集合
        if(root1==root2&&root1!=-1)
          printf("yes\n");
        else
          printf("no\n");
      }
      else if(c=='I')//连接两个元素使其成为同一个集合
        Connect(Data,root1,root2);
    }
    else{//执行集合检查
      int count=0;
      for(int i=1;i<num+1;i++){
        if(Data[i]<0)
          count++;
      }
      if(count==1)
        printf("The network is connected.\n");
      else
        printf("There are %d components.\n",count);
      break;
    }

  }

  return 0;
}


/*这里可以借鉴其思想,就只是想要递归的最终结果来搞事情*/
//最终结果使得这个集合上的结点直接连到了集合头上,把路径缩短
SetName DiminishFindRoot(Settype A[],ElementType X)
{
  if(A[X]<0)  return X;
  else
    return A[X]=Find(A,A[X]);
  //这里返回的是A[X],只是在返回前要先对其赋值
  //可以反过来理解,Find函数一直在调用自己,直到找到根节点
  //找到根节点后其下的第一个结点就对其父节点赋值为根节点,然后返回其父节点(也就是根节点)
  //而后根节点下的第二个节点通过Find函数得到的是根节点,他也将其赋值为其父节点
  //以此类推,最后原本根节点下的结点直接以最短路径挂在根节点下

  //不纠结于细节的简单理解是这样的:
  //return A[X]=Find(A,A[X]);
  //其实说白了就是把递归最终得到的结果同样的返回到了每一个中间递归
  //只是多做了一个赋值,而这里的赋值的意义仅仅是将其最终结果作为其父节点
}
