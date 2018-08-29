#include<stdio.h>

int main()
{
	int n;
	double a=1.0;
	double lasta=0.0;
	printf("please input a number:\n");
	scanf("%d",&n);
	while(a!=lasta)
	{
		lasta=a;
		a=(double)((a+n/a)/2);
		printf("temp a:%lf\n",a);
	}
	printf("final a:%lf\n",a);
	return 0;
}
