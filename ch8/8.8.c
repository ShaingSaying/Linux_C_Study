//代码有误，有待修复
#include<stdio.h>
int main()
{
	float first=0,second=0;
	char selection;
	printf("Enter the operation of your choice:\n");
	printf("a.add\t\ts.subtract\n");
	printf("m.multiply\t\td.divide\n");
	printf("q.quit\n");
	scanf("%c",&selection);
	printf("Enter first number:");
	scanf("%f",&first);
	printf("Enter second number:");
	scanf("%f",&second);
	while(selection!='q')
	{	
		switch(selection)
		{
			case 'a':printf("%.2f + %.2f =%.2f\n",first,second,first+second);
					break;
			case 's':printf("%.2f - %.2f =%.2f\n",first,second,first-second);
					break;
			case 'm':printf("%.2f * %.2f =%.2f\n",first,second,first*second);
					break;
			case 'd':printf("%.2f / %.2f =%.2f\n",first,second,first/second);
					break;

		}
		printf("Enter the operation of your choice:\n");
		printf("a.add\t\ts.subtract\n");	
		printf("m.multiply\t\td.divide\n");	
		printf("q.quit\n");  	
		scanf("%c",&selection);	
		printf("Enter first number:");	
		scanf("%f",&first);  	
		printf("Enter second number:");
 	       	scanf("%f",&second);
	}
	return 0;
}

