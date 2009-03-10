#include "stdafx.h"
#include "CTabView.h"
#include "spDoc.h"

// CTabView

IMPLEMENT_DYNCREATE(CTabView, CCtrlView)

CTabView::CTabView():CCtrlView(_T("SysTabControl32"), AFX_WS_DEFAULT_VIEW)
{
}

CTabView::~CTabView()
{
}


BEGIN_MESSAGE_MAP(CTabView, CCtrlView)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CTabView::OnSelchangeTabCtrl)
	ON_WM_SIZE()
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTabView message handlers
CTabCtrl& CTabView::GetTabCtrl() const
{
	return *(CTabCtrl*)this;
}

BOOL CTabView::PreCreateWindow(CREATESTRUCT& cs)
{
// TODO: Add your specialized code here and/or call the base class
	if(!CCtrlView::PreCreateWindow(cs))
		return FALSE;
//cs.style |= TCS_FIXEDWIDTH;
	return TRUE;
}

void CTabView::OnInitialUpdate()
{

// TODO: Add your specialized code here and/or call the base class
	rootPage.Create(IDD_TAB_ROOT,this);
	monitorPage.Create(IDD_TAB_MONITOR,this);
	sendPage.Create(IDD_SEND,this);
	dpPage.Create(IDD_TAB_DP,this);

	SetTabs(0);
	SetPages(0,0);

	CCtrlView::OnInitialUpdate();
}

void CTabView::SetTabs(int nTabLevel)
{
	static CString sLable[][9] = {
		{_T("Cortex Simulator")},
		{_T("Vbus"),_T("Device"),_T("Intterupts")},
		{_T("Memory"),_T("GPIOs")},
		{_T("VBus"),_T("INTs")},
		{_T("Motor")}
	};
	TC_ITEM item;

	item.mask  = TCIF_TEXT;
	for(int i = 0;!sLable[nTabLevel][i].IsEmpty();i++){
		item.pszText = (LPWSTR)(LPCTSTR)sLable[nTabLevel][i];
		item.cchTextMax = sLable[nTabLevel][i].GetLength();
		GetTabCtrl().InsertItem(i, &item);
	}
}

void CTabView::SetPages(int nViewType,int nTabIndex)
{
	GetTabCtrl().SetCurSel(nTabIndex);

	rootPage.ShowWindow(FALSE);
	monitorPage.ShowWindow(FALSE);
	sendPage.ShowWindow(FALSE);
	dpPage.ShowWindow(FALSE);
	switch(nViewType){
		case 0:
			switch(nTabIndex){
				case 0:
					rootPage.ShowWindow(TRUE);
					break;
			}
			break;
		case 1:
			switch(nTabIndex){
				case 0:
					rootPage.ShowWindow(TRUE);
					break;
				case 1:
					rootPage.ShowWindow(TRUE);
					break;
				case 2:
					rootPage.ShowWindow(TRUE);
					break;
			}
			break;
		case 2:
			switch(nTabIndex){
				case 0:
					monitorPage.ShowWindow(TRUE);
					break;
				case 1:
					monitorPage.ShowWindow(TRUE);
					break;
			}
			break;
		case 3:
			switch(nTabIndex){
				case 0:
					sendPage.ShowWindow(TRUE);
					break;
				case 1:
					sendPage.ShowWindow(TRUE);
					break;
			}
			break;
		case 4:
			switch(nTabIndex){
				case 0:
					dpPage.ShowWindow(TRUE);
					break;
			}
			break;
	}
}

void CTabView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CspDoc *m_pDoc = (CspDoc*)GetDocument();

	switch(lHint){
		case TVN_SELCHANGED:
			GetTabCtrl().DeleteAllItems();
			SetTabs(m_pDoc->m_nViewType);
			SetPages(m_pDoc->m_nViewType,m_pDoc->m_nTabIndex);
			break;
		case TCN_SELCHANGE:
			SetPages(m_pDoc->m_nViewType,m_pDoc->m_nTabIndex);
			break;
	}
}

void CTabView::OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	CspDoc *m_pDoc = (CspDoc*)GetDocument();
	int sel = GetTabCtrl().GetCurSel();

	if(m_pDoc){
		m_pDoc->m_nTabIndex = sel;
		m_pDoc->UpdateAllViews(NULL,TCN_SELCHANGE);
	}
}

void CTabView::OnSize(UINT nType, int cx, int cy)
{
	CCtrlView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GetTabCtrl().GetClientRect(&rs);
	rs.top+=27;
	rs.bottom-=4;
	rs.left+=4;
	rs.right-=4;

	if(rootPage && monitorPage){
		rootPage.MoveWindow(&rs);
		monitorPage.MoveWindow(&rs);
		sendPage.MoveWindow(&rs);
		dpPage.MoveWindow(&rs);
	}
}