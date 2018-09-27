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
	(*rear)->next=P;//连接 
	(*rear)=P;//尾部指针指向最后一个元素 
}

Polynomial Add(Polynomial P1,Polynomial P2,int Del)
{
	if((P1&&P2)==0)//零输入的特殊处理 
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
	
	if(start->next){//释放只做索引无数据的头节点
		Polynomial Temp=start;
		start=start->next;
		free(Temp);
	}else{//如果是0+0的情况,作为基准 
		start->coef=0;
		start->expon=0;
	}
	
	//释放掉两个加数的空间 
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

//给予我的启发，多次重复使用的部分直接抽象出来单独做一个函数！ 
//这个函数是将第一个多项式看成是可拆的加项去乘以完整的第二个多项式
//最后把每一项的结果都给累加起来 
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
	if((P1&&P2)==0)//零输入的特殊处理 
		return NULL;
	
	Polynomial FirstCell,SecondCell,Cell,Result;
	Polynomial temp;
	
	//单独前两项的和，然后再推广 
	if((P1->next)||(P2->next)){//P1，P2之间至少有一个两项或以上，可以推广 
		if(P1->next==NULL){//交换一下使其满足推广式 
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
			Result=Add(Result,Cell,1);//执行加法结束后也会把两个加数的空间释放掉
			P1=P1->next; 
		}
	}
	else//两个都是只有一项 
		Result=TimeUnit(P1,P2);	 
		
	if(Del==1){	//  释放两个乘数的空间
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
	printf("第一个位置是总项数，接下来是“系数 指数”形式结束\n");
	scanf("%d",&Size);
	
	if(Size>1){//有两个数据以上 
		Polynomial FirstCell,SecondCell,Cell;
		FirstCell=ApplyUnitSpace();
		SecondCell=ApplyUnitSpace();//先做开头便于后面推广 
		Result=Add(FirstCell,SecondCell,1);//用加法的原因是为了在输入阶段就完成该式子的合并同类项 
		Size=Size-2;	
		while(Size--){
			Cell=ApplyUnitSpace();
			Result=Add(Cell,Result,1);
		}
	}else if(Size==1){//单个数据 
		Result=ApplyUnitSpace();
	}else{//0个数据，错误输入 
		return NULL;
	}
	
	return Result;
}

void OutputData(Polynomial P)
{
	if(P==NULL){
		printf("Error!输入项数为0");
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
	printf("乘法结果\n"); 
	OutputData(P4);
	Polynomial P3=Add(P1,P2,0);
	printf("加法结果\n"); 
	OutputData(P3);
	
	//释放空间 
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



/*妹的,原来scanf函数遇到空格也会结束,参考scanf读取多位数就明白了!*/
/***********************getchar(),scanf()************************/ 
//ElementType ReadUnit()
//{	
//	char c;
//	int Negative=0;
//	int temp=0;
//	while((c=getchar())!=' '){//等待单个数据读取完毕 
//		if(c=='\n')//读取到最后的回车做特殊处理 
//			break;
//		if(c=='-')//有负号出现 
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
