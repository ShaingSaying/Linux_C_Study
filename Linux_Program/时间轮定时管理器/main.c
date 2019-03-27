#include"time_wheel.h"
void alarm_handler( int sig )
{
    time_t tt = time(NULL);
    int ret = tick( &tmanager );
    if ( ret < 0 )
    {
        printf("tick error\n");
        alarm(2);
    }
    alarm( tmanager.slot_interval );
}
int main()
{
    time_t tt = time(NULL);
    signal( SIGALRM, alarm_handler );
    init_t_manager( &tmanager, 60, 1 );
    add_timer( &tmanager, 6, NULL );
    add_timer( &tmanager, 11, NULL );
    add_timer( &tmanager, 22, NULL );
    add_timer( &tmanager, 33, NULL );
    add_timer( &tmanager, 44, NULL );
    add_timer( &tmanager, 55, NULL );
    add_timer( &tmanager, 66, NULL );
    add_timer( &tmanager, 77, NULL );
    add_timer( &tmanager, 88, NULL );
    add_timer( &tmanager, 99, NULL );
    add_timer( &tmanager, 111, NULL );
    add_timer( &tmanager, 122, NULL );
    add_timer( &tmanager, 133, NULL );
    add_timer( &tmanager, 144, NULL );
    printf("start time:%s\n", ctime(&tt));
    alarm( tmanager.slot_interval );
    while ( 1 )
        sleep( 5 );
    return 0;
}