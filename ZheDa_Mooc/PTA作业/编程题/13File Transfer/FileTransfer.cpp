#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef int SetName;
typedef int Settype;

//�����ȡ��Ԫ��ӳ�䵽�����±�,�����ŵ������Ǹ�Ԫ�صļ���ͷ
//������������ýṹ��,ֱ��������Ϳ���ʵ��

SetName FindRoot(Settype A[],ElementType X);
void Connect(Settype A[],SetName a,SetName b);
SetName DiminishFindRoot(Settype A[],ElementType X);


SetName FindRoot(Settype A[],ElementType X)
{
  //A[x]�����ļ���ͷ,�������ͷ�⻹�м���ͷ,��ô���»�׼��������
  for(;A[X]>=0;X=A[X]);
  return X;//���ؼ���ͷ,�������±�
}

void Connect(Settype A[],SetName Root1,SetName Root2)
{
  // SetName Root1=FindRoot(A,a);
  // SetName Root2=FindRoot(A,b);

  if(Root1!=Root2){//�������������ͬ������
    if(A[Root1]<A[Root2]){//�����1�ϵĽڵ�������,��2���ӵ���1��
      A[Root1]=A[Root1]+A[Root2];//���¸�1���ܽ����
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
  Settype Data[num+1];//�����0�±���û�б�ʹ�õ�,Ϊ�˸���Ŀ1-N���Ӧ
  for(int i=1;i<num+1;i++){
    Data[i]=-1;//��ʼ��,Ĭ�϶��ǵ������Ϊһ������
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
      if(c=='C'){//���������Ԫ���Ƿ�����ͬ������
        if(root1==root2&&root1!=-1)
          printf("yes\n");
        else
          printf("no\n");
      }
      else if(c=='I')//��������Ԫ��ʹ���Ϊͬһ������
        Connect(Data,root1,root2);
    }
    else{//ִ�м��ϼ��
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


/*������Խ����˼��,��ֻ����Ҫ�ݹ�����ս����������*/
//���ս��ʹ����������ϵĽ��ֱ�������˼���ͷ��,��·������
SetName DiminishFindRoot(Settype A[],ElementType X)
{
  if(A[X]<0)  return X;
  else
    return A[X]=Find(A,A[X]);
  //���ﷵ�ص���A[X],ֻ���ڷ���ǰҪ�ȶ��丳ֵ
  //���Է��������,Find����һֱ�ڵ����Լ�,ֱ���ҵ����ڵ�
  //�ҵ����ڵ�����µĵ�һ�����Ͷ��丸�ڵ㸳ֵΪ���ڵ�,Ȼ�󷵻��丸�ڵ�(Ҳ���Ǹ��ڵ�)
  //������ڵ��µĵڶ����ڵ�ͨ��Find�����õ����Ǹ��ڵ�,��Ҳ���丳ֵΪ�丸�ڵ�
  //�Դ�����,���ԭ�����ڵ��µĽ��ֱ�������·�����ڸ��ڵ���

  //��������ϸ�ڵļ������������:
  //return A[X]=Find(A,A[X]);
  //��ʵ˵���˾��ǰѵݹ����յõ��Ľ��ͬ���ķ��ص���ÿһ���м�ݹ�
  //ֻ�Ƕ�����һ����ֵ,������ĸ�ֵ����������ǽ������ս����Ϊ�丸�ڵ�
}
