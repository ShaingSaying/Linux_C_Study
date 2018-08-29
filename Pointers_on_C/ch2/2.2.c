#include<stdio.h>

int main(void)
{
	int count=0;
	int flag=0;
	int ch=0;
	while((ch=getchar())!=EOF)
	{
		if(ch=='{')
			count++;
		if(ch=='}'&&count==0)
		{
			printf("only have }");
			return 0;
		}

		if(ch=='}'&&count!=0)
		{
			count--;
		}
		
		if(flag==0)
		{
			flag=1;
		}
	}
	if(count==0&&flag==1)
	{
		printf("{ & } numbers equal\n");
	}
	else if(count==0&&flag==0)
	{
		printf("not have { or }\n");
	}
	else
	{
		printf("not equal\n");
	}
}
