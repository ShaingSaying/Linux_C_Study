#include<stdio.h>
double aver(double a,double b);
int main()
{
	double x,y;
	x=2;
	y=4;
	printf("the result is %.2lf\n",aver(x,y));
	return 0;
}
double aver(double a,double b)
{
	a=1/a;
	b=1/b;
	a=(a+b)/2;
	a=1/a;
	return a;
}
