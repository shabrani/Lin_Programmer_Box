// CDlg_Spec_Item_Set_etc.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec_Item_Set_etc.h"
#include "afxdialogex.h"


// CDlg_Spec_Item_Set_etc 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg_Spec_Item_Set_etc, CPropertyPage)

CDlg_Spec_Item_Set_etc::CDlg_Spec_Item_Set_etc()
	: CPropertyPage(CDlg_Spec_Item_Set_etc::IDD)
{
	m_var.nPnum = 0;
}

CDlg_Spec_Item_Set_etc::~CDlg_Spec_Item_Set_etc()
{
}

void CDlg_Spec_Item_Set_etc::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CWN_WAIT_TIME,	m_nieWaitTime);
	DDX_Control(pDX, IDC_CWN_VOLTAGE,	m_nieVoltage);
	DDX_Control(pDX, IDC_CWN_CURRENT,	m_nieCurrent);
}


BEGIN_MESSAGE_MAP(CDlg_Spec_Item_Set_etc, CPropertyPage)
END_MESSAGE_MAP()


// CDlg_Spec_Item_Set_etc 메시지 처리기입니다.


void CDlg_Spec_Item_Set_etc::f_Dlg_Set  (unsigned p)
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &m_var.pCSpec->m_stSpecInfo.Lin;


	this->m_nieWaitTime.SetValue(pLin->nWaitTime);

	this->m_nieVoltage.SetValue(pLin->fVoltage);
	this->m_nieCurrent.SetValue(pLin->fCurrent);

//	pLin->nChip = SELECT_CR665;

	this->UpdateData(FALSE);
}

void CDlg_Spec_Item_Set_etc::f_Dlg_Read (unsigned p)
{
	this->UpdateData(TRUE);

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;


	pLin->nWaitTime  = (unsigned)this->m_nieWaitTime.GetValue ();

	pLin->fVoltage  = (float)this->m_nieVoltage.GetValue ();
	pLin->fCurrent  = (float)this->m_nieCurrent.GetValue ();

}