// CQueryStation.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CQueryStation.h"

#include "map.h"
#include <string>

// CQueryStation

IMPLEMENT_DYNCREATE(CQueryStation, CFormView)

CQueryStation::CQueryStation()
	: CFormView(QueryStation)
{

}

CQueryStation::~CQueryStation()
{
}

void CQueryStation::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, n_stationname);
	DDX_Control(pDX, IDC_EDIT3, n_stationinfo);
}

BEGIN_MESSAGE_MAP(CQueryStation, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CQueryStation::OnBnClickedButton1)
END_MESSAGE_MAP()


// CQueryStation 诊断

#ifdef _DEBUG
void CQueryStation::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CQueryStation::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQueryStation 消息处理程序


void CQueryStation::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到变化的下拉项的序号
	int index = n_stationname.GetCurSel();
	CString str;
	n_stationname.GetLBText(index, str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* p = T2A(str);
	//MessageBox(CString(p));
	string s;
	m.Querystation(m.g_sMap, p, s);
	//MessageBox(CString(s.c_str()));
	n_stationinfo.SetWindowTextW(CString(s.c_str()));
}


void CQueryStation::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	Map m;
	m.InitData();
	for (int i = 0; i < m.g_sMap.station_num; ++i) {
		n_stationname.AddString(CString(m.g_sMap.stations[i].station));
	}

	n_stationname.SetCurSel(0);
}
