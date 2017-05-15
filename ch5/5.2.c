#include<stdio.h>
int main()
{
	int num=0;
	int i=0;
	printf("please input a number:");
	scanf("%d",&num);
	for(i=0;i<=10;i++)
	{
		printf("%d\t",num+i);
	}
	printf("\n");
	return 0;
}
