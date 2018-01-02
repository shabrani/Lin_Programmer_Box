#include "stdafx.h"
#include "MyHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXHeaderCtrl

CMyHeaderCtrl::CMyHeaderCtrl()
{
	m_bDoubleBuffer = TRUE;
	m_iSpacing = 6;
	m_sizeArrow.cx = 8;
	m_sizeArrow.cy = 8;
	m_sizeImage.cx = 0;
	m_sizeImage.cy = 0;
	m_bStaticBorder = FALSE;
	m_nDontDropCursor = 0;
	m_bResizing = FALSE;
	m_nClickFlags = 0;

	m_cr3DHighLight = ::GetSysColor(COLOR_3DHIGHLIGHT);
	m_cr3DShadow    = ::GetSysColor(COLOR_3DSHADOW);
	m_cr3DFace      = ::GetSysColor(COLOR_3DFACE);
	m_crBtnText     = ::GetSysColor(COLOR_BTNTEXT);	

	// JCW_+ 2008.04.12 START
	m_bTracking		= FALSE;
	m_bLMouseDown	= FALSE;

	m_bFlat = FALSE;
	m_colorHeader = RGB(0,0,0);

	m_nHeight		= 30;
	m_pTextFont		= NULL;
	// JCW_+ 2008.04.12 END
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CMyHeaderCtrl::~CMyHeaderCtrl()
{
}

///////////////////////////////////////////////////////////////////////////////
//
IMPLEMENT_DYNCREATE(CMyHeaderCtrl, CHeaderCtrl)

BEGIN_MESSAGE_MAP(CMyHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CXHeaderCtrl)
	ON_MESSAGE(HDM_INSERTITEM, OnInsertItem)
	ON_MESSAGE(HDM_DELETEITEM, OnDeleteItem)
	ON_MESSAGE(HDM_SETIMAGELIST, OnSetImageList)
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ModifyProperty
BOOL CMyHeaderCtrl::ModifyProperty(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case FH_PROPERTY_SPACING:
			m_iSpacing = (int)lParam;
			break;

		case FH_PROPERTY_ARROW:
			m_sizeArrow.cx = LOWORD(lParam);
			m_sizeArrow.cy = HIWORD(lParam);
			break;

		case FH_PROPERTY_STATICBORDER:
			m_bStaticBorder = (BOOL)lParam;
			break;

		case FH_PROPERTY_DONTDROPCURSOR:
			m_nDontDropCursor = (UINT)lParam;
			break;

		default:
			return FALSE;
	}

	Invalidate();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DrawItem
void CMyHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT)
{
	ASSERT(FALSE);  // must override for self draw header controls
}

///////////////////////////////////////////////////////////////////////////////
// DrawItem
void CMyHeaderCtrl::DrawItem(CDC* pDC, CRect rect, LPHDITEM lphdi)
{
	ASSERT(lphdi->mask & HDI_FORMAT);

	int iWidth = 0;

	CBitmap* pBitmap = NULL;
	BITMAP BitmapInfo;

	if (lphdi->fmt & HDF_BITMAP)
	{
		ASSERT(lphdi->mask & HDI_BITMAP);
		ASSERT(lphdi->hbm);

		pBitmap = CBitmap::FromHandle(lphdi->hbm);
		if (pBitmap)
			VERIFY(pBitmap->GetObject(sizeof(BITMAP), &BitmapInfo));
	}

	rect.left += ((iWidth = DrawImage(pDC, rect, lphdi, FALSE)) != 0) ? iWidth + m_iSpacing : 0;
	rect.right -= ((iWidth = DrawBitmap(pDC, rect, lphdi, pBitmap, &BitmapInfo, TRUE)) != 0) ? 
		iWidth + m_iSpacing : 0;

	DrawText(pDC, rect, lphdi);
}

///////////////////////////////////////////////////////////////////////////////
// DrawImage
int CMyHeaderCtrl::DrawImage(CDC* pDC, CRect rect, LPHDITEM lphdi, BOOL bRight)
{
	CImageList* pImageList = GetImageList();
	int iWidth = 0;

	if (lphdi->iImage != XHEADERCTRL_NO_IMAGE)
	{
		if (pImageList)
		{
			if (rect.Width() > 0)
			{
				POINT point;

				point.y = rect.CenterPoint().y - (m_sizeImage.cy >> 1);

				if (bRight)
					point.x = rect.right - m_sizeImage.cx;
				else
					point.x = rect.left;

				SIZE size;
				size.cx = rect.Width()<m_sizeImage.cx ? rect.Width():m_sizeImage.cx;
				size.cy = m_sizeImage.cy;

				// save image list background color
				COLORREF rgb = pImageList->GetBkColor();

				// set image list background color to same as header control
				pImageList->SetBkColor(pDC->GetBkColor());
				pImageList->DrawIndirect(pDC, lphdi->iImage, point, size, CPoint(0, 0));
				pImageList->SetBkColor(rgb);

				iWidth = m_sizeImage.cx;
			}
		}
	}

	return iWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawBitmap
int CMyHeaderCtrl::DrawBitmap(CDC* pDC, 
								CRect rect, 
								LPHDITEM lphdi, 
								CBitmap* pBitmap, 
								BITMAP* pBitmapInfo, 
								BOOL bRight)
{
	UNUSED_ALWAYS(lphdi);

	int iWidth = 0;

	if (pBitmap)
	{
		iWidth = pBitmapInfo->bmWidth;
		if (iWidth <= rect.Width() && rect.Width() > 0)
		{
			POINT point;

			// JCW_U 2008.04.12 START
			//point.y = rect.CenterPoint().y - (pBitmapInfo->bmHeight >> 1);
			point.y = rect.bottom - pBitmapInfo->bmHeight - 10;
			// JCW_U 2008.04.12 END

			if (bRight)
				point.x = rect.right - iWidth;
			else
				point.x = rect.left;

			CDC dc;
			if (dc.CreateCompatibleDC(pDC) == TRUE) 
			{
				VERIFY(dc.SelectObject(pBitmap));
				iWidth = pDC->BitBlt(
					point.x, point.y, 
					pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, 
					&dc, 
					0, 0, 
					SRCCOPY
				) ? iWidth:0;
			}
			else 
				iWidth = 0;
		}
		else
			iWidth = 0;
	}

	return iWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawText
int CMyHeaderCtrl::DrawText(CDC* pDC, CRect rect, LPHDITEM lphdi)
{
	// JCW_+ 2008.04.12 START
	pDC->SetBkMode(TRANSPARENT);
	// JCW_+ 2008.04.12 END

	CSize size;

	//pDC->SetTextColor(RGB(0,0,255));
	pDC->SetTextColor(m_colorHeader);

	if (rect.Width() > 0 && lphdi->mask & HDI_TEXT && lphdi->fmt & HDF_STRING)
	{
		size = pDC->GetTextExtent(lphdi->pszText);

		// JCW_U 2008.04.12 START
		rect.top = 5;
		// always center column headers
		pDC->DrawText(lphdi->pszText, -1, rect, 
			DT_CENTER|DT_END_ELLIPSIS|DT_SINGLELINE/*|DT_VCENTER*/);
		// JCW_U 2008.04.12 END
	}

	size.cx = rect.Width()>size.cx ? size.cx:rect.Width();
	return size.cx>0 ? size.cx:0;
}

///////////////////////////////////////////////////////////////////////////////
// OnInsertItem
LRESULT CMyHeaderCtrl::OnInsertItem(WPARAM, LPARAM)
{
	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnDeleteItem
LRESULT CMyHeaderCtrl::OnDeleteItem(WPARAM, LPARAM)
{
	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnSetImageList
LRESULT CMyHeaderCtrl::OnSetImageList(WPARAM, LPARAM lParam)
{
	CImageList* pImageList;
	pImageList = CImageList::FromHandle((HIMAGELIST)lParam);

	IMAGEINFO info;
	if (pImageList->GetImageInfo(0, &info))
	{
		m_sizeImage.cx = info.rcImage.right - info.rcImage.left;
		m_sizeImage.cy = info.rcImage.bottom - info.rcImage.top;
	}

	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnLayout
LRESULT CMyHeaderCtrl::OnLayout(WPARAM, LPARAM lParam)
{
// JCW_U 2008.04.12 START
#if 1
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

	if( m_nHeight > 0 )
	{
		LPHDLAYOUT lphdlayout = (LPHDLAYOUT)lParam;
		RECT *prc = lphdlayout->prc;
		WINDOWPOS *pwpos = lphdlayout->pwpos;

		pwpos->cy = m_nHeight;
		prc->top = m_nHeight;
	}
	return lResult;	
#else
	LPHDLAYOUT lphdlayout = (LPHDLAYOUT)lParam;

	if (m_bStaticBorder)
		lphdlayout->prc->right += GetSystemMetrics(SM_CXBORDER)*2;

	return CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
#endif
// JCW_U 2008.04.12 END
}

///////////////////////////////////////////////////////////////////////////////
// OnSysColorChange
void CMyHeaderCtrl::OnSysColorChange() 
{
	TRACE(_T("in CXHeaderCtrl::OnSysColorChange\n"));

	CHeaderCtrl::OnSysColorChange();
	
	m_cr3DHighLight = ::GetSysColor(COLOR_3DHIGHLIGHT);
	m_cr3DShadow    = ::GetSysColor(COLOR_3DSHADOW);
	m_cr3DFace      = ::GetSysColor(COLOR_3DFACE);
	m_crBtnText     = ::GetSysColor(COLOR_BTNTEXT);
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CMyHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);
	return TRUE;
}
