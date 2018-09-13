#include<stdio.h>

#define BUFFERSIZE 81

int main()
{
    char buffer[BUFFERSIZE];

    while(gets(buffer)!=NULL)
        puts(buffer);
    
    return 0;
}