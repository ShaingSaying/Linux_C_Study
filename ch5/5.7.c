#include<stdio.h>
double cube_value(double x);
int  main()
{
	double d;
	printf("please input a double vule:");
	scanf("%lf",&d);
	printf("%.2lf's cuble value is %.2lf\n",d,cube_value(d));
	return 0;
}
double cube_value(double x)
{
	double y;
	y=x*x*x;
	return y;
}
