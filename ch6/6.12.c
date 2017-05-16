#include<stdio.h>
int main()
{
	int i,n,k;
	float res1,res2;
	printf("please input how many turns do you want:");
	scanf("%d",&n);
	while(n>0)
	{
		res1=0.0;
		res2=0.0;
		k=1;
		for(i=1;i<=n;i++)
		{
			res1+=1/(float)i;
			res2+=k/(float)i;
			k=-k;
		}
		printf("the result is %f\n",res1+res2);
		printf("please input how many turns do you want:");
		scanf("%d",&n);
	}
	return 0;
}
