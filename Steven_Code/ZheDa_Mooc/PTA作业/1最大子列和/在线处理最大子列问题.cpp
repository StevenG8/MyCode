#include <stdio.h>

//���ߴ��������������
 
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
		if(ThisSum<0){//�����ʱ��˳�����к�С��0�����������¿�ʼ 
			ThisSum=0;
		}
	}
	return MaxSum;
}

int main()
{
	char i;
	int A[]={-2,11,-4,13,-5,-2};
	
	printf("�ڵ�ǰ������");
	for(i=0;i<sizeof(A)/sizeof(int);i++){
		printf("%d ",A[i]);
	}
	printf("����������֮����%d\n",MaxSubSequence(A,sizeof(A)/sizeof(int)));
	printf("������е���βλ����"); 
	return 0;	
}
