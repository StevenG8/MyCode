#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode* List;
struct LNode{
	ElementType Data;
	List Next;
};

int length(List PtrL)
{
	int j=0;
	while(PtrL){//ͼ����ʵ�����������еļ�ͷ�� 
		j++;
		PtrL=PtrL->Next;
	}
	return j;
}

List FindKth(int position,List PtrL)//�ҵ�����ŵ�Ԫ����ָ�� 
{
	int j=1;//����Ӧ���Ǵ�1��ͷ 
	while(PtrL&&j<position){
		PtrL=PtrL->Next;
		j++;
	} 
	if(j==position)
		return PtrL;
	else//�б�û����ô���Ԫ�أ����Ҳ��� 
		return NULL;
} 

List Find(ElementType X,List PtrL)//�ҵ���ֵ��Ԫ����ָ�� 
{
	while(PtrL){
		if(PtrL->Data==X)
		{
			return PtrL;
			break;
		}
		PtrL=PtrL->Next;
	}	
	return NULL;
}

List Insert(ElementType X,int position,List PtrL)//���Բ�������Ϸ�λ�� 
{
	List S;
	if(position==1){//�ڱ�ͷ����ͷָ��ı� 
		S=(List)malloc(sizeof(struct LNode));
		S->Next=PtrL;
		S->Data=X;
		return S;
	}
	List p;
	p=FindKth(position-1,PtrL);
	if(p==NULL){
		printf("λ�ò��Ϸ�");
		return NULL;
	}
	else{
		S=(List)malloc(sizeof(struct LNode));
		S->Data=X;
		S->Next=p->Next;
		p->Next=S;
		return PtrL;
	}
}

List Delete(int position,List PtrL)//����ɾ������Ϸ�λ��
{
	List p,s;
	if(position==1){
		s=PtrL;
		if(PtrL!=NULL)
			PtrL=PtrL->Next;
		else 
			return NULL;
		free(s);
		return PtrL;
	}
	p=FindKth(position-1,PtrL);
	if(p==NULL||p->Next==NULL){//Ҫɾ������position,��ǰ���Ԫ�ز�����Ҳ�޷�ɾ�� 
		printf("λ�ò��Ϸ�");
		return NULL;
	}
	else{
		s=p->Next;
		p->Next=s->Next;
		free(s);
		return PtrL;
	}
}	


int main()
{
	//������ 
	struct LNode L;
	List PtrL,s,p;
	PtrL=s=&L;//����ͷ�ڵ㣬��Ҫ�Ķ�PtrL��λ�ã�����һ������ȥ������ 
	
	//��ֵ�� 
	s->Data=3;//��ʼ��ͷ��ֵ 
	int i; 
	for(i=4;i<=8;i++){
		p=(List)malloc(sizeof(struct LNode)); //�����ռ� 
		p->Next=NULL;
		s->Next=p;
		s=s->Next;
		s->Data=i;
	} 
	 
	//�� 
	printf("��ǰ��%d\n",length(PtrL));

	//���ÿһ��Ԫ��
	p=PtrL;//��Ҫ�Ķ�ͷ���PtrL��λ�ã�����һ������ȥ������
	while(p){
		printf("%d ",p->Data);
		p=p->Next;
	} 
	
	//�������� 
	PtrL=Insert(1,1,PtrL);	
	PtrL=Insert(2,2,PtrL);
	PtrL=Insert(9,9,PtrL);
	PtrL=Insert(10,10,PtrL);
	
	//�±� 
	printf("\n�����ĵ�ǰ��%d\n",length(PtrL));
	
	//���ÿһ��Ԫ��
	p=PtrL; 
	while(p){
		printf("%d ",p->Data);
		p=p->Next;
	} 
	
	//Ѱ��Ԫ�ط���ָ�� 
	printf("\n��ǰ������Ԫ�ص�ַ��\n");
	p=PtrL;
	while(p){
		printf("%d\n",p->Data); 
		printf("%p\n",p);
		p=p->Next;
	}
	printf("FindKth(3,PtrL)=%p\n",FindKth(3,PtrL));
	printf("Find(2,PtrL)=%p\n",Find(2,PtrL));
	
	//ɾ��ָ��λ�õ�����
	printf("\nɾ��ָ��λ��֮��\n");
	PtrL=Delete(10,PtrL);
	PtrL=Delete(8,PtrL);
	
	p=PtrL;
	while(p){
		printf("%p\n",p);
		printf("%d\n",p->Data); 
		p=p->Next;
	}
	return 0; 
}

