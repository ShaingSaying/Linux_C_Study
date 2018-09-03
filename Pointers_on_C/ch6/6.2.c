#include<stdio.h>

char *match(char *str,const char *want)
{
	while(*want != '\0')
	{
		if(*str++ != *want++)
			return 0;
	}
	printf("get it str:%s\n",str);
	return str;
}

int del_substr(char *str, const char *substr)
{
	char *next=NULL;
	
	while(*str != '\0')
	{
		next = match(str, substr);
		if(next != 0)
			break;
		str++;
		printf("temp str:%s\n",str);
	}

	if(*str == '\0')
		return 0;
	printf("==next is:%s==\n",next);
	printf("==str is %s==\n",str);

	while(*str++=*next++)	//赋值操作
	{
		printf("temp char:[%c]\n",*(str-1));
		;
	}
	printf("temp char:[%c]\n",*(str-1));
	return 1;
}

int main(void)
{
	int res;
	char str[]="ABCDEFG";
	const char substr[]="CDE";
	printf("new str=[%s]\n",str);
	res = del_substr(str,substr);
	printf("new str=[%s]\n",str);
	return 0;
}
