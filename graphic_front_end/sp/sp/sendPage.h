#pragma once
#include "afxwin.h"


// CsendPage 对话框

class CsendPage : public CDialog
{
	DECLARE_DYNAMIC(CsendPage)

public:
	CsendPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CsendPage();

// 对话框数据
	enum { IDD = IDD_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit s_value_1;
public:
	CEdit s_addr_1;
public:
	afx_msg void OnBnClickedButton1();
};
