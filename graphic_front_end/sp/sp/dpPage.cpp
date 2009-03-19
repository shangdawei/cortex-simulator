// dpPage.cpp : 实现文件
//

#include "stdafx.h"
#include "sp.h"
#include "dpPage.h"
#include <math.h>
#include "vbus/vbus_interface.h"


// CdpPage 对话框

IMPLEMENT_DYNAMIC(CdpPage, CDialog)

CdpPage::CdpPage(CWnd* pParent /*=NULL*/)
	: CDialog(CdpPage::IDD, pParent)
{
	arrow_x = 50;
	arrow_y = 50;
	angle = 0;
	arrow_r = 15;
}

CdpPage::~CdpPage()
{
}

void CdpPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdpPage, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CdpPage 消息处理程序

void CdpPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	POINT arrow[3];

	dc.Rectangle(0,0,455,407);

	arrow[0].x = (long)(arrow_x + arrow_r*cos(angle));
	arrow[0].y = (long)(arrow_y + arrow_r*sin(angle));
	arrow[1].x = (long)(arrow_x + arrow_r*cos(angle + 3.14/2));
	arrow[1].y = (long)(arrow_y + arrow_r*sin(angle + 3.14/2));
	arrow[2].x = (long)(arrow_x + arrow_r*cos(angle - 3.14/2));
	arrow[2].y = (long)(arrow_y + arrow_r*sin(angle - 3.14/2));
	dc.Polygon(arrow, 3);
}
void CdpPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);

	arrow_x ++;
	SetTimer(1, 5, NULL);
	Invalidate();
}
