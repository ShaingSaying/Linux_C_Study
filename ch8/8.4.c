#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
int main()
{
	int word=0;
	int letter=0;
	bool isword=false;
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(isalpha(ch))		//如何是字母则返回真
		{
			if(isword!=true)
			{
				isword=true;
				word++;
			}
			letter++;
		}
		else
		{
			isword=false;
		}
	}
	//printf("\n");
	printf("world: %d\n",word);
	printf("letter: %d\n",letter);
	printf("the average about letters per word: %.2f\n",(float)letter/word);
	return 0;
}
