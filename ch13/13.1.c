#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 64

int main()
{
	char filename[MAXLEN];
	FILE* fp;
	int ch;
	long count=0;

	fputs("enter the filename: ",stdout);
	fgets(filename,MAXLEN,stdin);
	filename[strlen(filename)-1]='\0';
	if((fp=fopen(filename,"r"))==NULL)
	{
		fprintf(stderr,"can't open %s\n",filename);
		exit(EXIT_FAILURE);
	}
	while((ch=getc(fp))!=EOF)
	{
		putc(ch,stdout);
		count++;
	}
	fclose(fp);
	printf("File %s has %ld characters.\n",filename,count);
	return 0;
}
