/*
 *对输出加入行号
 */
#include<stdio.h>
int main(int argc, char *args[])
{
	int ch;
	int line=0;
	int flag=0;

	while((ch=getchar())!=EOF)
	{
		if(flag==0)
		{
			flag=1;
			line+=1;
			printf("%d ",line);
		}
		if(ch=='\n')
		{
			flag=0;
		}
		putchar(ch);
		
	}

	return 0;
}
