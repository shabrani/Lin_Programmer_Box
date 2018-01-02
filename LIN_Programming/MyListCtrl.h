#if !defined(AFX_MYLISTCTL_H__574961E0_C33C_11D7_9142_0050FC6ED3B6__INCLUDED_)
#define AFX_MYLISTCTL_H__574961E0_C33C_11D7_9142_0050FC6ED3B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxcmn.h"
#include "MyHeaderCtrl.h"

typedef struct tagNMITEM
{
	HWND	hwndFrom;
	int		iItem;
	int		iSubItem;
	CString sText;
} NMITEM;

struct XLISTCTRLDATA
{
	XLISTCTRLDATA()
	{
		bEnabled             = TRUE;
		crText               = ::GetSysColor(COLOR_WINDOWTEXT);
		crBackground         = RGB(255,255,255);//::GetSysColor(COLOR_WINDOW);
		bBold                = FALSE;
		nImage               = -1;
		bImageCenter		 = FALSE;

		crBar				 = RGB(0,200,0);

		nTextLeftmode		 = 0;

		dwItemData           = NULL;
	}

	BOOL			bEnabled;				// TRUE = enabled, FALSE = disabled (gray text)
	BOOL			bBold;					// TRUE = display bold text
	int				nImage;					// index in image list, else -1
	BOOL			bImageCenter;

	// for color
	COLORREF		crText;
	COLORREF		crBackground;	
	COLORREF		crBar;

	//
	int				nTextLeftmode;

	//
	DWORD			dwItemData;				// pointer to app's data
};

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

// Attributes
public:

// Operations
public:
	void	EnableFocusRect(BOOL bFocusRect=TRUE){m_bFocusRect=bFocusRect;}
	void	EnableResize(BOOL bResize=TRUE){m_bResize=bResize;}

	void	SetNoItemMsg(CString strNoItemMsg){m_strNoItemMsg=strNoItemMsg;}
	void	SetStatusColumn(int nSubItem){m_nStatusColumn=nSubItem;}

	void	SetBgColor(COLORREF crBg){m_crWindow=crBg;}
	void	SetUnderLine(BOOL bUnderLine=TRUE){m_bUnderLine=bUnderLine;}
	void	SetColorUnderLine(COLORREF crUnderLine){m_crUnderLine=crUnderLine;}

	void	GetDrawColors(int nItem, int nSubItem, COLORREF& colorText, COLORREF& colorBkgnd);

	BOOL	DeleteAllItems();
	BOOL	DeleteItem(int nItem);
	BOOL	GetBold(int nItem, int nSubItem);
	int		GetColumns();
	int		GetCurSel();
	BOOL	GetEnabled(int nItem);
	DWORD	GetExtendedStyleX() { return m_dwExtendedStyleX; }
	int		GetHeaderCheckedState(int nSubItem);
	DWORD	GetItemData(int nItem);
	BOOL	GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& rect);

	int		InsertItem(int nItem, LPCTSTR lpszItem);
	int		InsertItem(int nItem,
					   LPCTSTR lpszItem,
					   COLORREF crText,
					   COLORREF crBackground);
	int		InsertItem(const LVITEM* pItem);
	BOOL	SetBold(int nItem, int nSubItem, BOOL bBold);


	BOOL	SetCurSel(int nItem);
	BOOL	SetEnabled(int nItem, BOOL bEnable);
	DWORD	SetExtendedStyleX(DWORD dwNewStyle) 
	{
		DWORD dwOldStyle = m_dwExtendedStyleX;
		m_dwExtendedStyleX = dwNewStyle;
		return dwOldStyle;
	}

	BOOL	SetHeaderCheckedState(int nSubItem, int nCheckedState);
	int		SetItem(const LVITEM* pItem);
	BOOL	SetItemData(int nItem, DWORD dwData);
	
	BOOL	SetItemImage(int nItem, int nSubItem, int nImage, BOOL bImageCenter=FALSE);
	int		GetItemImage(int nItem, int nSubItem);

	BOOL	SetItemText(int nItem, int nSubItem, LPCTSTR lpszText); 
	BOOL	SetItemText(int nItem, 
						int nSubItem, 
						LPCTSTR lpszText,
						COLORREF crText, 
						COLORREF crBackground);
	BOOL	SetItemTextColor(int nItem, 
							 int nSubItem, 
							 COLORREF crText, 
							 COLORREF crBackground);

	void	UpdateSubItem(int nItem, int nSubItem);

	void	SetRowHeight(int nRowHeight);
	void	SetTextFont(CFont *pTextFont) { m_pTextFont = pTextFont; RedrawWindow(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMyHeaderCtrl	m_HeaderCtrl;
	int m_nListIndex;
	CFont m_MyFont;

	void SetMyTextColor(COLORREF TextColor);

protected:
	CImageList		m_cImageList;		// Image list for the header control

	BOOL			m_bUnderLine;		// 언더라인 그리기의 유무 설정
	BOOL			m_bResize;			// 마우스 드래그로 헤더 컬럼의 리사이즈 유무 설정
	BOOL			m_bFocusRect;		// Focus Rect 표시 유무
	CString			m_strNoItemMsg;		// 아이템이 없을때 표시 할 텍스트 설정
	int				m_nStatusColumn;	// 상태 컬럼의 Rect(백그라운드 컬러영역)을 재설정할 컬럼 설정

	COLORREF		m_crBgProgress;		// 프로그레스의 배경색	
	COLORREF		m_crUnderLine;		// 언더라인의 색

	BOOL			m_bHeaderTracking;	// 현재 헤더가 트래킹중인지 판단하는 플래그
	BOOL			m_bHeaderDraging;	// 현재 헤더가 드래깅중인지 판단하는 플래그

	BOOL			m_bTracking;
	
	CFont		*	m_pTextFont;

protected:
	int DrawImage(int nItem, 
				  int nSubItem, 
				  CDC* pDC, 
				  COLORREF crText,
				  COLORREF crBkgnd,
				  CRect rect,
				  XLISTCTRLDATA *pXLCD);

	void DrawText(int nItem, 
				  int nSubItem, 
				  CDC *pDC, 
				  COLORREF crText,
				  COLORREF crBkgnd,
				  CRect& rect, 
				  XLISTCTRLDATA *pCLD);
	void SubclassHeaderControl();

	BOOL			m_bHeaderIsSubclassed;
	DWORD			m_dwExtendedStyleX;

	COLORREF		m_cr3DFace;
	COLORREF		m_cr3DHighLight;
	COLORREF		m_cr3DShadow;
	COLORREF		m_crBtnFace;
	COLORREF		m_crBtnShadow;
	COLORREF		m_crBtnText;
	COLORREF		m_crGrayText;
	COLORREF		m_crHighLight;
	COLORREF		m_crHighLightText;
	COLORREF		m_crWindow;
	COLORREF		m_crWindowText;

	COLORREF		m_crTracking;
	
	int				m_nTrackingItem;

// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtl)
	afx_msg void OnNMCustomdrawListSpec(NMHDR* pNMHDR, LRESULT* pResult); // $Add 2014-10-01 yslee
	afx_msg void OnNMCustomdrawListData(NMHDR *pNMHDR, LRESULT *pResult); // $Add 2014-10-01 yslee
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

//	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//}}AFX_MSG
	COLORREF m_TextColor;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTL_H__574961E0_C33C_11D7_9142_0050FC6ED3B6__INCLUDED_)