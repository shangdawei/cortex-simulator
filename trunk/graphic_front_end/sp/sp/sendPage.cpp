// sendPage.cpp : 实现文件
//

#include "stdafx.h"
#include "sp.h"
#include "sendPage.h"
#include "vbus/vbus_interface.h"


// CsendPage 对话框

IMPLEMENT_DYNAMIC(CsendPage, CDialog)

CsendPage::CsendPage(CWnd* pParent /*=NULL*/)
	: CDialog(CsendPage::IDD, pParent)
{

}

CsendPage::~CsendPage()
{
}

void CsendPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, s_value_1);
	DDX_Control(pDX, IDC_EDIT1, s_addr_1);
}


BEGIN_MESSAGE_MAP(CsendPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CsendPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// CsendPage 消息处理程序

void CsendPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char m_caddr[64], m_value[64];

	s_addr_1.GetLine(0,(LPTSTR)m_caddr,64);
	s_value_1.GetLine(0,(LPTSTR)m_value,64);
	vb_write(_wtoi((wchar_t *)m_caddr),(char)_wtoi((wchar_t *)m_value));
}
