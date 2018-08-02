#include<stdio.h>
int main()
{
	int i,j,k,l;
	char a;
	printf("please input a number:");
	scanf("%c",&a);
	a=a-4;
	for(i=0;i<5;i++)
	{
	
		for(j=0;j<4-i;j++)
		{
			printf(" ");
		}
		for(k=0;k<i+1;k++)
		{
			printf("%c",a);
			a+=1;
		}
		a=a-1;
		for(l=0;l<i;l++)
		{
			a-=1;
			printf("%c",a);	
		}
		printf("\n");
	}
	return 0;
}
