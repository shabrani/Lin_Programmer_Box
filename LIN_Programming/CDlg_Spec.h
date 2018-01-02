#pragma once

#include <string>

#include "afxwin.h"
#include "CTest_Main.h"
#include "CFunc_Spec.h"
#include "afxcmn.h"

// CDlg_Spec dialog

class CDlg_Spec : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Spec)

public:
	CDlg_Spec(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_Spec();

// Dialog Data
	enum { IDD = IDD_DIALOG_SPEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

public:
	CFont		m_Font;

	struct{
		CTest_Main	*pTest;
		CFunc_Spec	*CSpec_pOrg;
		CFunc_Spec	CSpec_Edit;
	}m_var;


	CString		m_editbox_TestDevice;
	CString		m_editbox_SpecRevDate;
	CString		m_editbox_SpecRevNo;
	CString		m_editbox_SpecName;
	CString		m_editbox_ProgName;
	CString		m_editbox_ProgRev;
	CString		m_editbox_TestItem;
	CListCtrl	m_list_sedit;

	CNiButton	m_BTN_save;
	CNiButton	m_BTN_exit;

	
	void ClickCwnSave();
	void ClickCwnExit();

	afx_msg void OnNMDblclkSeditList	(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickSeditBtnSort	(void);
	afx_msg void OnClickSeditBtnAdd		(void);
	afx_msg void OnClickSeditBtnDelete	(void);

	void f_EditMode_Change					(void);

	void f_ListCtrl_Initialize_funcTest		(void);
	void f_ListCtrl_DispalyData				(void);
	void f_ListCtrl_DisplayData_funcTest	(void);

	void f_InsertCol			(LVCOLUMN &lv,     int nCol, int        nWidth, LPTSTR szHeader, int iFmt);
	void f_InsertLVItem_CStr	(LV_ITEM  &lvItem, int nCol, CString	&str	);
	void f_InsertLVItem_Text	(LV_ITEM  &lvItem, int nCol, const char *szText	);
	void f_InsertLVItem_uint	(LV_ITEM  &lvItem, int nCol, unsigned	uData, const char *szFmt);
	void f_InsertLVItem_float	(LV_ITEM  &lvItem, int nCol, double	    fData, const char *szFmt);
	
};
