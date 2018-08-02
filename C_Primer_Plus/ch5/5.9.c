#include<stdio.h>
void Tem(double a);
int main()
{
	double tem;
	printf("please input a number:");
	while(scanf("%lf",&tem)==1)
	{
		Tem(tem);
		printf("please input a number:");
	}
	return 0;
}
void Tem(double a)
{
	double s_tem,k_tem;
	const float ss=32.0;
	const float kk=273.16;
	s_tem=(5.0/9.0)*(a-ss);
	k_tem=s_tem+kk;
	printf("%.2lf	%.2lf	%.2lf\n",a,s_tem,k_tem);
}
