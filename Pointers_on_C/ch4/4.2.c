#include<stdio.h>
int main()
{
	int i,j;
	for(i=3;i<=100;i+=2)
	{
		for(j=3;j<i;j+=2)
		{
			if(i%j==0)
				break;
		}
		if(j>=i)
			printf("%d ",i);
	}
	printf("\n");
	return 0;
}
