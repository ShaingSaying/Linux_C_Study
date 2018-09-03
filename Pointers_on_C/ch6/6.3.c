#include<stdio.h>

void reverse_string(char *string)
{
	char *temp=NULL;
	char temp2;
	if(NULL==string)
	{
		printf("error\n");
	}
	temp=string;
	printf("temp=%s\n",temp);
	for(;*temp!='\0';temp++)
	{
		printf("%c\n",*temp);
	}
	temp--;
	for(;temp>string;string++,temp--)
	{
		temp2=*string;
		*string=*temp;
		*temp=temp2;
	}
	
}

int main(void)
{
	char string[]="ABCDEFG";
	reverse_string(string);
	printf("%s\n",string);
	return 0;
}
