#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"

using namespace std;

class CLogin
{
public:
	CLogin();
	~CLogin();

	//��ȡ��¼��Ϣ
	void ReadLogin(CString& name, CString& pwd);
};