// spDoc.cpp : CspDoc ���ʵ��
//

#include "stdafx.h"
#include "sp.h"

#include "spDoc.h"
#include "vbus/vbus_interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CspDoc

IMPLEMENT_DYNCREATE(CspDoc, CDocument)

BEGIN_MESSAGE_MAP(CspDoc, CDocument)
END_MESSAGE_MAP()


// CspDoc ����/����

CspDoc::CspDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_nViewType = 0;
	m_nTabIndex = 0;
}

CspDoc::~CspDoc()
{
}

BOOL CspDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	vb_load("vbus");

	return TRUE;
}




// CspDoc ���л�

void CspDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CspDoc ���

#ifdef _DEBUG
void CspDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CspDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CspDoc ����
