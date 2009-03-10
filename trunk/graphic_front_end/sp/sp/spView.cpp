// spView.cpp : CspView 类的实现
//

#include "stdafx.h"
#include "sp.h"

#include "spDoc.h"
#include "spView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CspView

IMPLEMENT_DYNCREATE(CspView, CView)

BEGIN_MESSAGE_MAP(CspView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CspView 构造/析构

CspView::CspView()
{
	// TODO: 在此处添加构造代码

}

CspView::~CspView()
{
}

BOOL CspView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CspView 绘制

void CspView::OnDraw(CDC* /*pDC*/)
{
	CspDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CspView 打印

BOOL CspView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CspView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CspView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CspView 诊断

#ifdef _DEBUG
void CspView::AssertValid() const
{
	CView::AssertValid();
}

void CspView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CspDoc* CspView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CspDoc)));
	return (CspDoc*)m_pDocument;
}
#endif //_DEBUG


// CspView 消息处理程序
