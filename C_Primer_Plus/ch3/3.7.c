#include<stdio.h>
#define INCH_PER_CM 2.54
int main()
{
	float inch=0.0;
	printf("please input your inch: ");
	scanf("%f",&inch);
	printf("your inch equal %.2f cm\n",inch*INCH_PER_CM);
	return 0;
}
