// spTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sp.h"
#include "spTreeView.h"
#include "spDoc.h"


// CspTreeView

IMPLEMENT_DYNCREATE(CspTreeView, CTreeView)

CspTreeView::CspTreeView()
{

}

CspTreeView::~CspTreeView()
{
}

BEGIN_MESSAGE_MAP(CspTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CspTreeView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CspTreeView ���

#ifdef _DEBUG
void CspTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CspTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG

void CspTreeView::OnInitialUpdate()
{
	root = GetTreeCtrl().InsertItem((LPCTSTR)_T("Cortex Simulator"),0,0,TVI_ROOT);
	m_subtree[0] = GetTreeCtrl().InsertItem((LPCTSTR)_T("System Config"),0,0,root);
	m_subtree[1] = GetTreeCtrl().InsertItem((LPCTSTR)_T("Monitor"),0,0,root);
	m_subtree[2] = GetTreeCtrl().InsertItem((LPCTSTR)_T("Send"),0,0,root);
	m_subtree[3] = GetTreeCtrl().InsertItem((LPCTSTR)_T("Data Process"),0,0,root);
}

// CspTreeView ��Ϣ�������

void CspTreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CspDoc *m_pDoc = (CspDoc*)GetDocument();
	HTREEITEM hTmp = GetTreeCtrl().GetSelectedItem();	//Get the selected node handle

	//Set the viewtype to 0
	if(hTmp == m_subtree[0] && m_pDoc)
		m_pDoc->m_nViewType = 1;
	
	//Set the viewtype to 1
	if(hTmp == m_subtree[1] && m_pDoc)
		m_pDoc->m_nViewType = 2;

	//Set the viewtype to 2
	if(hTmp == m_subtree[2] && m_pDoc)
		m_pDoc->m_nViewType = 3;

	//Set the viewtype to 3
	if(hTmp == m_subtree[3] && m_pDoc)
		m_pDoc->m_nViewType = 4;

	if(hTmp == m_subtree[0] || hTmp == m_subtree[1] 
	|| hTmp == m_subtree[2] || hTmp == m_subtree[3] && m_pDoc){
		m_pDoc->m_nTabIndex = 0;
		m_pDoc->UpdateAllViews(NULL,TVN_SELCHANGED);
	}
}

void CspTreeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���

}
