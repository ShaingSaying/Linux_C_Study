#include<stdio.h>
int main()
{
	int low=0,high=100;
	int guess=50;
	char ch;
	printf("Pick an integer from 1 to 100. I will try to guess it.\n");
    	printf("Respond with a y if my guess is right,\n");
	printf("with a l if my guess is less than yours,\n");
        printf("and with a g if it is greater than yours.\n");

    	printf("Uh...is your number %d?\n", guess);
	while((ch=getchar())!='y')
	{
		if(ch=='l')
		{
			low=guess;
		}
		else if(ch=='g')
		{
			high=guess;
		}
		else
		{
			printf("Wrong respond! try again.i\n");
            		printf("Well, then, is it %d?\n", guess);
            		continue;
		}
		guess = (low + high) / 2;
        	printf("Well, then, is it %d?\n", guess);
	}
	printf("I know i could do it!\n");
	return 0;
}
