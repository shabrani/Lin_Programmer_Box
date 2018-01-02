// CDlg_PasswordCheck.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_PasswordCheck.h"
#include "afxdialogex.h"
#include "CTest_Main.h"

extern CTest_Main	*pTest;

// CDlg_PasswordCheck dialog

IMPLEMENT_DYNAMIC(CDlg_PasswordCheck, CDialog)

CDlg_PasswordCheck::CDlg_PasswordCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PasswordCheck::IDD, pParent)
	, m_strPassword(_T(""))
{

}

CDlg_PasswordCheck::~CDlg_PasswordCheck()
{
}

void CDlg_PasswordCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlg_PasswordCheck, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlg_PasswordCheck::OnBnClickedOK)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlg_PasswordCheck::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlg_PasswordCheck message handlers


BOOL CDlg_PasswordCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	m_hbrBrush.CreateSolidBrush(RGB(237, 235, 235));
	m_staticBrush.CreateSolidBrush(RGB(241, 251, 253));

	// $ Delete by sjkim 2012-06-20
	//this->m_bPasswordEqual = false;
	//pTest->m_ts.Password.isEqual = false;
	// $ End

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlg_PasswordCheck::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG)
    {
        return (HBRUSH)m_hbrBrush;
    }
	if (nCtlColor == CTLCOLOR_EDIT)
    {
		pDC->SetBkColor(RGB(241, 251, 253));
		pDC->SetTextColor ( RGB(10,10,10) );
        return (HBRUSH)m_staticBrush;
    }
	if (nCtlColor == CTLCOLOR_STATIC)
    {
		pDC->SetBkColor(RGB(237, 235, 235));
		pDC->SetTextColor ( RGB(100,100,100) );
        return (HBRUSH)m_hbrBrush;
    }
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CDlg_PasswordCheck::OnDestroy()
{
	CDialog::OnDestroy();
	m_hbrBrush.DeleteObject();
	m_staticBrush.DeleteObject();
	// TODO: Add your message handler code here
}


void CDlg_PasswordCheck::OnBnClickedOK()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString regiPW;
	pTest->m_pReg->f_regiRead_Password ( regiPW );
	regiPW.MakeLower();


	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("Please Insert Password.");
		return;
	}

	this->m_strPassword.MakeLower();
	

	if(m_strPassword != regiPW)
	{
		AfxMessageBox("Password Not Equal.");
		return ;
	}

	// $ Delete by sjkim 2012-06-20 -> 결과처리를 Dlg.OK로 처리하도록 프로그램 수정
	//pTest->m_ts.Password.isEqual = true;
	//this->m_bPasswordEqual = true;
	// $ End	

	CDialog::OnOK();
}


void CDlg_PasswordCheck::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
