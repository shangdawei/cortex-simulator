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
};
