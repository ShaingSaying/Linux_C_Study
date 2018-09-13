#include<stdio.h>

#define BUFFSIZE 256

FILE *openfile(char *prompt, char *mode)
{
    char buf[BUFFSIZE];
    FILE *file;

    printf("%s filename?",prompt);
    if(gets(buf)==NULL)
    {
        fprintf(stderr,"Missing %s file name.\n",prompt);
        exit(EXIT_FAILURE);
    }

    if((file=fopen(buf,mode))==NULL)
    {
        perror(buf);
        exit(EXIT_FAILURE);
    }
    return file;
}

int main()
{
    char buf[BUFFSIZE];
    FILE *input;
    FILE *output;
    FILE *openfile();

    input=openfile("Input","r");
    output=openfile("output","w");

    while(fgets(buf,BUFFSIZE,input)!=NULL)
        fputs(buf,output);

    fclose(input);
    fclose(output);

    return 0;
}