#include<stdio.h>

int main(int argc, char *argv[])
{
	int ch;
	signed char checksum = -1;
	while((ch=getchar())!=EOF)
	{
		checksum+=ch;
		putchar(ch);
	}		
	printf("%d\n",checksum);
	return 0;
}
