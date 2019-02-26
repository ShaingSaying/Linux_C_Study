#include "dict.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    dict* mydict;
    int i,j;
    char *temp;

    mydict = dict_create(NULL);


    for(i=1;argv[i] != NULL; i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
        dict_add(mydict,argv[i],strlen(argv[i]),argv[i],strlen(argv[i]));
    }
    i--;
    j=i;
    for(i;i>0;i--)
    {
        printf("[%s]value:  %s\n",argv[i],(char *)dict_fetch_value(mydict,argv[i],strlen(argv[i])));
    }

    dict_replace(mydict,argv[1],strlen(argv[1]),argv[2],strlen(argv[2]));

    dict_delete(mydict,argv[3],strlen(argv[3]));

    for(j;j>0;j--)
    {
        printf("[%s]new value:  %s\n",argv[j],(char *)dict_fetch_value(mydict,argv[j],strlen(argv[j])));
    }


    //dict_release(mydict);
    return 0;
}
