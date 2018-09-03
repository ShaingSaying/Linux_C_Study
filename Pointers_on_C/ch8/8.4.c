#include<stdio.h>

int identity_matrix(int *a,int len)
{
	int i,j;
	for(i=0;i<len;i++)
	{
		for(j=0;j<len;j++)
		{
			if((i==j)&&(*(a++)==1))
				printf("1\n");
			else if((i!=j)&&(*(a++)==0))
				printf("0\n");
			else
				return 1;
		}
	}
	return 0;
}

int main()
{
	
	int a[3][3]={{1,0,0},{0,1,0},{0,0,1}};
	int res;
	res=identity_matrix(&a[0][0],3);
	printf("res=%d\n",res);
	return 0;
}
