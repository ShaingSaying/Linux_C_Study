#include<stdio.h>
#include<ctype.h>
int locate_alphabet(char ch);
int main()
{
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(isalpha(ch))
		{
			printf("%c is %d.\n",ch,locate_alphabet(ch));
		}
	}
	return 0;
}
int locate_alphabet(char ch)
{
	if(islower(ch))
	{
		return ch-'a'+1;
	}
	else if(isupper(ch))
	{
		return ch-'A'+1;
	}
	else
	{
		return -1;
	}

}
