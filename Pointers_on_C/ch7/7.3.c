#include<stdio.h>

int ascii_to_integer(char *string)
{
	char *temp;
	int a=0;
	temp=string;
	for(;*temp!='\0';temp++)
	{
		a=a*10+(int)(*temp-'0');
		printf("temp a:%d\n",a);	
	}
	return a;
}

int main()
{
	char a[]="1234567";
	printf("%d\n",ascii_to_integer(a));
	return 0;
}
