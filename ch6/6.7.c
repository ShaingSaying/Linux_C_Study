#include<stdio.h>
#include<string.h>
int main()
{
	int res,i;
	char zimu[20];
	printf("please input a world:");
	scanf("%s",zimu);
	res=strlen(zimu);
	for(i=res+1;i>=0;i--)
	{
		printf("%c",zimu[i]);
	}
	printf("\n");
	return 0;
}
