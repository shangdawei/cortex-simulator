// ledINTDlg.h : ͷ�ļ�
//

#pragma once

// CledINTDlg �Ի���
class CledINTDlg : public CDialog
{
// ����
public:
	CledINTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LEDINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int bd;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
