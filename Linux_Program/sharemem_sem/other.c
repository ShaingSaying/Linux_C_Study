#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
 
#define MAX_BUFFER_SIZE 10
#define SHM_MODE 0600
#define SEM_MODE 0600
 
#define SEM_FULL 0
#define SEM_EMPTY 1
#define MUTEX 2
 
struct my_buffer
{
	int head;
	int tail;
	char str[MAX_BUFFER_SIZE];
	int num;  //缓冲区里字母数量
	int is_empty;
};
 
const int N_CONSUMER    = 2;    //消费者数量
const int N_PRODUCER    = 2;    //生产者数量
const int N_BUFFER      = 10;   //缓冲区容量
const int N_WORKTIME    = 10;   //工作次数
int shm_id              = -1;
int sem_id              = -1;
pid_t child;
pid_t parent;
 
//得到10以内的一个随机数  
int get_random()  
{  
    int digit;  
    srand((unsigned)(getpid() + time(NULL)));  
    digit = rand() % 10;  
    return digit;  
}  
 
//得到A～Z的一个随机字母  
char getRandChar()
{
    char letter;  
    srand((unsigned)(getpid() + time(NULL)));  
    letter = (char)((rand() % 26) + 'A');  
    return letter;  
}
 
//sem_id 表示信号量集合的 id
//sem_num 表示要处理的信号量在信号量集合中的索引
//P操作
void waitSem(int sem_id,int sem_num)
{
	struct sembuf sb;
	sb.sem_num = sem_num;
	sb.sem_op = -1;//表示要把信号量减一
	sb.sem_flg = SEM_UNDO;//
	//第二个参数是 sembuf [] 类型的，表示数组
	//第三个参数表示 第二个参数代表的数组的大小
	if(semop(sem_id,&sb,1) < 0){
		perror("waitSem failed");
		exit(1);
	}
}
 
//V操作
void sigSem(int sem_id,int sem_num)
{
	struct sembuf sb;
	sb.sem_num = sem_num;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	//第二个参数是 sembuf [] 类型的，表示数组
	//第三个参数表示 第二个参数代表的数组的大小
	if(semop(sem_id,&sb,1) < 0){
		perror("sigSem failed");
		exit(1);
	}
}
 
//打印进程运行结果
void printTime()
{
	//打印时间
	time_t now;
	struct tm *timenow;         //实例化tm结构指针
	time(&now);
	timenow = localtime(&now);
	printf("执行时间： %s ",asctime(timenow));
}
 
int main(int argc, char ** argv)
{
	shm_id = shmget(IPC_PRIVATE,MAX_BUFFER_SIZE,SHM_MODE);   //申请共享内存
	if(shm_id < 0)
	{
		perror("create shared memory failed");
		exit(1);
	}
 
	struct my_buffer *shmptr;  
	shmptr = shmat(shm_id, 0, 0);   //将申请的共享内存附加到申请通信的进程空间
	if (shmptr == (void*)-1)
	{  
        perror("add buffer to using process space failed！\n");  
        exit(1);  
    }  
 
	if((sem_id = semget(IPC_PRIVATE,3,SEM_MODE)) < 0)
	{                  								//创建三个信号量，SEM_EMPTY,SEM_FULL和MUTEX
		perror("create semaphore failed! \n");
		exit(1);
	}
 
	if(semctl(sem_id,SEM_FULL,SETVAL,0) == -1)
	{												//将索引为0的信号量设置为0-->SEM_FULL
		perror("sem set value error! \n");		
		exit(1);
	}
 
	if(semctl(sem_id,SEM_EMPTY,SETVAL,10) == -1)
	{												//将索引为1的信号量设置为10-->SEM_EMPTY
	 	perror("sem set value error! \n");
	 	exit(1);
	}
	if(semctl(sem_id,MUTEX,SETVAL,1) == -1)
	{												//将索引为3的信号量设置为1-->MUTEX
	 	perror("sem set value error! \n");
	 	exit(1);
	}
 
	shmptr -> head = 0;  
    shmptr -> tail = 0;  
    shmptr -> is_empty = 1;  
    shmptr -> num = 0;
 
	for(int i = 0; i < N_PRODUCER; i++)
	{
		parent = fork();
		if(parent < 0)
		{
			perror("the fork failed");
			exit(1);
		}
		else if(parent == 0)
		{
			shmptr = shmat(shm_id, 0, 0);   //将申请的共享内存附加到申请通信的进程空间
			if (shmptr == (void*)-1)
			{  
        		perror("add buffer to using process space failed！\n");  
        		exit(1);  
    		}  
			int count = 0;
			for(int j = 0; j < N_WORKTIME; j++)
			{
				waitSem(sem_id, SEM_EMPTY);
				waitSem(sem_id, MUTEX);
				sleep(get_random()); 
 
				printf("-------------------------------------------------------------\n");
				printf("我是第 %d 个生产者进程，PID = %d\n", i + 1, getpid());
 
				/*生产产品*/
				char c = getRandChar();                                      //随机获取字母
				shmptr -> str[shmptr->tail] = c;
                shmptr -> tail = (shmptr->tail + 1) % MAX_BUFFER_SIZE;  
                shmptr -> is_empty = 0;           //写入新产品  
				shmptr -> num++;
 
				/*打印输出结果*/
				printTime();              //程序运行时间
 
				int p;
				printf("缓冲区数据（%d个）：",shmptr -> num);                   //打印缓冲区中的数据
				p = (shmptr->tail-1 >= shmptr->head) ? (shmptr->tail-1) : (shmptr->tail-1 + MAX_BUFFER_SIZE);  
                for (p; !(shmptr -> is_empty) && p >= shmptr -> head; p--)  
                {  
                    printf("%c", shmptr -> str[p % MAX_BUFFER_SIZE]);  
                }  
                printf("\t 生产者 %d  放入 '%c'. \n", i + 1, c);  
				printf("-------------------------------------------------------------\n");
 
				fflush(stdout);
				sigSem(sem_id, MUTEX);
				sigSem(sem_id, SEM_FULL);
			}
			//将共享段与进程之间解除连接  
            shmdt(shmptr);  
            exit(0); 
		} 
	}
 
	for(int i = 0; i < N_CONSUMER; i++)
	{
		child = fork();
		if(child < 0)//调用fork失败
		{
			perror("the fork failed");
			exit(1);
		}
		else if(child == 0)
		{
			int count = 0; 
			shmptr = shmat(shm_id, 0, 0);   //将申请的共享内存附加到申请通信的进程空间
			if (shmptr == (void*)-1)
			{  
        		perror("add buffer to using process space failed！\n");  
        		exit(1);  
    		} 
			for(int j = 0; j < N_WORKTIME; j++)
			{
 
				waitSem(sem_id, SEM_FULL);
				waitSem(sem_id, MUTEX);
				sleep(get_random()); 
 
				printf("-------------------------------------------------------------\n");
				printf("我是第 %d 个消费者进程，PID = %d\n", i + 1, getpid());
				/*消费数据*/
				char lt = shmptr -> str[shmptr -> head];  
                shmptr -> head = (shmptr -> head + 1) % MAX_BUFFER_SIZE;  
                shmptr -> is_empty = (shmptr->head == shmptr->tail);  //
				shmptr -> num--;
				/*打印输出结果*/
				printTime(); //程序运行时间
 
				int p;
				printf("缓冲区数据（%d个）：",shmptr -> num);                   //打印缓冲区中的数据
				p = (shmptr -> tail - 1 >= shmptr -> head) ? (shmptr -> tail-1) : (shmptr -> tail - 1 + MAX_BUFFER_SIZE);  
                for (p; !(shmptr -> is_empty) && p >= shmptr -> head; p--)  
                {  
                    printf("%c", shmptr -> str[p % MAX_BUFFER_SIZE]);  
                }  
                printf("\t 消费者 %d  取出 '%c'. \n", i + 1, lt);  
				printf("-------------------------------------------------------------\n");
 
				fflush(stdout);
				sigSem(sem_id,MUTEX);
				sigSem(sem_id,SEM_EMPTY);
			}
			//将共享段与进程之间解除连接  
        	shmdt(shmptr);  
        	exit(0);
		}  
	}
 
	    //主进程最后退出  
    while (wait(0) != -1);  
    //将共享段与进程之间解除连接  
    shmdt(shmptr);  
    //对共享内存区执行控制操作  
    shmctl(shm_id,IPC_RMID,0);//当cmd为IPC_RMID时，删除该共享段  
    shmctl(sem_id,IPC_RMID,0);  
    printf("主进程运行结束！\n");  
    fflush(stdout);  
    exit(0); 
	return 0;
}
