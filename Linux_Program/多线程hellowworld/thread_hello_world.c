#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//gcc thread_hello_world.c -o test -lpthread

void printf_message_function (void *ptr);

int main()
{
    int tmp1, tmp2;
    void *retval;
    pthread_t thread1, thread2;
    char *message1 = "thread1";
    char *message2 = "thread2";

    int ret_thrd1, ret_thrd2;

    ret_thrd1 = pthread_create(&thread1, NULL, (void *)&printf_message_function, (void *) message1);

    ret_thrd2 = pthread_create(&thread2, NULL, (void *)&printf_message_function, (void *) message2);

    if(ret_thrd1 != 0)
        printf("线程1创建失败\n");
    else
        printf("线程1创建成功\n");

    if(ret_thrd2 != 0)
        printf("线程1创建失败\n");
    else
        printf("线程1创建成功\n");

    tmp1 = pthread_join(thread1, &retval);
    printf("thread1 return value(retval) is %d\n", (int)retval);
    printf("thread1 return value(tmp) is %d\n", tmp1);
    if(tmp1 != 0)
        printf("cannot join with thread1\n");
    printf("thread1 end\n");

    tmp2 = pthread_join(thread2, &retval);
    printf("thread2 return value(retval) is %d\n", (int)retval);
    printf("thread2 return value(tmp) is %d\n", tmp2);
    if(tmp2 != 0)
        printf("cannot join with thread2\n");
    printf("thread2 end\n");

    return 0;
}

void printf_message_function(void *ptr)
{
    int i = 0;
    for(i; i<5; i++)
        printf("%s:\t%d\n",(char *)ptr, i);
}