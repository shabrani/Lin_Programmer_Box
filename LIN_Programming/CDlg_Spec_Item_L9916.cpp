// CDlg_Spec_Item_L9916.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec_Item_L9916.h"
#include "afxdialogex.h"


// CDlg_Spec_Item_L9916 dialog

IMPLEMENT_DYNAMIC(CDlg_Spec_Item_L9916, CPropertyPage)

CDlg_Spec_Item_L9916::CDlg_Spec_Item_L9916()
	: CPropertyPage(CDlg_Spec_Item_L9916::IDD)
{
	m_var.nPnum = 0;
}

CDlg_Spec_Item_L9916::~CDlg_Spec_Item_L9916()
{
}

void CDlg_Spec_Item_L9916::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CWN_OTP_ADDR00,	m_nieAddr00);
	DDX_Control(pDX, IDC_CWN_OTP_ADDR01,	m_nieAddr01);
	DDX_Control(pDX, IDC_CWN_OTP_ADDR02,	m_nieAddr02);
	DDX_Control(pDX, IDC_CWN_OTP_ADDR03,	m_nieAddr03);
	DDX_Control(pDX, IDC_CWN_OTP_ADDR04,	m_nieAddr04);
	DDX_Control(pDX, IDC_CWN_OTP_ADDR05,	m_nieAddr05);
}


BEGIN_MESSAGE_MAP(CDlg_Spec_Item_L9916, CPropertyPage)
END_MESSAGE_MAP()


// CDlg_Spec_Item_L9916 message handlers

void CDlg_Spec_Item_L9916::f_Dlg_Set  (unsigned p)
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &m_var.pCSpec->m_stSpecInfo.Lin;


	this->m_nieAddr00.SetValue (pLin->Nvm.Addr00);
	this->m_nieAddr01.SetValue (pLin->Nvm.Addr01);
	this->m_nieAddr02.SetValue (pLin->Nvm.Addr02);
	this->m_nieAddr03.SetValue (pLin->Nvm.Addr03);
	this->m_nieAddr04.SetValue (pLin->Nvm.Addr04);
	this->m_nieAddr05.SetValue (pLin->Nvm.Addr05);


	this->UpdateData(FALSE);
}

void CDlg_Spec_Item_L9916::f_Dlg_Read (unsigned p)
{
	this->UpdateData(TRUE);


	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;


	pLin->Nvm.Addr00 = (unsigned char)this->m_nieAddr00.GetValue ();
	pLin->Nvm.Addr01 = (unsigned char)this->m_nieAddr01.GetValue ();
	pLin->Nvm.Addr02 = (unsigned char)this->m_nieAddr02.GetValue ();
	pLin->Nvm.Addr03 = (unsigned char)this->m_nieAddr03.GetValue ();	
	pLin->Nvm.Addr04 = (unsigned char)this->m_nieAddr04.GetValue ();
	pLin->Nvm.Addr05 = (unsigned char)this->m_nieAddr05.GetValue ();

}



BOOL CDlg_Spec_Item_L9916::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	pLin->nChip = SELECT_L9916;

	return CPropertyPage::OnSetActive();
}
