#include<stdio.h>

char *find_char(const char *source, const char *chars)
{
	char *get;
	get=NULL;
	if(source==NULL||chars==NULL)
		return NULL;
	for(;*chars!='\0';*chars++)
	{
		for(get=source;*get!='\0';*get++)
		{
			if(*get==*chars)
			{
				return get;
			}
		}
	}
	return NULL;
}
int main()
{
	const char *source = "hello world";
	const char *chars = "abced";
	char *res;
	res=find_char(source,chars);
	printf("%s\n",res);

}
