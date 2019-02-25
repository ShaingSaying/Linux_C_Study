#include "dict.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    dict* mydict;
    int i;
    char *temp;

    mydict = dict_create(NULL);


    for(i=0;argv[i] != NULL; i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
        dict_add(mydict,&i,1,argv[i],strlen(argv[i]));
    }
    i--;
    for(i;i>=0;i--)
    {
        printf("[%d]value:  %s\n",i,(char *)dict_fetch_value(mydict,&i,1));
    }

    
    return 0;
}
