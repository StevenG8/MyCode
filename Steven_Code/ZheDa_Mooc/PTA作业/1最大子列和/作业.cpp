#include <stdio.h>

int MaxSubSuquence(int A[],int N); 
int main()
{
	int i,k,temp;
	k=temp=0;
	char c,flag=0;
	scanf("%d",&i);//总共有多少个整数
	int A[i];
	getchar();//吸收回车 
	
	while( ((c=getchar())!='\n')&& (k<i) ){
		if(c==' '){
			if(flag==1)
				A[k++]=-temp;
			else
				A[k++]=temp;
			temp=0;
			flag=0;
		}
		else{
			if(c=='-')
				flag=1;
			else
				temp=temp*10+(c-48);
		}
	} 
	if(flag==1)
		A[k]=-temp;
	else
		A[k]=temp;
	
	printf("%d",MaxSubSuquence(A,i));
	return 0;
} 
int MaxSubSuquence(int A[],int N)
{
	int k;
	int ThisSum,MaxSum; 
	ThisSum=MaxSum=0;
	for(k=0;k<N;k++){
		ThisSum+=A[k];
		if(ThisSum<0)
			ThisSum=0;
		if(ThisSum>MaxSum)
			MaxSum=ThisSum;
	}
	return MaxSum;
}
