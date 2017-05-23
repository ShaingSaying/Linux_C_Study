#include<stdio.h>
int floo(int i);
int main()
{
	int i,res;
	for(i=0;i<10;i++)
	{
		res=floo(i);
		printf("%d ",res);
	}
	printf("\n");
	return 0;
}
int floo(int i)
{
	return i+1;
}
