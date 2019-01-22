#include "lock.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TEST_FILE "test.ini"

//得到10以内的一个随机数  
int get_random()  
{  
    int digit;  
    srand((unsigned)(getpid() + time(NULL)));  
    digit = rand() % 10 + 2;  
    return digit;  
} 


int main()
{
    FILE *pFile = NULL;
    char letter;
    int i;

    if(access(TEST_FILE,F_OK) < 0)
    {
        printf("Line[%d]:[%s] is not exist.\n",__LINE__,TEST_FILE);
        return 0;
    }
    printf("---%d---\n",getpid());


    pFile = fopen(TEST_FILE,"r");
    if(NULL == pFile)
    {
        printf("Line[%d]:fopen [%s] failed.\n",__LINE__,TEST_FILE);
        return 0;
    }
    
    while(!feof(pFile))
    {
        lock_set(fileno(pFile),F_RDLCK);
        letter = fgetc(pFile);
        printf("[%d]:read letter [%c]\n",getpid(),letter);
        //sleep(get_random());
        lock_set(fileno(pFile),F_UNLCK);
        sleep(get_random());
    }

    if(NULL != pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }

    return 0;
}
