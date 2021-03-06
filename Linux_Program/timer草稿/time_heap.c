#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
 
typedef struct client_data {
    char buf[512];
    time_t tt;
    void* data;
} client_data;
 
typedef struct heap_timer {
    //单个定时器设置绝对时间
    time_t expire;
    //加的设置的定时器到时秒数
    int timeout;
    //到时回调函数
    void (*cb_func)( void* );
    //回调函数参数
    struct client_data* user_data;
} heap_timer ;
 
typedef struct h_t_manager {
    //定时器指针数组
    struct heap_timer** array;
    //当前定时管理器支持的最大定时器个数
    int capacity;
    //当前定时管理器上的定时器个数
    int cur_size;
} h_t_manager ;
void cb_func( void* param )
{
    time_t tt = time(NULL);
    printf("\n-----------------------------------------------\n");
    printf("\tontime,cur time - old time:%d\n", (int)(tt - ((client_data*)param)->tt));
    printf("\toldtime:%s", ctime(&(((client_data*)param)->tt)));
    printf("\tcurtime:%s", ctime(&tt));
    printf("-----------------------------------------------\n");
}
//下滤位置
static void percolate_down( h_t_manager* tmanager, int hole )
{
    //heap_timer* temp = tmanager->array[hole];
    //int flag = 0;
    int child = 0;
    for ( ; ((hole*2+1) <= (tmanager->cur_size-1)); hole = child )
    {
        //flag = 0;
        child = hole * 2 + 1;
 
        //这里找出当前节点左右儿子节点中的最小节点
        if ( (child < (tmanager->cur_size-1)) 
            && (tmanager->array[child+1]->expire) 
                < tmanager->array[child]->expire )
        {
            ++child;
        }
        //比较待删除节点和最小儿子节点，若大于就交换
        if ( tmanager->array[child]->expire < tmanager->array[hole]->expire )
        {
            heap_timer* tmp_heap_timer = tmanager->array[hole];
            tmanager->array[hole] = tmanager->array[child];
            tmanager->array[child] = tmp_heap_timer;
#if 0
            //这里的交换其实该用内存拷贝比较好
            int tmp_expire = tmanager->array[hole]->expire;
            int tmp_timeout = tmanager->array[hole]->timeout;
            tmanager->array[hole]->expire = tmanager->array[child]->expire;
            tmanager->array[hole]->timeout = tmanager->array[child]->timeout;
            tmanager->array[child]->expire = tmp_expire;
            tmanager->array[child]->timeout = tmp_timeout;
#endif
        }
        else
        {
            //找到的了位置，就不在继续向下比较
            break;
        }
        //新的下滤比较
        //temp = tmanager->array[child];
        //tmanager->array[hole] = temp;
    } 
    //free( tmanager->array[tmanager->cur_size] );
    //tmanager->array[tmanager->cur_size] = NULL;  
}
//将堆数组的容量扩大1倍
static int resize( h_t_manager* tmanager )
{
    printf("@@@@@@@@@@@[%s]@@@@@@@@@@@@@@\n",__func__);
    heap_timer** temp = (heap_timer**)
            malloc( 2 * tmanager->capacity * sizeof(heap_timer*) );
 
    int i = 0;
    for ( ; i < 2 * tmanager->capacity; ++i )
    {
        temp[i] = NULL;
    }
    if ( !temp )
    {
        return -1;
    }
    tmanager->capacity = 2 * tmanager->capacity;
    for ( i = 0; i < tmanager->cur_size; ++i )
    {
        temp[i] = tmanager->array[i];
        //free(tmanager->array[i]);
        tmanager->array[i] = NULL;
    }
    free(tmanager->array);
    tmanager->array = temp;
 
    return 0;
}
//初始化一个小根堆定时管理器
int init_ht_manager_0( h_t_manager* tmanager, int cap )
{
    tmanager->capacity = cap;
    tmanager->cur_size = 0;
    tmanager->array = (heap_timer**)malloc(cap * sizeof(heap_timer*));
 
    int i = 0;
    for ( ; i < cap; ++i )
    {
        tmanager->array[i] = NULL;
    }
    printf("[%s] over\n",__func__);
}
//添加定时器
int add_timer( h_t_manager* tmanager, int timeout )
{
    if ( !tmanager || timeout <= 0)
    {
        return -1;
    }
    if ( tmanager->cur_size >= tmanager->capacity )
    {
        printf("小根堆重分配\n");
        resize( tmanager );
    }
    int hole = tmanager->cur_size++;
    int parent = 0;
    heap_timer* timer = (heap_timer*)malloc(sizeof(heap_timer));
    time_t tt = time(NULL);
    timer->expire = (int)tt + timeout;
    timer->timeout = timeout;
    timer->user_data = (client_data*)malloc(sizeof(client_data));
    timer->user_data->tt = time(NULL);
    timer->cb_func = cb_func;
    for ( ; hole > 0; hole = parent )
    {
        parent = ( hole - 1 ) / 2;
        if ( tmanager->array[parent]->expire <= timer->expire )
        {
            break;
        }
        tmanager->array[hole] = tmanager->array[parent];
    }
    tmanager->array[hole] = timer;
    printf("[%s] add over\n",__func__);
    return 0;
}
/*
int del_timer( h_t_manager* tmanager, heap_timer* timer )
{
    if ( !tmanager || !timer )
    {
        return -1;
    }
    timer->cb_func = NULL;
}
*/
int empty( h_t_manager* tmanager )
{
    return tmanager->cur_size == 0;
}
/*
heap_timer* top( h_t_manager* tmanager )
{
    if ( empty(tmanager) )
    {
        printf("!!!!!!!top->empty cur size\n");
        return NULL;
    }
    return tmanager->array[0];
}
*/
//弹出第一个任务
int pop_timer( h_t_manager* tmanager )
{
    if ( empty( tmanager ) )
    {
        printf("!!!!!!!pop_timer->empty cur size\n");
        return -1;
    }
    if ( tmanager->array[0] )
    {
        free( tmanager->array[0] );     /* 弹出任务后，堆大小减小 */
        tmanager->array[0] = NULL;
        printf("###[%s]:tmanager->cur_size = [%d]\n",__func__,tmanager->cur_size);
        tmanager->array[0] = tmanager->array[--tmanager->cur_size];
       
        printf("###[%s]:tmanager->cur_size = [%d]\n",__func__,tmanager->cur_size);
        percolate_down( tmanager, 0 );
    }
    return 0;
}
//心跳检测函数
void tick( h_t_manager* tmanager )
{
    heap_timer* tmp = tmanager->array[0];
    time_t cur = time( NULL );
    while ( !empty(tmanager) )
    {
        if ( !tmp )
        {
            printf("tmanager->array[0] 不存在\n");
            break;
        }
        if ( tmp->expire > cur )
        {
            printf("时间还没到\n");
            break;
        }
        if ( tmanager->array[0]->cb_func )
        {
            printf("时间到了:\n");
            int i = 0;
            for ( ; i < tmanager->cur_size; i++ )
            {
                if ( tmanager->array[i] )
                    printf("第%d任务:超时时间%d ", i, tmanager->array[i]->timeout);
            }
            printf("\n启动第0个任务\n");
            tmanager->array[0]->cb_func( tmanager->array[0]->user_data );
        }
        pop_timer( tmanager );
        tmp = tmanager->array[0];
        printf("小根堆执行0任务后大小[%d]\n",tmanager->cur_size);
        int i = 0;
        for ( ; i < tmanager->cur_size; i++ )
        {
            if ( tmanager->array[i] )
                printf("~第%d个任务:超时时间%d ", i, tmanager->array[i]->timeout);
        }
        printf("\n");
    }
    printf("小根堆为空\n");
}

h_t_manager tmanager;

void alarm_handler( int sig )
{
 
    tick( &tmanager );
    printf("[%s]当前小根堆大小[%d]\n",__func__,tmanager.cur_size);
    if(tmanager.cur_size > 0)
        alarm( tmanager.array[0]->expire - time(NULL) );
    else
    {
        printf("当前没有任务\n");
        alarm(2);
    }
    
}
int main()
{
    printf("开始小根堆构建....\n");
    init_ht_manager_0( &tmanager, 6 );
    add_timer( &tmanager, 90 );
    add_timer( &tmanager, 80 );
    add_timer( &tmanager, 70 );
    add_timer( &tmanager, 60 );
    add_timer( &tmanager, 50 );


    signal( SIGALRM, alarm_handler );
 
    time_t tt = time(NULL);
    printf("当前时间:%s\n", ctime(&tt));
    alarm( tmanager.array[0]->expire - time(NULL) );

    int i = 6;
    while(i)
     {
        sleep(10);
        add_timer( &tmanager, i*i );
        printf("********************%d*******************\n",--i);
    }
    sleep(60);
    add_timer( &tmanager, 40 );
    add_timer( &tmanager, 30 );
    add_timer( &tmanager, 20 );
    add_timer( &tmanager, 10 );
    add_timer( &tmanager, 7 );
    
 
    while(1)
        sleep(5);
 
    return 0;
}
