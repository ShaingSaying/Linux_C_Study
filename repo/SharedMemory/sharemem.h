#ifndef __SHAREMEM_H__
#define __SHAREMEM_H__

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int create_shm(char* keyfile, int shm_size);
void destroy_shm(int shmid);
void *attach_shm(int shmid);
void detach_shm(void* pshm);

#endif