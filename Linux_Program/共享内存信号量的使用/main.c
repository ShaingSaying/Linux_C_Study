#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include "Semaphore.h"
#include "Sharemem.h"
#include "consumer.h"
#include "control.h"

#define SIG_RULE SIGRTMIN+14

DATA *data                  = NULL;     //共享内存结构体
unsigned char *data_start   = NULL;     //共享内存头地址

//创建数据源共享内存
int SHAREMEM_DATA_CREATE()
{
    int shmid;
    if(data_start == NULL)
    {
        shmid = create_shm(".helloworld", sizeof(DATA));
        data_start = (unsigned char*)attach_shm(shmid);
    }

    if(data_start != NULL)
    {
        data = (DATA *)data_start;
        data->a = 0;
        data->b = 0;
        data->c = 0;
        data->flag = 0;
    }
    return shmid;
}

//更新配置
static void update_configure(int signo)
{
    if(SIG_RULE == signo)
    {
        if(data->flag != 666)
            data->flag = 666;
        else
            data->flag = 555;
    }
    printf("recive update configure signo data->flag = [%d]\n", data->flag);
}
int main()
{
    pid_t pid;
    int semid1;
    int shmid;
    int a = 100;
    int pause_time;

    //创建共享内存1
    //SHAREMEM_DATA_CREATE();
    if(data_start == NULL)
    {
        shmid = create_shm(".helloworld", sizeof(DATA));
        data_start = (unsigned char*)attach_shm(shmid);
    }

    if(data_start != NULL)
    {
        data = (DATA *)data_start;
        data->a = 0;
        data->b = 0;
        data->c = 0;
        data->flag = 0;
        data->shmid = 0;
    }

    //注册一个信号函数
    if(signal(SIG_RULE,update_configure) == SIG_ERR)
    {
        printf("can't set update_configure for SIG_RULE\n");
    }

    
    //控制中心
    pid = fork();
    switch(pid)
    {
        case -1:
            break;
        case 0:
            control_center();
            return 0;
        default:
            break;
    }

    

    //创建信号量1
    semid1 = creat_sem((key_t)666);

    //消费数据
    pid = fork();
    switch(pid)
    {
        case -1:
            break;
        case 0:
            child_usage_data();
            return 0;
        default:
            break;
    }

    //主进程生产数据
    while(a)
    {
        //sleep(10);
        sem_p(semid1);
        data->a += 1;
        data->b += 2;
        data->c += 3;
        printf("[main]--data->a = %d\n",data->a);
        printf("[main]--data->b = %d\n",data->b);
        printf("[main]--data->c = %d\n",data->c);
        sem_v(semid1);
        sleep(5);    
        a--;
    }
   

    //删除信号量1
    del_sem(semid1);
    detach_shm(data_start);
    destroy_shm(shmid);

    return 0;
}