#include<stdio.h>
#include<string.h>

int main()
{
	int ch;
	while((ch=getchar())!=EOF)
	{

		if(ch>=65&&ch<=90)
		{
			ch=ch+32;
		}
		putchar(ch);
	}
	return 0;
}
