#include<stdio.h>
#include<string.h>
int encrypt(int ch, int base)
{
	ch -= base;
	ch += 13;
	ch %= 26;
	return ch+base;
}
int main()
{
	int ch;
	while((ch=getchar())!=EOF)
	{
		if(ch>='A' && ch<='Z')
			ch = encrypt(ch, 'A');
		else if(ch>='a' && ch<='z')
			ch = encrypt(ch,'a');
		else
			;
		putchar(ch);
	}
	return 0;
}
