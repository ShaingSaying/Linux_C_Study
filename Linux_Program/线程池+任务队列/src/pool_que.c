#include "pool_que.h"

void que_init(pque_t pq,int sizenum)
{
    pq->que_arr = (elem_t *)calloc(sizenum,sizeof(elem_t));
    pq->que_capacity = sizenum;
    pq->que_front = 0;
    pq->que_tail = 0;
    pthread_mutex_init(&pq->que_lock,NULL); //初始化互斥锁
    pthread_cond_init(&pq->que_pro,NULL); //初始化信号量
    pthread_cond_init(&pq->que_con,NULL);
}

STATUS que_empty(pque_t pq)
{
    if(pq->que_front == pq->que_tail) //队首和队尾相等则为空，该队列为循环队列
    {
        return EMPTY;
    }
    else
    {
        return NEITHER;
    }   
}

STATUS que_full(pque_t pq)
{
    if((pq->que_tail+1)%pq->que_capacity == pq->que_front)
    {
        return FULL;
    }
    else
    {
        return NEITHER;
    }
    
}

//将新的任务加入到线程池中
void que_push(pque_t pq,elem_t val)
{
    pthread_mutex_lock(&pq->que_lock); //增加互斥锁
    while(que_full(pq)==FULL)
    {
        //当任务队列为满时，等待执行任务的信号，并且将互斥锁打开
        printf("task queue is full\n");
        pthread_cond_wait(&pq->que_pro,&pq->que_lock);
    }
    pq->que_arr[pq->que_tail]=val;
    pq->que_tail = (pq->que_tail+1) % pq->que_capacity;
    //if(EMPTY==que_empty(pq))
        pthread_cond_signal(&pq->que_con); //通知线程有新任务出现
    pthread_mutex_unlock(&pq->que_lock); //打开互斥锁
}

elem_t que_top(pque_t pq)
{
    pthread_mutex_lock(&pq->que_lock); //上锁
    while(EMPTY==que_empty(pq))
    {
        pthread_cond_wait(&pq->que_con,&pq->que_lock);
    }
    return pq->que_arr[pq->que_front];
}

void que_pop(pque_t pq)
{
    pq->que_front=(pq->que_front+1)%pq->que_capacity;
    //if(que_full(pq)==FULL)
        pthread_cond_signal(&pq->que_pro); //有任务处理掉后，发送执行任务信号
    pthread_mutex_unlock(&pq->que_lock);
}

void que_destroy(pque_t pq)
{
    free(pq->que_arr);
    pthread_mutex_destroy(&pq->que_lock); //销毁锁和信号
    pthread_cond_destroy(&pq->que_pro);
    pthread_cond_destroy(&pq->que_con);
}
