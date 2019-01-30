// acAlgorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	char	out[MAX_LENGTH_FILE_NAME] = {'\0'};
	char	ptn[MAX_LENGTH_FILE_NAME] = {'\0'};
	char	mch[MAX_LENGTH_FILE_NAME] = {'\0'};

	ifstream fptn,fmch;
	ofstream fout;
	struct AC_State root;
	char   a_model[MAX_LENGTH_PATTERN]={'\0'};
	char   isContinue;
/*/
	//参数分析
	switch(argc)		
	{
	case 2:
		memcpy(mch, argv[1],strlen(argv[1]));
		memcpy(ptn, "pattern",strlen("pattern"));
		memcpy(out, "output",strlen("output"));
		break;
	case 3:
		memcpy(mch, argv[1],strlen(argv[1]));
		memcpy(ptn, argv[2],strlen(argv[2]));
		memcpy(out, "output",strlen("output"));
		break;
	case 4:
		memcpy(mch, argv[1],strlen(argv[1]));
		memcpy(ptn, argv[2],strlen(argv[2]));
		memcpy(out, argv[3],strlen(argv[3]));
		break;
	default:
		cout<<"Usage:acAlgorithm.exe [匹配文本 [模式集 [输出文件]]]"<<endl;
		exit(0);
	}
//*/
	//*
	memcpy(mch, "test",strlen("test"));
	memcpy(ptn, "pattern",strlen("pattern"));
	memcpy(out, "output",strlen("output"));
	//*/

	cout<<"待匹配文本文件:"<<mch<<"\n模式集文件:"<<ptn<<"\n匹配结果输出文件:"<<out<<endl;

	//初始化状态树
	init(&root);
	fptn.open(ptn);	//打开模式集文件
	if(fptn.fail())
	{
		cout<<"不能打开文件:"<<ptn<<endl;
		exit(0);
	}
	
	//将模式串一个个加入到状态树中，并得出部分输出节点
	while(fptn.getline(a_model, MAX_LENGTH_PATTERN))
	{
		if(strlen(a_model)>MAX_LENGTH_PATTERN)	//模式串过长则报错退出
		{
			cout<<"某个模式长度超过最大长度\n"<<endl;
			exit(0);
		}
		addPattern(&root, a_model, strlen(a_model));	//添加模式串到状态树root中
		memset(a_model, 0, MAX_LENGTH_PATTERN);	//重置
	}
	fptn.close();

	//得到每个状态节点的失效函数，并得到全部的输出节点
	getFailFunc(&root);

L:
	fmch.clear();	//先清空缓冲区
	fmch.open(mch);	//打开待匹配文本
	if(fmch.fail())
	{
		cout<<"不能打开文件:"<<mch<<endl;
		exit(0);
	}
	fout.clear();
	fout.open(out);	//打开保存输出匹配结果信息的文件
	if(fout.fail())
	{
		cout<<"不能打开文件:"<<out<<endl;
		exit(0);
	}

	//执行搜索
	acSearch(&root, &fmch, &fout);

	fmch.close();
	fout.close();

	cout<<"匹配结果已经存入文件，是否继续使用此模式集匹配？ 是(y or Y),否(其他)"<<endl;
	cin>>isContinue;
	if(isContinue == 'y' || isContinue == 'Y')
	{
		cout<<"输入【待匹配文件名】以及【结果输出文件名】，并用空格隔开"<<endl;
		memset(mch, 0, MAX_LENGTH_FILE_NAME);	//重置mch和out
		memset(out, 0, MAX_LENGTH_FILE_NAME);
		cin>>mch>>out;

		goto L;
	}
	cout<<"程序结束，释放内存清理中。。。"<<endl;
	acFree(&root);
	getchar();
	return 0;
}