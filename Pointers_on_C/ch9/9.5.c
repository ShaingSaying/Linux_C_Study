#include<stdio.h>
#include<string.h>

void my_strncat(char *dest, char src, int dest_len)
{
	register int len;
	len = strlen(dst);
	dest_len -=len+1;
	if(dest_len>0)
		strncat(dest, src, dest_len);
}
