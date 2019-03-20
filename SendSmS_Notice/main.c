#include "shm_base.h"
#include "sms_heap.h"

int main()
{
    int shmid = 0;
    int ret = 0;
    heap* heaphead;


    shmid = gen_shm("/.heap",sizeof(heap));
    if(-1 == shmid)
    {
        printf("gen_shm error\n")
        return -1;
    }

    ret = attach_shm(shmid, (void **)&heaphead);
    if(0 != ret)
    {
        printf("attach_shm error\n");
        return -1;
    }

    

}