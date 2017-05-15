#include<stdio.h>
int main()
{
	const int days_per_week=7;
	int day=0;
	int week=0;
	int days=0;
	printf("please input days:(<0 to quit):");
	scanf("%d",&day);
	while(day>0)
	{
		do
		{
			week=day/days_per_week;
			days=day%days_per_week;
		}while(days>=7);
		printf("%d days are %d weeks,%d days.\n",day,week,days);
		printf("please input days:(<0 to quit):");
		scanf("%d",&day);
	}
	return 0;
}
