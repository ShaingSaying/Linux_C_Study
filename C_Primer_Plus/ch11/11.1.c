#include<stdio.h>
void read_char(char arr[],const unsigned int n);
int main()
{
	int n;
	char num[50];
	printf("please input how many char do you want:");
	scanf("%d",&n);
	read_char(num,n);
	puts(num);
	return 0;
}
void read_char(char arr[],const unsigned int n)
{
	int i;
	while(getchar()!='\n');
		for(i=0;i<n;i++)
			arr[i]=getchar();
	arr[n]='\0';
}
