#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CmonitorPage �Ի���

class CmonitorPage : public CDialog
{
	DECLARE_DYNAMIC(CmonitorPage)

public:
	CmonitorPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmonitorPage();

// �Ի�������
	enum { IDD = IDD_TAB_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
