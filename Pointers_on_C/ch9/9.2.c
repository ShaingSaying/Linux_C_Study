#include<stdio.h>
#include<stdsef.h>

size_t my_strlen(char *string, int n)
{
	register size_t count==0;
	while(*string++ != '\0' && n-->0)
		count++;
	return count;
}
