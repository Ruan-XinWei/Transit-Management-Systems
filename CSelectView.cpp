// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "Transit Management Systems.h"
#include "CSelectView.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_Select);

	//图片列表的创建CImageList::Create
	//30,30	指定图标的宽度和高度
	//ILC_COLOR32	图标格式
	//1，1	有多少图标就写多少个
	n_ImageList.Create(30, 30, ILC_COLOR32, 1, 1);

	//图片列表添加图标CImageList::Add
	n_ImageList.Add(icon);

	//获取视图的树控件CImageList::GetTreeCtrl
	n_TreeCtrl = &GetTreeCtrl();

	//树控件设置图片列表CTreeCtrl::SetImageList
	n_TreeCtrl->SetImageList(&n_ImageList, TVSIL_NORMAL);

	//树控件设置节点CTreeCtrl::InsertItem
	n_TreeCtrl->InsertItem(TEXT("查询公交"), 0, 0, NULL);
	n_TreeCtrl->InsertItem(TEXT("查询站点"), 0, 0, NULL);
	n_TreeCtrl->InsertItem(TEXT("查询线路"), 0, 0, NULL);
	n_TreeCtrl->InsertItem(TEXT("修改信息"), 0, 0, NULL);
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM item =  n_TreeCtrl->GetSelectedItem();
	CString str = n_TreeCtrl->GetItemText(item);
	//MessageBox(str);

	if (str == TEXT("查询公交"))
	{
		//需要包含框架类头文件#include "MainFrm.h"
		//CWnd::PostMessage 将一个消息放入到窗口的消息队列
		//AfxGetMainWnd();	框架窗口对象的指针
		//AfxGetMainWnd().GetSafeHwnd();获取返回窗口的句柄，CWnd::GetSafeHwnd
		//WM_A	自定义消息
		//(WPARAM)WU_1	指定了附加的消息信息
		//(LPARAM)0		指定了附加的消息信息，此参数这里没有意义。
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_1, (WPARAM)WU_1, (LPARAM)0);
	}
	if (str == TEXT("查询站点")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_2, (WPARAM)WU_2, (LPARAM)0);
	}
	if (str == TEXT("查询线路")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_3, (WPARAM)WU_3, (LPARAM)0);
	}
	if (str == TEXT("修改信息")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_4, (WPARAM)WU_4, (LPARAM)0);
	}
}
