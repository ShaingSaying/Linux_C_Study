#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<semaphore.h>

char buff[128] = {0};
sem_t sem;

void *pthread_fun(void *arg)
{
    pthread_t t_id;
    t_id = pthread_self();
    sem_wait(&sem);
    while(1)
    {
        sem_wait(&sem);
        //sleep(2);
        if(strncmp(buff,"end",3) == 0)
        {
            printf("total thread[%u] exiting...\n",t_id);
            break;
        }
        printf("total thread[%u] buff length:%d\n",t_id ,strlen(buff) - 1);
    }
}

int main()
{
    pthread_t id,thread_id;
    sem_init(&sem,0,0);
    int res = 0;
    res = pthread_create(&id, NULL, pthread_fun, NULL);
    assert(res == 0);
    thread_id = pthread_self();
    while(1)
    {
        printf("get buff[%u][please input]:\n",thread_id);
        fflush(stdout);
        fgets(buff,128,stdin);
        sem_post(&sem);
        if(strncmp(buff, "end", 3) == 0)
        {
            printf("get buff thread[%u] exiting...\n",thread_id);
            break;
        }
        sleep(1);
    }
    pthread_join(id,NULL);
    return 0;
}
