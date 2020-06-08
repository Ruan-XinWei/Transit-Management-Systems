#include "stdafx.h"
#include "Login.h"
#include "pch.h"

CLogin::CLogin()
{
}


CLogin::~CLogin()
{
}

//读取登录信息
void CLogin::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs;	//创建文件输入对象
	ifs.open(_F_LOGIN);

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));	//读取一行内容
	name = CString(buf);	//将char* 转换为CString

	ifs.getline(buf, sizeof(buf));	//读取一行内容
	pwd = CString(buf);	//将char* 转换为CString

	ifs.close();	//关闭文件
}
