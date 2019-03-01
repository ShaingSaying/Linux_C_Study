/*
 * 文件名： mypwd1.c
 * 描述：通过系统函数getcwd实现pwd命令
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, int argv[])
{
	char buf[1024];
	char *cwd = getcwd(buf, sizeof(buf));
	
	if( cwd == NULL)
	{
		perror("Get current working directory fail.\n");
		exit(-1);
	}
	else
		printf("Current working directory is: %s\n", cwd);
	
	return 0;
}




