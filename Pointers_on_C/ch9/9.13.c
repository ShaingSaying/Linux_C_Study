#include<stdio.h>
#include<ctype.h>
void encrypt(char *data, char const *key)
{
	int character;
	for(;(character=*data)!='\0';data++)
	{
		if(islower(character))
			*data=key[character-'a'];
		else if(isupper(character))
			*data=toupper(key[character-'A']);
	}
}
