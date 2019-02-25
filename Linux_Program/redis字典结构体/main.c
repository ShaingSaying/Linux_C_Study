#include "dict.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    dict* mydict;
    int i;
    char *temp;

    mydict = dict_create(NULL);


    for(i=1;argv[i] != NULL; i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
        dict_add(mydict,argv[i],strlen(argv[i]),argv[i],strlen(argv[i]));
    }
    i--;
    for(i;i>0;i--)
    {
        printf("[%s]value:  %s\n",argv[i],(char *)dict_fetch_value(mydict,argv[i],strlen(argv[i])));
    }

    //dict_release(mydict);
    return 0;
}
