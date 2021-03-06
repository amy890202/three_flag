
// flagView.h: CflagView 類別的介面
//

#pragma once


class CflagView : public CView
{
protected: // 僅從序列化建立
	CflagView() noexcept;
	DECLARE_DYNCREATE(CflagView)


// 屬性
public:
	CflagDoc* GetDocument() const;

// 作業
public:

private:
	CPoint pt1;//兩個座標點(滑鼠點進去與彈起來時)
	int page = 1;
// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CflagView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 對 flagView.cpp 中的版本進行偵錯
inline CflagDoc* CflagView::GetDocument() const
   { return reinterpret_cast<CflagDoc*>(m_pDocument); }
#endif

