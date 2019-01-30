//
#include "stdafx.h"

char *PatternSet[MAX_NUM_OF_PATTERN];	//ģʽ��
int  STATE_NO;		//״̬�ı��

/* ****************************************************************
    ������void init(struct AC_State *)
	Ŀ�ģ�//AC״̬�����ݽṹ�Լ������ĳ�ʼ��
	������
		state => AC�Զ��� ģʽ�����ṹ
    ���أ�
	    ��
 ****************************************************************/
void init(struct AC_State *state)
{
	STATE_NO = 0;
	state->state_no		= 0;
	state->depth		= 0;
	state->failure		= 0;
	state->num_of_goto	= 0;
	state->is_final_state= 0;
	state->str.append("\0");
	
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)	//������ʽ��ʼ��
		state->output[i] = -1;
	for(i=0; i<MAX_NUM_OF_GOTO; i++)
		state->Goto[i] = NULL;
	for(i=0; i<MAX_NUM_OF_PATTERN; i++)
		PatternSet[i] = NULL;
	
	return;
}

/* ****************************************************************
    ������int	addPattern(struct AC_State *, const char*, int)
	Ŀ�ģ�//��һ��ģʽ���벢����ת����
	������
		root => AC״̬��ģʽ�����ṹ�ĳ�ʼ״̬�ڵ�
		pattern => ����ģʽ�Ӵ�
		length => ģʽ������
    ���أ�
	    int - ����ʧ��false���ɹ�true
 ****************************************************************/
int	addPattern(struct AC_State *root, const char* pattern, int length)
{
	unsigned char ch;
	int on;
	int i,j;
	struct AC_State *temp = root, *new_state;
	if(strlen(pattern) < length)		//��ֹ�ִ����������������
		return false;

	for(i=0; i<MAX_NUM_OF_PATTERN; i++)
		if(PatternSet[i]==NULL)			//��ӵ�ģʽ����һ����λ����
		{
			PatternSet[i] = (char*)malloc(length+1);	//�����һλ����Ž�����־"\0"
			memcpy(PatternSet[i], pattern, length);
			PatternSet[i][length]='\0';
			on = i;
			break;
		}

	for(i=0; i<length; i++)		//����ģʽ��ӵ�״̬����
	{
		ch = pattern[i];
		
		if(temp->Goto[ch]==NULL)	//���������δ���ֵ�״̬(�������ַ�)���´���
		{
			string str_temp = string(temp->str.c_str());	//ȡ����������״̬�ڵ���ַ�����
			new_state = new struct AC_State;
			new_state->str = str_temp.append(1, ch);		//�ó���״̬��Ӧ�ַ���
			new_state->depth = temp->depth+1;			//״̬�ڵ����+1
			new_state->failure = 0;
			new_state->num_of_goto = 0;
			new_state->state_no = STATE_NO+1;	//��¼���
			new_state->is_final_state = 0;	//����¥����̬

			for(j=0; j<MAX_NUM_OF_PATTERN; j++)
				new_state->output[j]=-1;	//?? ����״̬�ڵ���������ʼ��Ϊ-1 ��
			memset(new_state->Goto, NULL, MAX_NUM_OF_GOTO);	//??
			temp->num_of_goto++;	//��Ϊ�������µ�״̬����ת������ü�һ
			temp->Goto[ch] = new_state; //����ת��
			temp = new_state;
			if(i==length-1)	//��ģʽ����β�����ɵõ�һ�����Ҳ������̬
			{
				new_state->is_final_state = 1;	//��̬
				new_state->output[0] = on;
			}
			for(j=0; j<MAX_NUM_OF_GOTO; j++)
				temp->Goto[j] = NULL;
		}
		else
		{		//�Ѿ����ֹ����ַ�
			temp = temp->Goto[ch];	//ָ������ת��״̬�ڵ�
			if(i==length-1)	//�����ȫƥ����
				for(int j=0; j<MAX_NUM_OF_PATTERN; j++)	//�����е�״̬�����ɨ��
					if(temp->output[j]==-1)
					{
						temp->is_final_state = 1;	//ȷ��Ϊ��̬
						temp->output[j] = on;	//��Ϊ����ڵ�
						break;
					}
		}
	}
	return true;
}

/* ****************************************************************
    ������void getFailFunc(struct AC_State *)
	Ŀ�ģ�
		//�õ�ʧЧָ�룬���Ҹ��ݴ˵ó����е�����ڵ㣬Ҳ������̬
		//�������õ���ԭ��ch�Ǹ�״̬��ǰ��ת���״̬�������ַ�
		//��״̬�ڵ��ʧЧָ��Ϊ,��ǰ����ʧЧָ��ָ��Ľڵ�,������chʱ��ת��״̬�ڵ㣬
		//���ת��ʧ����Ϊ����
	������
		root => AC״̬��ģʽ�����ṹ�ĳ�ʼ״̬�ڵ�
    ���أ�
	    ��
 ****************************************************************/
void getFailFunc(struct AC_State *root)
{
	queue<struct AC_State *> 	q;	//ʹ�ö��н��й�����ȱ���
	struct AC_State *temp;

	q.push(root);
	root->failure = root;
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		if(temp->num_of_goto == 0)	//������ĩβ��ʲô������
			continue;
		else
			for(int i=0; i<MAX_NUM_OF_GOTO; i++)
				if(temp->Goto[i] != NULL)
				{
					q.push(temp->Goto[i]);
					if(temp->Goto[i]->depth == 1)//����temp�����temp�ĺ�̵�ʧЧָ��
						temp->Goto[i]->failure = root;	
					else
						if(temp->failure->Goto[i] == NULL)
							temp->Goto[i]->failure = root;
						else
						{
							temp->Goto[i]->failure = temp->failure->Goto[i]; 
							if(temp->Goto[i]->is_final_state==1 && temp->failure->Goto[i]->is_final_state==1)	//���״̬�ڵ��������
								finalAssign(temp->Goto[i]->output, temp->failure->Goto[i]->output);	
						}
				}
	}
	return;
}

/* ****************************************************************
    ������int acSearch(struct AC_State *, ifstream *, ofstream *)
	Ŀ�ģ�//������������״̬��ִ������
	������
		root => AC״̬��ģʽ�����ṹ�ĳ�ʼ״̬�ڵ�
		_if => �������ƥ���ı����ļ�
		out => ����ɹ�ƥ���ģʽ��Ϣ���ļ�
    ���أ�
	    int - ����ʧ��false���ɹ�true
 ****************************************************************/
int acSearch(struct AC_State *root, ifstream *_if, ofstream *out)
{
	char buf[BUFSIZE]={'\0'};			//���ļ�������
	unsigned char ch;
	struct AC_State *temp=root;
	int    row=1, column=1;				//���м�����
	int    size;

	while(_if->read(buf, BUFSIZE))	//ѭ��ÿ�ζ���BUFSIZE��С���ִ�����
	{
		for(int i=0; i<BUFSIZE; i++)	//�Զ�����ַ����д���
		{
			ch = buf[i];
			column++;	//����һ���ַ�����+1
			if(ch == '\n')	//�����س�����+1��������1
			{
				row++;
				column=1;
			}
			if(temp->Goto[ch]==NULL)		//���ת��ʧ�ܣ���ת��ʧЧָ��
				temp = temp->failure;
			else							//����ת��ɹ�
				temp = temp->Goto[ch];
			if(temp->is_final_state)		//���������̬,��ô����Բ������
			{
				for(int j=0; j<MAX_NUM_OF_PATTERN; j++)
				{
					if(temp->output[j]==-1)	//����ģʽ���������
						break;
					//�˴�����λ�ã�ָ�����ڸ���ǰ����ģʽ
					//cout<<"\n��:"<<row<<"  ��:"<<column<<"\n����: "<<PatternSet[temp->output[j]]<<endl;
					(*out)<<"\n��:"<<row<<"  ��:"<<column<<"\n����: "<<PatternSet[temp->output[j]]<<endl;	//������ļ�
				}
				if(temp->Goto[ch]==NULL)		//��ת��Ȼ�󽫴�״̬ת��ʧЧָ��
					temp = temp->failure;
		}
		}
		memset(buf, 0, BUFSIZE);	//	���û�����
	}

	//�����ļ�ĩβ����С��BUFSIZE�Ĳ�������.�������whileѭ�������һ��
	size = _if->gcount();
	for(int i=0; i<size; i++)
	{
		ch = buf[i];
		column++;
		if(ch == '\n')
		{
			row++;
			column=0;
		}
		if(temp->Goto[ch]==NULL)
			temp = temp->failure;
		else
			temp = temp->Goto[ch];
		if(temp->is_final_state)
		{
			for(int j=0; j<MAX_NUM_OF_PATTERN; j++)
			{
				if(temp->output[j]==-1)
					break;
				cout<<"\n��:"<<row<<"  ��:"<<column<<"\n����: "<<PatternSet[temp->output[j]]<<endl;
				(*out)<<"\n��:"<<row<<"  ��:"<<column<<"\n����: "<<PatternSet[temp->output[j]]<<endl;
			}
			if(temp->Goto[ch]==NULL)
				temp = temp->failure;
		}
	}
	memset(buf, 0, BUFSIZE);
	return true;
}

/* ****************************************************************
    ������void finalAssign(int *, int *)
	Ŀ�ģ�//��s�����е���ЧԪ�ظ��Ƶ�t�Ŀ��д�
	������
		t => �������ƥ���ı����ļ�
		s => ����
    ���أ�
	    ��
 ****************************************************************/
void finalAssign(int *t, int *s)
{
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)
	{
		if(*(s+i)!=-1)	//Ԫ����Ч������и��Ʋ���
			for(int j=0; j<MAX_NUM_OF_PATTERN; j++)
				if(*(t+j)==-1)	//���Ƶ�����λ��
				{
					*(t+j) = *(s+i);
					break;
				}
	}
}

/* ****************************************************************
    ������void acFree(struct AC_State *)
	Ŀ�ģ�//�ͷ������õ����ڴ���Դ
	������
		root => AC״̬��
    ���أ�
	    ��
 ****************************************************************/
void acFree(struct AC_State *root)
{
	queue<struct AC_State *> 	q;	//ʹ�ö���
	struct AC_State *temp;

	q.push(root);
	/////////////////////////////////////
	//ʹ�ö���ѭ���ͷ�״̬��
	while(q.empty())
	{
		temp = q.front();
		q.pop();

		if(temp->num_of_goto==0)
		{
			delete temp;
			continue;
		}
		for(int i=0; i<MAX_NUM_OF_GOTO; i++)
			if(temp->Goto[i]!=NULL)
				q.push(temp->Goto[i]);
		if(temp->state_no!=0)
			delete temp;
	}
	
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)//�ͷ�ģʽ��
		free(PatternSet[i]);
}

/* ****************************************************************
    ������void    printInfo(struct AC_State *root)
	Ŀ�ģ����
	������
		root => AC״̬��ģʽ�����ṹ�ĳ�ʼ״̬�ڵ�
    ���أ�
	    ��
 ****************************************************************/
void    printInfo(struct AC_State *root)
{
	
}
