#pragma once

#include "CFunc_Spec.h"
#include "CTest_Main.h"
#include "afxwin.h"


// CDlg_Spec_Item_LIN2112 dialog


class CDlg_Spec_Item_LIN2112 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlg_Spec_Item_LIN2112)

public:
	CDlg_Spec_Item_LIN2112();
	virtual ~CDlg_Spec_Item_LIN2112();

// Dialog Data
	enum { IDD = IDD_DIALOG_LIN2112 };

	struct
	{
		unsigned		nPnum;

		CDialog			*pParentDlg;
		CFunc_Spec		*pCSpec;
		CTest_Main		*pTest;
	}m_var;

public:
	CNiNumEdit	m_nieOffset0_5;
	CNiNumEdit	m_nieOffset0_6;
	CNiNumEdit	m_nieOffset0_7;
	CNiNumEdit	m_nieOffset0_8;
	CNiNumEdit	m_nieOffset1_5;
	CNiNumEdit	m_nieOffset1_6;
	CNiNumEdit	m_nieOffset1_7;
	CNiNumEdit	m_nieOffset1_8;
	CNiNumEdit	m_nieOffset2_5;
	CNiNumEdit	m_nieOffset2_6;
	CNiNumEdit	m_nieOffset2_7;
	CNiNumEdit	m_nieOffset2_8;

	void f_Dlg_Set  (unsigned p);
	void f_Dlg_Read (unsigned p);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
