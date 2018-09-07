#include<stdio.h>
#include<string.h>

char *my_strcpy_end(char dst,char src)
{
	strcpy(dst,src);
	int  length = strlen(dst);
	dst += length;
	return dst;
}

char *my_strcpy_end(char dst,char src)
{
	while(*dst!='\0')
		dst++;
	while(*src != '\0')
		*dst++=*src++;
	return 
}
