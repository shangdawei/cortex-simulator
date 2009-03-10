// demoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOVIEW_H__01344CD8_F517_447F_9EFA_CDFC0D5CD498__INCLUDED_)
#define AFX_DEMOVIEW_H__01344CD8_F517_447F_9EFA_CDFC0D5CD498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDemoView : public CScrollView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attributes
public:
	CDemoDoc* GetDocument();
	CDialog* panel;
	double	pos_x,pos_y,direction;
	double	vpos_x,vpos_y,vorign_x,vorign_y;
	char	mouse_enable;
	char	rect_state,leds,isdemo,panelnum; //rect_state F:0 L:1 R:2 B:3 S:4 I:5
	int		steps,lregs,rregs;
	char	demogo;
	char	State_Table[16][16];
	char	state_o,poweron;
	CSize	sizeTotal;
	unsigned char	wheel_old,wheel;
	LRESULT Demo_over(WPARAM wParam,LPARAM lParam);
	void Get_State();
	HANDLE hMemMap;
	LPBYTE pMemView;
	FILE *fp;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoView();
	void Draw_Rect(CDC* pDC);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg LRESULT OnOperGo(WPARAM wParam,LPARAM lParam);
	afx_msg void OnOperStop();
	afx_msg void OnOperLeft();
	afx_msg void OnOperRight();
	afx_msg void OnOperForward();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOperPause();
	afx_msg void OnFileDemo();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__01344CD8_F517_447F_9EFA_CDFC0D5CD498__INCLUDED_)
