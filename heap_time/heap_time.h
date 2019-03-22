#ifndef _HEAP_TIME_
#define _HEAP_TIME_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

typedef struct alarm_data
{

} alarm_data;

typedef struct heap_unit
{
    time_t      expire;     //单个定时器设置绝对时间
    int         timeout;    //定时时间
    void        (*alarm_func)(void *);  //定时回调函数
    struct      alarm_data *client_alarm_data;  //回调函数参数
} heap_unit;

typedef struct heap_time
{
    struct heap_unit**  heap_arry;  //定时器指针数组
    int                 capacity;   //定时器的最大容量
    int                 cur_num;    //当前定时管理器上得定时器个数
} heap_time;
#endif