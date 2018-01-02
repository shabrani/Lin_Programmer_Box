#pragma once

#include "CFunc_Spec.h"
#include "CTest_Main.h"
// CDlg_Spec_Item_Set_etc 대화 상자입니다.

class CDlg_Spec_Item_Set_etc : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlg_Spec_Item_Set_etc)

public:
	CDlg_Spec_Item_Set_etc();
	virtual ~CDlg_Spec_Item_Set_etc();

	struct
	{
		unsigned	nPnum;

		CDialog		*pParentDlg;
		CFunc_Spec	*pCSpec;
		CTest_Main	*pTest;
	}m_var;

	CNiNumEdit	m_nieWaitTime;
	CNiNumEdit	m_nieVoltage;
	CNiNumEdit	m_nieCurrent;

	void f_Dlg_Set  (unsigned p);
	void f_Dlg_Read (unsigned p);
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SET_ETC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
