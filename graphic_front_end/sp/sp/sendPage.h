#pragma once
#include "afxwin.h"


// CsendPage �Ի���

class CsendPage : public CDialog
{
	DECLARE_DYNAMIC(CsendPage)

public:
	CsendPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CsendPage();

// �Ի�������
	enum { IDD = IDD_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit s_value_1;
public:
	CEdit s_addr_1;
public:
	afx_msg void OnBnClickedButton1();
};
