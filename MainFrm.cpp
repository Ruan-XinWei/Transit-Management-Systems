
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Transit Management Systems.h"

#include "CDisplayView.h"
#include "CSelectView.h"

#include "MainFrm.h"
#include "WinUser.h"

#include "CBusinfo.h"
#include "CQueryStation.h"
#include "CQueryroute.h"
#include "CUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
	//产生WU_X消息，自动调用OnMyChange()函数
	ON_MESSAGE(WU_1, OnMyChange)
	ON_MESSAGE(WU_2, OnMyChange)
	ON_MESSAGE(WU_3, OnMyChange)
	ON_MESSAGE(WU_4, OnMyChange)
	//ON_MESSAGE(WU_5, OnMyChange)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标
	SetClassLong(m_hWnd, -14, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_Win));


	//设置右侧标题
	SetTitle(TEXT("Transit Management Systems"));

	//设置窗口大小
	MoveWindow(0, 0, 1200, 1000);

	//居中
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	m_Splitter.CreateStatic(this, 1, 2);

	m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(300, 1000), pContext);
	m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(GetSystemMetrics(SM_CXFULLSCREEN) - 300, 1000), pContext);

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{

	CCreateContext context;
	if (WU_1 == wParam)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CBusinfo);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_Splitter.GetPane(0, 1);
		m_Splitter.DeleteView(0, 1);
		m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CBusinfo), CSize(600, 500), &context);
		CBusinfo* pNewView = (CBusinfo*)m_Splitter.GetPane(0, 1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0, 1);
	}
	else if (WU_2 == wParam) {
		context.m_pNewViewClass = RUNTIME_CLASS(CQueryStation);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_Splitter.GetPane(0, 1);
		m_Splitter.DeleteView(0, 1);
		m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CQueryStation), CSize(600, 500), &context);
		CQueryStation* pNewView = (CQueryStation*)m_Splitter.GetPane(0, 1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0, 1);
	}
	else if (WU_3 == wParam) {
		context.m_pNewViewClass = RUNTIME_CLASS(CQueryroute);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_Splitter.GetPane(0, 1);
		m_Splitter.DeleteView(0, 1);
		m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CQueryroute), CSize(600, 500), &context);
		CQueryroute* pNewView = (CQueryroute*)m_Splitter.GetPane(0, 1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0, 1);
	}
	else if (WU_4 == wParam) {
		context.m_pNewViewClass = RUNTIME_CLASS(CUpdate);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_Splitter.GetPane(0, 1);
		m_Splitter.DeleteView(0, 1);
		m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CUpdate), CSize(600, 500), &context);
		CUpdate* pNewView = (CUpdate*)m_Splitter.GetPane(0, 1);
		m_Splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_Splitter.SetActivePane(0, 1);
	}
	return 0;
}
