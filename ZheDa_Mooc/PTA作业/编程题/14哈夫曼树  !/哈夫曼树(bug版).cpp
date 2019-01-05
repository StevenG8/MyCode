#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MinNum -1

/*
	���ǲ��õ�����С�ѵ�Ԫ��װָ��ָ����ڵ㣬��������ڵ�ĵ�ַ
	����Ҳ���Խ���С�ѵ�Ԫ�ػ��ɽṹ�������ָ�룬���ǰѸ��ڵ��ȫ�����ݿ�����ʵҲ���ڸ��ڵ�
	��DeleteMin�����ɽ�㸴��
	��Insert��copy
*/
typedef struct HuffmanTree *HTree;
struct HuffmanTree{
  HTree left;
  HTree right;
  int weight;
};
typedef struct MinHeap *MinH;
struct MinHeap{
  int size;
  HTree *T;//��Ź��ڹ���������ָ�������
};
typedef struct BinaryTree *Tree;
struct BinaryTree{
  Tree left,right;
};



MinH CreateMinheap(int num);
void MinHFInsert(MinH H,int X);
void MinHTInsert(MinH H,HTree *T);
HTree DeleteMin(MinH H);
HTree BuildHuffmanTree(MinH H);
Tree EmptyTree();
int BuildTree(char s[],int times,Tree T);
int WPL(HTree T,int depth);


//��Ϊ��С������ȫ������,������������ŵ�
//Ҫ����С���������,ֻ��Ҫ�������ŵ�������������Ϊ��
//�������迼���������������⣬ֻ�踳Ȩֵ����
//���������Ĺ������ں���Ĺ�����������ɵ�
MinH CreateMinheap(int num)
{
  MinH H=(MinH)malloc(sizeof(struct MinHeap));//�����
  H->size=0;
  H->T=(HTree *)malloc((num+1)*sizeof(HTree));//ָ����������
  for(int i=0;i<num+1;i++)
  	H->T[i]=(HTree)malloc(sizeof(struct HuffmanTree));//����Ԫ������
  H->T[0]->weight=MinNum;//�����ڱ�
  for(int i=0;i<num+1;i++)
  	H->T[i]->left = H->T[i]->right = NULL;//����������ʼ��Ϊ��
  return H;
}

//����Ԫ�أ�����ֻ�Ǹ�ֵ���轻����ַ
void MinHFInsert(MinH H,int frenquency)
{
  int pos;
  for(pos = ++H->size ; frenquency < H->T[pos/2]->weight ; pos/=2)
    H->T[pos]->weight = H->T[pos/2]->weight;
  H->T[pos]->weight = frenquency;
}



void MinHTInsert(MinH H,HTree *T)
{
  int pos;
  for(pos = ++H->size ; (*T)->weight < H->T[pos/2]->weight ; pos/=2)
    H->T[pos]= H->T[pos/2]; //������ָ��ĵ�ַ��Ҳ���ǽ�������ŵĹ���������
  H->T[pos] = *T;//ʹ����ָ���ָ�룬Ŀ����Ϊ�˽����ڵ�ĵ�ַд��
  //������һ����������������Ӧ�ò�����Ǹ��ڵ�ĵ�ַ�����������������ᶪʧ��
}

HTree DeleteMin(MinH H)
{
  if(H->size==0){
    printf("�ѿ�\n");
    return H->T[0];//�����ڱ�
  }

  int child,parent;
  HTree result=H->T[1];//���ض���Ȩֵ��С�ĸ��ڵ���

  //������ʵ����ͷ�ó���������λ���ƶ�������ٰ�ͷ���ȥ
  HTree DeleteNode=H->T[H->size--];
  for(parent=1;parent*2 <= H->size;parent=child){//������С�ڻ���ڣ�����ͻ����
	child=parent*2;
    if(child!=H->size && H->T[child+1]->weight < H->T[child]->weight )
      child++;
    if(DeleteNode->weight < H->T[child]->weight)
	    break;
    else
      H->T[parent] = H->T[child];//Ҫ�õ�ַ����������Ȩֵ����
	  //�����Ȩֵ�����ᵼ��ÿ�η��صĶ���H->T[1]Ԫ����ָ��ĵ�ַ��Ҳ��������ͬһ�����������ٽ�������������������
  }
  H->T[parent]=DeleteNode;

  return result;
}


HTree BuildHuffmanTree(MinH H)
{
  HTree T;
  int times=H->size;//��С��Ԫ������

  //����Ҫ��times����ֱ����H->size��ԭ���ǣ�H->size����DeleteMin�����м�С������ѭ���Ĳ����仯
  for(int i=1;i<times;i++){//�����ó������ٲ��ȥ��N��Ԫ�ؾ�Ҫִ��N-1��
    T=(HTree)malloc(sizeof(struct HuffmanTree));//mallocӦ��ѭ������,�����ѭ��������ǰ��д��������д
	T->left=DeleteMin(H);
    T->right=DeleteMin(H);
    T->weight = (T->left->weight) + (T->right->weight);
    MinHTInsert(H,&T);//������ڵ�ĵ�ַ�͵��ڴ�����������
  }
  T=DeleteMin(H);
  return T;
}

int WPL(HTree T,int depth)
{
  if(T->left==NULL&&T->right==NULL){//���������������������ô��ΪҶ�ڵ㣬�������Ȩ·��ֵ
  	return (T->weight)*depth;
  }
  else{  //��Ϊ��������ֻ�ж�Ϊ0��2�Ľ�㣬���Ҫô����������Ϊ�գ�Ҫô��������������
	return ( WPL(T->left,depth+1) + WPL(T->right,depth+1) );
	//��������������������Ĵ�Ȩ·��ֵ���
  }
}



Tree EmptyTree()
{
  Tree T=(Tree)malloc(sizeof(struct BinaryTree));
  T->left=T->right=NULL;
  return T;
}

//���������ı��뷽ʽ���Զ�����,��ֻҪ����������Ϳ���˵�ǹ�������
//1.��Ȩ·������֮����С
//2.���ݽ�����Ҷ�ڵ���
//�����Ź��������ж�Ϊ1�Ľ�㣬��ô��·�����ȾͲ�������С
//��Ϊ������ж�Ϊ1�Ľ�㣬Ϊʲô�����м�����·��������
int BuildTree(char s[],int times,Tree T)
{
  for(int i=0;i<times;i++){
    if(s[i]=='0'){
      if(T->left==NULL)
        T->left=EmptyTree();
      T=T->left;
    }
    else{
      if(T->right==NULL)
        T->right=EmptyTree();
      T=T->right;
    }
  }
  if(T->right||T->left)//����������·���϶�����Ҷ�ӽڵ�
    return 1;

  return 0;
}


int main()
{
  int num,i,j;

  scanf("%d",&num);
  getchar();
  MinH H=CreateMinheap(num);//ȷ����С�ѵĴ�С

  char alphabet;
  int frequency[num];//��¼Ȩֵ
  for(i=0;i<num;i++){
    scanf("%c %d",&alphabet,&frequency[i]);
    getchar();
    MinHFInsert(H,frequency[i]);//������С��
  }

  HTree HuffmanT=BuildHuffmanTree(H);//���ɹ�������
  int Value=WPL(HuffmanT,0);

  int checknum,flag;
  scanf("%d",&checknum);
  int length,power=0;
  char s[num][64];
  Tree T;

  for(i=0;i<checknum;i++){
    flag=1;
    power=0;
    T=EmptyTree();
    for(j=0;j<num;j++){
      getchar();
      scanf("%c",&alphabet);
      scanf("%s",s[j]);
      length=strlen(s[j]);//���·����
      power=length*frequency[j]+power;//Ȩֵ�ۼ�
      if( flag && BuildTree(s[j],length,T) )
		flag=0;//������������г�����־��0
    }

    if(flag){//������Ӧû����
      if(power==Value)//У��Ȩֵ�Ƿ���ͬ
      	printf("Yes\n");
	  else
	  	printf("No\n");
	}
    else
      printf("No\n");
  }
  return 0;
}
