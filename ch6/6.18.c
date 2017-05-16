#include<stdio.h>
int main()
{
	int a=5;
	int zou=1;
	while(a<=150)
	{
		a=(a-zou)*2;
		printf("%d's zou have %d's friends\n",zou,a);
		zou++;
	}
	return 0;
}
