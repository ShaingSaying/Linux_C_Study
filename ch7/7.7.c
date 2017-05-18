#include<stdio.h>
#define BASE 10
#define MORE 1.5
#define PRE_TAX 0.15
#define MID_TAX 0.2
#define END_TAX 0.25
int main()
{
	int time;
	int money;
	float tax;
	printf("please input how many time you work:");
	scanf("%d",&time);
	if(time<=40)
	{
		money=time*BASE;
	}
	else
	{
		time=(time-40)*MORE;
		money=time*BASE+40*BASE;
	}
	if(money<=300)
	{
		tax=money*PRE_TAX;
	}
	else if(money>300&&money<=450)
	{
		tax=(money-300)*MID_TAX+300*PRE_TAX;
	}
	else
	{
		tax=(money-450)*END_TAX+150*MID_TAX+300*PRE_TAX;
	}
	printf("your money is %d tax is %.2f and result is %.2f\n",money,tax,money-tax);
	return 0;
}
