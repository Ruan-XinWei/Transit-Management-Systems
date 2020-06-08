#pragma once



// CQueryStation 窗体视图

class CQueryStation : public CFormView
{
	DECLARE_DYNCREATE(CQueryStation)

protected:
	CQueryStation();           // 动态创建所使用的受保护的构造函数
	virtual ~CQueryStation();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = QueryStation };
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
private:
	CComboBox n_stationname;
	CEdit n_stationinfo;
public:
	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
};


