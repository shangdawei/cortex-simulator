#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CmonitorPage 对话框

class CmonitorPage : public CDialog
{
	DECLARE_DYNAMIC(CmonitorPage)

public:
	CmonitorPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmonitorPage();

// 对话框数据
	enum { IDD = IDD_TAB_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CEdit m_AddrEdit;
public:
	afx_msg void OnBnClickedButton1();
public:
	virtual BOOL OnInitDialog();
	void ReloadData();
public:
	CListCtrl m_monitorList;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton2();
};
