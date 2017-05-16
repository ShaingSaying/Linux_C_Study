#include<stdio.h>
int main()
{
	int arr[8];
	int i;
	for(i=0;i<8;i++)
	{
		printf("Enter the %d's numbers into array:",i+1);
		scanf("%d",&arr[i]);
	}
	for(i=7;i>=0;i--)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;

}
