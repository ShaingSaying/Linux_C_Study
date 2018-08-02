#include<stdio.h>
#include<string.h>
const char * search_char(const char*,const char);
int main()
{
	const unsigned int LEN =128;
	char str[LEN];
	char ch;
	const char* ptr;
	puts("input a string:");
//	while(1)
//	{
		fgets(str,LEN,stdin);
//		if(*str=='\n')
//		break;
//	}
	puts("input a char to search:");
	ch=getchar();
	ptr=search_char(str,ch);
	if (ptr == NULL)
        {
            puts("Not found!");
        }
        else
        {
            puts("Found!");
            printf("Char: %c\n", *ptr);
            printf("Address: %p\n", ptr);
        }

    return 0;
}
const char * search_char(const char* str,const char ch)
{
	const char* ptr=str;
	while(*ptr!='\0')
	{
		if(*ptr==ch)
			break;
		ptr++;
	}
	if(*ptr!='\0')
		return ptr;
	else
		return NULL;

}
