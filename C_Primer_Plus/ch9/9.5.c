#include<stdio.h>
void larger_of(double a,double b);
int main()
{
	double x,y;
	x=98.23;
	y=76.52;
	larger_of(y,x);
	return 0;	
}
void larger_of(double a,double b)
{
	a=b=a>b?a:b;
	printf("a=b=%.2lf\n",a);
}
