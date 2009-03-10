#pragma once

#include "Resource.h"

// CrootPage 对话框

class CrootPage : public CDialog
{
	DECLARE_DYNAMIC(CrootPage)

public:
	CrootPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CrootPage();

// 对话框数据
	enum { IDD = IDD_TAB_ROOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CRect rs;
};
