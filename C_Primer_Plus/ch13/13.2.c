#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fs,*fd;
	int ch;
	long count=0;
	
	if(argc<3)
	{
		fprintf(stderr,"Usage:%s [source_filename] [destiation_filename]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if((fs=fopen(argv[1],"rb"))==NULL)
	{
		fprintf(stderr,"Can't open file %s\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	if((fd=fopen(argv[2],"wb"))==NULL)
	{
		fprintf(stderr,"Can't open file %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}
	while((ch=getc(fs))!=EOF)
	{
		putc(ch,fd);
		count++;
	}
	fclose(fs);
	fclose(fd);
	printf("%ld characters have been copied to file %s from file %s\n", count, argv[2], argv[1]);
}
