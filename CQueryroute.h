#pragma once



// CQueryroute 窗体视图

class CQueryroute : public CFormView
{
	DECLARE_DYNCREATE(CQueryroute)

protected:
	CQueryroute();           // 动态创建所使用的受保护的构造函数
	virtual ~CQueryroute();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QueryRoute };
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
	virtual void OnInitialUpdate();
private:
	CComboBox n_start;
	CComboBox n_end;
public:
	afx_msg void OnBnClickedButton1();
private:
	CEdit n_Routeinfo;
public:
	afx_msg void OnEnChangeEdit3();
};


