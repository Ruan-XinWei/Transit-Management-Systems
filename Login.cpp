#include "stdafx.h"
#include "Login.h"
#include "pch.h"

CLogin::CLogin()
{
}


CLogin::~CLogin()
{
}

//��ȡ��¼��Ϣ
void CLogin::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs;	//�����ļ��������
	ifs.open(_F_LOGIN);

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));	//��ȡһ������
	name = CString(buf);	//��char* ת��ΪCString

	ifs.getline(buf, sizeof(buf));	//��ȡһ������
	pwd = CString(buf);	//��char* ת��ΪCString

	ifs.close();	//�ر��ļ�
}
