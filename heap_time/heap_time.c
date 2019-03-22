/* https://blog.csdn.net/u012785877/article/details/52420535 */
#include"heap_time.h"

void alarm_func(void* param)
{
    printf("hello world\n");
}

void percolate_down(heap_time * tmanager, int hole)
{
    heap_unit *temp = tmanager->heap_arry[hole];
    int flag = 0;
    int child = 0;
    for(;((hole*2+1) <= (tmanager->cur_num-1)); hole = child)
    {
        flag = 0;
        child = hole * 2 + 1;

        //这里找出当前节点最小儿子节点
        if ( (child < (tmanager->cur_num-1)) 
            && (tmanager->heap_arry[child+1]->expire) 
                < tmanager->heap_arry[child]->expire )
        {
            ++child;
        }
        //比较待删除节点和最小儿子节点，大于就交换
        if(tmanager->heap_arry[child]->expire < temp->expire)
        {
            //这里的交换其实该用内存拷贝比较好
            int tmp_expire = tmanager->heap_arry[hole]->expire;
            int tmp_timeout = tmanager->heap_arry[hole]->timeout;
            tmanager->heap_arry[hole]->expire = tmanager->heap_arry[child]->expire;
            tmanager->heap_arry[hole]->timeout = tmanager->heap_arry[child]->timeout;
            tmanager->heap_arry[child]->expire = tmp_expire;
            tmanager->heap_arry[child]->timeout = tmp_timeout;
        }
        else
        {
            break;
        }
        temp = tmanager->heap_arry[child];
    }
}

int resize(heap_time * tmanager)
{
    heap_unit** temp = (heap_timer**)
            malloc(2*tmanager->capacity*sizeof(heap_time));

    int i = 0;
    for(; i<2*tmanager->capacity;++i)
    {
        temp[i] = NULL;
    }
    if(!temp)
    {
        return -1;
    }
    tmanager->capacity = 2 * tmanager->capacity;
    for(i=0;i<tmanager->cur_num;++i)
    {
        temp[i] = tmanager->heap_arry[i];
        free(tmanager->heap_arry[i]);
        tmanager->heap_arry[i] = NULL;
    }
    tmanager->heap_arry = temp;
    return 0;
}