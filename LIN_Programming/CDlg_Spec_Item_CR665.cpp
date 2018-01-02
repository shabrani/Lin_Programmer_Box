// CDlg_Spec_Item_CR665.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec_Item_CR665.h"
#include "afxdialogex.h"


// CDlg_Spec_Item_CR665 dialog

IMPLEMENT_DYNAMIC(CDlg_Spec_Item_CR665, CPropertyPage)

CDlg_Spec_Item_CR665::CDlg_Spec_Item_CR665()
	: CPropertyPage(CDlg_Spec_Item_CR665::IDD)
{
	m_var.nPnum = 0;
}

CDlg_Spec_Item_CR665::~CDlg_Spec_Item_CR665()
{
}

void CDlg_Spec_Item_CR665::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CWN_FID_RX,	m_nieFid_Rx);
	DDX_Control(pDX, IDC_CWN_FID_TX4,	m_nieFid_Tx1);
	DDX_Control(pDX, IDC_CWN_FID_TX5,	m_nieFid_Tx2);
	DDX_Control(pDX, IDC_CWN_FID_TX6,	m_nieFid_Tx3);

	DDX_Control(pDX, IDC_CWN_NVM_A00,	m_nieNvm_A00);
	DDX_Control(pDX, IDC_CWN_NVM_A10,	m_nieNvm_A10);
	DDX_Control(pDX, IDC_CWN_NVM_A20,	m_nieNvm_A20);
	DDX_Control(pDX, IDC_CWN_NVM_A30,	m_nieNvm_A30);
	DDX_Control(pDX, IDC_CWN_NVM_A40,	m_nieNvm_A40);
	DDX_Control(pDX, IDC_CWN_NVM_A50,	m_nieNvm_A50);
	DDX_Control(pDX, IDC_CWN_NVM_A60,	m_nieNvm_A60);
	DDX_Control(pDX, IDC_CWN_NVM_A70,	m_nieNvm_A70);
	DDX_Control(pDX, IDC_CWN_NVM_A80,	m_nieNvm_A80);

	DDX_Control(pDX, IDC_COMBO_REGULATOR, m_combo_regulator);
	DDX_Control(pDX, IDC_COMBO_VERSION2, m_combo_version);
}


BEGIN_MESSAGE_MAP(CDlg_Spec_Item_CR665, CPropertyPage)
//	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO_REGULATOR, &CDlg_Spec_Item_CR665::OnCbnSelchangeComboRegulator)
END_MESSAGE_MAP()


// CDlg_Spec_Item_CR665 message handlers
BOOL CDlg_Spec_Item_CR665::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	this->m_combo_regulator.AddString("  Regulator1");
	this->m_combo_regulator.AddString("  Regulator2");

	this->m_combo_version.ResetContent();
	this->m_combo_version.AddString (" 0 : Version A");
	this->m_combo_version.AddString (" 1 : Version B");


	this->UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlg_Spec_Item_CR665::f_Dlg_Set  (unsigned p)
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &m_var.pCSpec->m_stSpecInfo.Lin;


	this->m_nieNvm_A00.SetValue (pLin->Nvm.Addr00);
	this->m_nieNvm_A10.SetValue (pLin->Nvm.Addr01);
	this->m_nieNvm_A20.SetValue (pLin->Nvm.Addr02);
	this->m_nieNvm_A30.SetValue (pLin->Nvm.Addr03);
	this->m_nieNvm_A40.SetValue (pLin->Nvm.Addr04);
	this->m_nieNvm_A50.SetValue (pLin->Nvm.Addr05);
	this->m_nieNvm_A60.SetValue (pLin->Nvm.Addr06);
	this->m_nieNvm_A70.SetValue (pLin->Nvm.Addr07);
	this->m_nieNvm_A80.SetValue (pLin->Nvm.Addr08);

	this->m_nieFid_Rx.SetValue  (pLin->Fid.nRx);
	this->m_nieFid_Tx1.SetValue (pLin->Fid.nTx1);
	this->m_nieFid_Tx2.SetValue (pLin->Fid.nTx2);
	this->m_nieFid_Tx3.SetValue (pLin->Fid.nTx3);

//	pLin->nChip = SELECT_CR665;

	this->UpdateData(FALSE);
}

void CDlg_Spec_Item_CR665::f_Dlg_Read (unsigned p)
{
	this->UpdateData(TRUE);


	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;


	pLin->Nvm.Addr00 = (unsigned char)this->m_nieNvm_A00.GetValue ();
	pLin->Nvm.Addr01 = (unsigned char)this->m_nieNvm_A10.GetValue ();
	pLin->Nvm.Addr02 = (unsigned char)this->m_nieNvm_A20.GetValue ();
	pLin->Nvm.Addr03 = (unsigned char)this->m_nieNvm_A30.GetValue ();	
	pLin->Nvm.Addr04 = (unsigned char)this->m_nieNvm_A40.GetValue ();
	pLin->Nvm.Addr05 = (unsigned char)this->m_nieNvm_A50.GetValue ();
	pLin->Nvm.Addr06 = (unsigned char)this->m_nieNvm_A60.GetValue ();
	pLin->Nvm.Addr07 = (unsigned char)this->m_nieNvm_A70.GetValue ();
	pLin->Nvm.Addr08 = (unsigned char)this->m_nieNvm_A80.GetValue ();

	pLin->Fid.nRx  = (unsigned)this->m_nieFid_Rx.GetValue  ();
	pLin->Fid.nTx1 = (unsigned)this->m_nieFid_Tx1.GetValue ();
	pLin->Fid.nTx2 = (unsigned)this->m_nieFid_Tx2.GetValue ();
	pLin->Fid.nTx3 = (unsigned)this->m_nieFid_Tx3.GetValue ();
}

void CDlg_Spec_Item_CR665::f_Chip_Change ()
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;



	pLin->nRegulator = this->m_combo_regulator.GetCurSel();
	pLin->nVersion   = this->m_combo_version.GetCurSel  ();

	switch(pLin->nRegulator)
	{
	case ENUM_LIN_VREG_CFG_REGULATOR::M00_REGULATOR_1:

		this->m_nieFid_Rx.SetValue	(0x29);
		this->m_nieFid_Tx1.SetValue (0x11);
		this->m_nieFid_Tx2.SetValue (0x12);
		this->m_nieFid_Tx3.SetValue (0x15);

		break;

	case ENUM_LIN_VREG_CFG_REGULATOR::M01_REGULATOR_2:

		this->m_nieFid_Rx.SetValue	(0x2A);
		this->m_nieFid_Tx1.SetValue (0x13);
		this->m_nieFid_Tx2.SetValue (0x14);
		this->m_nieFid_Tx3.SetValue (0x16);

		break;

	default:
		break;
	}
}

BOOL CDlg_Spec_Item_CR665::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	pLin->nChip = SELECT_CR665;

	return CPropertyPage::OnSetActive();
}


void CDlg_Spec_Item_CR665::OnCbnSelchangeComboRegulator()
{
	// TODO: Add your control notification handler code here
	this->f_Chip_Change ();
}
