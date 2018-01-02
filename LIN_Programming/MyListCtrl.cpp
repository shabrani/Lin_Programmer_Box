#include "stdafx.h"
#include "LIN_Programming.h"
#include "CTest_Main.h"
#include "MyListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable:4996)

/////////////////////////////////////////////////////////////////////////////
// CMyListCtl

extern void MySetScrollPos(UINT nPos);
extern void MySetScrollPageDown();
extern void MySetScrollPageUp();
extern void MySetScrollLineDown();
extern void MySetScrollLineUp();
extern BOOL g_bListCtlIsFun;
extern int g_nListIndex;

CMyListCtrl::CMyListCtrl()
{
	m_TextColor = RGB(0, 0, 0);
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtl)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_SPEC, &CMyListCtrl::OnNMCustomdrawListSpec)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_DATA, &CMyListCtrl::OnNMCustomdrawListData)
//	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtl::OnCustomDraw)
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtl message handlers

void CMyListCtrl::OnNMCustomdrawListSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	*pResult = 0;

	switch(pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT: // Before an item is drawn
        //request notification for subitems
		if( (pLVCD->nmcd.dwItemSpec % 2)== 0 )
		{
			pLVCD->clrText   = RGB(0, 0, 0);
			pLVCD->clrTextBk = RGB(230, 230, 230);
		}
		else
		{
			pLVCD->clrText   = RGB(0, 0, 0);          
			pLVCD->clrTextBk = RGB(255, 255, 255);
		}
		*pResult = CDRF_DODEFAULT;
        break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM: // Before a subitem is drawn
        *pResult = CDRF_SKIPDEFAULT;
        break;

    default:
        *pResult = CDRF_DODEFAULT;
        break;
    }
}


void CMyListCtrl::OnNMCustomdrawListData(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	*pResult = 0;

	switch(pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT: // Before an item is drawn
        //request notification for subitems
		if( (pLVCD->nmcd.dwItemSpec % 2)== 0 )
		{
			pLVCD->clrText   = RGB(0, 0, 0);
			pLVCD->clrTextBk = RGB(255, 0, 0);
		}
		else
		{
			pLVCD->clrText   = RGB(0, 0, 0);          
			pLVCD->clrTextBk = RGB(0, 255, 0);
		}
		*pResult = CDRF_DODEFAULT;
        break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM: // Before a subitem is drawn
        *pResult = CDRF_SKIPDEFAULT;
        break;

    default:
        *pResult = CDRF_DODEFAULT;
        break;
    }
}

/*
void CMyListCtl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
	int nSubItem = pLVCD->iSubItem;

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.

		*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.

		XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) pLVCD->nmcd.lItemlParam;
		if( !pXLCD )
			return;
		
		COLORREF crText  = pXLCD[nSubItem].crText;
		COLORREF crBkgnd = pXLCD[nSubItem].crBackground;
		
		if( !pXLCD[0].bEnabled )
			crText = m_crGrayText;

		// store the colors back in the NMLVCUSTOMDRAW struct
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
		CRect rect;
		GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);

		rect.left += DrawImage(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);
		DrawText(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);
	
	}
}*/

int CMyListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;	
	return 0;
}


void CMyListCtrl::SetMyTextColor(COLORREF TextColor)
{
	m_TextColor = TextColor;
}

void CMyListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode)
    {
		case SB_PAGEUP:
			MySetScrollPageUp();
			return;
			break;
		case SB_PAGEDOWN:
			MySetScrollPageDown();
			return;
			break;
        case SB_THUMBPOSITION:
			MySetScrollPos(nPos);
			break;
		case SB_THUMBTRACK:
			g_nListIndex = this->m_nListIndex;
			MySetScrollPos(nPos);
			break;
		case SB_LINEDOWN:
			if(g_bListCtlIsFun)
				break;
			else
			{
				MySetScrollLineDown();
				return;
			}
			break;
		case SB_LINEUP:
			if(g_bListCtlIsFun)
				break;
			else
			{
				MySetScrollLineUp();
				return;
			}
			break;
	}	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMyListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP || pMsg->wParam == VK_HOME || pMsg->wParam == VK_END || pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT)
		{
			pMsg->wParam = 0;
		}
	}
	if(pMsg->message == WM_MOUSEWHEEL)
	{
			pMsg->wParam = 0;
	}	
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CMyListCtrl::GetDrawColors(int nItem,
							   int nSubItem,
							   COLORREF& colorText,
							   COLORREF& colorBkgnd)
{
	DWORD dwStyle    = GetStyle();
	DWORD dwExStyle  = GetExtendedStyle();

	COLORREF crText  = colorText;
	COLORREF crBkgnd = colorBkgnd;

	if (GetItemState(nItem, LVIS_SELECTED) && m_bFocusRect)
	{
		if (dwExStyle & LVS_EX_FULLROWSELECT)
		{
			// selected?  if so, draw highlight background
			crText  = m_crHighLightText;
			crBkgnd = m_crHighLight;

			// has focus?  if not, draw gray background
			if (m_hWnd != ::GetFocus())
			{
				if (dwStyle & LVS_SHOWSELALWAYS)
				{
					crText  = m_crWindowText;
					crBkgnd = m_crBtnFace;
				}
				else
				{
					crText  = colorText;
					crBkgnd = colorBkgnd;
				}
			}
		}
	}

	// 해당 Item이 Tracking Item과 동일하면 배경 색을 Tracking Color로 저장한다.
	if( m_nTrackingItem >= 0 )
	{
		if( nItem == m_nTrackingItem )
			crBkgnd = m_crTracking;
	}

	colorText = crText;
	colorBkgnd = crBkgnd;
}

BOOL CMyListCtrl::DeleteAllItems()
{
	int n = GetItemCount();
	for (int i = 0; i < n; i++)
	{
		XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(i);
		if (pXLCD)
			delete [] pXLCD;
		CListCtrl::SetItemData(i, 0);
	}

	return CListCtrl::DeleteAllItems();
}

BOOL CMyListCtrl::DeleteItem(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
		delete [] pXLCD;
	CListCtrl::SetItemData(nItem, 0);
	return CListCtrl::DeleteItem(nItem);
}

BOOL CMyListCtrl::GetBold(int nItem, int nSubItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	// update bold flag
	return pXLCD[nSubItem].bBold;
}

int CMyListCtrl::GetColumns()
{
	return GetHeaderCtrl()->GetItemCount();
}

int CMyListCtrl::GetCurSel()
{
	POSITION pos = GetFirstSelectedItemPosition();
	int nSelectedItem = -1;
	if (pos != NULL)
		nSelectedItem = GetNextSelectedItem(pos);
	return nSelectedItem;
}

BOOL CMyListCtrl::GetEnabled(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	return pXLCD[0].bEnabled;
}

///////////////////////////////////////////////////////////////////////////////
// GetHeaderCheckedState
//
// The GetHeaderCheckedState and SetHeaderCheckedState may be used to toggle
// the checkbox in a column header.
//     0 = no checkbox
//     1 = unchecked
//     2 = checked
//
int CMyListCtrl::GetHeaderCheckedState(int nSubItem)
{
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return -1;

	HDITEM hditem;

	// use the image index (0 or 1) to indicate the checked status
	hditem.mask = HDI_IMAGE;
	m_HeaderCtrl.GetItem(nSubItem, &hditem);
	return hditem.iImage;
}

///////////////////////////////////////////////////////////////////////////////
// GetItemData
//
// The GetItemData and SetItemData functions allow for app-specific data
// to be stored, by using an extra field in the XLISTCTRLDATA struct.
//
DWORD CMyListCtrl::GetItemData(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return 0;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return 0;
	}

	return pXLCD->dwItemData;
}

///////////////////////////////////////////////////////////////////////////////
// GetSubItemRect
BOOL CMyListCtrl::GetSubItemRect(int nItem,
								int nSubItem,
								int nArea,
								CRect& rect)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL bRC = CListCtrl::GetSubItemRect(nItem, nSubItem, nArea, rect);

	// if nSubItem == 0, the rect returned by CListCtrl::GetSubItemRect
	// is the entire row, so use left edge of second subitem
	if (nSubItem == 0)
	{
		if (GetColumns() > 1)
		{
			CRect rect1;
			bRC = GetSubItemRect(nItem, 1, LVIR_BOUNDS, rect1);
			rect.right = rect1.left;
		}
	}

	// 마우스가 올라왔을때 Grid line이 지워지는 문제를 보완
	rect.bottom -= 1;

	return bRC;
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CMyListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	ASSERT(nItem >= 0);
	if (nItem < 0)
		return -1;

	return InsertItem(nItem,
					  lpszItem,
					  m_crWindowText,
					  m_crWindow);
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CMyListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, COLORREF crText, COLORREF crBackground)
{
	ASSERT(nItem >= 0);
	if (nItem < 0)
		return -1;

	int index = CListCtrl::InsertItem(nItem, lpszItem);

	if (index < 0)
		return index;

	XLISTCTRLDATA *pXLCD = new XLISTCTRLDATA [GetColumns()];
	ASSERT(pXLCD);
	if (!pXLCD)
		return -1;

	pXLCD[0].crText       = crText;
	pXLCD[0].crBackground = crBackground;
	CListCtrl::SetItemData(index, (DWORD) pXLCD);

	return index;
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CMyListCtrl::InsertItem(const LVITEM* pItem)
{
	ASSERT(pItem->iItem >= 0);
	if (pItem->iItem < 0)
		return -1;

	int index = CListCtrl::InsertItem(pItem);

	if (index < 0)
		return index;

	XLISTCTRLDATA *pXLCD = new XLISTCTRLDATA [GetColumns()];
	ASSERT(pXLCD);
	if (!pXLCD)
		return -1;

	pXLCD[0].crText       = m_crWindowText;
	pXLCD[0].crBackground = m_crWindow;
	pXLCD[0].nImage       = pItem->iImage;

	CListCtrl::SetItemData(index, (DWORD) pXLCD);

	return index;
}

///////////////////////////////////////////////////////////////////////////////
// SetBold
BOOL CMyListCtrl::SetBold(int nItem, int nSubItem, BOOL bBold)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	// update bold flag
	pXLCD[nSubItem].bBold = bBold;

	UpdateSubItem(nItem, nSubItem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetCurSel
BOOL CMyListCtrl::SetCurSel(int nItem)
{
	return SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,
		LVIS_FOCUSED | LVIS_SELECTED);
}

///////////////////////////////////////////////////////////////////////////////
// SetEnabled
BOOL CMyListCtrl::SetEnabled(int nItem, BOOL bEnable)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	pXLCD[0].bEnabled = bEnable;

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);
	InvalidateRect(&rect);
	UpdateWindow();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetHeaderCheckedState
BOOL CMyListCtrl::SetHeaderCheckedState(int nSubItem, int nCheckedState)
{
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;
	ASSERT(nCheckedState == 0 || nCheckedState == 1 || nCheckedState == 2);

	HDITEM hditem;

	hditem.mask = HDI_IMAGE;
	hditem.iImage = nCheckedState;
	m_HeaderCtrl.SetItem(nSubItem, &hditem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetItem
int CMyListCtrl::SetItem(const LVITEM* pItem)
{
	ASSERT(pItem->iItem >= 0);
	if (pItem->iItem < 0)
		return -1;

	BOOL rc = CListCtrl::SetItem(pItem);

	if (!rc)
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(pItem->iItem);
	if (pXLCD)
	{
		pXLCD[pItem->iSubItem].nImage = pItem->iImage;
		UpdateSubItem(pItem->iItem, pItem->iSubItem);
		rc = TRUE;
	}
	else
	{
		rc = FALSE;
	}

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemData
BOOL CMyListCtrl::SetItemData(int nItem, DWORD dwData)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	pXLCD->dwItemData = dwData;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemImage
BOOL CMyListCtrl::SetItemImage(int nItem, int nSubItem, int nImage, BOOL bImageCenter/*=FALSE*/)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL rc = TRUE;

	if (nItem < 0)
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
	{
		// 기존 데이터와 비교후 틀리면 업데이트
		if( pXLCD[nSubItem].nImage == nImage && 
			pXLCD[nSubItem].bImageCenter == bImageCenter )
			return rc;

		pXLCD[nSubItem].nImage = nImage;
		pXLCD[nSubItem].bImageCenter = bImageCenter;
	}

	UpdateSubItem(nItem, nSubItem);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// GetItemImage
int CMyListCtrl::GetItemImage(int nItem, int nSubItem)
{
	int nImage = -1;

	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return nImage;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return nImage;	

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
		nImage = pXLCD[nSubItem].nImage;

	return nImage;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemText
BOOL CMyListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;
	
	CString	szText(_T(""));
	szText = GetItemText(nItem, nSubItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	if( !szText.Compare( lpszText ) )
		return 0;

	BOOL rc = CListCtrl::SetItemText(nItem, nSubItem, lpszText);

	UpdateSubItem(nItem, nSubItem);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemText
//
// This function will set the text and colors for a subitem.  If lpszText
// is NULL, only the colors will be set.  If a color value is -1, the display
// color will be set to the default Windows color.
//
BOOL CMyListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText,
					COLORREF crText, COLORREF crBackground)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL rc = TRUE;

	if (nItem < 0)
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	if( !pXLCD[nSubItem].crBackground == crBackground && pXLCD[nSubItem].crText == crText )
		return FALSE;

	if (lpszText)
		rc = CListCtrl::SetItemText(nItem, nSubItem, lpszText);
	
	if (pXLCD)
	{
		pXLCD[nSubItem].crText       = (crText == -1) ? m_crWindowText : crText;
		pXLCD[nSubItem].crBackground = (crBackground == -1) ? m_crWindow : crBackground;
	}

	UpdateSubItem(nItem, nSubItem);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemTextColor
//
BOOL CMyListCtrl::SetItemTextColor(int nItem, int nSubItem, COLORREF crText, COLORREF crBackground)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	if (nItem < 0)
		return FALSE;

	XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) CListCtrl::GetItemData(nItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	if( pXLCD[nSubItem].crBackground == crBackground &&
		pXLCD[nSubItem].crText == crText )
		return FALSE;

	if (pXLCD)
	{
		pXLCD[nSubItem].crText       = (crText == -1) ? m_crWindowText : crText;
		pXLCD[nSubItem].crBackground = (crBackground == -1) ? m_crWindow : crBackground;
	}

	UpdateSubItem(nItem, nSubItem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// UpdateSubItem
void CMyListCtrl::UpdateSubItem(int nItem, int nSubItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return;

	CRect rect;
	if (nSubItem == -1)
		GetItemRect(nItem, &rect, LVIR_BOUNDS);
	else
		GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);

	InvalidateRect(&rect);
	UpdateWindow();
}

void CMyListCtrl::SetRowHeight(int nRowHeight)
{
	CFont font;
	LOGFONT logfont;

	CDC *pDC = GetDC();
	if( !pDC ) return;

	int nRevision=7;

	logfont.lfHeight = -MulDiv(nRowHeight-nRevision, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
	ReleaseDC( pDC );

	logfont.lfEscapement	= 0;
	logfont.lfOrientation	= 0;
	logfont.lfWeight		= FW_NORMAL;
	logfont.lfItalic		= FALSE;
	logfont.lfUnderline		= FALSE;
	logfont.lfStrikeOut		= FALSE;
	logfont.lfCharSet		= ANSI_CHARSET;
	logfont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	logfont.lfQuality		= PROOF_QUALITY;
	logfont.lfPitchAndFamily= DEFAULT_PITCH;
	_tcscpy(logfont.lfFaceName, _T("System"));
	font.CreateFontIndirect(&logfont);

	SetFont(&font);

	font.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// DrawImage
int CMyListCtrl::DrawImage(int nItem,
						  int nSubItem,
						  CDC* pDC,
						  COLORREF crText,
						  COLORREF crBkgnd,
						  CRect rect,
  						  XLISTCTRLDATA *pXLCD)
{
	GetDrawColors(nItem, nSubItem, crText, crBkgnd);

	pDC->FillSolidRect(&rect, crBkgnd);

	CPen newPen(PS_SOLID, 1, m_crUnderLine);
	CPen *pOldPen = pDC->SelectObject(&newPen);	
	if( m_bUnderLine )
	{
		pDC->MoveTo( rect.left-1, rect.bottom );
		pDC->LineTo( rect.right+1, rect.bottom );
	}

	int nWidth = 0;

	CImageList* pImageList = GetImageList(LVSIL_NORMAL);
	if(pImageList)
	{
		SIZE sizeImage;
		sizeImage.cx = sizeImage.cy = 0;
		IMAGEINFO info;

		int nImage = -1;
		if (pXLCD)
			nImage = pXLCD[nSubItem].nImage;

		if (nImage == -1)
			return 0;

		if (pImageList->GetImageInfo(nImage, &info))
		{
			sizeImage.cx = info.rcImage.right - info.rcImage.left;
			sizeImage.cy = info.rcImage.bottom - info.rcImage.top;
		}
		
		if (nImage >= 0)
		{
			if (rect.Width() > 0)
			{
				if( pXLCD[nSubItem].bImageCenter )
					rect.left += rect.Width()/2-sizeImage.cx/2;
				else
					rect.left += m_HeaderCtrl.GetSpacing();

				POINT pt;					
				pt.y = rect.CenterPoint().y - (sizeImage.cy >> 1);
				pt.x = rect.left;
				
				SIZE size;
				size.cx = rect.Width() < sizeImage.cx ? rect.Width() : sizeImage.cx;
				size.cy = rect.Height() < sizeImage.cy ? rect.Height() : sizeImage.cy;

				COLORREF rgb = pImageList->GetBkColor();	// save image list background color					
				pImageList->SetBkColor(crBkgnd);			// set image list background color
				pImageList->DrawIndirect(pDC, nImage, pt, size, CPoint(0, 0));
				pImageList->SetBkColor(rgb);
			
				if( pXLCD[nSubItem].bImageCenter )
					nWidth = rect.right;
				else
					nWidth = sizeImage.cx + m_HeaderCtrl.GetSpacing();
			}
		}
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();

	return nWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawText
void CMyListCtrl::DrawText(int nItem,
						  int nSubItem,
						  CDC *pDC,
						  COLORREF crText,
						  COLORREF crBkgnd,
						  CRect& rect,
						  XLISTCTRLDATA *pXLCD)
{
	ASSERT(pDC);
	ASSERT(pXLCD);

	CRect rcNew;
	rcNew = rect;

	CFont *pOldFont = pDC->SelectObject(m_pTextFont);
	CPen newPen(PS_SOLID, 1, m_crUnderLine);
	CPen *pOldPen = pDC->SelectObject(&newPen);

	if( nSubItem == m_nStatusColumn )
	{
		COLORREF crTemp = m_crWindow;
		GetDrawColors(nItem, nSubItem, crText, crTemp);

		pDC->FillSolidRect(&rect, crTemp);
		rcNew.top	+= 1;
		rcNew.left	+= 2;
		rcNew.right	-= 2;
		rcNew.bottom-= 2;
		pDC->FillSolidRect(&rcNew, crBkgnd);
	}
	else
	{
		GetDrawColors(nItem, nSubItem, crText, crBkgnd);
		pDC->FillSolidRect(&rect, crBkgnd);
	}

	CString str(_T(""));
	str = GetItemText(nItem, nSubItem);	
	if (!str.IsEmpty())
	{
		// get text justification
		HDITEM hditem;
		hditem.mask = HDI_FORMAT;
		m_HeaderCtrl.GetItem(nSubItem, &hditem);
		int nFmt = hditem.fmt & HDF_JUSTIFYMASK;
		UINT nFormat = DT_VCENTER | DT_SINGLELINE;
		if (nFmt == HDF_CENTER)
		{
			nFormat |= DT_CENTER;
		}
		else if (nFmt == HDF_LEFT)
		{
			nFormat |= DT_LEFT;
			rcNew.left += 4;
		}
		else
		{
			nFormat |= DT_RIGHT;
		}

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(crText);
		pDC->SetBkColor(crBkgnd);
		rcNew.OffsetRect(0, 1);
		pDC->DrawText(str, &rcNew, nFormat);
	}

	if( m_bUnderLine )
	{
		pDC->MoveTo( rect.left-1, rect.bottom );
		pDC->LineTo( rect.right+1, rect.bottom );
	}

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// SubclassHeaderControl
void CMyListCtrl::SubclassHeaderControl()
{
	if (m_bHeaderIsSubclassed)
		return;

	// if the list control has a header control window, then
	// subclass it

	// Thanks to Alberto Gattegno and Alon Peleg젨and their article
	// "A Multiline Header Control Inside a CListCtrl" for easy way
	// to determine if the header control exists.

	CHeaderCtrl* pHeader = GetHeaderCtrl();
	if (pHeader)
	{
		VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));
		m_bHeaderIsSubclassed = TRUE;
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CMyListCtrl::OnPaint()
{
	Default();
	
	if(GetItemCount() <= 0)
	{
		CDC* pDC = GetDC();
		int nSavedDC = pDC->SaveDC();

		CRect rc;
		GetWindowRect(&rc);
		ScreenToClient(&rc);
		CHeaderCtrl* pHC = GetHeaderCtrl();
		if (pHC != NULL)
		{
			CRect rcH;
			pHC->GetItemRect(0, &rcH);
			rc.top += rcH.bottom;
		}

		CString strText = m_strNoItemMsg;
		COLORREF crText = m_crWindowText;
		COLORREF crBkgnd = m_crWindow;		
		pDC->SetTextColor(crText);
		pDC->SetBkColor(crBkgnd);
		pDC->SelectStockObject(ANSI_VAR_FONT);
		pDC->FillSolidRect(&rc, crBkgnd);

		rc.top += 10;
		pDC->DrawText(strText, -1, rc, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP);

		pDC->RestoreDC(nSavedDC);
		ReleaseDC(pDC);
	}
	m_HeaderCtrl.RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CMyListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
#if 1
	CRect clip;
	m_HeaderCtrl.GetWindowRect(&clip);		// get rect of the control
	ScreenToClient(&clip);
	pDC->ExcludeClipRect(&clip);
	pDC->GetClipBox(&clip);
	pDC->FillSolidRect(clip, m_crWindow);
	return TRUE;
#else
	return TRUE;	
#endif
	return CMyListCtrl::OnEraseBkgnd(pDC);
}
