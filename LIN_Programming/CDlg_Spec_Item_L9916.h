#pragma once

#include "CFunc_Spec.h"
#include "CTest_Main.h"
#include "afxwin.h"


// CDlg_Spec_Item_L9916 dialog


class CDlg_Spec_Item_L9916 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlg_Spec_Item_L9916)

public:
	CDlg_Spec_Item_L9916();
	virtual ~CDlg_Spec_Item_L9916();

// Dialog Data
	enum { IDD = IDD_DIALOG_L9916 };

	struct
	{
		unsigned		nPnum;

		CDialog			*pParentDlg;
		CFunc_Spec		*pCSpec;
		CTest_Main		*pTest;
	}m_var;

public:
	CNiNumEdit	m_nieAddr00;
	CNiNumEdit	m_nieAddr01;
	CNiNumEdit	m_nieAddr02;
	CNiNumEdit	m_nieAddr03;
	CNiNumEdit	m_nieAddr04;
	CNiNumEdit	m_nieAddr05;

	void f_Dlg_Set  (unsigned p);
	void f_Dlg_Read (unsigned p);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
