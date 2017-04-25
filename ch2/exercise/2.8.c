#include<stdio.h>
void two();
void one_three();
int main()
{
	printf("starting now:\n");
	one_three();
	printf("done!\n");
	return 0;
}
void two()
{
	printf("two\n");
}
void one_three()
{
	printf("one\n");
	two();
	printf("three\n");
}
