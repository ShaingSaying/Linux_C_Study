#include "time_wheel.h"
void* ontime_func( void* param )
{
    client_data* data = (client_data*)param;
    time_t tt = time(NULL);
    printf("\n----------------------------------------------------\n");
    printf("\tontime,interval:%d\n", (int)(tt - data->tt));
    printf("\told time:%s", ctime(&data->tt));
    printf("\t%s", data->buf);
    printf("\tcur time:%s", ctime(&tt));
    printf("----------------------------------------------------\n");
    return NULL;
}

int add_timer( timer_manager* tmanager, int timeout, client_data* c_data )
{
    if ( timeout < 0 || !tmanager )
        return -1;
 
    int tick = 0;           /* 转动几个槽触发 */
    int rotation = 0;       /* 处于时间轮第几转 */
    int slot = 0;           /* 距离当前槽相差几个槽 */
 
    if ( timeout < tmanager->slot_interval )
        tick = 0;
    else
        tick = timeout / tmanager->slot_interval;
 
    rotation = tick / tmanager->slot_num_r;     /* 时间轮一转的总槽数 */
    /* (当前槽位置+转动槽个数%一圈总槽数)%一圈总槽数 */
    slot = ( tmanager->cur_slot + tick % tmanager->slot_num_r ) % \
         tmanager->slot_num_r - 1;
 
    printf("addtimer-->timeout:%d, rotation:%d, slot:%d\n",
        timeout, rotation, slot);
 
    tw_timer* tmp_t = (tw_timer*)malloc(sizeof(tw_timer));
    if(NULL == tmp_t)
    {
        printf("malloc error\n");
    }
    
    char buf[100] = {0};
    time_t tt = time(NULL) + timeout;
    sprintf( buf, "set time:%s", ctime(&tt));
    memset( tmp_t->c_data.buf, 0, sizeof(tmp_t->c_data.buf));
    strcpy( tmp_t->c_data.buf, buf );

    tmp_t->c_data.tt = tt;
    tmp_t->rotation = rotation;
    tmp_t->slot = slot;
    tmp_t->cb_func = ontime_func;
 
    if ( !tmanager->slots_head[slot] )
    {
        tmanager->slots_head[slot] = tmp_t;
        tmp_t->next = NULL;
        return 0;
    }
    tmp_t->next = tmanager->slots_head[slot]->next;     /* 头插法 */
    tmanager->slots_head[slot]->next = tmp_t;
 
    return 0;
}
int del_all_timer( timer_manager* tmanager )
{
    //清除、释放所有定时器
}
int tick( timer_manager* tmanager )
{
    if ( !tmanager )
        return -1;
 
    tw_timer* tmp = tmanager->slots_head[tmanager->cur_slot];
    tw_timer* p_tmp;
 
    while ( tmp )
    {
        /* rotation减一，当前时间轮转不起作用
        假设这个tmp指向第0个槽的头，链中某个结点的rotaion为下一圈，
        即rotation=1，所以这个定时器不起作用，而因为cur_slot不断
        走动，tmp在当前转不可能再指向这个定时器，下一圈cur_slot
        为0时能继续判断这个定时器，故实现了定时器处于不同转的判断 */
        if ( tmp->rotation > 0 )
        {
            tmp->rotation--;
            p_tmp = tmp;
            tmp = tmp->next;
        }
        else    /* 一直遍历到rotation==0的事件 */
        {
            tmp->cb_func( &tmp->c_data );                           /* 否则定时器到时，触发回调函数 */
            /* 排除rotation!=0的结点都是要触发的事件 */
            if ( tmp == tmanager->slots_head[tmanager->cur_slot] )  /* 删除此定时器结点，双向链表会更好 */
            {
                tmanager->slots_head[tmanager->cur_slot] = tmp->next;
                p_tmp = tmp;
                tmp = tmp->next;
                free( p_tmp );
                p_tmp = NULL;
                p_tmp = tmp;
            }
            else    /* 跳过tmp结点 */
            {
                p_tmp->next = p_tmp->next->next;
                free( tmp );
                tmp = NULL;
                tmp = p_tmp->next;
            }
        }
    }
    //更新时间轮，转动一个槽，转一圈又从开始转
    tmanager->cur_slot = ++tmanager->cur_slot % tmanager->slot_num_r;
 
    return 0;
}
int init_t_manager( timer_manager* tmanager, int slot_num_r, int slot_interval )
{
    tmanager->cur_slot = 0;
    tmanager->slot_num_r = slot_num_r;
    tmanager->slot_interval = slot_interval;
 
    return 0;
}