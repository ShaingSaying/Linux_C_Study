#include<stdio.h>
int main()
{
	int a =97;
	//printf("%d\t%c\n",a,a);
	int i=0;
	int b[26];
	for(i=0;i<26;i++)
	{
		b[i]=a+i;
		printf("%c ",b[i]);
	}
	printf("\n");
	return 0;
}
