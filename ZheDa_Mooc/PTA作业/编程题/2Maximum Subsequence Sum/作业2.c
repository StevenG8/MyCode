#include <stdio.h>

void MaxSubSuquence(int A[],int N);
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

	MaxSubSuquence(A,i);
	return 0;
}
void MaxSubSuquence(int A[],int N)
{
	int k,temp,flag,finish;
	int ThisSum,MaxSum;
	ThisSum=MaxSum=0;
	int start,stop,StartTemp;
	start=StartTemp=0;
	stop=N-1;
	flag=finish=1;
	for(k=0;k<N;k++){
		ThisSum+=A[k];
		if(ThisSum>MaxSum){
			MaxSum=ThisSum;
			stop=k;//比旧子列大就更新结尾和开头
			start=StartTemp;
			flag=0;//只要有一个数值大于0就可以不考虑全零和负数的情况
		}
		else if(ThisSum==0&&MaxSum==0&&finish){//全是零和负数的特殊情况
			temp=k;
			finish=0;//两个零取位置靠前的
		}
		if(ThisSum<0){
			ThisSum=0;
			StartTemp=k+1;//暂存的开头，只有大于旧的子列才转正
		}
	}

	if(flag==0)//正常情况即存在正数，有最大子列
		printf("%d %d %d",MaxSum,A[start],A[stop]);
	else {//没有正数
		if(finish==0)//有零
			printf("%d %d %d",MaxSum,A[temp],A[temp]);
		else//全是负数
			printf("%d %d %d",MaxSum,A[0],A[N-1]);
	}
}
