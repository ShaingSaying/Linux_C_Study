#include<stdio.h>
#include<string.h>
int main()
{
	char name_x[10];
	char name_m[10];
	printf("please input you xing:");
	scanf("%s",name_x);
	printf("please input you ming:");
	scanf("%s",name_m);
	printf("%s %s\n",name_x,name_m);
	printf("%*d %*d\n",(int)strlen(name_x),(int)strlen(name_x),(int)strlen(name_m),(int)strlen(name_m));
	printf("%s %s\n",name_x,name_m);
	printf("%-*d %-*d\n",(int)strlen(name_x),(int)strlen(name_x),(int)strlen(name_m),(int)strlen(name_m));
	return 0;
}
