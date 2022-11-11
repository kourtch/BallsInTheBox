
// BallsInTheBoxView.h : interface of the CBallsInTheBoxView class
//

#pragma once


class CBallsInTheBoxView : public CView
{
protected: // create from serialization only
	CBallsInTheBoxView();
	DECLARE_DYNCREATE(CBallsInTheBoxView)

// Attributes
public:
	CBallsInTheBoxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBallsInTheBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


  UINT m_nTimer;

// Generated message map functions
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnTimer(UINT nIDEvent);
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BallsInTheBoxView.cpp
inline CBallsInTheBoxDoc* CBallsInTheBoxView::GetDocument() const
   { return reinterpret_cast<CBallsInTheBoxDoc*>(m_pDocument); }
#endif

