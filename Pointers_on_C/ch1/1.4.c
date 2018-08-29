#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 1001
int main(int argc, char *argv[])
{
	int max_len = -1;
	int len = 0;
	char buffer[MAX_LENGTH];
	char lbuffer[MAX_LENGTH];
	while(gets(buffer)!=NULL)
	{
		len = strlen(buffer);
		if(len>max_len)
		{
			max_len=len;
			strcpy(lbuffer,buffer);
		}
	}
	printf("the max length str is:%s\n",lbuffer);
	return 0;
}
