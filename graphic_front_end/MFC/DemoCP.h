#if !defined(AFX_DEMOCP_H__3AC58401_B861_427F_8EB0_F10699684C12__INCLUDED_)
#define AFX_DEMOCP_H__3AC58401_B861_427F_8EB0_F10699684C12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemoCP.h : header file
//

#define WM_COORD		WM_USER+1
#define WM_LEDS		WM_USER+2
#define WM_PORT		WM_USER+3
#define WM_GO		WM_USER+4
#define WM_OVER		WM_USER+5

/////////////////////////////////////////////////////////////////////////////
// DemoCP dialog

class DemoCP : public CDialog
{
// Construction
public:
	DemoCP(CDemoView* pParent);   // standard constructor
	CDemoView* pWnd;

	LRESULT GetCoord(WPARAM wParam,LPARAM lParam);
	LRESULT SetLEDS(WPARAM wParam,LPARAM lParam);
	LRESULT SetPort(WPARAM wParam,LPARAM lParam);
	char port_lines;
	char stops;

// Dialog Data
	//{{AFX_DATA(DemoCP)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_polar;
	CEdit	m_mstate;
	CStatic	m_led5;
	CStatic	m_led4;
	CStatic	m_led3;
	CStatic	m_led2;
	CEdit	m_port;
	CStatic	m_led1;
	CEdit	m_rw;
	CEdit	m_lw;
	CEdit	m_coord;
	HBITMAP bledon,bledoff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DemoCP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(DemoCP)
	afx_msg void OnOver();
	afx_msg void OnLink();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOCP_H__3AC58401_B861_427F_8EB0_F10699684C12__INCLUDED_)
