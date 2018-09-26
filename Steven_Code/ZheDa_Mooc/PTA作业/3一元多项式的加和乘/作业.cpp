#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node* Polynomial;
struct Node{
	int coef;
	int expon;
	Polynomial next;
};

int compare(int e1,int e2);
void Attach(int c,int e,Polynomial* rear);
Polynomial Add(Polynomial P1,Polynomial P2,int Del);
Polynomial TimeUnit(Polynomial P1,Polynomial P2);
Polynomial Time(Polynomial P1,Polynomial P2,int Del);
Polynomial ReadData();
Polynomial ApplyUnitSpace();
void OutputData(Polynomial P);

int compare(int e1,int e2)
{
	if(e1>e2) 
		return 1;
	else if(e1<e2)
	    return -1;
	else return 0;
}

void Attach(int c,int e,Polynomial* rear)
{
	Polynomial P=(Polynomial)malloc(sizeof(struct Node));
	P->coef=c;
	P->expon=e;
	P->next=NULL;
	(*rear)->next=P;//���� 
	(*rear)=P;//β��ָ��ָ�����һ��Ԫ�� 
}

Polynomial Add(Polynomial P1,Polynomial P2,int Del)
{
	if((P1&&P2)==0)//����������⴦�� 
		return NULL;
	
	int sum;
	Polynomial start,rear;
	Polynomial temp1=P1,temp2=P2;
	start=rear=(Polynomial)malloc(sizeof(struct Node));
	start->next=NULL;
	
	while(P1&&P2){
		switch(compare(P1->expon,P2->expon)){
			case 1:
				if(P1->coef)
					Attach(P1->coef,P1->expon,&rear);
				P1=P1->next;
				break;
			case -1:
				if(P2->coef)
					Attach(P2->coef,P2->expon,&rear);
				P2=P2->next;
				break;
			case 0:
				sum=P1->coef+P2->coef;
				if(sum)
					Attach(sum,P1->expon,&rear);
				P1=P1->next;
				P2=P2->next;
				break;
		}
	}
	for(;P1;P1=P1->next){ 
		if(P1->coef) 
			Attach(P1->coef,P1->expon,&rear);
	} 
	for(;P2;P2=P2->next){ 
		if(P2->coef)
			Attach(P2->coef,P2->expon,&rear);
	} 
	
	if(start->next){//�ͷ�ֻ�����������ݵ�ͷ�ڵ�
		Polynomial Temp=start;
		start=start->next;
		free(Temp);
	}else{//�����0+0�����,��Ϊ��׼ 
		start->coef=0;
		start->expon=0;
	}
	
	//�ͷŵ����������Ŀռ� 
	if(Del==1){
		Polynomial Temp;
		while(temp2){
			Temp=temp2;
			temp2=temp2->next;
			free(Temp);
		}
		while(temp1){
			Temp=temp1;
			temp1=temp1->next;
			free(Temp);
		}	
	}
	
	return start;
}

//�����ҵ�����������ظ�ʹ�õĲ���ֱ�ӳ������������һ�������� 
//��������ǽ���һ������ʽ�����ǿɲ�ļ���ȥ���������ĵڶ�������ʽ
//����ÿһ��Ľ�������ۼ����� 
Polynomial TimeUnit(Polynomial P1,Polynomial P2)
{
	Polynomial start,rear; 
	int coef,expon;
	start=rear=(Polynomial)malloc(sizeof(struct Node));
	
	while(P2){
		coef=(P1->coef)*(P2->coef);
		expon=(P1->expon)+(P2->expon);
		Attach(coef,expon,&rear);
		P2=P2->next;
	}
	
	Polynomial temp=start;
	start=start->next;
	free(temp);
	
	return start;		
}

Polynomial Time(Polynomial P1,Polynomial P2,int Del)
{
	if((P1&&P2)==0)//����������⴦�� 
		return NULL;
	
	Polynomial FirstCell,SecondCell,Cell,Result;
	Polynomial temp;
	
	//����ǰ����ĺͣ�Ȼ�����ƹ� 
	if((P1->next)||(P2->next)){//P1��P2֮��������һ����������ϣ������ƹ� 
		if(P1->next==NULL){//����һ��ʹ�������ƹ�ʽ 
			temp=P1;
			P1=P2;
			P2=temp;
		}
		FirstCell=TimeUnit(P1,P2);
		P1=P1->next;
		SecondCell=TimeUnit(P1,P2);
		P1=P1->next;
		Result=Add(FirstCell,SecondCell,1);
		while(P1){
			Cell=TimeUnit(P1,P2);
			Result=Add(Result,Cell,1);//ִ�мӷ�������Ҳ������������Ŀռ��ͷŵ�
			P1=P1->next; 
		}
	}
	else//��������ֻ��һ�� 
		Result=TimeUnit(P1,P2);	 
		
	if(Del==1){	//  �ͷ����������Ŀռ�
		while(P1){
		Cell=P1;
		P1=P1->next;
		free(Cell);
		} 
		while(P2){
		Cell=P2;
		P2=P2->next;
		free(Cell);
		}	
	}
	
	return Result;	
}

Polynomial ApplyUnitSpace()
{
	Polynomial temp=(Polynomial)malloc(sizeof(struct Node));
	scanf("%d %d",&temp->coef,&temp->expon);
	temp->next=NULL;
	return temp; 
} 

Polynomial ReadData()
{
	int Size;
	Polynomial Result;
	printf("��һ��λ�������������������ǡ�ϵ�� ָ������ʽ����\n");
	scanf("%d",&Size);
	
	if(Size>1){//�������������� 
		Polynomial FirstCell,SecondCell,Cell;
		FirstCell=ApplyUnitSpace();
		SecondCell=ApplyUnitSpace();//������ͷ���ں����ƹ� 
		Result=Add(FirstCell,SecondCell,1);//�üӷ���ԭ����Ϊ��������׶ξ���ɸ�ʽ�ӵĺϲ�ͬ���� 
		Size=Size-2;	
		while(Size--){
			Cell=ApplyUnitSpace();
			Result=Add(Cell,Result,1);
		}
	}else if(Size==1){//�������� 
		Result=ApplyUnitSpace();
	}else{//0�����ݣ��������� 
		return NULL;
	}
	
	return Result;
}

void OutputData(Polynomial P)
{
	if(P==NULL){
		printf("Error!��������Ϊ0");
		return; 
	}
	
	while(P->next){
		printf("%d %d ",P->coef,P->expon);
		P=P->next;
	}
	printf("%d %d\n",P->coef,P->expon);
}

int main()
{
	Polynomial P1=ReadData();
	Polynomial P2=ReadData();
//	OutputData(P1);
//	OutputData(P2);
	Polynomial P4=Time(P1,P2,0);
	printf("�˷����\n"); 
	OutputData(P4);
	Polynomial P3=Add(P1,P2,0);
	printf("�ӷ����\n"); 
	OutputData(P3);
	
	//�ͷſռ� 
	Polynomial Cell;
	while(P1){
		Cell=P1;
		P1=P1->next;
		free(Cell);
	} 
	while(P2){
		Cell=P2;
		P2=P2->next;
		free(Cell);
	}
	return 0;
}



/*�õ�,ԭ��scanf���������ո�Ҳ�����,�ο�scanf��ȡ��λ����������!*/
/***********************getchar(),scanf()************************/ 
//ElementType ReadUnit()
//{	
//	char c;
//	int Negative=0;
//	int temp=0;
//	while((c=getchar())!=' '){//�ȴ��������ݶ�ȡ��� 
//		if(c=='\n')//��ȡ�����Ļس������⴦�� 
//			break;
//		if(c=='-')//�и��ų��� 
//			Negative=1;
//		else
//			temp=temp*10+(c-48);
//	}
//	if(Negative==1){
//		temp=-temp;
//		Negative=0;
//	}
//	return temp;		
//}
