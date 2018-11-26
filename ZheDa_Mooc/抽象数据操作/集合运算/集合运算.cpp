
#define Maxsize 1000
#define Error -1

typedef int ElementType;
typedef struct{
  ElementType Data;
  int parent;//�伯������
}SetType;//���������˺�Ķ���,Ҳ����˽ṹ�������.
//���������ṹ�岻��Ҫдstruct SetType X,ֱ��дSetType X����

//���ϵ������õ���˫�ױ�ʾ��,ƽʱ�����ĸ��ڵ�ָ����������,������������ָ����ڵ�.
//�������ָ��ͬһ�����ڵ�,������ڵ����Ϊ������ϵı�־
//���ϵ�ͷ��parent��ֵ�Ǹ���,����ֵ��С�����伯�ϴ�С


void CombineRoots(SetType A[],ElementType a,ElementType b);
int Find(SetType A[],ElementType X);

int Find(SetType A[],ElementType X)
{
  //������д�����Ӽ��,��һ�����޴�����ѭ��������һ��Ԫ��
  for(int i=0 ; i<Maxsize&&A[i].Data!=X ; i++);//�ҳ�Ԫ����������±�

  if(i>=Maxsize){
    printf("�Ҳ���\n");
    return Error;
  }

  //Ѱ���ϵ�ͷ
  int head=A[i].parent;
  while(A[head].parent>=0){//�����м��С����
    head=A[head].parent;
  }
  return A[parent].parent;
}

//����������ҳ�����Ԫ�طֱ��������ĸ�����,������ϲ�ͬ,������ߵ�ͷ���Ϻϲ�
//-------------����ϲ�����ͳ�����ϵ�����Ԫ�غϲ�Ϊһ�����ϲ�һ��-------------
void CombineRoots(SetType A[],ElementType a,ElementType b)
{
  int root1,root2;
  //�ҵ�������Ԫ�صļ���ͷ
  root1=Find(A,a);
  root2=Find(A,b);

  if(root!=root2){//�������ϲ�ͬ
    if( (A[root1].parent)< (A[root2].parent))//������root2�Ĵ�С��С�ڼ���root1
      A[root2].parent=root1;//������root2�ҵ�����root1��
    else
      A[root1].parent=root2;
  }
}
