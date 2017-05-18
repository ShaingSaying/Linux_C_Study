#include<stdio.h>
int main()
{
	char ch;
	int i=0,j=0;
	while((ch=getchar())!='#')
	{
		if(ch=='!')
		{
			putchar('!');
			i++;
		}
		if(ch=='.')
		{
			//++ch='!';
			ch='!';
			j++;
		}
		putchar(ch);
	}
	printf("\n");
	printf("total is: %d\n",i+j);
	return 0;
}
