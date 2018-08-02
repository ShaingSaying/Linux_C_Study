#include<stdio.h>
void print(char ch,int x,int y);
int main()
{
	char c;
	int num1,num2;
	printf("please input a char:");
	scanf("%c",&c);
	printf("please input two number:");
	scanf("%d%d",&num1,&num2);
	print(c,num1,num2);
	printf("\n");
	return 0;

}

void print(char ch,int x,int y)
{
	int i,j;
	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			putchar(ch);
		}
		putchar('\n');
	}
}
