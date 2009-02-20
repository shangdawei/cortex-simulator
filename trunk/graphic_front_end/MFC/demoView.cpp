// demoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "demo.h"

#include "demoDoc.h"
#include "demoView.h"
#include "DemoCP.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CDemoView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_MESSAGE(WM_GO,OnOperGo)
	ON_COMMAND(ID_OPER_STOP, OnOperStop)
	ON_COMMAND(ID_OPER_LEFT, OnOperLeft)
	ON_COMMAND(ID_OPER_RIGHT, OnOperRight)
	ON_COMMAND(ID_OPER_FORWARD, OnOperForward)
	ON_WM_TIMER()
	ON_COMMAND(ID_OPER_PAUSE, OnOperPause)
	ON_COMMAND(ID_FILE_DEMO, OnFileDemo)\
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_OVER,Demo_over)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here
	rect_state = 5;
	vpos_x = 0;
	vpos_y = 0;
	vorign_x = 100;
	vorign_y = 100;
	direction = 0;
	leds = 0;
	isdemo = 0;
	panelnum = 0;
	wheel = 0x33;
	mouse_enable = 0;
	steps = 0;
	rregs = lregs = 0;
	state_o = rect_state;
	poweron = 0;
	demogo = 0;
//forward : 1   backword : 2   stop : 3    failed : -1
	State_Table[0xf][0x3] = 1;
	State_Table[0x3][0xb] = 1;
	State_Table[0xb][0x8] = 1;
	State_Table[0x8][0xa] = 1;
	State_Table[0xa][0x2] = 1;
	State_Table[0x2][0xe] = 1;
	State_Table[0xe][0xc] = 1;
	State_Table[0xc][0xf] = 1;

	State_Table[0x3][0xf] = 2;
	State_Table[0xb][0x3] = 2;
	State_Table[0x8][0xb] = 2;
	State_Table[0xa][0x8] = 2;
	State_Table[0x2][0xa] = 2;
	State_Table[0xe][0x2] = 2;
	State_Table[0xc][0xe] = 2;
	State_Table[0xf][0xc] = 2;

	State_Table[0xf][0xf] = 3;
	State_Table[0x3][0x3] = 3;
	State_Table[0xb][0xb] = 3;
	State_Table[0x8][0x8] = 3;
	State_Table[0xa][0xa] = 3;
	State_Table[0x2][0x2] = 3;
	State_Table[0xe][0xe] = 3;
	State_Table[0xc][0xc] = 3;
}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(isdemo){
		Draw_Rect(pDC);
		if(demogo == 1){
			pDC->MoveTo(vorign_x - 5, vorign_y - 5);
			pDC->LineTo(vorign_x + 5, vorign_y + 5);
			pDC->MoveTo(vorign_x + 5, vorign_y - 5);
			pDC->LineTo(vorign_x - 5, vorign_y + 5);
		}
	}
	// TODO: add draw code for native data here
}

void CDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	sizeTotal.cx = 700;
	sizeTotal.cy = 400;
	SetScrollSizes(MM_TEXT, sizeTotal);

	hMemMap = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,
	PAGE_READWRITE | SEC_COMMIT,0,0xf,"ShareMem");	//Get a share memory handle
	pMemView = (LPBYTE)MapViewOfFile(hMemMap,FILE_MAP_READ,0,0,0);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

LRESULT CDemoView::OnOperGo(WPARAM wParam,LPARAM lParam) 
{
	// TODO: Add your command handler code here
	if(isdemo){
		SetTimer(1,5,NULL);
		Invalidate();
		poweron = 1;
		demogo = 1;
	}

	return 0;
}

void CDemoView::OnOperStop() 
{
	// TODO: Add your command handler code here
	if(isdemo){
		pos_x = 100;
		pos_y = 100;
		direction = 0;
		leds = 0;
		KillTimer(1);
		Invalidate();

		UpdateData(TRUE);
		panel->SendMessage(WM_COORD);
		panel->SendMessage(WM_LEDS);
	}
}

void CDemoView::OnOperLeft() 
{
	// TODO: Add your command handler code here
	rect_state = 1;
}

void CDemoView::OnOperRight() 
{
	// TODO: Add your command handler code here
	rect_state = 2;	
}

void CDemoView::OnOperForward() 
{
	// TODO: Add your command handler code here
	rect_state = 0;
	
}

void CDemoView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnTimer(nIDEvent);

	wheel = pMemView[0] | ((unsigned char)pMemView[1] >> 4);
	leds = pMemView[2] | (pMemView[3]);
	
	UpdateData(TRUE);
	panel->SendMessage(WM_LEDS);
	Get_State();

	if(!rect_state){
		steps++;
		vpos_x += 1 * cos(direction);
		vpos_y += 1 * sin(direction);
	}
	else if(rect_state == 1){
		lregs++;
		direction -=3.14 / (175);
	}
	else if(rect_state == 2){
		rregs ++;
		direction +=3.14 / (175);
	}
	else if(rect_state == 3){
		vpos_x -= 1 * cos(direction);
		vpos_y -= 1 * sin(direction);
	}

	pos_x = vpos_x + vorign_x;
	pos_y = vpos_y + vorign_y;
	if((int)pos_x > (sizeTotal.cx-80)){
		sizeTotal.cx += 120;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}
	if((int)pos_y > (sizeTotal.cy-80)){
		sizeTotal.cy += 120;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}
	if((int)pos_x < 40){
		sizeTotal.cx = sizeTotal.cx + 120;
		vorign_x += 120;
		pos_x = vpos_x + vorign_x;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}
	if((int)pos_y < 40){
		sizeTotal.cy = sizeTotal.cy + 120;
		vorign_y += 120;
		pos_y = vpos_y + vorign_y;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

	state_o = rect_state;
	SetTimer(1,5,NULL);
	Invalidate();
}

void CDemoView::Draw_Rect(CDC* pDC)
{
	double px_start = pos_x + 20 * cos(direction - 3.14 / 6);
	double py_start = pos_y + 20 * sin(direction - 3.14 / 6);
	pDC->MoveTo(int(px_start),int(py_start));

	double px = pos_x + 20 * cos(direction - 3.14 * 3 / 4);
	double py = pos_y + 20 * sin(direction - 3.14 * 3 / 4);
	pDC->LineTo(int(px),int(py));

	px = pos_x + 20 * cos(direction - 3.14 * 5 / 4);
	py = pos_y + 20 * sin(direction - 3.14 * 5 / 4);
	pDC->LineTo(int(px),int(py));

	px = pos_x + 20 * cos(direction + 3.14 / 6);
	py = pos_y + 20 * sin(direction + 3.14 / 6);
	pDC->LineTo(int(px),int(py));

	pDC->LineTo((int)px_start,(int)py_start);

	char sposx[10],sposy[10],spos[30] = "(";
	itoa((int)(vpos_x/8),sposx,10);
	itoa((int)(vpos_y/8),sposy,10);
	strcat(spos,sposx);
	strcat(spos," cm, ");
	strcat(spos,sposy);
	strcat(spos,"cm)");
	pDC->TextOut((int)pos_x,(int)pos_y-40,spos);
}

void CDemoView::OnOperPause() 
{
	// TODO: Add your command handler code here
	KillTimer(1);
}

void CDemoView::OnFileDemo() 
{
	// TODO: Add your command handler code here
	int i;
	if(panelnum == 0){
		fp = fopen("portmessage.dat", "w");
		mouse_enable = 1;
		isdemo = 1;
		panelnum++;
		LPBYTE wpMemView = (LPBYTE)MapViewOfFile(hMemMap,FILE_MAP_WRITE,0,0,0);
		for(i=0; i<16; i++)
			wpMemView[i] = 0;
		rect_state = 5;
		vpos_x = 0;
		vpos_y = 0;
		vorign_x = 100;
		vorign_y = 100;
		direction = 0;
		leds = 0;
		wheel = 0x33;
		steps = 0;
		rregs = lregs = 0;
		state_o = rect_state;
		poweron = 0;
		}
}

LRESULT CDemoView::Demo_over(WPARAM wParam,LPARAM lParam)
{
	OnOperStop();
	isdemo = 0;
	panelnum = 0;
	demogo = 0;
	fclose(fp);
	return 0;
}

void CDemoView::Get_State()
{
	unsigned char lwheel,rwheel,lwheel_o,rwheel_o;
	char lw,rw;

	if(pMemView[4] == pMemView[5] && pMemView[4] !=0){
	if(rect_state == 5){
		rect_state = 4;
		wheel_old = wheel;
	}
	else{
		lwheel = wheel & 0xf0;
		lwheel = lwheel >> 4;
		rwheel = wheel & 0x0f;
		lwheel_o = wheel_old & 0xf0;
		lwheel_o = lwheel_o >> 4;
		rwheel_o = wheel_old & 0x0f;
		lw = State_Table[lwheel_o][lwheel];
		rw = State_Table[rwheel_o][rwheel];

		if(lw == 1 && rw == 2)
			rect_state = 0;
		else if((lw == 1 && rw == 1) || (lw == 1 && rw == 3))
			rect_state = 1;
		else if((lw == 2 && rw == 2) || (lw == 3 && rw == 2))
			rect_state = 2;
		else if(lw == 2 && rw == 1)
			rect_state = 3;
		else if(lw == 3 && rw == 3)
			rect_state = 4;
		else
			rect_state = 5;
		wheel_old = wheel;
	}
	}
	if(state_o != rect_state && rect_state != 4 || (rect_state == 4 && state_o == 5))
		panel->SendMessage(WM_PORT);
	panel->SendMessage(WM_COORD);
}

void CDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnMouseMove(nFlags, point);

	if(mouse_enable){
		pos_x = point.x;
		pos_y = point.y;
		Invalidate();
	}
}

BOOL CDemoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(mouse_enable){
		if(zDelta > 0)
			direction +=3.14 / 18;
		else if(zDelta < 0)
			direction -=3.14 / 18;
		Invalidate();
	}


	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(mouse_enable){
		vorign_x = pos_x;
		vorign_y = pos_y;
		mouse_enable = 0;
		panel = new DemoCP(this);
		panel->Create(IDD_DIALOG1);
		panel->ShowWindow(SW_SHOW);
		Invalidate();
	}

	CScrollView::OnLButtonDown(nFlags, point);
}
