#include "shm_base.h"

int gen_shm(const char *file_name, int size)
{
    int shmid;
    FILE *fp = NULL;
    key_t shm_key;

    if(NULL == file_name || 0 >= size)
    {
        //LOG_ERROR("gen_shm:param error, file_name:%s, size:%d", file_name, size);
        return -1;
    }

    if(NULL == (fp = fopen(file_name, "w")))
    {
        //LOG_ERROR("fopen error: %s", file_name);
        return -1;
    }
    fclose(fp);

    if(-1 == (shm_key = ftok(file_name, 0)))
    {
        //LOG_ERROR("ftok error: %s", file_name);
        return -1;
    }

    shmid = shmget(shm_key, size, 0666 | IPC_CREAT);
    if(-1 == shmid)
    {
        //LOG_ERROR("shmget error:%s", strerror(errno));
        //print_err(errno);
        return -1;
    }

    return shmid;
}

int attach_shm(int shmid, void **shm)
{
    void *tmp = NULL;

    tmp = shmat(shmid, 0, 0);
    if((void *)(-1) == tmp)
    {
        //LOG_ERROR("shmat error");
        return -1;
    }

    *shm = tmp;
    return 0;
}

int attach_shm_by_filename(const char *file_name, void **shm)
{
    key_t shm_key;
    int shmid;
    void *tmp = NULL;

    if(-1 == (shm_key = ftok(file_name, 0)))
    {
        //LOG_ERROR("ftok error: %s", file_name);
        return -1;
    }

    shmid = shmget(shm_key, 0, 0);
    if(-1 == shmid)
    {
        //LOG_ERROR("shmget error:%s", strerror(errno));
        //print_err(errno);
        return -1;
    }

    tmp = shmat(shmid, 0, 0);
    if((void *)(-1) == tmp)
    {
        //LOG_ERROR("shmat error");
        return -1;
    }

    *shm = tmp;
    return 0;
}

int detach_shm(void *shm)
{
    if(-1 == shmdt(shm))
    {
        //LOG_ERROR("shmdt error");
        return -1;
    }
    return 0;
}

int rm_shm(int shmid)
{
    if(-1 == shmctl(shmid, IPC_RMID, 0))
    {
        //LOG_ERROR("shmctl error");
        return -1;
    }
    return 0;
}

