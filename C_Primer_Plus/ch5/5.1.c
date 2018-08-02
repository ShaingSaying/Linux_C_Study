#include<stdio.h>
#define HPM 60
int main()
{
	int min=0;
	int hour=0;
	while(1)
	{
		printf("please input minute:(0 to quit)");
		scanf("%d",&min);
		if(min==0)
			break;
		while(min>=HPM)
		{
			hour=min/HPM;
			min=min%HPM;
		}
		printf("the minute is equal %d hour %d minutes.\n",hour,min);
	}
	return 0;
}
