#include<stdio.h>
int main()
{
	float speed=0;
	float document=0;
	printf("please input the speed:");
	scanf("%f",&speed);
	printf("please input the documnet:");
	scanf("%f",&document);
	printf("At %.2f megabits per second,a file of %.2f megabytes\n",speed,document);
	printf("downloads in %.2f seconds.\n",document*8/speed);
	return 0;
}
