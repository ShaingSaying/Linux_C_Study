#include<stdio.h>
#include<string.h>
void copy_n(char dst[],char src[],int n)
{
	int i;
	int len;
	len=strlen(src);
	if(len>=n)
	{
		for(i=0;i<n;i++)
		{
			dst[i]=src[i];
		}
	}
	else
	{
		for(i=0;i<len;i++)
		{
			dst[i]=src[i];
		}
		for(i=len;i<n;i++)
		{
			printf("0000");
			dst[i]='\0';
		}
	}
}
int main(void)
{
	char dst[128];
	char src[128];
	int len;
	printf("please input a str\n");
	scanf("%s",src);
	len=strlen(src);
	copy_n(dst,src,128);
	printf("dst str:%s\n",dst);
	return 0;
}
