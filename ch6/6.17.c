#include<stdio.h>
#define MONEY 100
int main()
{
	int year=1;
	float money=MONEY;
	while(money>0)
	{
		money=money+money*0.08;
		money=money-10;
		year++;
	}
	printf("%d year well gg\n",year);
	return 0;
}
