#include<stdio.h>
int arr_max(int arr[],int n);
int main()
{
	int arr[]={1,2,3,4,5,6,7,8,9};
	printf("the max number is:%d\n",arr_max(arr,9));
	return 0;
}
int arr_max(int arr[],int n)
{
	int max=arr[0];
	int i;
	for(i=1;i<n;i++)
	{
		if(arr[i]>max)
			max=arr[i];	
	}
	return max;
}
