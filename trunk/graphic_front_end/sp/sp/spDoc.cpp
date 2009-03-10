// spDoc.cpp : CspDoc 类的实现
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


// CspDoc 构造/析构

CspDoc::CspDoc()
{
	// TODO: 在此添加一次性构造代码
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

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	vb_load("vbus");

	return TRUE;
}




// CspDoc 序列化

void CspDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CspDoc 诊断

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


// CspDoc 命令
