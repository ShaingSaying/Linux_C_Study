#include<stdio.h>
int main()
{
	int i,j;
	int a=65;
	for(i=0;i<6;i++)
	{
		for(j=0;j<i+1;j++)
		{
			printf("%c",a);
			a+=1;
		}
		printf("\n");
	}
	return 0;
}
