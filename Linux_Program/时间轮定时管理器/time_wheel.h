#ifndef _TIME_WHEEL_
#define _TIME_WHEEL_
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

typedef struct client_data {
    time_t tt;
    char buf[512];
    void* data;

}client_data;

typedef struct tw_timer {
    int rotation;                       /* 处于时间轮第几转，即时间轮转多少转 */
    int slot;                           /* 处于当前时间轮转的第几个槽 */
    void* (*cb_func)( void* param );    /* 定时器到时执行的回调函数 */
    struct client_data c_data;          /* 用户数据，触发回调任务函数的参数 */
    //struct tw_timer* prev;
    struct tw_timer* next;              /* 这里只需要单向不循环链表即可 */
}tw_timer;

typedef struct timer_manager {
    /* 时间轮当前槽，每经过一个间隔时间，加一实现轮转动，
    超过总槽数即归零表示当前轮转完 */
    int cur_slot;
    int slot_num_r;                 /* 时间轮一转的总槽数，总槽数越大槽链表越短，效率越高 */
    /* 相邻时间槽间隔时间，即时间轮转到下一个槽需要时间，*/
    /* 间隔时间越短，精度越高，例如10s，表示定时器支持10s */
    /* 间隔定时器添加，最小支持1s */
    int slot_interval;
    /*每个时间槽链表头结点，即一个槽管理一条链表
    添加相同槽数的结点，转数可能不同*/
    struct tw_timer* slots_head[512];
}timer_manager;
 
timer_manager tmanager;

int tick( timer_manager* tmanager );
int add_timer( timer_manager* tmanager, int timeout, client_data* c_data );
int init_t_manager( timer_manager* tmanager, int slot_num_r, int slot_interval );

#endif