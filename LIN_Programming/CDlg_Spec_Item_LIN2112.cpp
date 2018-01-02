// CDlg_Spec_Item_LIN2112.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec_Item_LIN2112.h"
#include "afxdialogex.h"


// CDlg_Spec_Item_LIN2112 dialog

IMPLEMENT_DYNAMIC(CDlg_Spec_Item_LIN2112, CPropertyPage)

CDlg_Spec_Item_LIN2112::CDlg_Spec_Item_LIN2112()
	: CPropertyPage(CDlg_Spec_Item_LIN2112::IDD)
{
	m_var.nPnum = 0;
}

CDlg_Spec_Item_LIN2112::~CDlg_Spec_Item_LIN2112()
{
}

void CDlg_Spec_Item_LIN2112::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CWN_OFFSET0_5,	m_nieOffset0_5);
	DDX_Control(pDX, IDC_CWN_OFFSET0_6,	m_nieOffset0_6);
	DDX_Control(pDX, IDC_CWN_OFFSET0_7,	m_nieOffset0_7);
	DDX_Control(pDX, IDC_CWN_OFFSET0_8,	m_nieOffset0_8);

	DDX_Control(pDX, IDC_CWN_OFFSET1_5,	m_nieOffset1_5);
	DDX_Control(pDX, IDC_CWN_OFFSET1_6,	m_nieOffset1_6);
	DDX_Control(pDX, IDC_CWN_OFFSET1_7,	m_nieOffset1_7);
	DDX_Control(pDX, IDC_CWN_OFFSET1_8,	m_nieOffset1_8);

	DDX_Control(pDX, IDC_CWN_OFFSET2_5,	m_nieOffset2_5);
	DDX_Control(pDX, IDC_CWN_OFFSET2_6,	m_nieOffset2_6);
	DDX_Control(pDX, IDC_CWN_OFFSET2_7,	m_nieOffset2_7);
	DDX_Control(pDX, IDC_CWN_OFFSET2_8,	m_nieOffset2_8);
}


BEGIN_MESSAGE_MAP(CDlg_Spec_Item_LIN2112, CPropertyPage)
END_MESSAGE_MAP()


// CDlg_Spec_Item_LIN2112 message handlers

void CDlg_Spec_Item_LIN2112::f_Dlg_Set  (unsigned p)
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &m_var.pCSpec->m_stSpecInfo.Lin;


	this->m_nieOffset0_5.SetValue (pLin->Nvm.Addr00);
	this->m_nieOffset0_6.SetValue (pLin->Nvm.Addr01);
	this->m_nieOffset0_7.SetValue (pLin->Nvm.Addr02);
	this->m_nieOffset0_8.SetValue (pLin->Nvm.Addr03);

	this->m_nieOffset1_5.SetValue (pLin->Nvm.Addr04);
	this->m_nieOffset1_6.SetValue (pLin->Nvm.Addr05);
	this->m_nieOffset1_7.SetValue (pLin->Nvm.Addr06);

	this->m_nieOffset2_5.SetValue (pLin->Nvm.Addr08);
	this->m_nieOffset2_6.SetValue (pLin->Nvm.Addr09);
	this->m_nieOffset2_7.SetValue (pLin->Nvm.Addr10);


	this->UpdateData(FALSE);
}

void CDlg_Spec_Item_LIN2112::f_Dlg_Read (unsigned p)
{
	this->UpdateData(TRUE);


	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;


	pLin->Nvm.Addr00 = (unsigned char)this->m_nieOffset0_5.GetValue ();
	pLin->Nvm.Addr01 = (unsigned char)this->m_nieOffset0_6.GetValue ();
	pLin->Nvm.Addr02 = (unsigned char)this->m_nieOffset0_7.GetValue ();
	pLin->Nvm.Addr03 = (unsigned char)this->m_nieOffset0_8.GetValue ();	

	pLin->Nvm.Addr04 = (unsigned char)this->m_nieOffset1_5.GetValue ();
	pLin->Nvm.Addr05 = (unsigned char)this->m_nieOffset1_6.GetValue ();
	pLin->Nvm.Addr06 = (unsigned char)this->m_nieOffset1_7.GetValue ();

	pLin->Nvm.Addr08 = (unsigned char)this->m_nieOffset2_5.GetValue ();
	pLin->Nvm.Addr09 = (unsigned char)this->m_nieOffset2_6.GetValue ();
	pLin->Nvm.Addr10 = (unsigned char)this->m_nieOffset2_7.GetValue ();
}



BOOL CDlg_Spec_Item_LIN2112::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	pLin->nChip = SELECT_LIN2112;

	return CPropertyPage::OnSetActive();
}
