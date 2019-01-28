#ifndef _QUE
#define _QUE
#include "pool_common.h"
typedef enum{
    EMPTY,FULL,NEITHER      //枚举类型，判断队列是否为空返回的状态
}STATUS;
typedef struct que
{
    elem_t *que_arr; //任务队列中的任务数组，存储数据
    int que_front;  //任务队列的头
    int que_tail;   //任务队列的尾
    int que_capacity;   //任务队列所容纳任务的数量
    pthread_mutex_t que_lock;   //任务队列的互斥锁
    pthread_cond_t que_pro;     //任务产生的信号
    pthread_cond_t que_con;     //任务被执行的信号
}que_t,*pque_t;

void que_init(pque_t pq,int sizenum);   //任务队列初始化
STATUS que_full(pque_t pq);     //判断队列是否满了
STATUS que_empty(pque_t pq);    //判断队列是否为空
void que_push(pque_t pq,elem_t val);       //将新的任务加入队列
void que_pop(pque_t pq);        //将任务从队列中删除
elem_t que_top(pque_t pq);      //获得任务队列首任务，和上个函数结合使用，即将任务交于线程执行
void que_destroy(pque_t pq);    //销货队列
#endif
