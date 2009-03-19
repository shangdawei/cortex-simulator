// motorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "motor.h"
#include "motorDlg.h"
#include "vbus/vbus_interface.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmotorDlg �Ի���




CmotorDlg::CmotorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmotorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	arrow_x = 50;
	arrow_y = 50;
	angle = 0;
	arrow_r = 15;
	vbAddr[0] = 0;
	vbAddr[1] = 4;
	vbAddr[2] = 8;
	vbLens[0] = 4;
	vbLens[1] = 4;
	vbLens[2] = 4;
	vNew = TRUE;
}

void CmotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, bArrow);
}

BEGIN_MESSAGE_MAP(CmotorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CmotorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CmotorDlg ��Ϣ�������

BOOL CmotorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	vb_load("vbus");
	//bArrow.SetIcon(m_hIcon);
	SetTimer(1, 50, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmotorDlg::OnPaint()
{
	CPaintDC dc(this);// ���ڻ��Ƶ��豸������

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else if(vNew == TRUE)
	{
		POINT arrow[3];

		dc.Rectangle(0,0,400,300);
		arrow[0].x = (long)(arrow_x + arrow_r*cos(angle));
		arrow[0].y = (long)(arrow_y + arrow_r*sin(angle));
		arrow[1].x = (long)(arrow_x + arrow_r*cos(angle + 3.14/2));
		arrow[1].y = (long)(arrow_y + arrow_r*sin(angle + 3.14/2));
		arrow[2].x = (long)(arrow_x + arrow_r*cos(angle - 3.14/2));
		arrow[2].y = (long)(arrow_y + arrow_r*sin(angle - 3.14/2));
		dc.Polygon(arrow, 3);
		vNew = FALSE;
	}
	else{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CmotorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmotorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnTimer(nIDEvent);

	float x,y;
	vb_nread(vbAddr[0], (char *)(&x), sizeof(x));
	vb_nread(vbAddr[1], (char *)(&y), sizeof(y));
	vb_nread(vbAddr[2], (char *)(&angle), sizeof(angle));
	arrow_x = (long)x + 50;
	arrow_y = (long)y + 50;
	vNew = TRUE;
	Invalidate();
	SetTimer(nIDEvent, 50, NULL);
}

void CmotorDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
