#include<stdio.h>
#define BUFFSIZE 256
int main()
{
    char buf[BUFFSIZE];
    while(fgets(buf,BUFFSIZE,stdin)!=NULL)
        fputs(buf,stdout);

    return 0;
}