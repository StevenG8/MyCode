#include <time.h>

clock_t start,stop;
double duration;	

int main()
{	
	start=clock();
	Function(); 
	stop=clock();
	duration=(stop-start)/CLK_TCK/10000;
	printf("duration=%f",duration); 
} 
