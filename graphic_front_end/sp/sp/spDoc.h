// spDoc.h : CspDoc 类的接口
//


#pragma once


class CspDoc : public CDocument
{
protected: // 仅从序列化创建
	CspDoc();
	DECLARE_DYNCREATE(CspDoc)

public:
	int m_nViewType;	//View type of the right window
	int m_nTabIndex;	//Tab index of the right window

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CspDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


