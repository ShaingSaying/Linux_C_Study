#include<stdio.h>
double power(double num,int n);
int main()
{
	double n=0;
	int p=0;
	printf("Please enter the base number and the exponent: ");
    	scanf("%lf %d", &n, &p);

    	printf("%.3g to the power %d is %.5g\n", n, p, power(n, p));
    
    	return 0;
}
double power(double num,int n)
{
	double res=num;
	int exp=0;
	if(num==0)
		return 0.0;
	if(n==0)
		return 1.0;
	exp=(n>0)?n:-n;
	while(--exp!=0)
	{
		res*=num;
	}
	return (n>0)?res:(double)1/res;
}
