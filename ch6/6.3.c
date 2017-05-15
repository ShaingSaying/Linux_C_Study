#include<stdio.h>
int main()
{
	int a=70;
	int i,j;
	for(i=0;i<6;i++)
	{
		a=70;
		for(j=0;j<i+1;j++)
		{
			printf("%c",a);
			a-=1;
		}
		printf("\n");
	}
	return 0;
}
