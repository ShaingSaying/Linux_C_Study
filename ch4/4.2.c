#include<stdio.h>
#include<string.h>
int main()
{
	char name[32];
	printf("please input your name:");
	scanf("%s",name);
	printf("\"%20s\"\n",name);
	printf("\"%-20s\"\n",name);
	printf("\"%*s\"\n",(int)strlen(name)+3,name);
	return 0;
}
