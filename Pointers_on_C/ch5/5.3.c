#include<stdio.h>
#include<string.h>
unsigned int reverse_bits(unsigned int value)
{
	unsigned int result;
	unsigned int i;
	result=0;
	for(i=1;i!=0;i<<=1)
	{
		result<<=1;
		if(value&1)
			result |= 1;
		value>>=1;
	}
	return result;
}
int main()
{
	unsigned int num=25;
	unsigned int res=0;
	res = reverse_bits(num);
	printf("func[%s]res=[%u]\n",__func__,res);
	return 0;
}
