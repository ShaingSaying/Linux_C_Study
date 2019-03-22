#include "shm_base.h"
#include "sms_heap.h"
int capacity = 4;
int irand()
{
    int a;
    srand((unsigned)time(NULL));
    a = rand()%100 +50;
    //sleep(1);
    return a;
}

time_t get_time()
{
    time_t t;
    time(&t);
    return t;
}

void child()
{
    int ret;
    heap* heaphead;
    time_t nowtime;

    ret = attach_shm_by_filename("/.heap",(void **)&heaphead);
    if(-1 == ret)
    {
        printf("attach_shm_by_filename error\n");
        return;
    }

    while(1)
    {
        pthread_mutex_lock(&heaphead->mutex);
        nowtime=get_time();
        if(heaphead->heap_node[0].time != 0 && (nowtime-heaphead->heap_node[0].time) > 15)       /* 如果堆顶元素到达某值，则取出 */
        {
            printf("子进程访问堆顶元素,定时到达nowtime[%ld]beginetime[%ld]则发出:\n",nowtime,heaphead->heap_node[0].time);
            heaphead->heap_node[0].time = 0;
            heaphead->heap_node[0].data = 0;
            heaphead->heap_node[0].num = 0;
            HeapSort(heaphead,capacity);
        }
        printf("子进程[%ld]遍历打印堆元素:\n",getpid());
        printfheap(heaphead,capacity);
        pthread_mutex_unlock(&heaphead->mutex);
        sleep(5);
    }

    detach_shm(heaphead);
}
int main()
{
    int shmid = 0;
    int ret = 0;
    heap* heaphead;
    pid_t pid;
    int i;

    shmid = gen_shm("/.heap",sizeof(heap));
    if(-1 == shmid)
    {
        printf("gen_shm error\n");
        return -1;
    }

    ret = attach_shm(shmid, (void **)&heaphead);
    if(0 != ret)
    {
        printf("attach_shm error\n");
        return -1;
    }

    pthread_mutexattr_init(&heaphead->mutexattr);
    pthread_mutexattr_setpshared(&heaphead->mutexattr,PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&heaphead->mutex,&heaphead->mutexattr);

    printf("init heap:\n");
    memset(heaphead->heap_node,0x00,sizeof(heapnode)*capacity);
    printfheap(heaphead,capacity);


    pid = fork();
    if(0 == pid)
    {
       child();
    }

    while(1)
    {
        pthread_mutex_lock(&heaphead->mutex);
        printf("======主进程遍历堆:======\n");
        for(i=0;i<capacity;i++)
        {
            if(heaphead->heap_node[i].time == 0)
            {
                printf("主进程寻找到空位置则插入值:\n");
                heaphead->heap_node[i].time = get_time();
                heaphead->heap_node[i].data = irand();
                heaphead->heap_node[i].num = irand();
                HeapSort(heaphead,capacity);
                break;
            }
        }
        printf("主进程[%ld]遍历打印堆元素:\n",getpid());
        printfheap(heaphead,capacity);
        pthread_mutex_unlock(&heaphead->mutex);
        sleep(3);
    }

    pthread_mutexattr_destroy(&heaphead->mutexattr);
    pthread_mutex_destroy(&heaphead->mutex);
    detach_shm(heaphead);
    rm_shm(shmid);
    return 0;
}
