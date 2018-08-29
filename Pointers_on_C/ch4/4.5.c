#include<stdio.h>
#include<string.h>
#define MAX_SIZE 127
int main()
{
	char buffer1[MAX_SIZE];
	char buffer2[MAX_SIZE]={0};
	int flag=0;

	while(gets(buffer1)!=NULL)
	{
		if(strcmp(buffer1,buffer2)==0)
		{
			flag=1;
		}
		else
		{
			if(flag==0)
			{
				strcpy(buffer2,buffer1);
			}
			else
			{
				flag=0;
				printf("%s\n",buffer2);
			}
		}
	}
	return 0;
}
