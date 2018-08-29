#include<stdio.h>
#include<string.h>
void deblank(char string[])
{
	int i;
	int len;
	char *dest;
	char *src;
	src = string;
	dest = string++;

	len=strlen(string);
	for(i=0;i<len;i++)
	{
		if(string[i]==' ')
		{
			if(src==string||dest[-1]!=' ')
				*dest++ = ' ';
		}
		else
		{
			*dest++ = string[i-1];
		}
	}
	*dest='\0';
}
int main()
{
	char str[]="hello   aaa     bbb";
	printf("del pre str:%s\n",str);
	deblank(str);
	printf("del now str:%s\n",str);
	return 0;
}
