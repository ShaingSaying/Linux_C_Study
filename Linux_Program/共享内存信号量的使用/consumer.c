#include "consumer.h"
#include "Sharemem.h"
#include "Semaphore.h"

extern DATA* data;
void child_usage_data()
{
    int semid1,semid2;
    int a = 10;
    INFO *info;
    int shmid1;

    
    //连接以创建的信号量
    if((semid1 = semget((key_t)666,1,IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(1);
    }
    
    while(a)
    {
        sleep(3);
        sem_p(semid1);
        data->a++;
        data->b++;
        data->c++;
        printf("[%d][child_usage_data]--data->a = %d\n", getpid(), data->a);
        printf("[%d][child_usage_data]--data->b = %d\n", getpid(), data->b);
        printf("[%d][child_usage_data]--data->c = %d\n", getpid(), data->c);
        sem_v(semid1);
   
        a--;
    }

    //连接已创建的共享内存
    shmid1 = create_shm(".helloworld123", sizeof(INFO));
    info = (INFO *)attach_shm(shmid1);
    if((semid2 = semget((key_t)555,1,IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(1);
    }

    a+=30;
    while(a)
    {
        sleep(3);
        sem_p(semid2);
        info->i++;
        printf("[%d][child_usage_data]info->info=[%d]\n",getpid(),info->i);
        sem_v(semid2);      
        a--;
    }
}