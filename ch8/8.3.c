#include<stdio.h>
#include<ctype.h>
int main()
{
	char ch;
	int lower=0,upper=0;
	while((ch=getchar())!=EOF)
	{
		if(islower(ch))
			lower++;
		if(isupper(ch))
			upper++;
	}
	printf("lower: %d\n",lower);
	printf("upper: %d\n",upper);
	return 0;
}
