// CDlg_Diagnostic_FRDM.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Diagnostic_FRDM.h"
#include "afxdialogex.h"


// CDlg_Diagnostic_FRDM dialog

#include "tmenu_file.h"
#include "CTest_Main.h"
#include "CDlg_PasswordCheck.h"
#include "CFunc_FilePath.h"


extern CTest_Main	*pTest;

IMPLEMENT_DYNAMIC(CDlg_Diagnostic_FRDM, CDialog)

CDlg_Diagnostic_FRDM::CDlg_Diagnostic_FRDM(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Diagnostic_FRDM::IDD, pParent)
{
	m_cwn_bInput1	= FALSE;
	m_cwn_bInput2	= FALSE;
	m_cwn_bOutput1	= FALSE;
	m_cwn_bOutput2	= FALSE;
	m_cwn_bOutput3	= FALSE;
	m_cwn_bOutput4	= FALSE;
	m_cwn_bOutput5	= FALSE;
	m_cwn_bOutput6	= FALSE;
}

CDlg_Diagnostic_FRDM::~CDlg_Diagnostic_FRDM()
{
}

void CDlg_Diagnostic_FRDM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SET_VOLTAGE, m_editbox_set_vol);
	DDX_Control(pDX, IDC_EDIT_MEAS_VOLTAGE, m_editbox_meas_vol);


	DDX_OCBool(pDX, IDC_CWN_INPUT1, DISPID(2),  m_cwn_bInput1);
	DDX_OCBool(pDX, IDC_CWN_INPUT2, DISPID(2),  m_cwn_bInput2);

	DDX_OCBool(pDX, IDC_CWN_OUTPUT1, DISPID(2),  m_cwn_bOutput1);
	DDX_OCBool(pDX, IDC_CWN_OUTPUT2, DISPID(2),  m_cwn_bOutput2);
	DDX_OCBool(pDX, IDC_CWN_OUTPUT3, DISPID(2),  m_cwn_bOutput3);
	DDX_OCBool(pDX, IDC_CWN_OUTPUT4, DISPID(2),  m_cwn_bOutput4);
	DDX_OCBool(pDX, IDC_CWN_OUTPUT5, DISPID(2),  m_cwn_bOutput5);
	DDX_OCBool(pDX, IDC_CWN_OUTPUT6, DISPID(2),  m_cwn_bOutput6);
}


BEGIN_MESSAGE_MAP(CDlg_Diagnostic_FRDM, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SET_VOL, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetVol)
	ON_BN_CLICKED(IDC_BUTTON_MEAS_VOL, &CDlg_Diagnostic_FRDM::OnBnClickedButtonMeasVol)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CDlg_Diagnostic_FRDM::OnBnClickedButtonExit)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_READ_INPUT1, &CDlg_Diagnostic_FRDM::OnBnClickedButtonReadInput1)
	ON_BN_CLICKED(IDC_BUTTON_READ_INPUT2, &CDlg_Diagnostic_FRDM::OnBnClickedButtonReadInput2)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT1, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput1)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT1, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput1)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT2, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput2)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT2, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput2)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT3, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput3)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT3, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput3)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT4, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput4)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT4, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput4)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT5, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput5)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT5, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput5)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT6, &CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput6)
	ON_BN_CLICKED(IDC_BUTTON_CLR_OUTPUT6, &CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput6)
END_MESSAGE_MAP()


// CDlg_Diagnostic_FRDM message handlers


BOOL CDlg_Diagnostic_FRDM::OnInitDialog()
{
	CDialog::OnInitDialog();

	f_Initialize_FRDM();

	this->UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlg_Diagnostic_FRDM::f_Initialize_FRDM()
{
	m_cwn_bInput1	= FALSE;
	m_cwn_bInput2	= FALSE;

	m_cwn_bOutput1	= FALSE;
	m_cwn_bOutput2	= FALSE;
	m_cwn_bOutput3	= FALSE;
	m_cwn_bOutput4	= FALSE;
	m_cwn_bOutput5	= FALSE;
	m_cwn_bOutput6	= FALSE;
}

void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetVol()
{
	// TODO: Add your control notification handler code here 
	CString strVol;

	m_editbox_set_vol.GetWindowText(strVol);
	char *temp = LPSTR(LPCSTR(strVol));

	pTest->m_pFrdm->f_Voltage_Set(VOLTAGE_SET, temp);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonMeasVol()
{
	// TODO: Add your control notification handler code here
	float measVol;
	CString str_measVol;

	measVol = pTest->m_pFrdm->f_Voltage_Read();
	str_measVol.Format(_T("%f"), measVol);
	str_measVol = str_measVol.Left(5);

	UpdateData(TRUE);
	m_editbox_meas_vol.SetWindowText(str_measVol);
	UpdateData(FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	pTest->m_pFrdm->f_Clear_Output();

	CDialog::OnOK();
}

void CDlg_Diagnostic_FRDM::OnBnClickedButtonReadInput1()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Check_Signal("ireq", " pf", " 01");

	if(0x01 == (temp&0x01))
	{
		m_cwn_bInput1 = FALSE;
	}
	else if(0x00 == (temp&0x01))
	{
		m_cwn_bInput1 = TRUE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonReadInput2()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Check_Signal("ireq", " pg", " 08");

	if(0x08 == (temp&0x08))
	{
		m_cwn_bInput2 = FALSE;
	}
	else if(0x00 == (temp&0x08))
	{
		m_cwn_bInput2 = TRUE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput1()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pf", " 80");

	if(0x80 == (temp&0x80))
	{
		m_cwn_bOutput1 = TRUE;
	}
	else if(0x00 == (temp&0x80))
	{
		m_cwn_bOutput1 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput1()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pf", " 80");
	
	if(0x00 == (temp&0x80))
	{
		m_cwn_bOutput1 = FALSE;
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput2()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pc", " 01");

	if(0x01 == (temp&0x01))
	{
		m_cwn_bOutput2 = TRUE;
	}
	else if(0x00 == (temp&0x01))
	{
		m_cwn_bOutput2 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput2()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pc", " 01");

	if(0x00 ==(temp&0x01))
	{
		m_cwn_bOutput2 = FALSE;
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput3()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pc", " 02");

	if(0x02 == (temp&0x02))
	{
		m_cwn_bOutput3 = TRUE;
	}
	else if(0x00 == (temp&0x02))
	{
		m_cwn_bOutput3 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput3()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pc", " 02");
	
	if(0x00 == (temp&0x02))
	{
		m_cwn_bOutput3 = FALSE;
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput4()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pc", " 04");

	if(0x04 == (temp&0x04))
	{
		m_cwn_bOutput4 = TRUE;
	}
	else if(0x00 == (temp&0x04))
	{
		m_cwn_bOutput4 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput4()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pc", " 04");

	if(0x00 == (temp&0x04))
	{
		m_cwn_bOutput4 = FALSE;
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput5()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pc", " 08");

	if(0x08 == (temp&0x08))
	{
		m_cwn_bOutput5 = TRUE;
	}
	else if(0x00 == (temp&0x08))
	{
		m_cwn_bOutput5 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput5()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pc", " 08");

	if(0x00 == (temp&0x08))
	{
		m_cwn_bOutput5 = FALSE;
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonSetOutput6()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Send_Signal("bset", " pf", " 40");

	if(0x40 == (temp&0x40))
	{
		m_cwn_bOutput6 = TRUE;
	}
	else if(0x00 == (temp&0x40))
	{
		m_cwn_bOutput6 = FALSE;
	}
	else
	{
//		잘못된 값이기 때문에 디버깅이 필요함.
	}

	this->UpdateData (FALSE);
}


void CDlg_Diagnostic_FRDM::OnBnClickedButtonClrOutput6()
{
	// TODO: Add your control notification handler code here
	int temp;
	temp = pTest->m_pFrdm->f_Bit_Clear("bclr", " pf", " 40");

	if(0x00 == (temp&0x40))
	{
		m_cwn_bOutput6 = FALSE;
	}

	this->UpdateData (FALSE);
}
