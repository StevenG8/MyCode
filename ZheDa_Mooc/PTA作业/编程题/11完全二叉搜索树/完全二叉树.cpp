#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Maxsize 1000
typedef int ElementType; 
ElementType T[Maxsize];//����ȫ�ֱ���

int LogaB(int a,int b);

int getleftNum(int num);
void CompleteBinaryTree(ElementType A[],int num,int root);

int compare(const void*a,const void* b);

//�����������ʦ���Ľ�����ȫ�������Ĵ���
/*
  //��ʼ����Ӧ��������д��CompleteBinaryTree(0,num-1,0);

  //������������A�����±꣬���±꣬����������T�ĸ��ڵ��±�
  void CompleteBinaryTree(int Aleft,int Aright,int Troot)
  {
    int num=Aright-Aleft+1;//������鳤��
    if(num==0)  return;//�ݹ�Ļ�׼
    int leftNum=getleftNum(num);//����������Ŀ���������Ľ���������Ϊ��ȫ����������״�ǹ̶��ģ�
    T[Troot]=A[Aleft+leftNum];//����������A�ĸ��ڵ��ֵ��ŵ�����������T����Ӧ���ڵ�λ��
    int leftroot=Troot*2+1;//����������������ڶ���������T���±�ֵ
    int rightroot=leftroot+1;
    CompleteBinaryTree(Aleft,Aleft+leftNum-1,leftroot);//�ݹ�
    CompleteBinaryTree(Aleft+LeftNum+1,Aright,rightroot);
  }
*/

//�������������ǰ�˳���ŵģ�0�Ǹ��ڵ㡣�������ɵ����鰴˳���������һ�������
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
  //��������ȫ�������ж��ٲ㣬������1��ʼ�ۼ�����
  //ע������Ҫnum+1���ٸ����ӣ�4��Ķ������ܹ���15����㣬3����Ϊ7�����
  //�ڵ�ǰ��layer���ڶ���������������ȫ�������ģ�
  int layer=LogaB(2,num+1);

  //�Ͳ�-->������ͼ������·�-->��Ŀ�ĸ߲㣻����ͳһ�ײ��ʾ����˼�Ƕ�����ͼ������·���Ҳ������Ŀ����߲�
  int MaxleftNum=pow(2,layer-1);//���ڵ������������Ͳ�����ܹҶ��ٸ����
  int FullNum=pow(2,layer)-1;//��������ȫ�������ĸ߲����������Ľ�����
  int leftNum=num-FullNum;//�����ײ�Ľ�����
  if(leftNum>MaxleftNum)
    leftNum=MaxleftNum;//ʵ�ʵĸ��ڵ����������ײ�Ľ�����

  return leftNum+(FullNum-1)/2;//��(FullNum-1)/2���ǳ�ȥ��ײ�ĸ��ڵ�����������ܸ���
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
  qsort(Data,num,sizeof(ElementType),compare);//ʹ�ÿ����������С��������
  
  CompleteBinaryTree(Data,num,0);//������ȫ������ 
  
  for(i=0;i<num-1;i++){
    printf("%d ",T[i]);
  }
  printf("%d",T[num-1]);
  
  return 0;
}
