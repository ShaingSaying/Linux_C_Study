#include<stdio.h>

int main()
{
	int data[3];
	int i;
	printf("please input three numbers:\n");
	for(i=0;i<3;i++)
	{
		scanf("%d",&data[i]);
	}
	if(data[0]<0||data[1]<0||data[2]<0)
	{
		printf("error numbers1\n");
		return 0;
	}
	if(((data[0]+data[1])>data[2])&&((data[0]-data[1])<data[2]))
	{
		if(data[0]!=data[1]&&data[1]!=data[2]&&data[2]!=data[0])
		{
			printf("bu deng bian san jiao xing\n");
		}
		else if(data[0]==data[1]&&data[1]==data[2])
		{
			printf("deng bian san jiao xing\n");
		}
		else
		{
			printf("deng yao san jiao xing\n");
		}
	}
	else
	{
		printf("error numbers2\n");
	}
	
	return 0;
}
