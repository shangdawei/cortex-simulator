// motorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "motor.h"
#include "motorDlg.h"
#include "vbus/vbus_interface.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmotorDlg 对话框




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


// CmotorDlg 消息处理程序

BOOL CmotorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	vb_load("vbus");
	//bArrow.SetIcon(m_hIcon);
	SetTimer(1, 50, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmotorDlg::OnPaint()
{
	CPaintDC dc(this);// 用于绘制的设备上下文

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CmotorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmotorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加控件通知处理程序代码
}
