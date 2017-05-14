#include<stdio.h>
int main()
{
	float tall=0;
	char name[20];
	printf("please input your name:");
	scanf("%s",name);
	printf("please input your tall:");
	scanf("%f",&tall);
	printf("%s,you are %f feet tall\n",name,tall);
	return 0;
}
