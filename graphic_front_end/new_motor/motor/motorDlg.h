// motorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CmotorDlg 对话框
class CmotorDlg : public CDialog
{
// 构造
public:
	CmotorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MOTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	long arrow_x,arrow_y;
	float angle, arrow_r;
	unsigned int vbAddr[128];
	unsigned int vbLens[128];
	bool vNew;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedButton1();
public:
	CButton bArrow;
};
