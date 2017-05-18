#include<stdio.h>
int main()
{
	int count=0;
	const char std[]="ei";
	char cur,pre;
	pre=' ';
	while((cur=getchar())!='#')
	{
		if(pre==std[0]&&cur==std[1])
		{
			count++;
		}
		pre=cur;
	}
	printf("%s is appear %d\n",std,count);
	return 0;
}
