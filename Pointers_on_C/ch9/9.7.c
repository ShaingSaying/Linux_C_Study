#include<stdio.h>
#include<string.h>

char *my_strrchar(const char *str, int ch)
{
	char *prev_answer=NULL;
	for(;(str=strchr(str,ch))!=NULL;str+=1)
		prev_answer=str;

	return prev_answer;
}
