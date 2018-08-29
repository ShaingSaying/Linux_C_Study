#include<stdio.h>
#include<string.h>

int substr(char dst[], char src[], int start, int len)
{
	int src_len;
	int i;
	src_len=strlen(src);
	if(src_len-start<=len)
	{
		for(i=0;i<(src_len-start);i++)
			dst[i]=src[start+i];
		dst[src_len-start]='\0';
	}
	else
	{
		for(i=0;i<len;i++)
			dst[i]=src[start+i];
		dst[len]='\0';
	}
	return strlen(dst);
}
int main()
{
	char src[]="Hello World!";
	char dst[128];
	int res;
	res=substr(dst,src,4,20);
	printf("dst:%s\tlen:%d\n",dst,res);
	return 0;
}
