// CQueryroute.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CQueryroute.h"

#include "map.h"

// CQueryroute

IMPLEMENT_DYNCREATE(CQueryroute, CFormView)

CQueryroute::CQueryroute()
	: CFormView(IDD_QueryRoute)
{

}

CQueryroute::~CQueryroute()
{
}

void CQueryroute::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, n_start);
	DDX_Control(pDX, IDC_COMBO2, n_end);
	DDX_Control(pDX, IDC_EDIT3, n_Routeinfo);
}

BEGIN_MESSAGE_MAP(CQueryroute, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CQueryroute::OnBnClickedButton1)
END_MESSAGE_MAP()


// CQueryroute 诊断

#ifdef _DEBUG
void CQueryroute::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CQueryroute::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQueryroute 消息处理程序


void CQueryroute::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	Map m;
	m.InitData();
	for (int i = 0; i < m.g_sMap.station_num; ++i) {
		n_start.AddString(CString(m.g_sMap.stations[i].station));
		n_end.AddString(CString(m.g_sMap.stations[i].station));
	}

	n_start.SetCurSel(0);
	n_end.SetCurSel(0);

}


void CQueryroute::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到变化的下拉项的序号
	int start_index = n_start.GetCurSel();
	int end_index = n_end.GetCurSel();
	CString start_str;
	CString end_str;
	n_start.GetLBText(start_index, start_str);
	n_end.GetLBText(end_index, end_str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* pstart = T2A(start_str);
	char* pend = T2A(end_str);
	//MessageBox(CString(p));
	string s;
	m.QueryRoute(m.g_sMap, pstart, pend, s);
	n_Routeinfo.SetWindowTextW(CString(s.c_str()));
	//m.Querystation(m.g_sMap, p, s);
	//MessageBox(CString(s.c_str()));
	//n_stationinfo.SetWindowTextW(CString(s.c_str()));
}

