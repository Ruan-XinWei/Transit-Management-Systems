// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "Login.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, n_name(_T(""))
	, n_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, n_name);
	DDX_Text(pDX, IDC_EDIT2, n_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序
void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//直接登录1
	CLoginDlg::OnCancel();

	CString name, pwd;
	//CLogin l;
	//l.ReadLogin(name, pwd);
	
	//直接登录2
	n_name = name;
	n_pwd = pwd;
	UpdateData(FALSE);

	UpdateData(TRUE);

	if (n_name.IsEmpty() || n_pwd.IsEmpty()) {
		if (n_name.IsEmpty()) {
			//MessageBox(TEXT("用户名不能为空"));
		}
		else {
			//MessageBox(TEXT("密码不能为空"));
		}
		return;
	}

	if (name == n_name) {
		if (pwd == n_pwd) {
			CLoginDlg::OnCancel();
		}
		else {
			//MessageBox(TEXT("密码错误"));
		}
	}
	else {
		MessageBox(TEXT("用户名错误"));
	}
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//退出当前对话框
	//CDialogEx::OnClose();

	//退出程序
	exit(0);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	n_name = TEXT("管理员");
	n_pwd = TEXT("123456");
	UpdateData(FALSE);
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
