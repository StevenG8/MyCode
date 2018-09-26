#include <stdio.h>

int Max3(int a,int b,int c)//求三者的最大值 
{
	if(a>b&&a>c)
		return a;
	else if(b>a&&b>c)
		return b;
	else
		return c;	
}

static int MaxSubSum(const int A[],int Left,int Right)
{
	int MaxLeftSum,MaxRightSum;
	int MaxLeftBorderSum,MaxRightBorderSum;
	int LeftBorderSum,RightBorderSum;
	int Center,i;
	
	//递归基准情况(适用于左右两个子列) 
	if(Left==Right){//二分法到最后只剩一个数字 
		if(A[Left]>0)
			return A[Left];//如果这个数字是正的就保留下来
			//return之后的内容仍然会进行，但是返回的值已经确定了是不会改变的！ 
		else
			return 0;//负数无视 
	}
	
	Center=(Left+Right)/2;
	MaxLeftSum=MaxSubSum(A,Left,Center);
	MaxRightSum=MaxSubSum(A,Center+1,Right);
	//不断地二分法，从边上最小的单独一个数的子列一个一个地录入一直到最大的子列 
	
	//求出当前二分法中左右列中的最大子列和 
	//这里是“分” 
	MaxLeftBorderSum=0; 
	LeftBorderSum=0;
	for(i=Center;i>=Left;i--){
		LeftBorderSum+=A[i];
		if(LeftBorderSum>MaxLeftBorderSum)
			MaxLeftBorderSum=LeftBorderSum;
	}
	
	MaxRightBorderSum=0;
	RightBorderSum=0;
	for(i=Center+1;i<=Right;i++){
		RightBorderSum+=A[i];
		if(RightBorderSum>MaxRightBorderSum)
			MaxRightBorderSum=RightBorderSum;
	}
	
	//计算左边的最大子列，右边的最大子列，再计算整个合并的值，取三者最大值作为最大子列 
	//这里是“治” 
	return Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
}
 
int MaxSubSequenceSum(const int A[],int N)
{
	return MaxSubSum(A,0,N-1);
}

int main()
{
	char i;
	int A[]={1,5,-4,8,1,-12,9,2,-6,8,8};
	
	printf("在当前的数列");
	for(i=0;i<sizeof(A)/sizeof(int);i++){
		printf("%d ",A[i]);
	}
	printf("中最大的子列之和是%d\n",MaxSubSequenceSum(A,sizeof(A)/sizeof(int)));
	printf("这个子列的首尾位置是"); 
	return 0;	
}


//T(N)=T(N/2)+T(N/2)+O(N),O(N)是扫描左右两个子列所耗费的时间，T(N/2)是递归调用两个子列所耗费的时间
//不断递归调用，就变成了T(N/2)=T(N/4)*2+O(N/2)...... 
//同理S(N) 
