#pragma once



// CUpdate 窗体视图

class CUpdate : public CFormView
{
	DECLARE_DYNCREATE(CUpdate)

protected:
	CUpdate();           // 动态创建所使用的受保护的构造函数
	virtual ~CUpdate();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Update };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
private:
	CComboBox n_d_station;
public:
	CComboBox n_d_bus;
private:
	CComboBox n_u_station_old;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
private:
//	CEdit n_a_station;
	CString n_a_station;
	CString n_a_bus_1;
	CString n_a_bus_2;
	CString n_a_bus_3;
//	CString n_a_route_1;
//	CString n_a_route_2;
//	CString n_a_route_3;
//	CString n_a_route_4;
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	int n_a_route_1;
private:
	int n_a_route_2;
	int n_a_route_3;
	int n_a_route_4;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
private:
	int n_d_route_1;
	int n_d_route_2;
	int n_d_route_3;
	int n_d_route_4;
public:
	afx_msg void OnBnClickedButton9();
private:
	CString n_u_station_new;
	CString n_u_bus_old_1;
	CString n_u_bus_old_2;
	CString n_u_bus_old_3;
	CString n_u_bus_new_1;
	CString n_u_bus_new_2;
	CString n_u_bus_new_3;
public:
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
private:
	int n_u_route_old_1;
	int n_u_route_old_2;
	int n_u_route_old_3;
	int n_u_route_old_4;
	int n_u_route_new_1;
	int n_u_route_new_2;
	int n_u_route_new_3;
	int n_u_route_new_4;
public:
	afx_msg void OnCbnSelchangeCombo1();
};


