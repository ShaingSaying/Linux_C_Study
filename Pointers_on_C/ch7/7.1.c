#include<stdio.h>

int hermite(int n,int x)
{
	if(n<=0)
		return 1;
	if(1==n)
		return 2*x;
	if(n>=2)
		return (2*x*hermite(n-1,x))-(2*(n-1)*hermite(n-2,x));
}

int main()
{
	int res=0;
	res=hermite(3,2);
	printf("res=%d\n",res);
	return 0;
}
