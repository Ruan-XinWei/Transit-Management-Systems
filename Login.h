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

	//¶ÁÈ¡µÇÂ¼ÐÅÏ¢
	void ReadLogin(CString& name, CString& pwd);
};