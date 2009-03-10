// rootPage.cpp : 实现文件
//

#include "stdafx.h"
#include "sp.h"
#include "rootPage.h"


// CrootPage 对话框

IMPLEMENT_DYNAMIC(CrootPage, CDialog)

CrootPage::CrootPage(CWnd* pParent /*=NULL*/)
	: CDialog(CrootPage::IDD, pParent)
{

}

CrootPage::~CrootPage()
{
}

void CrootPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CrootPage, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CrootPage 消息处理程序
