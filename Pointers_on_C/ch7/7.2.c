#include<stdio.h>

int gcd(int M, int N)
{
	int T;
	if(0==M || 0==N)
	{
		return 0;
	}
	if(M%N==0)
		return N;
	else if((T=M%N)&&T>0)
		return gcd(N,T);
	else
		;
}

int main()
{
	printf("res=%d\n",gcd(45,15));
	return 0;
}
