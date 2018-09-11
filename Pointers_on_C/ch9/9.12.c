#include<ctype.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

int prepare_key(char *key)
{
	char *keyp;
	char *dup;
	int character;
	
	if(*key=='\0')
		return FALSE;

	for(keyp=key;(character=*keyp)!='\0';keyp++)
	{
		if(!islower(character))
		{
			if(!isupper(character))
				return FALSE;
			*keyp=tolower(character);
		}
	}

	for(keyp=key;(character=*keyp)!='\0';)
	{
		dup=++keyp;
		while((dup=strchr(dup,character))!=NULL)
			strcpy(dup,dup+1);
	}

	for(character='a';character<='z';character+=1)
	{
		if(strchr(key,character)==NULL)
		{
			*keyp++=character;
			*keyp='\0';
		}		
	}

	return TRUE;
}

int main()
{
	char key[27]={"TRAILBLAZERS"};
	prepare_key(key);
	printf("key:%s\n",key);
	return 0;
}
