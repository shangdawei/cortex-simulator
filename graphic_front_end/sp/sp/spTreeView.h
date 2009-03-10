#pragma once


// CspTreeView ��ͼ

class CspTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CspTreeView)

protected:
	CspTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CspTreeView();

protected:
	HTREEITEM root;			//The node of the tree
	HTREEITEM m_subtree[4];

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:		//User reload function
	void CspTreeView::OnInitialUpdate();

public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


