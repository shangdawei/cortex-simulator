// DemoCP.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"

#include "demoDoc.h"
#include "demoView.h"
#include "DemoCP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DemoCP dialog


DemoCP::DemoCP(CDemoView* pParent)
{
	//{{AFX_DATA_INIT(DemoCP)
	//}}AFX_DATA_INIT
	pWnd = pParent;
	port_lines = 0;
	stops = 0;
//	CDemoView CV;

}


void DemoCP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DemoCP)
	DDX_Control(pDX, IDC_EDIT_COORD2, m_polar);
	DDX_Control(pDX, IDC_EDIT_M, m_mstate);
	DDX_Control(pDX, IDC_STATIC_LED3, m_led3);
	DDX_Control(pDX, IDC_STATIC_LED2, m_led2);
	DDX_Control(pDX, IDC_PORT, m_port);
	DDX_Control(pDX, IDC_STATIC_LED, m_led1);
	DDX_Control(pDX, IDC_EDIT_RW, m_rw);
	DDX_Control(pDX, IDC_EDIT_LW, m_lw);
	DDX_Control(pDX, IDC_EDIT_COORD, m_coord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DemoCP, CDialog)
	//{{AFX_MSG_MAP(DemoCP)
	ON_BN_CLICKED(ID_OVER, OnOver)
		ON_MESSAGE(WM_COORD,GetCoord)
		ON_MESSAGE(WM_LEDS,SetLEDS)
		ON_MESSAGE(WM_PORT,SetPort)
	ON_BN_CLICKED(IDC_LINK, OnLink)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DemoCP message handlers

LRESULT DemoCP::GetCoord(WPARAM wParam,LPARAM lParam)
{
	char spos[10];

	
	itoa((int)(pWnd->vpos_x/4),spos,10);
	m_coord.SetSel(0,-1);
	itoa(pWnd->lregs,spos,10);
	m_coord.ReplaceSel(spos);
	m_coord.ReplaceSel(" : ");
	itoa(pWnd->rregs,spos,10);
	m_coord.ReplaceSel(spos);

	itoa(pWnd->steps,spos,10);
	m_polar.SetSel(0,-1);
	m_polar.ReplaceSel(spos);
	if(pWnd->state_o != pWnd->rect_state){
	if(pWnd->rect_state == 0){
		m_mstate.SetSel(0,-1);
		m_mstate.ReplaceSel("Move forward");
		m_lw.SetSel(0,-1);
		m_lw.ReplaceSel("Positive");
		m_rw.SetSel(0,-1);
		m_rw.ReplaceSel("Positive");
	}
	else if(pWnd->rect_state == 1){
		m_mstate.SetSel(0,-1);
		m_mstate.ReplaceSel("Turn left");
		m_lw.SetSel(0,-1);
		m_lw.ReplaceSel("Reverse");
		m_rw.SetSel(0,-1);
		m_rw.ReplaceSel("Positive");
	}
	else if(pWnd->rect_state == 2){
		m_mstate.SetSel(0,-1);
		m_mstate.ReplaceSel("Turn right");
		m_lw.SetSel(0,-1);
		m_lw.ReplaceSel("Positive");
		m_rw.SetSel(0,-1);
		m_rw.ReplaceSel("Reverse");
	}
	else if(pWnd->rect_state == 3){
		m_mstate.SetSel(0,-1);
		m_mstate.ReplaceSel("Back up");
		m_lw.SetSel(0,-1);
		m_lw.ReplaceSel("Reverse");
		m_rw.SetSel(0,-1);
		m_rw.ReplaceSel("Reverse");
	}
	}
	if(pWnd->rect_state == 4)
		stops ++;
	else
		stops = 0;
	if(stops > 100){
		m_mstate.SetSel(0,-1);
		m_mstate.ReplaceSel("Stop");
		m_lw.SetSel(0,-1);
		m_lw.ReplaceSel("Run down");
		m_rw.SetSel(0,-1);
		m_rw.ReplaceSel("Run down");
	}
	return 0;
}

BOOL DemoCP::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	GetCoord(0,0);
	SetLEDS(0,0);
	m_port.SetSel(0,-1);
	bledon = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LEDON));
	bledoff = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LEDOFF));
	SetLEDS(0,0);
	m_mstate.SetSel(0,-1);
	m_mstate.ReplaceSel("Stop");
	m_lw.SetSel(0,-1);
	m_lw.ReplaceSel("Run down");
	m_rw.SetSel(0,-1);
	m_rw.ReplaceSel("Run down");
	return TRUE;
}

LRESULT DemoCP::SetLEDS(WPARAM wParam,LPARAM lParam)
{
	if(pWnd->poweron & 1)
		m_led1.SetBitmap(bledon);
	else
		m_led1.SetBitmap(bledoff);
	if(pWnd->leds & 1)
		m_led2.SetBitmap(bledon);
	else
		m_led2.SetBitmap(bledoff);
	if(pWnd->leds & 2)
		m_led3.SetBitmap(bledon);
	else
		m_led3.SetBitmap(bledoff);

	return 0;
}

void DemoCP::OnOver() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pWnd->SendMessage(WM_OVER);
	CDialog::OnOK();
}

LRESULT DemoCP::SetPort(WPARAM wParam,LPARAM lParam)
{
	char reg[9],i;
	unsigned char bp;

	port_lines++;
	if(port_lines >12){
		port_lines = 0;
		m_port.SetSel(0,-1);
	}
	m_port.ReplaceSel("R: ");
	for(i = 0, bp = 0x80; i < 4;i++, bp = bp >> 1){
		if(bp & pWnd->wheel)
			reg[i] = '1';
		else
			reg[i] = '0';
	}
	reg[4] = '\0';
	m_port.ReplaceSel(reg);
	m_port.ReplaceSel(" ");

	m_port.ReplaceSel("L: ");
	for(i = 4, bp = 0x08; i < 8;i++, bp = bp >> 1){
		if(bp & pWnd->wheel)
			reg[i-4] = '1';
		else
			reg[i-4] = '0';
	}
	reg[4] = '\0';
	m_port.ReplaceSel(reg);
	m_port.ReplaceSel("   ");

	m_port.ReplaceSel("LED: ");
	for(i = 0, bp = 0x08; i < 4;i++, bp = bp >> 1){
		if(bp & pWnd->leds)
			reg[i] = '1';
		else
			reg[i] = '0';
	}
	reg[4] = '\0';
	m_port.ReplaceSel(reg);

	m_port.ReplaceSel("\r\n");
	fprintf(pWnd->fp, "0x%x\t : 0x%x\t\n", pWnd->wheel, pWnd->leds);
	fflush(pWnd->fp);

	return 0;
}

void DemoCP::OnLink() 
{
	UpdateData(TRUE);
	pWnd->SendMessage(WM_GO);
}