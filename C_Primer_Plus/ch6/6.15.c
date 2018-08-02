#include<stdio.h>
#include<string.h>
int main()
{
	char a[100];
	int i,n=0;
	printf("please input something:");
	scanf("%s",a);
	n=strlen(a);
	for(i=n;i>=0;i--)
		printf("%c",a[i]);
	printf("\n");
	return 0;
	
}
