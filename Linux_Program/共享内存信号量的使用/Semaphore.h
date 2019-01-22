#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<string.h>
#include<unistd.h>
union semun
{
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int sem_p(int sem_id);
int sem_v(int sem_id);
int del_sem(int sem_id);
int creat_sem(key_t key);
#endif