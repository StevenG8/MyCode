#include <stdio.h>

int Max3(int a,int b,int c)//�����ߵ����ֵ 
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
	
	//�ݹ��׼���(������������������) 
	if(Left==Right){//���ַ������ֻʣһ������ 
		if(A[Left]>0)
			return A[Left];//���������������ľͱ�������
			//return֮���������Ȼ����У����Ƿ��ص�ֵ�Ѿ�ȷ�����ǲ���ı�ģ� 
		else
			return 0;//�������� 
	}
	
	Center=(Left+Right)/2;
	MaxLeftSum=MaxSubSum(A,Left,Center);
	MaxRightSum=MaxSubSum(A,Center+1,Right);
	//���ϵض��ַ����ӱ�����С�ĵ���һ����������һ��һ����¼��һֱ���������� 
	
	//�����ǰ���ַ����������е�������к� 
	//�����ǡ��֡� 
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
	
	//������ߵ�������У��ұߵ�������У��ټ��������ϲ���ֵ��ȡ�������ֵ��Ϊ������� 
	//�����ǡ��Ρ� 
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
	
	printf("�ڵ�ǰ������");
	for(i=0;i<sizeof(A)/sizeof(int);i++){
		printf("%d ",A[i]);
	}
	printf("����������֮����%d\n",MaxSubSequenceSum(A,sizeof(A)/sizeof(int)));
	printf("������е���βλ����"); 
	return 0;	
}


//T(N)=T(N/2)+T(N/2)+O(N),O(N)��ɨ�����������������ķѵ�ʱ�䣬T(N/2)�ǵݹ���������������ķѵ�ʱ��
//���ϵݹ���ã��ͱ����T(N/2)=T(N/4)*2+O(N/2)...... 
//ͬ��S(N) 
