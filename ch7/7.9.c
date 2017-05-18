#include<stdio.h>
int main()
{
	int num;
	int i,j,k=0;
	while(scanf("%d",&num)!=1)
	{
		printf("error!\n");
	}
	for(i=2;i<=num;i++)
	{
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			break;
		}
		if(j>=i)
		{
			printf("%-4d",i);
			k++;
			if(k%8==0)
				printf("\n");
		}
	}
	printf("\n");
	return 0;
}
