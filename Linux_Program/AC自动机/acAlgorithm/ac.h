#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define BUFSIZE						4096		//读文件缓冲区大小
#define MAX_NUM_OF_PATTERN			32			//模式的最大数量
#define MAX_NUM_OF_GOTO				256			//转向指针数量的最大值
#define MAX_LENGTH_FILE_NAME        128			//文件名最大长度
#define MAX_LENGTH_PATTERN			128			//模式的最大长度

//定义状态节点的结构
typedef struct AC_State
{
	int state_no;				//状态的编号，没有实际的用处，可以用来模拟老师课件上的输出
	int	depth;					//深度
	int is_final_state;			//判断该节点是否为楼阁终态
	int output[MAX_NUM_OF_PATTERN];			//输出函数值，对应模式，可能有多个
	int num_of_goto;						//有多少个节点
	string str;								//存储从树根到该节点的字符序列，便于调试
	struct AC_State *Goto[MAX_NUM_OF_GOTO]; //转向指针
	struct AC_State *failure;				//失效指针
} AC_State;

void	init(struct AC_State *state);		//初始化
int		addPattern(struct AC_State *root, const char* pattern, int length);	//将一个模式加入并构建转向函数
void    getFailFunc(struct AC_State *root);		//求失效指针
int     acSearch(struct AC_State *root, ifstream *_if, ofstream *out);		//执行匹配
void	finalAssign(int *t, int *s);			
void    acFree(struct AC_State *root);		//释放空间

void    printInfo(struct AC_State *root);