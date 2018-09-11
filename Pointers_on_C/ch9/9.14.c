#include<stdio.h>
#include<string.h>

static char alphabet[] = "abcdefjhijklmnopqrstuvwxyz";

void decrypt(char *data, const char *key)
{
	int character;
	for(;(character=*data)!='\0';data++)
	{
		if(islower(character))
			*data=alphabet[strchr(key,character)-key];
		else if(isupper(character))
			*data=toupper(alphabet[strchr(key,tolower(character))-key]);
	}
}
