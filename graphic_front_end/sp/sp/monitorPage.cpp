// monitorPage.cpp : 实现文件
//

#include "stdafx.h"
#include "sp.h"
#include "monitorPage.h"
#include "vbus/vbus_interface.h"


// CmonitorPage 对话框

IMPLEMENT_DYNAMIC(CmonitorPage, CDialog)

CmonitorPage::CmonitorPage(CWnd* pParent /*=NULL*/)
	: CDialog(CmonitorPage::IDD, pParent)
{

}

CmonitorPage::~CmonitorPage()
{
}

void CmonitorPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_AddrEdit);
	DDX_Control(pDX, IDC_LIST2, m_monitorList);
}


BEGIN_MESSAGE_MAP(CmonitorPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CmonitorPage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CmonitorPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CmonitorPage::OnBnClickedButton2)
END_MESSAGE_MAP()


// CmonitorPage 消息处理程序

void CmonitorPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char m_caddr[64];

	m_AddrEdit.GetLine(0,(LPTSTR)m_caddr);
	if(m_caddr[0] !='\0'){
		/*for(int i = 0; i< m_monitorList.GetItemCount(); i++){
			CString s_temp(m_caddr);
			if(s_temp == m_monitorList.GetItemText(i,0))
				return;
		}*/
		int insertPos = m_monitorList.GetItemCount();
		m_monitorList.InsertItem(insertPos,(LPCTSTR)m_caddr);
		ReloadData();
	}
}

BOOL CmonitorPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_monitorList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_monitorList.InsertColumn(0,(LPCTSTR)_T("Address"), LVCFMT_LEFT, 220);
	m_monitorList.InsertColumn(1,(LPCTSTR)_T("Value"), LVCFMT_LEFT, 260);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CmonitorPage::ReloadData()
{
	for(int i = 0; i < m_monitorList.GetItemCount(); i++){
		CString s_addr = m_monitorList.GetItemText(i,0);
		int m_address = _wtoi(s_addr.GetBuffer(0));
		int m_data = (int)vb_read(m_address);
		wchar_t s_data[128];
		_itow(m_data, s_data, 10);
		m_monitorList.SetItemText(i, 1, (LPCTSTR)s_data);
	}
}
void CmonitorPage::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ReloadData();
}

void CmonitorPage::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0; i< m_monitorList.GetItemCount(); i++){
		if(m_monitorList.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED){
			m_monitorList.DeleteItem(i);
			i--;
		}
	}
}
