#include"heap_timer.h"
#include<signal.h>

int main()
{
    
    printf("Start building heaps....\n");
    init_heap_time(&tmanager1, 6);

    add_timer( &tmanager1, 90, 1 );
    add_timer( &tmanager1, 80, 2 );
    add_timer( &tmanager1, 70, 3 );
    add_timer( &tmanager1, 60, 4 );
    add_timer( &tmanager1, 50, 5 );

    signal( SIGALRM, alarm_handler );

    time_t tt = time(NULL);
    printf("当前时间:%s\n", ctime(&tt));
    alarm( tmanager1.heap_array[0]->expire - time(NULL) );

    int i = 6;
    int j = 6;
    while(i)
     {
        sleep(10);
        add_timer( &tmanager1, i*i,  j++);
        printf("********************%d*******************\n",--i);
    }
    sleep(60);
    add_timer( &tmanager1, 40 , j++);
    add_timer( &tmanager1, 30 , j++);
    add_timer( &tmanager1, 20 , j++);
    add_timer( &tmanager1, 10 , j++);
    add_timer( &tmanager1, 7 , j++);
    
    j = 0;
    while(1)
        sleep(5);
 
    return 0;
}