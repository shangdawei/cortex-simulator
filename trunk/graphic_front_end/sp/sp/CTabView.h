#pragma once

// CTabView

#include "rootPage.h"
#include "monitorPage.h"
#include "sendPage.h"
#include "dpPage.h"

class CTabView : public CCtrlView
{
	DECLARE_DYNCREATE(CTabView)
public:
	CTabView();
	virtual ~CTabView();
	
	CTabCtrl& GetTabCtrl() const;
protected:
	CrootPage rootPage;
	CmonitorPage monitorPage;
	CsendPage sendPage;
	CdpPage dpPage;
	CRect rs;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnInitialUpdate();

	//User defines function
	void SetTabs(int nTabLevel);
	void SetPages(int nViewType,int nTabIndex);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

public:	//message process function
	afx_msg void OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnPaint();
};