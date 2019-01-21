#include "Sharemem.h"

//创建一块共享内存
int create_shm(char *keyfile, int shm_size)
{
    int z       = 0;    /*状态代码*/
    int offset  = 0;    /*字节的offset*/
    int shmid   = 0;
    struct shmid_ds shminfo;    /*共享内存信息*/
    FILE *fp;
    key_t shmk;

    if((fp = fopen(keyfile,"w")) == NULL)
    {
        printf("Failed to create shm key file!\n");
        exit(-1);
    }
    fclose(fp);

    if((shmk = ftok(keyfile,'&')) == -1)
    {
        printf("Failed to obtain shm key!\n");
        exit(-1);
    }

    
    z = shmget(shmk, shm_size, IPC_CREAT|0666); /*创建shmem*/
    if(z == -1)
    {
        fprintf(stderr,"%s:shmget(shmk=%d,shm_size=%d,IPC_CREAT)\n",strerror(errno),shmk,shm_size);
        exit(1);
    }

    shmid = z; /*shmem的IPC ID*/
    z = shmctl(shmid,IPC_STAT,&shminfo); /*显示该内存区域实际的长度*/
    if(z == -1)
    {
        fprintf(stderr,"%s:shmctl(%d,IPC_STAT)\n",strerror(errno),shmid);
        exit(1);
    }

    shm_size = shminfo.shm_segsz; /*shmem实际的长度*/
    fprintf(stderr,"real length of shm_size = %d\n", shm_size);
    return shmid;
}

//删除一个共享内存池
void destroy_shm(int shmid)
{
    int z   = 0;
    /*删除 IPC ID*/
    z = shmctl(shmid, IPC_RMID, NULL);
    if(z == -1)
    {
        fprintf(stderr,"%s:shmctl(%d,IPC_RMID)\n",strerror(errno),shmid);
        exit(1);
    }
    return;
}

//绑定一个共享内存池
void *attach_shm(int shmid)
{
    void *pshm = NULL;

    pshm = shmat(shmid, 0, 0);
    if((void *)(pshm) == (void *)(-1))
    {
        fprintf(stderr,"%s:shmat(%d,0,0)\n",strerror(errno),shmid);
        exit(1);
    }
    return pshm;
}

//卸载一个共享内存
void detach_shm(void *pshm)
{
    int z = 0;
    z = shmdt(pshm);
    if(z == -1)
    {
        fprintf(stderr,"%s:shmdt(2)\n",strerror(errno));
        exit(1);
    }
    return;
}