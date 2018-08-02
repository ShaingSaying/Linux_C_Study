#include<stdio.h>
int main()
{
	float a,b;
	printf("please input two float value:");
	while(scanf("%f%f",&a,&b)==2)
	{
		printf("the result is %f\n",(a-b)/(a*b));
		printf("please input two float value:");
	}
	return 0;
}
