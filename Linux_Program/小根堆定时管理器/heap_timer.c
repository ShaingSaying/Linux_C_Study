/* https://blog.csdn.net/u012785877/article/details/52420535 */
#include"heap_timer.h"

char* time_t2string(time_t intime)
{
    char* strtime = (char *)malloc(sizeof(char)*20);
#if 0
    strftime(strtime, 20, "%Y-%m-%d %H:%M:%S", localtime(&intime));
#endif
    strftime(strtime, 20, "%H:%M:%S", localtime(&intime));
    return strtime;
}

void task_func(void* param)
{
    task_param* taskparam = (task_param*)param;
    printf("************************************************************************\n");
    printf("uuid [%d] the timer begin time: [%s]\n",taskparam->uid,time_t2string(taskparam->tt));
    printf("************************************************************************\n");
}

/* 堆状态打印 */
void print_heap_time(heap_timer* tmanager)
{
    int i = 0;
    time_t cur = time(NULL);
    printf("------------------------------------------------------------------------\n");
    printf("func:[%s] timer numbers:[%d] now time:[%s]\n",__func__,tmanager->cur_num,time_t2string(cur));
    for(;i<tmanager->cur_num;i++)
    {
        if(tmanager->heap_array[i])
        printf("order:[%d] uuid:[%d] begin time:[%s] delay time:[%d] dealtime:[%s]\n",i,tmanager->heap_array[i]->uuid, \
        time_t2string((time_t)(tmanager->heap_array[i]->expire-tmanager->heap_array[i]->delay_time)), \
        tmanager->heap_array[i]->delay_time,time_t2string((time_t)tmanager->heap_array[i]->expire));
    }
    printf("------------------------------------------------------------------------\n");
}
/* 下滤堆调整 */
void percolate_down(heap_timer* tmanager, int hole)
{
    int child = 0;
    for(;((hole*2+1) <= (tmanager->cur_num-1)); hole = child)
    {
        child = hole * 2 + 1;
        //这里找出当前节点最小儿子节点
        if ( (child < (tmanager->cur_num-1)) 
            && (tmanager->heap_array[child+1]->expire) 
                < tmanager->heap_array[child]->expire )
        {
            ++child;
        }
        //比较待删除节点和最小儿子节点，大于就交换
        if(tmanager->heap_array[child]->expire < tmanager->heap_array[hole]->expire)
        {
            //这里的交换其实该用内存拷贝比较好
            task_unit* tmp_heap_timer = tmanager->heap_array[hole];
            tmanager->heap_array[hole] = tmanager->heap_array[child];
            tmanager->heap_array[child] = tmp_heap_timer;
        }
        else
        {
            break;
        }
    }
}
/* 将堆空间增大一倍 */
int increase_heap(heap_timer* tmanager)
{
    printf("increase_heap\n");
    task_unit** temp = (task_unit**)
            malloc(2*tmanager->capacity*sizeof(task_unit*));

    int i = 0;
    for(; i<2*tmanager->capacity;++i)
    {
        temp[i] = NULL;
    }
    if(!temp)
    {
        return -1;
    }
    tmanager->capacity = 2 * tmanager->capacity;
    for(i=0;i<tmanager->cur_num;++i)
    {
        temp[i] = tmanager->heap_array[i];
        tmanager->heap_array[i] = NULL;
    }
    free(tmanager->heap_array);
    tmanager->heap_array = temp;
    return 0;
}
/* 减小堆空间(待修改，未使用) */
int reduce_resize(heap_timer* tmanager)
{
    printf("reduce_resize\n");
    task_unit** temp = (task_unit**)
            malloc(0.75*tmanager->capacity*sizeof(task_unit*));

    int i = 0;
    for(; i<2*tmanager->capacity;++i)
    {
        temp[i] = NULL;
    }
    if(!temp)
    {
        return -1;
    }
    tmanager->capacity = 0.75 * tmanager->capacity;
    for(i=0;i<tmanager->cur_num;++i)
    {
        temp[i] = tmanager->heap_array[i];
        tmanager->heap_array[i] = NULL;
    }
    free(tmanager->heap_array);
    tmanager->heap_array = temp;
    return 0;
}
/* 初始化一个小根堆空间 */
int init_heap_time(heap_timer* tmanager, int cap)
{
    tmanager->capacity = cap;
    tmanager->cur_num = 0;
    tmanager->heap_array = (task_unit**)malloc(cap * sizeof(task_unit*));
    if(NULL == tmanager->heap_array)
    {
        printf("init heap error\n");
    }
    int i = 0;
    for(;i<cap;++i)
    {
        tmanager->heap_array[i] = NULL;
    }
    printf("[%s] complete...\n",__func__);
    return 0;
}
/* 添加定时任务到堆空间 */
int add_timer(heap_timer *tmanager, int timeout, int uuid)
{
    if(!tmanager || timeout <= 0)
    {
        return -1;
    }
    if(tmanager->cur_num >= tmanager->capacity)
    {
        printf("Insufficient heap space,Redistribution....\n");
        increase_heap(tmanager);
    }

    int hole = tmanager->cur_num++;
    int parent = 0;
    task_unit* timer = (task_unit*)malloc(sizeof(task_unit));
    time_t tt = time(NULL);
    timer->expire = (int)tt + timeout;
    timer->delay_time = timeout;
    timer->uuid = uuid;
    timer->client_alarm_data = (task_param*)malloc(sizeof(task_param*));
    timer->client_alarm_data->tt = tt;
    timer->client_alarm_data->uid = uuid;
    timer->task_func = task_func;

    for(; hole>0; hole=parent)
    {
        parent = (hole-1)/2;
        if(tmanager->heap_array[parent]->expire <= timer->expire)
        {
            break;
        }
        tmanager->heap_array[hole] = tmanager->heap_array[parent];
    }
    tmanager->heap_array[hole] = timer;
    printf("[%s] uuid:[%d] begin time:[%s] delay_time:[%d] add over...\n",__func__ , tmanager->heap_array[hole]->uuid, \
    time_t2string(tt), tmanager->heap_array[hole]->delay_time);
    return 0;
}
/* 判断堆空间是否为0 */
int empty(heap_timer* tmanager)
{
    return tmanager->cur_num == 0;
}
/* 定时时间到，启动任务 */
int pop_timer(heap_timer* tmanager)
{
    if(empty(tmanager))
    {
        printf("[%s]empty cur size\n",__func__);
        return -1;
    }
    if(tmanager->heap_array[0])
    {
        printf("%s...\n",__func__);
        free(tmanager->heap_array[0]);
        tmanager->heap_array[0] = NULL;
        tmanager->heap_array[0] = tmanager->heap_array[--tmanager->cur_num];
        percolate_down(tmanager, 0);
        //free(tmanager->heap_arry[tmanager->cur_num]);
        //tmanager->heap_arry[tmanager->cur_num] = NULL;
    }
    return 0;
}

/* 心跳检测函数 */
void tick(heap_timer* tmanager)
{
    task_unit *tmp = tmanager->heap_array[0];
    time_t cur = time(NULL);
    while(!empty(tmanager))
    {
        if(!tmp)
        {
            break;
        }
        if(tmp->expire > cur)
        {
            printf("%s check no task comming...\n",__func__);
            break;
        }
        if(tmanager->heap_array[0]->task_func)
        {
            printf("%s task comming begin working...\n",__func__);
            print_heap_time(tmanager);
            tmanager->heap_array[0]->task_func(tmanager->heap_array[0]->client_alarm_data);
        }
        pop_timer(tmanager);
        print_heap_time(tmanager);
    }
}
/* 信号处理函数 */
void alarm_handler(int sig)
{
    tick(&tmanager1);
    if(tmanager1.cur_num > 0)      /* 当有任务存在时 */
    {
        alarm(tmanager1.heap_array[0]->expire-time(NULL));
    }
    else
    {
        printf("no task!\n");
        alarm(2);
    }
}