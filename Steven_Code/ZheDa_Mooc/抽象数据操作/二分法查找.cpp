#include <stdio.h>

int BinarySearch(int x,int sort[],int n); 

int main()
{
	int Sort[10]={0,1,2,3,4,5,6,7,8,9};
	int x;
	scanf("%d",&x);
	printf("下标为%d",BinarySearch(x,Sort,sizeof(Sort)/sizeof(int)) ); 
	return 0;
}

//适用于从小到大已经排好序的二分查找 
int BinarySearch(int x,int sort[],int n)
{
	int result=-1;//返回-1表示未能本找到 
 
	int left=0;
	int right=n;
	int mid;
	while(left<right){
		mid=(left+right)/2;
		printf("当前的二分位置是%d\n",mid);
		if(x<sort[mid])
			right=mid;//注意这里并不减一！！！ 
		else if(x>sort[mid])
			left=mid+1;//这里要加一！！！ 
		else{
			result=mid;
			break;
		} 	 
	} 
	return result;
} 
