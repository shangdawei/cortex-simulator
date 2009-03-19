// dpPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sp.h"
#include "dpPage.h"
#include <math.h>
#include "vbus/vbus_interface.h"


// CdpPage �Ի���

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


// CdpPage ��Ϣ�������

void CdpPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnTimer(nIDEvent);

	arrow_x ++;
	SetTimer(1, 5, NULL);
	Invalidate();
}
