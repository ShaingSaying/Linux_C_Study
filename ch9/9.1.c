#include<stdio.h>
double min(double a,double b);
int main()
{
	double num1,num2;
	scanf("%lf%lf",&num1,&num2);
	printf("the min num is %.2lf\n",min(num1,num2));
	return 0;
}
double min(double a,double b)
{
	return a<b?a:b;
}
