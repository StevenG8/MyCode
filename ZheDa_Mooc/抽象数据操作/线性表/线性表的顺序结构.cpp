#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10 

typedef int ElementType;
typedef struct LNode* List;
struct LNode{
	ElementType Data[Maxsize];
	int last;//������Ա��е����һ��Ԫ�ص��±� 
}; 

List MakeEmpty()
{
	List PtrL;
	PtrL=(List)malloc(sizeof(struct LNode));
	//malloc����������һ��ռ䲢���ظÿռ�ĵ�ַ
	PtrL->last=-1;//�ձ�
	return PtrL; 
} 

int FindPosition(ElementType X,List PtrL)
{
	int i=0;
	while(PtrL->last>=i){
		if(PtrL->Data[i]==X)
			break;
		i++;
	}
	if(i>PtrL->last)
		return -1;//û���ҵ� 
	else 
		return i;
}

int Insert(ElementType X,int position,List PtrL)
{
	if(position>PtrL->last||position<0){
		printf("λ�ò��Ϸ�\n");
		return -1; 
	}
	if(PtrL->last==Maxsize-1){
		printf("����\n");
		return -1; 
	} 
	int i;
	//���������ֵҪ�ѴӸ�λ�����ȫ����������Ųһλ���������±꿪ʼ 
	for(i=PtrL->last;i>=position;i--) 
		PtrL->Data[i+1]=PtrL->Data[i];
	PtrL->Data[position]=X;
	PtrL->last++;
	return 1;
} 

int Delete(int position,List PtrL)
{
	if(position>PtrL->last||position<0){
		printf("λ�ò��Ϸ�\n");
		return -1;
	}
	int i;
	//����ɾ����ֵҪ�ѴӸ�λ�����ȫ��������ǰŲһλ������С���±꿪ʼ 
	for(i=position;i<=PtrL->last;i++)
		PtrL->Data[i]=PtrL->Data[i+1];
	PtrL->last--;
	return 1;
} 

int main()
{
	List L;
	L=MakeEmpty();
	printf("L->last=%d,L->Data[0]=%d\n",L->last,L->Data[0]);

	L->last=0;//ʹ��ӿձ��Ϊ��һ��Ԫ�ص�ʵ�� 
	Insert(1,0,L);
	Insert(2,1,L);
	Insert(3,2,L);
	printf("L->last=%d,L->Data[0]=%d,L->Data[1]=%d,L->Data[2]=%d,L->Data[3]=%d\n",L->last,L->Data[0],L->Data[1],L->Data[2],L->Data[3]);
	Insert(4,-1,L);//λ�ò��Ϸ� 
	printf("Ԫ��1��λ��Ϊ%d\n",FindPosition(1,L));
	Delete(1,L);
	printf("L->last=%d,L->Data[0]=%d,L->Data[1]=%d,L->Data[2]=%d,L->Data[3]=%d\n",L->last,L->Data[0],L->Data[1],L->Data[2],L->Data[3]);
	return 0;
}
