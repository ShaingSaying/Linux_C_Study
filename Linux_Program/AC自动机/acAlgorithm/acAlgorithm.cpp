// acAlgorithm.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��������
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
		cout<<"Usage:acAlgorithm.exe [ƥ���ı� [ģʽ�� [����ļ�]]]"<<endl;
		exit(0);
	}
//*/
	//*
	memcpy(mch, "test",strlen("test"));
	memcpy(ptn, "pattern",strlen("pattern"));
	memcpy(out, "output",strlen("output"));
	//*/

	cout<<"��ƥ���ı��ļ�:"<<mch<<"\nģʽ���ļ�:"<<ptn<<"\nƥ��������ļ�:"<<out<<endl;

	//��ʼ��״̬��
	init(&root);
	fptn.open(ptn);	//��ģʽ���ļ�
	if(fptn.fail())
	{
		cout<<"���ܴ��ļ�:"<<ptn<<endl;
		exit(0);
	}
	
	//��ģʽ��һ�������뵽״̬���У����ó���������ڵ�
	while(fptn.getline(a_model, MAX_LENGTH_PATTERN))
	{
		if(strlen(a_model)>MAX_LENGTH_PATTERN)	//ģʽ�������򱨴��˳�
		{
			cout<<"ĳ��ģʽ���ȳ�����󳤶�\n"<<endl;
			exit(0);
		}
		addPattern(&root, a_model, strlen(a_model));	//���ģʽ����״̬��root��
		memset(a_model, 0, MAX_LENGTH_PATTERN);	//����
	}
	fptn.close();

	//�õ�ÿ��״̬�ڵ��ʧЧ���������õ�ȫ��������ڵ�
	getFailFunc(&root);

L:
	fmch.clear();	//����ջ�����
	fmch.open(mch);	//�򿪴�ƥ���ı�
	if(fmch.fail())
	{
		cout<<"���ܴ��ļ�:"<<mch<<endl;
		exit(0);
	}
	fout.clear();
	fout.open(out);	//�򿪱������ƥ������Ϣ���ļ�
	if(fout.fail())
	{
		cout<<"���ܴ��ļ�:"<<out<<endl;
		exit(0);
	}

	//ִ������
	acSearch(&root, &fmch, &fout);

	fmch.close();
	fout.close();

	cout<<"ƥ�����Ѿ������ļ����Ƿ����ʹ�ô�ģʽ��ƥ�䣿 ��(y or Y),��(����)"<<endl;
	cin>>isContinue;
	if(isContinue == 'y' || isContinue == 'Y')
	{
		cout<<"���롾��ƥ���ļ������Լ����������ļ����������ÿո����"<<endl;
		memset(mch, 0, MAX_LENGTH_FILE_NAME);	//����mch��out
		memset(out, 0, MAX_LENGTH_FILE_NAME);
		cin>>mch>>out;

		goto L;
	}
	cout<<"����������ͷ��ڴ������С�����"<<endl;
	acFree(&root);
	getchar();
	return 0;
}