#include<stdio.h>
#include<string.h>
#include<limits.h>
unsigned  character_offset(unsigned bit_number)
{
	return bit_number / CHAR_BIT;
}
unsigned bit_offset(unsigned bit_number)
{
	return bit_number % CHAR_BIT;
}
void set_bit(char bit_array[],unsigned bit_number)
{
	bit_array[character_offset(bit_number)] |= 1<< bit_offset(bit_number);
}
void clear_bit(char bit_array[],unsigned bit_number)
{
	bit_array[character_offset(bit_number)] &= ~(1<<bit_offset(bit_number));
}
void assign_bit(char bit_array[], unsigned bit_number, int value)
{
	if(value != 0)
		set_bit(bit_array, bit_number);
	else
		clear_bit(bit_array, bit_number);
}
int test_bit(char bit_array[], unsigned bit_number)
{
	return (bit_array[character_offset(bit_number)] & 1 << bit_offset(bit_number))!=0;	
}
int main()
{
	char bit_array[]="hello world";
	unsigned  bit_number=23;
	printf("CHAR_BIT=[%d]\n",CHAR_BIT);
	printf("bit_array=[%s]\n",bit_array);
	set_bit(bit_array,bit_number);
	printf("bit_array=[%s]\n",bit_array);
	clear_bit(bit_array,bit_number);
	printf("bit_array=[%s]\n",bit_array);
	assign_bit(bit_array,bit_number,1);
	printf("bit_array=[%s]\n",bit_array);
	printf("test_bit=[%d]\n",test_bit(bit_array,bit_number));
}
