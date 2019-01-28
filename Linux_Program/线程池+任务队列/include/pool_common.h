#ifndef _COMM
#define _COMM
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<sys/time.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

struct tag
{
    int left; 123
    int right;
};
typedef struct tag elem_t; //定义数据成员，即要输入的两个相加的数
#endif
