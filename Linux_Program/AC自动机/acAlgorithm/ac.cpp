//
#include "stdafx.h"

char *PatternSet[MAX_NUM_OF_PATTERN];	//模式集
int  STATE_NO;		//状态的编号

/* ****************************************************************
    函数：void init(struct AC_State *)
	目的：//AC状态机数据结构以及变量的初始化
	参数：
		state => AC自动机 模式串集结构
    返回：
	    无
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
	
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)	//必须显式初始化
		state->output[i] = -1;
	for(i=0; i<MAX_NUM_OF_GOTO; i++)
		state->Goto[i] = NULL;
	for(i=0; i<MAX_NUM_OF_PATTERN; i++)
		PatternSet[i] = NULL;
	
	return;
}

/* ****************************************************************
    函数：int	addPattern(struct AC_State *, const char*, int)
	目的：//将一个模式加入并构建转向函数
	参数：
		root => AC状态机模式串集结构的初始状态节点
		pattern => 新增模式子串
		length => 模式串长度
    返回：
	    int - 新增失败false，成功true
 ****************************************************************/
int	addPattern(struct AC_State *root, const char* pattern, int length)
{
	unsigned char ch;
	int on;
	int i,j;
	struct AC_State *temp = root, *new_state;
	if(strlen(pattern) < length)		//防止字串过长出现溢出错误
		return false;

	for(i=0; i<MAX_NUM_OF_PATTERN; i++)
		if(PatternSet[i]==NULL)			//添加到模式集的一个空位置中
		{
			PatternSet[i] = (char*)malloc(length+1);	//多分配一位，存放结束标志"\0"
			memcpy(PatternSet[i], pattern, length);
			PatternSet[i][length]='\0';
			on = i;
			break;
		}

	for(i=0; i<length; i++)		//将该模式添加到状态树中
	{
		ch = pattern[i];
		
		if(temp->Goto[ch]==NULL)	//如果遇到从未出现的状态(即是新字符)，新创建
		{
			string str_temp = string(temp->str.c_str());	//取从树根到该状态节点的字符序列
			new_state = new struct AC_State;
			new_state->str = str_temp.append(1, ch);		//得出该状态对应字符串
			new_state->depth = temp->depth+1;			//状态节点深度+1
			new_state->failure = 0;
			new_state->num_of_goto = 0;
			new_state->state_no = STATE_NO+1;	//记录编号
			new_state->is_final_state = 0;	//不是楼阁终态

			for(j=0; j<MAX_NUM_OF_PATTERN; j++)
				new_state->output[j]=-1;	//?? 所有状态节点的输出均初始化为-1 ？
			memset(new_state->Goto, NULL, MAX_NUM_OF_GOTO);	//??
			temp->num_of_goto++;	//因为创建了新的状态所以转向个数得加一
			temp->Goto[ch] = new_state; //设置转向
			temp = new_state;
			if(i==length-1)	//该模式串结尾，即可得到一个输出也就是终态
			{
				new_state->is_final_state = 1;	//终态
				new_state->output[0] = on;
			}
			for(j=0; j<MAX_NUM_OF_GOTO; j++)
				temp->Goto[j] = NULL;
		}
		else
		{		//已经出现过的字符
			temp = temp->Goto[ch];	//指向它的转向状态节点
			if(i==length-1)	//如果完全匹配了
				for(int j=0; j<MAX_NUM_OF_PATTERN; j++)	//对所有的状态的输出扫描
					if(temp->output[j]==-1)
					{
						temp->is_final_state = 1;	//确定为终态
						temp->output[j] = on;	//设为输出节点
						break;
					}
		}
	}
	return true;
}

/* ****************************************************************
    函数：void getFailFunc(struct AC_State *)
	目的：
		//得到失效指针，并且根据此得出所有的输出节点，也就是终态
		//在这里用到的原理：ch是该状态的前驱转向该状态遇到的字符
		//该状态节点的失效指针为,由前驱的失效指针指向的节点,在遇到ch时的转向状态节点，
		//如果转向失败则为树根
	参数：
		root => AC状态机模式串集结构的初始状态节点
    返回：
	    无
 ****************************************************************/
void getFailFunc(struct AC_State *root)
{
	queue<struct AC_State *> 	q;	//使用队列进行广度优先遍历
	struct AC_State *temp;

	q.push(root);
	root->failure = root;
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		if(temp->num_of_goto == 0)	//到达了末尾则什么都不做
			continue;
		else
			for(int i=0; i<MAX_NUM_OF_GOTO; i++)
				if(temp->Goto[i] != NULL)
				{
					q.push(temp->Goto[i]);
					if(temp->Goto[i]->depth == 1)//根据temp计算出temp的后继的失效指针
						temp->Goto[i]->failure = root;	
					else
						if(temp->failure->Goto[i] == NULL)
							temp->Goto[i]->failure = root;
						else
						{
							temp->Goto[i]->failure = temp->failure->Goto[i]; 
							if(temp->Goto[i]->is_final_state==1 && temp->failure->Goto[i]->is_final_state==1)	//完成状态节点完整输出
								finalAssign(temp->Goto[i]->output, temp->failure->Goto[i]->output);	
						}
				}
	}
	return;
}

/* ****************************************************************
    函数：int acSearch(struct AC_State *, ifstream *, ofstream *)
	目的：//根据所建立的状态树执行搜索
	参数：
		root => AC状态机模式串集结构的初始状态节点
		_if => 读入包含匹配文本的文件
		out => 输出成功匹配的模式信息到文件
    返回：
	    int - 搜索失败false，成功true
 ****************************************************************/
int acSearch(struct AC_State *root, ifstream *_if, ofstream *out)
{
	char buf[BUFSIZE]={'\0'};			//读文件缓冲区
	unsigned char ch;
	struct AC_State *temp=root;
	int    row=1, column=1;				//行列计数器
	int    size;

	while(_if->read(buf, BUFSIZE))	//循环每次读入BUFSIZE大小的字串处理
	{
		for(int i=0; i<BUFSIZE; i++)	//对读入的字符进行处理
		{
			ch = buf[i];
			column++;	//读入一个字符，列+1
			if(ch == '\n')	//遇到回车，行+1，列重置1
			{
				row++;
				column=1;
			}
			if(temp->Goto[ch]==NULL)		//如果转向失败，则转到失效指针
				temp = temp->failure;
			else							//否则转向成功
				temp = temp->Goto[ch];
			if(temp->is_final_state)		//如果遇到终态,那么则可以产生输出
			{
				for(int j=0; j<MAX_NUM_OF_PATTERN; j++)
				{
					if(temp->output[j]==-1)	//发现模式并将其输出
						break;
					//此处的列位置，指的是在该列前发现模式
					//cout<<"\n行:"<<row<<"  列:"<<column<<"\n发现: "<<PatternSet[temp->output[j]]<<endl;
					(*out)<<"\n行:"<<row<<"  列:"<<column<<"\n发现: "<<PatternSet[temp->output[j]]<<endl;	//输出到文件
				}
				if(temp->Goto[ch]==NULL)		//若转向，然后将此状态转向到失效指针
					temp = temp->failure;
		}
		}
		memset(buf, 0, BUFSIZE);	//	重置缓冲区
	}

	//处理文件末尾长度小于BUFSIZE的部分内容.与上面的while循环类代码一致
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
				cout<<"\n行:"<<row<<"  列:"<<column<<"\n发现: "<<PatternSet[temp->output[j]]<<endl;
				(*out)<<"\n行:"<<row<<"  列:"<<column<<"\n发现: "<<PatternSet[temp->output[j]]<<endl;
			}
			if(temp->Goto[ch]==NULL)
				temp = temp->failure;
		}
	}
	memset(buf, 0, BUFSIZE);
	return true;
}

/* ****************************************************************
    函数：void finalAssign(int *, int *)
	目的：//将s数组中的有效元素复制到t的空闲处
	参数：
		t => 读入包含匹配文本的文件
		s => 数组
    返回：
	    无
 ****************************************************************/
void finalAssign(int *t, int *s)
{
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)
	{
		if(*(s+i)!=-1)	//元素有效，则进行复制操作
			for(int j=0; j<MAX_NUM_OF_PATTERN; j++)
				if(*(t+j)==-1)	//复制到空闲位置
				{
					*(t+j) = *(s+i);
					break;
				}
	}
}

/* ****************************************************************
    函数：void acFree(struct AC_State *)
	目的：//释放所有用到的内存资源
	参数：
		root => AC状态机
    返回：
	    无
 ****************************************************************/
void acFree(struct AC_State *root)
{
	queue<struct AC_State *> 	q;	//使用队列
	struct AC_State *temp;

	q.push(root);
	/////////////////////////////////////
	//使用队列循环释放状态树
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
	
	for(int i=0; i<MAX_NUM_OF_PATTERN; i++)//释放模式集
		free(PatternSet[i]);
}

/* ****************************************************************
    函数：void    printInfo(struct AC_State *root)
	目的：输出
	参数：
		root => AC状态机模式串集结构的初始状态节点
    返回：
	    无
 ****************************************************************/
void    printInfo(struct AC_State *root)
{
	
}
