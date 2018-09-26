#include <stdio.h>

//在线处理最大子列问题
 
int MaxSubSequence(int A[],int N)
{
	char i;
	int MaxSum,ThisSum;
	MaxSum=ThisSum=0;
	for(i=0;i<N;i++){
		ThisSum+=A[i];
		if(ThisSum>MaxSum){
			MaxSum=ThisSum;
		}
		if(ThisSum<0){//如果此时的顺序子列和小于0，则舍弃重新开始 
			ThisSum=0;
		}
	}
	return MaxSum;
}

int main()
{
	char i;
	int A[]={-2,11,-4,13,-5,-2};
	
	printf("在当前的数列");
	for(i=0;i<sizeof(A)/sizeof(int);i++){
		printf("%d ",A[i]);
	}
	printf("中最大的子列之和是%d\n",MaxSubSequence(A,sizeof(A)/sizeof(int)));
	printf("这个子列的首尾位置是"); 
	return 0;	
}
