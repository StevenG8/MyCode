
//x��δ֪����N�Ƕ���ʽ������a[]�Ƕ���ʽ��ϵ������ 
double QingJiuShao(double x,int n,int a[])
{
	double sum=a[n];//��һ��Ҫ��ʼ�� 
	int i;
	for(i=n;i>0;i--){
		sum=sum*x+a[n-1];//a[n-1]����һ���ϵ�� 
	}	
	return sum;
}
