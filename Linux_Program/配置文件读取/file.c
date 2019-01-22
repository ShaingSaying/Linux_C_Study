#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#define ML_CONF_FILE "/home/study/machine_learning_configure.ini"
#define ML_STATE "/home/study/machine_state.ini"
long char_convert_time(char *str_time)
{
	struct tm stm;
	strptime(str_time,"%Y-%m-%d %H:%M:%S",&stm);
	long t = mktime(&stm);
	return t;
}
int read_ML_configure()
{
	FILE *pFile = NULL;
	unsigned char szOneline[1024];
	char study_time[64] = {0};
	unsigned int iLineCount = 0;
	unsigned int switch_flag = 0;
	int mldays = 0;
	int i = 0;
	long ttime = 0;
	printf("into read_ML_configure function...\n");
	if(access(ML_CONF_FILE,F_OK)<0)
	{
		printf("file is not exist\n");
	}
	pFile = fopen(ML_CONF_FILE,"r+");
	if(NULL == pFile)
	{
		printf("fopen error\n");
	}	
	memset(szOneline,0x00,sizeof(szOneline));
	while(0x00 != fgets(szOneline,sizeof(szOneline),pFile))
	{
		if(szOneline[0] == '#')
		{
			printf("%c\n",szOneline[0]);
			continue;
		}
		else
		{
			iLineCount++;
			szOneline[strlen(szOneline)-1] = '\0';
			printf("[%u][%s]\n",iLineCount,szOneline);
			switch(iLineCount)
			{
				case 1:
					switch_flag = atoi(szOneline);
					printf("switch_flag=[%d]\n",switch_flag);
					break;
				case 2:
					mldays = atoi(szOneline);
					printf("mldays=[%d]\n",mldays);
					break;
				case 3:
					strncpy(study_time,szOneline,strlen(szOneline));
					printf("study_time=[%s]\n",study_time);
					ttime = char_convert_time(study_time);
					printf("ttime=[%ld]\n",ttime);
					break;
				default:
					break;
			}		
		}
		memset(szOneline, 0x00, sizeof(szOneline));
	}
	if(NULL != pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
	return 0;
}

int main()
{	
	FILE *pFile = NULL;
	unsigned char szOneline[1024];
	int old_time = 0;
	char record[32] = {0};

	read_ML_configure();
#if 0
	if(access(ML_STATE, F_OK)<0)
		printf("file is not exist\n");
	pFile = fopen(ML_STATE,"r+");
	if(NULL == pFile)
		printf("fopen failed\n");
	memset(szOneline,0x00,sizeof(szOneline));
	if(0x00 != fgets(szOneline, sizeof(szOneline), pFile))
	{
		old_time = atoi(szOneline);
		printf("old_time = %d\n",old_time);
	}
	pFile = fopen(ML_STATE,"w+");
	if(NULL == pFile)
		printf("fopen failed\n");
	sprintf(record,"%d",8);
	fwrite(record,strlen(record),1,pFile);

	if(NULL != pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
#endif
	return 0;
}
