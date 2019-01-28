#include "pool_thread.h"
//quecapacity 任务队列大小，threadsnum线程数
void pool_init(pthreadspool_t ppool,int quecapacity, int threadsnum, consumer_handle hd)
{
    que_init(&ppool->pool_que,quecapacity); //初始化任务队列
    ppool->pool_arr = (pthread_t *)calloc(threadsnum,sizeof(pthread_t));
    ppool->pool_cnt = threadsnum; //线程数
    ppool->pool_handle = hd;
}

void pool_on(pthreadspool_t ppool)
{
    int i;
    for(i=0; i<ppool->pool_cnt; i++)
    {
        if(0 != pthread_create(ppool->pool_arr+i,NULL,ppool->pool_handle,(void*)ppool))   //创建线程，并且执行
        {
            printf("thread create fail!\n");
            exit(1);
        }
    }
}

void pool_off(pthreadspool_t ppool)
{
    int i;
    for(i=0;i<ppool->pool_cnt; i++)
    {
        pthread_join(ppool->pool_arr[i],NULL); //关闭线程
    }
}

//将新的任务加入到线程池中
void pool_put(pthreadspool_t ppool,elem_t val)
{
    que_push(&ppool->pool_que,val);
}

void pool_get(pthreadspool_t ppool,elem_t* val)
{
    *val = que_top(&ppool->pool_que);
    que_pop(&ppool->pool_que);
}

void pool_destroy(pthreadspool_t ppool)
{
    que_destroy(&ppool->pool_que);
    free(ppool->pool_arr);
}
