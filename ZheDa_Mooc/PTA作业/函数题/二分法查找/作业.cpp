#include <stdio.h>

int BinarySearch(int x,int sort[],int n); 

int main()
{
	int Sort[10]={0,1,2,3,4,5,6,7,8,9};
	int x;
	scanf("%d",&x);
	printf("�±�Ϊ%d",BinarySearch(x,Sort,sizeof(Sort)/sizeof(int)) ); 
	return 0;
}

//�����ڴ�С�����Ѿ��ź���Ķ��ֲ��� 
int BinarySearch(int x,int sort[],int n)
{
	int result=-1;//����-1��ʾδ�ܱ��ҵ� 
 
	int left=0;
	int right=n;
	int mid;
	while(left<right){
		mid=(left+right)/2;
		printf("��ǰ�Ķ���λ����%d\n",mid);
		if(x<sort[mid])
			right=mid;//ע�����ﲢ����һ������ 
		else if(x>sort[mid])
			left=mid+1;//����Ҫ��һ������ 
		else{
			result=mid;
			break;
		} 	 
	} 
	return result;
} 
