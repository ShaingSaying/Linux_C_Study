#include<stdio.h>
int main()
{
	int lower,upper;
	int i;
	int res=0;
	printf("Enter lower and upper integer limits: ");
	scanf("%d%d",&lower,&upper);
	while(upper>lower)
	{
		for(i=lower;i<=upper;i++)
			res+=i*i;
		printf("The sums of the squares from %d to %d is %d\n",lower,upper,res);
		printf("Enter lower and upper integer limits: ");
		scanf("%d%d",&lower,&upper);
	}
	printf("Done\n");
	return 0;
}
