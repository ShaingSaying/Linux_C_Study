#include<stdio.h>
int main()
{
	int num,odd,even;
	int odd_sum=0;
	int even_sum=0;
	even=0;
	odd=0;
	num=0;
	while((scanf("%d",&num)==1)&&num!=0)
	{
		if(num%2==0)
		{
			odd++;
			odd_sum+=num;
		}
		else
		{
			even++;
			even_sum+=num;
		}
	}
	printf("even number:%d and average is %.2f\n",even,(float)even_sum/even);
	printf("odd number:%d and average is %.2f\n",odd,(float)odd_sum/odd);
	return 0;
}
