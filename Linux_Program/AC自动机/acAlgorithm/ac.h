#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define BUFSIZE						4096		//���ļ���������С
#define MAX_NUM_OF_PATTERN			32			//ģʽ���������
#define MAX_NUM_OF_GOTO				256			//ת��ָ�����������ֵ
#define MAX_LENGTH_FILE_NAME        128			//�ļ�����󳤶�
#define MAX_LENGTH_PATTERN			128			//ģʽ����󳤶�

//����״̬�ڵ�Ľṹ
typedef struct AC_State
{
	int state_no;				//״̬�ı�ţ�û��ʵ�ʵ��ô�����������ģ����ʦ�μ��ϵ����
	int	depth;					//���
	int is_final_state;			//�жϸýڵ��Ƿ�Ϊ¥����̬
	int output[MAX_NUM_OF_PATTERN];			//�������ֵ����Ӧģʽ�������ж��
	int num_of_goto;						//�ж��ٸ��ڵ�
	string str;								//�洢���������ýڵ���ַ����У����ڵ���
	struct AC_State *Goto[MAX_NUM_OF_GOTO]; //ת��ָ��
	struct AC_State *failure;				//ʧЧָ��
} AC_State;

void	init(struct AC_State *state);		//��ʼ��
int		addPattern(struct AC_State *root, const char* pattern, int length);	//��һ��ģʽ���벢����ת����
void    getFailFunc(struct AC_State *root);		//��ʧЧָ��
int     acSearch(struct AC_State *root, ifstream *_if, ofstream *out);		//ִ��ƥ��
void	finalAssign(int *t, int *s);			
void    acFree(struct AC_State *root);		//�ͷſռ�

void    printInfo(struct AC_State *root);