#pragma once



// CBusinfo 窗体视图

class CBusinfo : public CFormView
{
	DECLARE_DYNCREATE(CBusinfo)

protected:
	CBusinfo();           // 动态创建所使用的受保护的构造函数
	virtual ~CBusinfo();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = Bus_information };
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
	afx_msg void OnBnClickedButton1();
private:
	CEdit n_businfo;
public:
	//afx_msg void OnEnChangeEdit1();
private:
	CComboBox n_busname;
public:
	virtual void OnInitialUpdate();
};


