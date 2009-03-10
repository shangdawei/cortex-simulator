// spView.h : CspView ��Ľӿ�
//


#pragma once


class CspView : public CView
{
protected: // �������л�����
	CspView();
	DECLARE_DYNCREATE(CspView)

// ����
public:
	CspDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CspView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // spView.cpp �еĵ��԰汾
inline CspDoc* CspView::GetDocument() const
   { return reinterpret_cast<CspDoc*>(m_pDocument); }
#endif

