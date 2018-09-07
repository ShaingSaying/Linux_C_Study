#include<stdio.h>
#include<string.h>

char *my_strcat(char *dst, char *src, int size)
{
	size_t length=size-1-my_strlen(dst,size);
	if(length>0)
	{
		strncat(dst,src,length);
		*(dst+size-1)='\0';
	}
	return dst;
}
