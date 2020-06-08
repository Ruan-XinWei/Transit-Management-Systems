// CBusinfo.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CBusinfo.h"
#include <iostream>
#include <string>
#include <fstream>
#include "map.h"
#include "model.h"

using namespace std;

// CBusinfo

IMPLEMENT_DYNCREATE(CBusinfo, CFormView)

CBusinfo::CBusinfo()
	: CFormView(Bus_information)
{

}

CBusinfo::~CBusinfo()
{
}

void CBusinfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, n_businfo);
	DDX_Control(pDX, IDC_COMBO1, n_busname);
}

BEGIN_MESSAGE_MAP(CBusinfo, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CBusinfo::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT1, &CBusinfo::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CBusinfo 诊断

#ifdef _DEBUG
void CBusinfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBusinfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBusinfo 消息处理程序


void CBusinfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到变化的下拉项的序号
	int index = n_busname.GetCurSel();
	CString str;
	n_busname.GetLBText(index, str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* p = T2A(str);
	//MessageBox(CString(p));
	string s;
	m.QueryBus(m.g_sMap, p, s);
	//MessageBox(CString(s.c_str()));
	n_businfo.SetWindowTextW(CString(s.c_str()));
}



void CBusinfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	Map m;
	m.InitData();
	for (int i = 0; i < m.g_sMap.bus_num; ++i) {
		n_busname.AddString(CString(m.g_sMap.buses[i].name));
	}

	n_busname.SetCurSel(0);
}
