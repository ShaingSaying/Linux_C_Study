#include<stdio.h>
int main()
{
	char ch;
	int i=0,j=0;
	while((ch=getchar())!='#')
	{
		switch(ch)
		{
			case '!': putchar('!');
				  i++;
				  break;
			case '.': ch='!';
				  j++;
				  break;
		}
		putchar(ch);
	}
	printf("total is %d\n",i+j);
	return 0;
}
