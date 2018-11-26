#include <stdlib.h>

#define Maxsize 1000
#define MinNum -1
typedef int ElementType;

typedef struct HeapStruct *Heap;
typedef struct HeapStruct *PriorityQueue;
struct HeapStruct{
  ElementType* Data;
  int size;//��ǰ�Ĵ�С
  int capacity;//�������
}

//��������
PriorityQueue Initialise(int MaxElements);
void Destory(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void MinInsert(ElementType X,PriorityQueue H);//��С�ѵĲ���
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
void MaxInsert(ElementType X,PriorityQueue H);
ElementType DeleteMax(PriorityQueue H);
ElementType FindMax(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

/*
  �����������ԣ�һ����ȫ��������������洢�������ӽڵ����/С�ڸ��ڵ㣨��������֮��û�д�С��ϵ����
  ����ĵ�0��Ԫ�����ڱ�����������ݡ��ӵ�һ��Ԫ�ؿ�ʼ�Ŵ�����ݡ�
  ����ý����±�Ϊi����ô���������2i���Ҷ�����2i+1��������i/2��
*/
PriorityQueue Initialise(int MaxElements)
{
    PriorityQueue H=(PriorityQueue)malloc(sizeof(struct HeapStruct));
    if(H=NULL)
      printf("error,out of space\n");

    //���Maxsize+1������Ϊ����ĵ�0λ����Ϊ�ڱ����������ݴ洢
    H->Data=(ElementType *)malloc((Maxsize+1)*sizeof(ElementType));
    H->Data[0]=MinNum;
    H->size=0;
    H->capacity=Maxsize;
}

void MinInsert(ElementType X,PriorityQueue H)//��С�ѵĲ���
{
  int position;
  if(IsFull(H)){
    printf("Full\n");
    return;
  }
  //position=++H->size����ȫ����������һ����㣬���ȴ�СҪ�仯���������һ���µĽ���λ���ǹ̶���
  //X < H->Data[position/2]�����Ҫ����Ľ��AС�ڸýڵ�B������BҪ�����Ķ��ӻ�һ��λ�ã�������
  //position/=2����������׼���ı�
  for(position=++H->size; X < H->Data[position/2] ; position/=2){
      H->Data[position]=H->Data[position/2];
  }
  H->Data[position]=X;//���뵼�µ�˳������Ѿ������������Ҫ�����λ�ò嵽��Ӧ�е�λ��
}

ElementType DeleteMin(PriorityQueue H)
{
  if(IsEmpty(H)){
    printf("Empty\n");
    return H->Data[0];
  }

  ElementType result=H->Data[1];//���Ҫ���صĽ��
  ElementType DeleteNode=H->Data[size--];//��Ϊɾ���˸��ڵ㣬��С-1������ȫ����������״�̶�����ײ����ҵĽ����Ҫ��ɾ����
  int parent;//���ڵ�
  int child;//���ڵ��������

  /*
    �ӵ�һ�����ڵ㿪ʼ�����ˡ�
    �Ƚϸ��ڵ�������������ҳ���С�ģ��ٸ���ɾ���Ľ�����Ƚϣ���˭ȥ������ڵ�
    �������������ȥ������ڵ㣬�Ǹ�ȥ������������ظ��ڶ��еĶ�����ֱ��û����������
    �����ɾ���Ľ��ȥ������ڵ㣬��ô�Ͳ��ü���ִ����

    parent��㲻�����ִ�������Զ�ǿյģ��ȴ���С�Ľ�����
    �������̾����ǰ�ͷ���ó��������������һ��λ�õĽ���ó�����Ȼ�������Ĳ��ְ�˳������ȥ�������ó����Ľ���ٲ��ȥ
  */
  for(parent=1 ; parent*2 < H->size ; parent=child){//parent*2 < H->size,һֱִ�е������ȫ����������ײ�

    /*--------------�ҳ����ڵ��У����������ĸ���С--------------*/
    //������ȫ����������״�����һ����ֻ�е�����㣬��ô�ⵥ�����������Ľ��
    //�ж��������Ƿ����������ӣ�ֻ���ж���������������ǲ��������ȫ�����������һ����㼴��
    child=parent*2;//���ڵ��������
    if( child!=H->size && H->Data[child+1] < H->Data[child] )//������������ӣ��Ҹ��ڵ��������С��������
      child++;//��������С

    /*-------------�Ƚ������С��������ɾ������ײ����ҵĽ��------*/
    if(DeleteNode < H->Data[child])//�������ײ����ҵĽ����С����ôֱ�ӽ��ý����뼴��
      break;//��ʱ��parent��㻹û��������break��������������ȷ��
    else
      H->Data[parent]=H->Data[child];//�����������С����ô��С����A���뵽�丸���ϣ������AΪ���׽�����ִ��
      //parent���������ִ�С�parent*2 < H->size���жϣ���û������������������ѭ������ʱparent�������ײ�Ľ�㣨����ֵ��
  }
  H->Data[parent]=DeleteNode;//���˽�������ɾ���Ľ����뵽��Ӧ��λ����

  return result;
}


ElementType DeleteMax(PriorityQueue H)
{
  if(IsEmpty(H)){
    printf("Empty\n");
    return H->Data[0];
  }

  ElementType DeleteNum=H->Data[size--];
  ElementType result=H->Data[1];

  int parent;
  int child;
  for(parent=1; 2*parent< H->size ;parent=child){
    child=parent*2;
    if( child!=H->size && H->Data[child+1]>H->Data[child] )
      child++;
    if(DeleteNum>H->Data[child])
      break;
    else
      H->Data[parent]=H->Data[child];
  }
  H->Data[parent]=DeleteNum;

  return result;
}
