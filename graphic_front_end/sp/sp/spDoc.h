// spDoc.h : CspDoc ��Ľӿ�
//


#pragma once


class CspDoc : public CDocument
{
protected: // �������л�����
	CspDoc();
	DECLARE_DYNCREATE(CspDoc)

public:
	int m_nViewType;	//View type of the right window
	int m_nTabIndex;	//Tab index of the right window

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CspDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


