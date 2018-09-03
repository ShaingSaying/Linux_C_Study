#include<stdio.h>

int identity_matrix(int a[10][10])
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if((i==j)&&(a[i][j]==1))
				printf("1\n");
			else if((i!=j)&&(a[i][j]==0))
				printf("0\n");
			else
				return 1;
		}
	}
	return 0;
}

int main()
{
	int a[10][10]={1,0};
	int res;
	res=identity_matrix(a);
	printf("res=%d\n",res);
	return 0;
}
