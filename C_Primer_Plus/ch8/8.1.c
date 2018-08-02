#include<stdio.h>
int main()
{
	int cnt=0;

	while(getchar()!=EOF)
	{
		cnt++;
	}
	printf("characters: %d\n",cnt);
	
	return 0;
}
