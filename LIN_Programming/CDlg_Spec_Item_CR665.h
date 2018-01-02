#pragma once

#include "CFunc_Spec.h"
#include "CTest_Main.h"
#include "afxwin.h"


// CDlg_Spec_Item_CR665 dialog


class CDlg_Spec_Item_CR665 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlg_Spec_Item_CR665)

public:
	CDlg_Spec_Item_CR665();
	virtual ~CDlg_Spec_Item_CR665();

// Dialog Data
	enum { IDD = IDD_DIALOG_CR665 };

	struct
	{
		unsigned		nPnum;

		CDialog			*pParentDlg;
		CFunc_Spec		*pCSpec;
		CTest_Main		*pTest;
	}m_var;

	TS_CLIN_VREG_CFG_FRAME_ID	m_fid;

public:
	CComboBox m_combo_regulator;
	CComboBox m_combo_version;

	CNiNumEdit	m_nieFid_Rx;
	CNiNumEdit	m_nieFid_Tx1;
	CNiNumEdit	m_nieFid_Tx2;
	CNiNumEdit	m_nieFid_Tx3;
	CNiNumEdit	m_nieNvm_A00;
	CNiNumEdit	m_nieNvm_A10;
	CNiNumEdit	m_nieNvm_A20;
	CNiNumEdit	m_nieNvm_A30;
	CNiNumEdit	m_nieNvm_A40;
	CNiNumEdit	m_nieNvm_A50;
	CNiNumEdit	m_nieNvm_A60;
	CNiNumEdit	m_nieNvm_A70;
	CNiNumEdit	m_nieNvm_A80;

	virtual BOOL OnInitDialog();

	void f_Dlg_Set  (unsigned p);
	void f_Dlg_Read (unsigned p);
	void f_Chip_Change (void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();

	afx_msg void OnCbnSelchangeComboRegulator();
};
