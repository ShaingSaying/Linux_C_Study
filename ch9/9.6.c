#include<stdio.h>
void three(double* a,double* b,double* c);
int main()
{
	double a=76.5,b=21.8,c=99.9;
	double *x,*y,*z;
	x=&a;y=&b;z=&c;
	three(x,y,z);
	return 0;
}
void three(double* a,double* b,double* c)
{
	double tem;
	if(*a>*b)
	{  tem=*a;*a=*b;*b=tem;}
	if(*a>*c)
	{  tem=*a;*a=*c;*c=tem;}
	if(*b>*c)
	{  tem=*b;*b=*c;*c=tem;}
	printf("a=%.2lf b=%.2lf c=%.2lf\n",*a,*b,*c);
}
