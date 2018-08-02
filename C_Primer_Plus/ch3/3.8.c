#include<stdio.h>
#define BTP 0.5
#define BTA 8
#define ATD 2
#define	DTC 3
int main()
{
	float num=0.0;
	printf("please input the cup number: ");
	scanf("%f",&num);
	printf("the cup equal %.2f B\n",num*BTP);
	printf("the cup equal %.2f A\n",num*BTA);
	printf("the cup equal %.2f D\n",num*BTA*ATD);
	printf("the cup equal %.2f C\n",num*BTA*ATD*DTC);
	return 0;
}
