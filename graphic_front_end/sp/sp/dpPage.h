#pragma once


// CdpPage �Ի���

class CdpPage : public CDialog
{
	DECLARE_DYNAMIC(CdpPage)

public:
	CdpPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CdpPage();

// �Ի�������
	enum { IDD = IDD_TAB_DP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	
	long arrow_x,arrow_y;
	float angle, arrow_r;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
