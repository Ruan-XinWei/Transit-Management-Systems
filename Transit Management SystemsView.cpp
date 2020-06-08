﻿
// Transit Management SystemsView.cpp: CTransitManagementSystemsView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Transit Management Systems.h"
#endif

#include "Transit Management SystemsDoc.h"
#include "Transit Management SystemsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransitManagementSystemsView

IMPLEMENT_DYNCREATE(CTransitManagementSystemsView, CView)

BEGIN_MESSAGE_MAP(CTransitManagementSystemsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTransitManagementSystemsView 构造/析构

CTransitManagementSystemsView::CTransitManagementSystemsView() noexcept
{
	// TODO: 在此处添加构造代码

}

CTransitManagementSystemsView::~CTransitManagementSystemsView()
{
}

BOOL CTransitManagementSystemsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTransitManagementSystemsView 绘图

void CTransitManagementSystemsView::OnDraw(CDC* /*pDC*/)
{
	CTransitManagementSystemsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTransitManagementSystemsView 打印

BOOL CTransitManagementSystemsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTransitManagementSystemsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTransitManagementSystemsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTransitManagementSystemsView 诊断

#ifdef _DEBUG
void CTransitManagementSystemsView::AssertValid() const
{
	CView::AssertValid();
}

void CTransitManagementSystemsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTransitManagementSystemsDoc* CTransitManagementSystemsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransitManagementSystemsDoc)));
	return (CTransitManagementSystemsDoc*)m_pDocument;
}
#endif //_DEBUG


// CTransitManagementSystemsView 消息处理程序
