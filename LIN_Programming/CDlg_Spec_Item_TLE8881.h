#pragma once

#include "CFunc_Spec.h"
#include "CTest_Main.h"
#include "afxwin.h"


// CDlg_Spec_Item_TLE8881 dialog


class CDlg_Spec_Item_TLE8881 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlg_Spec_Item_TLE8881)

public:
	CDlg_Spec_Item_TLE8881();
	virtual ~CDlg_Spec_Item_TLE8881();

// Dialog Data
	enum { IDD = IDD_DIALOG_TLE8881 };

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
	CNiNumEdit	m_nieNvm_A00_L;
	CNiNumEdit	m_nieNvm_A00_H;
	CNiNumEdit	m_nieNvm_A01_L;
	CNiNumEdit	m_nieNvm_A01_H;
	CNiNumEdit	m_nieNvm_A02_L;
	CNiNumEdit	m_nieNvm_A02_H;
	CNiNumEdit	m_nieNvm_A03_L;
	CNiNumEdit	m_nieNvm_A03_H;

	virtual BOOL OnInitDialog();

	void f_Dlg_Set     (unsigned p);
	void f_Dlg_Read    (unsigned p);
	void f_Chip_Change (void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeComboRegulator();
	virtual BOOL OnSetActive();
};
