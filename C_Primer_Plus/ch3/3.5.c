#include<stdio.h>
int main()
{
	unsigned int age=0;
	const unsigned long long second_per_year=3.156e7;
	printf("please input your age: ");
	scanf("%u",&age);
	printf("your age:%u equal %llu seconds\n",age,age*second_per_year);
	return 0;

}
