#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>


int main()
{
	int ch;
	float n_cntrl=0;
	float n_space=0;
	float n_digit=0;
	float n_lower=0;
	float n_upper=0;
	float n_punct=0;
	float n_nprint=0;
	float total=0;

	while((ch=getchar())!=EOF)
	{
		total+=1;
	
		if(iscntrl(ch))
			n_cntrl+=1;
		if(isspace(ch))
			n_space+=1;
		if(isdigit(ch))
			n_digit+=1;
		if(islower(ch))
			n_lower+=1;
		if(isupper(ch))
			n_upper+=1;
		if(ispunct(ch))
			n_punct+=1;
		if(!isprint(ch))
			n_nprint+=1;
	}

	if(total==0)
		printf("No characters in the input!\n");
	else
	{
		printf("%3.0f%% %s control characters\n",n_cntrl*100.0/total);
		printf("%3.0f%% %s whitespace characters\n",n_space*100.0/total);
		printf("%3.0f%% %s digit characters\n",n_digit*100.0/total);
		printf("%3.0f%% %s lower case characters\n",n_lower*100.0/total);
		printf("%3.0f%% %s upper case characters\n",n_upper*100.0/total);
		printf("%3.0f%% %s punctuation characters\n",n_punct*100.0/total);
		printf("%3.0f%% %s non-printable characters\n",n_nprint*100.0/total);
	}
	return 0;	
}
