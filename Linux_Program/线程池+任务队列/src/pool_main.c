#include "pool_thread.h"

void *handle(void *arg) //任务处理函数
{
    pthreadspool_t ppool=(pthreadspool_t)arg;
    elem_t val;
    while(1)
    {
        pool_get(ppool,&val);   //从线程池中获得线程执行任务数据
        printf("thread[%u]:excute task!,%d+%d=%d\n",pthread_self(),val.left,val.right,val.left+val.right);  //执行输出
#if 0
        switch(val.left)
        {
            case: 1
                function1(val.right);
                break;
            case: 2
                function2(val.right);
                break;
            default:
                break;
        }
#endif
    }
}
int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("EXE QUE_CAPACITY THREADS_NUM!\n");
        exit(1);
    }//生成的可执行函数后面必须加上2个变量，否则出错
    threadspool_t mypool;
    pool_init(&mypool,atoi(argv[1]),atoi(argv[2]),handle); //线程池初始化 argv[1]->任务队列大小 argv[2]->线程池大小，线程数
    pool_on(&mypool); //启动线程池
    char buf[1024];
    //select函数,每隔一秒去监听键盘上是否有数组输入，如果有，那么把数据流中的数据转换为任务数据添加到任务队列中去
#if 0
    while(1)
    {
        fd_set rds;
        FD_ZERO(&rds);      //初始化
        FD_SET(0,&rds);     //rds捆绑输入，监听

        struct timeval tm;
        tm.tv_sec = 1;
        tm.tv_usec = 0;     //设置时间
        if(0 == select(1024, &rds, NULL, NULL, &tm))
        {
            continue;
        }//如果没有输入，继续监听
        if(FD_ISSET(0,&rds))
        {
            memset(buf, 0, sizeof(buf));
            if(read_char(0,buf,127) == 0) //将键盘上输入的字符流存储到数组中去
            {
                break;
            }
            elem_t val;
            sscanf(buf,"%d%d",&val.left,&val.right); //将数组中的字符赋值两个数字到数据项
            pool_put(&mypool,val);  //加入任务队列
        }
    }
#endif
    //第二种输入方法，不停的输入数字，并将这些数据添加到任务队列中，不用select函数
    int i,x,y;
    elem_t val;
    while(1)
    {
        scanf("%d%d",&x,&y);
        val.left=x;
        val.right=y;
        pool_put(&mypool,val);
    }
    pool_off(&mypool); //关闭多线程
    pool_destroy(&mypool); //销毁线程池
    return 0;
}
