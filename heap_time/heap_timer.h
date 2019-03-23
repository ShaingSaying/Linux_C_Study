#ifndef _HEAP_TIME_
#define _HEAP_TIME_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>


typedef struct task_param
{
    int         uid;
    time_t      tt;
} task_param;

typedef struct task_unit
{
    time_t      expire;                             /* 定时器设置绝对时间 */
    int         uuid;                               /* 任务标识符 */
    void        (*task_func)(void *);               /* 定时回调函数 */
    struct      task_param* client_alarm_data;      /* 回调函数参数 */
} task_unit;

typedef struct heap_timer
{
    struct task_unit**  heap_array;                 /* 定时器指针数组 */
    int                 capacity;                   /* 定时器的最大容量 */
    int                 cur_num;                    /* 当前定时管理器上得定时器个数 */
} heap_timer;

heap_timer tmanager1;

void task_func(void* param);
void percolate_down(heap_timer* tmanager, int hole);
int resize(heap_timer* tmanager);
int init_heap_time(heap_timer* tmanager, int cap);
int empty(heap_timer* tmanager);
int pop_timer(heap_timer* tmanager);
void print_heap_time(heap_timer* tmanager);
int add_timer(heap_timer *tmanager, int timeout, int uuid);
void tick(heap_timer* tmanager);
void alarm_handler(int sig);
#endif