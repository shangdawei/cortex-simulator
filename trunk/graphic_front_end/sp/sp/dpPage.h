#pragma once


// CdpPage 对话框

class CdpPage : public CDialog
{
	DECLARE_DYNAMIC(CdpPage)

public:
	CdpPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CdpPage();

// 对话框数据
	enum { IDD = IDD_TAB_DP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	
	long arrow_x,arrow_y;
	float angle, arrow_r;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
