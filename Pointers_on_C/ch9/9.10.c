#include<ctype.h>

#define TRUE 1
#define FALSE 0

int palindrome(char *string)
{
	char *string_end;
	
	string_end=string+strlen(string)-1;
	
	while(TRUE)
	{
		while(!isalpha(*string))
			string++;
		while(!isalpha(*string_end))
			string_end--;
		if(string_end<=string)
			return TRUE;
		if(tolower(*string)!=tolower(*string_end))
			return FALSE;
		string++;
		string_end--;
	}
}
