#include "Semaphore.h"

//初始化信号量
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

// P操作: 
// 若信号量值为1，获取资源并将信号量值减1 
// 若信号量值为0，进程挂起等待
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V操作： 
// 释放资源并将信号量值+1 
// 如果有进程正在挂起等待，则唤醒它们 
int sem_v(int sem_id) 
{ 
    struct sembuf sbuf; 
    sbuf.sem_num = 0; /*序号*/ 
    sbuf.sem_op = 1; /*V操作*/ 
    sbuf.sem_flg = SEM_UNDO; 
    if(semop(sem_id, &sbuf, 1) == -1) 
    { 
        perror("V operation Error"); 
        return -1; 
    } 
    return 0; 
}

// 删除信号量集
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}

//创建一个信号量集
int creat_sem(key_t key)
{
    int sem_id;
    if((sem_id = semget(key,1,IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(-1);
    }
    init_sem(sem_id, 1);
    return sem_id;
}