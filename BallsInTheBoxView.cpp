
// BallsInTheBoxView.cpp : implementation of the CBallsInTheBoxView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BallsInTheBox.h"
#endif

#include "BallsInTheBoxDoc.h"
#include "BallsInTheBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBallsInTheBoxView

IMPLEMENT_DYNCREATE(CBallsInTheBoxView, CView)

BEGIN_MESSAGE_MAP(CBallsInTheBoxView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
  ON_WM_TIMER()
END_MESSAGE_MAP()

// CBallsInTheBoxView construction/destruction

CBallsInTheBoxView::CBallsInTheBoxView()
{
	// TODO: add construction code here

}

CBallsInTheBoxView::~CBallsInTheBoxView()
{
}

BOOL CBallsInTheBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBallsInTheBoxView drawing

void CBallsInTheBoxView::OnDraw(CDC* pDC)
{
	CBallsInTheBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

  CRect rect;
  GetClientRect(&rect);

  if (pDoc->m_balls.empty())
  {
    pDoc->initBalls(rect);
    m_nTimer = SetTimer(1, 10, NULL);
  }

  CDC memDC;
  memDC.CreateCompatibleDC(pDC);

  CBitmap bmp;
  bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
  CBitmap *pOldBitmap = memDC.SelectObject(&bmp);

  // Fill in the control with the standard background color
  memDC.FillSolidRect(&rect, RGB(255, 255, 255));

  for (Ball b : pDoc->m_balls)
  {
    CPen pen(PS_SOLID, 1, b.color);
    CPen* def_pen = memDC.SelectObject(&pen);
    CBrush brush(b.color);
    CBrush* defBrush = memDC.SelectObject(&brush);

    CRect r(int(b.p.x - b.radius), int(b.p.y - b.radius), int(b.p.x + b.radius), int(b.p.y + b.radius));
    memDC.Ellipse(&r);

    memDC.SelectObject(&def_pen);
    memDC.SelectObject(&defBrush);
  }

  memDC.SetBkMode(TRANSPARENT);


  Vector2<float> total1;
  int pos1 = 20;
  memDC.TextOut(200, pos1, CString("Impulse"));
  pos1 += 20;
  for (Ball b : pDoc->m_balls)
  {
    total1 += b.v;
    CString str;
    str.Format(_T("     %6.2f %6.2f"), b.v.x, b.v.y);
    memDC.TextOut(200, pos1, str);
    pos1 += 20;
  }
  CString strTotal1;
  strTotal1.Format(_T("Sum: %6.2f %6.2f"), total1.x, total1.y);
  memDC.TextOut(200, pos1, strTotal1);


  float total = 0;
  int pos = 20;
  memDC.TextOut(20, pos, CString("Energy"));
  pos += 20;
  for (Ball b : pDoc->m_balls)
  {
	  float energy = b.v * b.v;
    total += energy;
    CString str;
    str.Format(_T("     %f"), energy);
    memDC.TextOut(20, pos, str);
    pos += 20;
  }
  CString strTotal;
  strTotal.Format(_T("Sum: %f"), total);
  memDC.TextOut(20, pos, strTotal);


  // Copy everything to the control
  pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
  // Restore the old bitmap to avoid memory leaks
  memDC.SelectObject(pOldBitmap);
}

void CBallsInTheBoxView::OnTimer(UINT nIDEvent)
{
  if (nIDEvent != 1) return;
  // TODO: Add your message handler code here and/or call default

  CBallsInTheBoxDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;

  CRect rcClient;
  GetClientRect(&rcClient);
  pDoc->step(rcClient, 1.0f);

  InvalidateRect(NULL, 0);
}


void CBallsInTheBoxView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBallsInTheBoxView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBallsInTheBoxView diagnostics

#ifdef _DEBUG
void CBallsInTheBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CBallsInTheBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBallsInTheBoxDoc* CBallsInTheBoxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallsInTheBoxDoc)));
	return (CBallsInTheBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CBallsInTheBoxView message handlers
