
//x是未知量，N是多项式项数，a[]是多项式的系数数组 
double QingJiuShao(double x,int n,int a[])
{
	double sum=a[n];//第一项要初始化 
	int i;
	for(i=n;i>0;i--){
		sum=sum*x+a[n-1];//a[n-1]是下一项的系数 
	}	
	return sum;
}
