#pragma once

#include "Resource.h"

// CrootPage �Ի���

class CrootPage : public CDialog
{
	DECLARE_DYNAMIC(CrootPage)

public:
	CrootPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CrootPage();

// �Ի�������
	enum { IDD = IDD_TAB_ROOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CRect rs;
};
