#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#define SIG_RULE SIGRTMIN+14
unsigned int flag = 0;
static void recive_sig(int signo)
{
	flag++;
	printf("yes! i recive a signo\n");
}
void child_process()
{
	pid_t ppid = -1;
	ppid = getppid();
	printf("i am a child process ppid=[%d]\n",ppid);	
	sleep(7);
		if(kill(ppid,SIG_RULE)==-1)
		{
			printf("fail to send signal\n");
		}
		else
		{
			printf("kill signal send success\n");
		}
}
int main()
{
	pid_t pid;

	pid = fork();
	switch(pid)
	{
		case -1:
			printf("fork child error\n");
			break;
		case 0:
			child_process();
			return 0;
		default:
			break;
	}
	
	if(signal(SIG_RULE,recive_sig)==SIG_ERR)
	{
		perror("can't set recive_sig for SIGINT");
		exit(1);
	}	
	while(1)
	{
		//if(signal(SIGINT))
		if(flag==0)
		{
			printf("flag=[%d]\n",flag);
		}
		else
		{
			printf("flag=[%d]\n",flag);
			sleep(5);
			break;
		}
		sleep(2);
	}
	printf("flag=[%d]\n",flag);
	return 0;
}
