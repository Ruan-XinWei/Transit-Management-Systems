// CUpdate.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CUpdate.h"

#include "map.h"

// CUpdate

IMPLEMENT_DYNCREATE(CUpdate, CFormView)

CUpdate::CUpdate()
	: CFormView(IDD_Update)
	, n_a_station(_T(""))
	, n_a_bus_1(_T(""))
	, n_a_bus_2(_T(""))
	, n_a_bus_3(_T(""))
	, n_a_route_1(0)
	, n_a_route_2(0)
	, n_a_route_3(0)
	, n_a_route_4(0)
	, n_d_route_1(0)
	, n_d_route_2(0)
	, n_d_route_3(0)
	, n_d_route_4(0)
	, n_u_station_new(_T(""))
	, n_u_bus_old_1(_T(""))
	, n_u_bus_old_2(_T(""))
	, n_u_bus_old_3(_T(""))
	, n_u_bus_new_1(_T(""))
	, n_u_bus_new_2(_T(""))
	, n_u_bus_new_3(_T(""))
	, n_u_route_old_1(0)
	, n_u_route_old_2(0)
	, n_u_route_old_3(0)
	, n_u_route_old_4(0)
	, n_u_route_new_1(0)
	, n_u_route_new_2(0)
	, n_u_route_new_3(0)
	, n_u_route_new_4(0)
{

}

CUpdate::~CUpdate()
{
}

void CUpdate::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, n_d_station);
	DDX_Control(pDX, IDC_COMBO2, n_d_bus);
	DDX_Control(pDX, IDC_COMBO3, n_u_station_old);
	//  DDX_Control(pDX, IDC_EDIT14, n_a_station);
	DDX_Text(pDX, IDC_EDIT14, n_a_station);
	DDX_Text(pDX, IDC_EDIT11, n_a_bus_1);
	DDX_Text(pDX, IDC_EDIT12, n_a_bus_2);
	DDX_Text(pDX, IDC_EDIT13, n_a_bus_3);
	//  DDX_Text(pDX, IDC_EDIT7, n_a_route_1);
	//  DDX_Text(pDX, IDC_EDIT8, n_a_route_2);
	//  DDX_Text(pDX, IDC_EDIT9, n_a_route_3);
	//  DDX_Text(pDX, IDC_EDIT10, n_a_route_4);
	DDX_Text(pDX, IDC_EDIT7, n_a_route_1);
	DDX_Text(pDX, IDC_EDIT8, n_a_route_2);
	DDX_Text(pDX, IDC_EDIT9, n_a_route_3);
	DDX_Text(pDX, IDC_EDIT10, n_a_route_4);
	DDX_Text(pDX, IDC_EDIT2, n_d_route_1);
	DDX_Text(pDX, IDC_EDIT4, n_d_route_2);
	DDX_Text(pDX, IDC_EDIT5, n_d_route_3);
	DDX_Text(pDX, IDC_EDIT6, n_d_route_4);
	DDX_Text(pDX, IDC_EDIT22, n_u_station_new);
	DDX_Text(pDX, IDC_EDIT23, n_u_bus_old_1);
	DDX_Text(pDX, IDC_EDIT24, n_u_bus_old_2);
	DDX_Text(pDX, IDC_EDIT25, n_u_bus_old_3);
	DDX_Text(pDX, IDC_EDIT19, n_u_bus_new_1);
	DDX_Text(pDX, IDC_EDIT20, n_u_bus_new_2);
	DDX_Text(pDX, IDC_EDIT21, n_u_bus_new_3);
	DDX_Text(pDX, IDC_EDIT15, n_u_route_old_1);
	DDX_Text(pDX, IDC_EDIT16, n_u_route_old_2);
	DDX_Text(pDX, IDC_EDIT17, n_u_route_old_3);
	DDX_Text(pDX, IDC_EDIT18, n_u_route_old_4);
	DDX_Text(pDX, IDC_EDIT26, n_u_route_new_1);
	DDX_Text(pDX, IDC_EDIT27, n_u_route_new_2);
	DDX_Text(pDX, IDC_EDIT28, n_u_route_new_3);
	DDX_Text(pDX, IDC_EDIT29, n_u_route_new_4);
}

BEGIN_MESSAGE_MAP(CUpdate, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &CUpdate::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CUpdate::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CUpdate::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CUpdate::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CUpdate::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &CUpdate::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CUpdate::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CUpdate::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUpdate::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CUpdate 诊断

#ifdef _DEBUG
void CUpdate::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUpdate::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUpdate 消息处理程序



void CUpdate::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	Map m;
	m.InitData();
	for (int i = 0; i < m.g_sMap.station_num; ++i) {
		n_d_station.AddString(CString(m.g_sMap.stations[i].station));
		n_u_station_old.AddString(CString(m.g_sMap.stations[i].station));
	}

	for (int i = 0; i < m.g_sMap.bus_num; ++i) {
		n_d_bus.AddString(CString(m.g_sMap.buses[i].name));
	}

	n_d_station.SetCurSel(0);
	n_u_station_old.SetCurSel(0);
	n_d_bus.SetCurSel(0);
}

void CUpdate::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加站点

	UpdateData(TRUE);
	UpdateData(FALSE);
	USES_CONVERSION;
	char* p = T2A(n_a_station);

	Map m;
	int n = m.AddStation(m.STATIONFILE, p);
	if (n == 0) {
		MessageBox(TEXT("添加成功！"));
	}
	else {
		MessageBox(TEXT("添加失败！"));
	}

	OnCbnSelchangeCombo1();
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_a_station = TEXT("");
	CUpdate::OnInitialUpdate();
	//UpdateData(TRUE);
	//UpdateData(FALSE);
}


void CUpdate::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加公交信息
	UpdateData(TRUE);
	UpdateData(FALSE);
	USES_CONVERSION;
	char* p1 = T2A(n_a_bus_1);
	char* p2 = T2A(n_a_bus_2);
	char* p3 = T2A(n_a_bus_3);
	Map m;
	int n = m.AddBuses(m.BUSESFILE, p1, p2, p3);
	if (n == 0) {
		MessageBox(TEXT("添加成功！"));
	}
	else {
		MessageBox(TEXT("添加失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_a_bus_1 = TEXT("");
	n_a_bus_2 = TEXT("");
	n_a_bus_3 = TEXT("");
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加路径信息
	UpdateData(TRUE);
	UpdateData(FALSE);
	Map m;
	int n = m.AddRoute(m.ROUTESFILE, n_a_route_1, n_a_route_2, n_a_route_3, n_a_route_4);
	if (n == 0) {
		MessageBox(TEXT("添加成功！"));
	}
	else {
		MessageBox(TEXT("添加失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_a_route_1 = 0;
	n_a_route_2 = 0;
	n_a_route_3 = 0;
	n_a_route_4 = 0;
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//删除站点
	//拿到变化的下拉项的序号
	int index = n_d_station.GetCurSel();
	CString str;
	n_d_station.GetLBText(index, str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* p = T2A(str);
	int n = m.DeleteStation(m.STATIONFILE, p);
	if (n == 0) {
		MessageBox(TEXT("删除成功！"));
	}
	else {
		MessageBox(TEXT("删除失败！"));
	}
	
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除公交
	//拿到变化的下拉项的序号
	int index = n_d_bus.GetCurSel();
	CString str;
	n_d_bus.GetLBText(index, str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* p = T2A(str);
	int n = m.DeleteBuses(m.BUSESFILE, p);
	if (n == 0) {
		MessageBox(TEXT("删除成功！"));
	}
	else {
		MessageBox(TEXT("删除失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除路径
	UpdateData(TRUE);
	UpdateData(FALSE);
	Map m;
	int n = m.DeleteRoute(m.ROUTESFILE, n_d_route_1, n_d_route_2, n_d_route_3, n_d_route_4);
	if (n == 0) {
		MessageBox(TEXT("删除成功！"));
	}
	else {
		MessageBox(TEXT("删除失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_d_route_1 = 0;
	n_d_route_1 = 0;
	n_d_route_1 = 0;
	n_d_route_1 = 0;
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新站点
	//拿到变化的下拉项的序号
	int index = n_u_station_old.GetCurSel();
	CString str;
	n_u_station_old.GetLBText(index, str);
	Map m;
	m.InitData();
	USES_CONVERSION;
	char* p = T2A(str);

	UpdateData(TRUE);
	UpdateData(FALSE);
	char* newname = T2A(n_u_station_new);

	int n = m.UpdateStation(m.STATIONFILE, p, newname);

	if (n == 0) {
		MessageBox(TEXT("更新成功！"));
	}
	else {
		MessageBox(TEXT("更新失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_u_station_new = TEXT("");
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新公交
	UpdateData(TRUE);
	UpdateData(FALSE);
	USES_CONVERSION;
	char* p1 = T2A(n_u_bus_old_1);
	char* p2 = T2A(n_u_bus_old_2);
	char* p3 = T2A(n_u_bus_old_3);
	char* p4 = T2A(n_u_bus_new_1);
	char* p5 = T2A(n_u_bus_new_2);
	char* p6 = T2A(n_u_bus_new_3);

	Map m;
	int n = m.UpdateBuses(m.BUSESFILE, p1, p2, p3, p4, p5, p6);
	if (n == 0) {
		MessageBox(TEXT("更新成功！"));
	}
	else {
		MessageBox(TEXT("更新失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_u_bus_new_1 = TEXT("");
	n_u_bus_new_2 = TEXT("");
	n_u_bus_new_3 = TEXT("");
	n_u_bus_old_1 = TEXT("");
	n_u_bus_old_2 = TEXT("");
	n_u_bus_old_3 = TEXT("");
	CUpdate::OnInitialUpdate();
}


void CUpdate::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新路径
	UpdateData(TRUE);
	UpdateData(FALSE);
	Map m;
	int n = m.UpdateRoute
	(m.ROUTESFILE, 
		n_u_route_old_1, n_u_route_old_2, n_u_route_old_3, n_u_route_old_4, 
		n_u_route_new_1, n_u_route_new_2, n_u_route_new_3, n_u_route_new_4);
	if (n == 0) {
		MessageBox(TEXT("更新成功！"));
	}
	else {
		MessageBox(TEXT("更新失败！"));
	}
	n_d_station.ResetContent();
	n_d_bus.ResetContent();
	n_u_station_old.ResetContent();
	n_u_route_new_1 = 0;
	n_u_route_new_2 = 0;
	n_u_route_new_3 = 0;
	n_u_route_new_4 = 0;
	n_u_route_old_1 = 0; 
	n_u_route_old_2 = 0;
	n_u_route_old_3 = 0;
	n_u_route_old_4 = 0;

	CUpdate::OnInitialUpdate();
}


void CUpdate::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = n_d_station.GetCurSel();
	CString str;
	n_d_station.GetLBText(index, str);
	UpdateData(TRUE);
	UpdateData(FALSE);
}
