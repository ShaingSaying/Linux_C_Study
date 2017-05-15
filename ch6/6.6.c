#include<stdio.h>
int main()
{
	int up,down;
	int i;
	int num=6;
	printf("please input up and down value: ");
	scanf("%d%d",&up,&down);
	for(i=up;i<=down;i++)
	{
		printf("%d\t%d\t%d\t%d\n",i,num,num*num,num*num*num);
	}
	return 0;
}
