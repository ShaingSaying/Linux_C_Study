#include "control.h"
#include "Sharemem.h"
#include "Semaphore.h"

extern DATA* data;
void control_center()
{
    pid_t ppid = -1;
    int a = 10;
    int shmid;
    INFO *info = NULL;
    int semid2;

    //创建第二块共享内存
    data->shmid = create_shm(".helloworld123", sizeof(INFO));
    info = (INFO *)attach_shm(data->shmid);
    if(info != NULL)
    {
        info->i = 0;
        info->e = 0;
    }

    //获取主进程pid
    ppid = getppid();
    while(a)
    {
        //发送信号
        if(kill(ppid,SIG_RULE) == -1)
        {
            printf("send signal faild\n");
        }
        printf("control center send SIG_RULE signol pid=[%d]\n",getpid());
        sleep(3);
        a--;
    }    

    //创建信号量1
    semid2 = creat_sem((key_t)555);
    a+=30;
    while(a)
    {
        sem_p(semid2);
        info->i+=2;
        printf("[control conter][%d]info->info=[%d]\n",getpid(),info->i);
        sem_v(semid2);
        sleep(5);
        a--;
    }

    //删除信号量2
    del_sem(semid2);
    detach_shm(info);
    destroy_shm(data->shmid);
}