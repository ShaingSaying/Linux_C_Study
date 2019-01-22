#ifndef _LOCK_H_
#define _LOCK_H_
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int lock_set(int fd, int type);
#endif
