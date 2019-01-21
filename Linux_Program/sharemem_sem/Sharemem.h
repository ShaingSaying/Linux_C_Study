#ifndef _SHAREMEM_H_
#define _SHAREMEM_H_
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

typedef struct _DATA_ 
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int flag;
    int shmid;
}DATA;

typedef struct _INFO_
{
    unsigned int i;
    unsigned int e;
}INFO;

void destroy_shm(int shmid);
void *attach_shm(int shmid);
void detach_shm(void *pshm);
#endif