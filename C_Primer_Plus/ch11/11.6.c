#include<stdio.h>
#include<string.h>
int is_within(const char ch,const char *str);
int main()
{
    const unsigned int LEN = 128;
    char str[LEN];
    char ch;
    int a;

    while (1)
    {
        puts("Input a string('Enter' to quit):");
        fgets(str, LEN, stdin);
        if (*str == '\n')
        {
            break;
        }
        puts("Input a char to search");
        ch = getchar();
        a = is_within(ch,str);
        if (a == 0)
        {
            puts("Not found!");
        }
        else
        {
            puts("Found!");
        }
    }

    return 0;

}
int is_within(const char ch,const char *str)
{
	const char* ptr=str;
	while(*ptr!='\0')
	{
		if(*ptr==ch)
		{
			break;
		}
		ptr++;
	}
	if(*ptr!='\0')
		return 1;
	else
		return 0;
}
