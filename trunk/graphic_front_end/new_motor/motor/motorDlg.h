// motorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CmotorDlg �Ի���
class CmotorDlg : public CDialog
{
// ����
public:
	CmotorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MOTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	long arrow_x,arrow_y;
	float angle, arrow_r;
	unsigned int vbAddr[128];
	unsigned int vbLens[128];
	bool vNew;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
