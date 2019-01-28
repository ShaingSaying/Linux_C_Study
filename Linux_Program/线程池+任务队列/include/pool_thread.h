#ifndef _POOL_THREAD
#define _POOL_THREAD
#include "pool_que.h"
typedef void* (*consumer_handle)(void*); //定义线程所执行的任务函数名

typedef struct threads
{
    que_t pool_que; //线程池中的任务队列
    int pool_cnt;   //线程池中线程个数
    pthread_t *pool_arr;    //线程数组
    consumer_handle pool_handle;    //线程索要处理的任务函数
}threadspool_t,*pthreadspool_t;

void pool_init(pthreadspool_t ppool, int quecapacity, int threadsnum, consumer_handle hd);  //初始化多线程
void pool_on(pthreadspool_t ppool);     //启动多线程
void pool_off(pthreadspool_t ppool);    //关闭多线程
void pool_put(pthreadspool_t ppool, elem_t val);    //将新的任务加入到线程池中
void pool_get(pthreadspool_t ppool,elem_t *val);    //取出线程池中的任务
void pool_destroy(pthreadspool_t ppool);    //销毁线程池
#endif
