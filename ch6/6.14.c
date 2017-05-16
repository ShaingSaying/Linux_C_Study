#include<stdio.h>
int main()
{
	double arr1[8],arr2[8];
	int i;
	for(i=0;i<8;i++)
		arr1[i]+=(i+1);
	arr2[0]=arr1[0];
	for(i=1;i<8;i++)
		arr2[i]=arr2[i-1]+arr1[i];
	for(i=0;i<8;i++)
		printf("%-8.2lf",arr1[i]);
	printf("\n");
	for(i=0;i<8;i++)
		printf("%-8.2lf",arr2[i]);
	printf("\n");
	return 0;
}
