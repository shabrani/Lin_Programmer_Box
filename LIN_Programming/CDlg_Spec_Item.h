#pragma once

#include "afxwin.h"
#include "CTest_Main.h"
#include "CFunc_Spec.h"
#include "CDlg_Spec_Item_CR665.h"
#include "CDlg_Spec_Item_TLE8881.h"
#include "CDlg_Spec_Item_TLE8880.h"
#include "CDlg_Spec_Item_L9916.h"
#include "CDlg_Spec_Item_LIN2112.h"
#include "CDlg_Spec_Item_Set_etc.h"

// CDlg_Spec_Item dialog

class CDlg_Spec_Item : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Spec_Item)

public:
	CDlg_Spec_Item(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_Spec_Item();

// Dialog Data
	enum { IDD = IDD_DIALOG_SPEC_ITEM };

	CPropertySheet	*m_pPropSheet;

	struct
	{
		CDlg_Spec_Item_CR665	CR665;
		CDlg_Spec_Item_TLE8881	TLE8881;
		CDlg_Spec_Item_TLE8880	TLE8880;
		CDlg_Spec_Item_L9916	L9916;
		CDlg_Spec_Item_LIN2112	LIN2112;
		CDlg_Spec_Item_Set_etc	SetEtc;
	}m_page;

	struct {
		unsigned pnum_prev;
		unsigned pnum;

		CTest_Main		*pTest;
		CFunc_Spec		*pCSpec;

		CFunc_Spec_Item	*pTitem;

		CPropertySheet	*pPropertySheet;
	}m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CNiNumEdit	m_cwn_nPnum;
	CNiNumEdit	m_cwn_nTnum;

	CComboBox	m_combo_RefTitem;
	CComboBox	m_combo_DataType;
	CComboBox	m_combo_LimitMode;

	CString		m_edit_TestName;
	CString		m_edit_DataFormat;
	CString		m_edit_Symbol;
	CString		m_edit_Unit;

	CNiNumEdit	m_edit_Baudrate;
	CNiNumEdit	m_cwn_HSL;
	CNiNumEdit	m_cwn_LSL;


	void f_ComboBox_Initialize	(void);
	void f_Page_Initialize		(void);

	void f_spec_load_from_CSpec  (unsigned pnum);
	void f_spec_save_to_CSpec	 (unsigned pnum);

	void f_page_load_from_CSpec (unsigned pnum);
	void f_page_save_to_CSepc   (unsigned pnum);

	void f_SPEC_LIMIT_View_Select_with_Mode();
	void f_SPEC_LIMIT_Format_Change_with_Mode();

	DECLARE_EVENTSINK_MAP()
	void ClickBtnEdit();
	void ValueChangedCwnPnum(VARIANT* Value, VARIANT* PreviousValue, BOOL OutOfRange);
	
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboDataType();
	afx_msg void OnCbnSelchangeComboLimitMode();
};
