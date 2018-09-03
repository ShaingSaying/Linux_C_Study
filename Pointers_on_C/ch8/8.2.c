#include<stdio.h>

float single_tax(float income)
{
	if(income>0&&income<=23350)
		return income*0.15;
	else if(income>23350&&income<=56550)
		return 35502.5+(income-23350)*0.28;
	else if(income>56550&&income<=117950)
		return 12798.50+(income-56550)*0.31;
	else if(income>117950&&income<=256500)
		return 31832.5+(income-117950)*0.36;
	else
		return 81710.5+(income-256500)*0.396;
	
}

int main()
{
	printf("res=%f\n",single_tax(54321.0));
	return 0;
}
