
// flagView.cpp: CflagView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "flag.h"
#endif

#include "flagDoc.h"
#include "flagView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflagView

IMPLEMENT_DYNCREATE(CflagView, CView)

BEGIN_MESSAGE_MAP(CflagView, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CflagView 建構/解構

CflagView::CflagView() noexcept
{
	// TODO: 在此加入建構程式碼

}

CflagView::~CflagView()
{
}

BOOL CflagView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CflagView 繪圖

void CflagView::OnDraw(CDC* pDC)//電腦需要重劃視窗時就會自己呼叫ondraw
{
	CflagDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	double cx, cy,rx,ry;
	double r,xs,ys,Inxs,Inys;
	const static double PI = 3.14159265359;
	const static double val = PI / 180;//角度小技巧
	//依據視窗大小動態改變五芒星
	if (pt1.x == -1)
	{
		if (page < 3)
			page++;
		else if (page == 3)
			page = 1;
	}
	CPen red_pen, blue_pen, white_pen, *old_pen;//因oldpen要存的是舊筆的指標 所以宣告為指標
	CBrush red_brush, blue_brush, white_brush, *old_brush;
	red_brush.CreateSolidBrush(RGB(255, 0, 0));
	red_pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	white_brush.CreateSolidBrush(RGB(255, 255, 255));
	white_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	blue_brush.CreateSolidBrush(RGB(0, 0, 255));
	blue_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	CRect r1;
	GetClientRect(&r1);//為了回傳視窗多高多寬
	int H = r1.Height();
	int W = r1.Width();
	if (page == 1)
	{



		old_pen = pDC->SelectObject(&red_pen);//後半段會指定新筆(&是取他的地址/指標)因為他要的是指標 前半段會回傳被取代掉的那隻舊筆的指標(地址)
		old_brush = pDC->SelectObject(&red_brush);//後半段傳進新brush的地址 現在系統拿紅刷 並把舊刷地址傳進old_brush


		rx = W;
		ry = H;
		if (W >= (H * 3 / 2))
		{
			ys = H;
			xs = ys * 3 / 2;
			pDC->MoveTo(xs, 0);
			pDC->LineTo(xs, ys);
		}
		else
		{
			xs = W;
			ys = xs * 2 / 3;
			pDC->MoveTo(0, ys);
			pDC->LineTo(xs, ys);
		}
		pDC->FloodFill(xs*2.0 / 3.0, ys*2.0 / 3.0, RGB(255, 0, 0));//brush從哪個點開始蔓延 碰到哪個顏色時就停
		//記得除2.0 /2會沒有小數點   


		pDC->SelectObject(blue_pen);
		pDC->SelectObject(blue_brush);
		Inys = ys / 2;
		Inxs = xs / 2;
		pDC->MoveTo(Inxs, 0);
		pDC->LineTo(Inxs, Inys);
		pDC->MoveTo(0, Inys);
		pDC->LineTo(Inxs, Inys);
		pDC->FloodFill(Inxs / 2.0, Inys / 2.0, RGB(0, 0, 255));
	//	pDC->SelectObject(old_pen);//用完色筆記得換回原來系統的筆
	//	pDC->SelectObject(old_brush);
	//	pDC->SelectObject(blue_pen);
	//	pDC->SelectObject(blue_brush);
		CRect OutCircleRect(Inxs*15.0 / 60, Inys*5.0 / 40, Inxs*45.0 / 60, Inys * 35 / 40);
		pDC->Ellipse(OutCircleRect);

		pDC->SelectObject(old_brush);//用完色筆記得換回原來系統的筆
		pDC->SelectObject(white_pen);
		cx = Inxs / 2.0;
		cy = Inys / 2.0;
		r = Inxs * 15 / 60;//OutCircle半徑
		for (int i = 0; i <= 11; i++)
		{
			pDC->MoveTo(cx + r * cos(30 * i*val), cy - r * sin(30 * i*val));
			pDC->LineTo(cx + r * cos((150 + i * 30) * val), cy - r * sin((150 + i * 30) * val));
			//pDC->MoveTo(cx + r * cos(30 * i*val), cy - r * sin(30 * i*val));
			pDC->MoveTo(cx + r * cos(30 * i*val), cy - r * sin(30 * i*val));
			pDC->LineTo(cx + r * cos((210 + i * 30) * val), cy - r * sin((210 + i * 30) * val));

		}
		for (int i = 0; i <= 11; i++)
		{
			pDC->FloodFill(cx + r / 2.0 * cos(30 * i*val), cy - r / 2.0 * sin(30 * i*val), RGB(255, 255, 255));
		}
		pDC->SelectObject(blue_brush);
		CRect RingCircleRect(Inxs*21.5 / 60, Inys*11.5 / 40, Inxs*38.5 / 60, Inys * 28.5 / 40);//左上x,y 右下x,y
		pDC->Ellipse(RingCircleRect);
		pDC->SelectObject(old_brush);
		CRect InCircleRect(Inxs*22.5 / 60, Inys*12.5 / 40, Inxs*37.5 / 60, Inys * 27.5 / 40);
		pDC->Ellipse(InCircleRect);

		pDC->FloodFill(cx + r - r / 1000.0, cy - r + r / 100.0, RGB(0, 0, 255));

		pDC->SelectObject(old_pen);
	}
	if (page == 2)
	{
		rx = W;
		ry = H;
		old_pen = pDC->SelectObject(&red_pen);
		if (W >= (H * 3 / 2))
		{
			ys = H;
			xs = ys * 3 / 2;
			pDC->MoveTo(xs, 0);
			pDC->LineTo(xs, ys/2.0);
			pDC->SelectObject(old_pen);
			pDC->MoveTo(xs, ys / 2.0);
			pDC->LineTo(xs, ys);
		}
		else
		{
			xs = W;
			ys = xs * 2 / 3;
			pDC->SelectObject(old_pen);
			pDC->MoveTo(0, ys);
			pDC->LineTo(xs, ys);
		}
		pDC->SelectObject(red_pen);
		pDC->MoveTo(0, ys / 2.0);
		pDC->LineTo(xs, ys / 2.0);
		pDC->SelectObject(old_pen);
		old_brush = pDC->SelectObject(&red_brush);
		pDC->FloodFill(xs/2.0, ys/4.0, RGB(255, 0, 0));
		pDC->SelectObject(old_brush);

	}
	if (page == 3)
	{
		if (W >= (H * 3 / 2))
		{
			ys = H;
			xs = ys * 3 / 2;
			pDC->MoveTo(xs, 0);
			pDC->LineTo(xs, ys);
		}
		else
		{
			xs = W;
			ys = xs * 2 / 3;
			pDC->MoveTo(0, ys);
			pDC->LineTo(xs, ys);
		}
		old_pen = pDC->SelectObject(&red_pen);
		old_brush = pDC->SelectObject(&red_brush);
		CRect CircleRect(xs*4.5/15, ys*1.0/5, xs*10.5 / 15, ys*4.0/5);
		pDC->Ellipse(CircleRect);
		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);
	}
	pt1.x = -2;																		 
	// TODO: 在此加入原生資料的描繪程式碼
}



// CflagView 列印

BOOL CflagView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CflagView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CflagView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}
// CflagView 診斷

#ifdef _DEBUG
void CflagView::AssertValid() const
{
	CView::AssertValid();
}

void CflagView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CflagDoc* CflagView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CflagDoc)));
	return (CflagDoc*)m_pDocument;
}
#endif //_DEBUG


// CflagView 訊息處理常式

//void CflagView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	//
//	pt1 = point;
//	//Invalidate();
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//
//	CView::OnLButtonDown(nFlags, point);
//}


void CflagView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt1.x = -1;
	Invalidate();//有這行視窗就會重繪
	CView::OnLButtonUp(nFlags, point);
}
