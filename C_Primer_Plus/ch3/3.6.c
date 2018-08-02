#include<stdio.h>
int main()
{
	int kuake=0;
	const double per_water_quality=3.0e-23;
	printf("please input how many kuake: ");
	scanf("%d",&kuake);
	printf("%d kuake water have %e water number\n",kuake,(double)(kuake*950)/per_water_quality);
	return 0;

}
