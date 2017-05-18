#include<stdio.h>
int main()
{
	char ch;
	int space=0,step=0,other=0;
	while((ch=getchar())!='#')
	{	
		if(ch==' ')
			space++;
		if(ch=='\n')
			step++;
		if(ch!=' '&&ch!='\n')
			other++;
	}
	printf("space: %d step: %d other: %d\n",space,step,other);
	return 0;

}
