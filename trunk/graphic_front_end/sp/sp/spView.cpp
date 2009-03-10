// spView.cpp : CspView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CspView ����/����

CspView::CspView()
{
	// TODO: �ڴ˴���ӹ������

}

CspView::~CspView()
{
}

BOOL CspView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CspView ����

void CspView::OnDraw(CDC* /*pDC*/)
{
	CspDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CspView ��ӡ

BOOL CspView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CspView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CspView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CspView ���

#ifdef _DEBUG
void CspView::AssertValid() const
{
	CView::AssertValid();
}

void CspView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CspDoc* CspView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CspDoc)));
	return (CspDoc*)m_pDocument;
}
#endif //_DEBUG


// CspView ��Ϣ�������
