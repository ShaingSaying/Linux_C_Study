#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int count_the(char *string)
{
	int count=0;
	char whitespace[]=" \t\f\r\v\n";
	char *p;
	for(p=strtok(string,whitespace);p!=NULL;p=strtok(NULL,whitespace))
	{
		if(strcmp(p,"the")==0)
			count++;
	}
	return count;
}

int main()
{
	char string[100];
	gets(string);
	printf("\"the\" is appeared %d times",count_the(string));
	return 0;
}
