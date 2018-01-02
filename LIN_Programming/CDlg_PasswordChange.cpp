// CDlg_PasswordChange.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_PasswordChange.h"
#include "afxdialogex.h"

#include "CTest_Main.h"

extern CTest_Main	*pTest;


// CDlg_PasswordChange dialog

IMPLEMENT_DYNAMIC(CDlg_PasswordChange, CDialog)

CDlg_PasswordChange::CDlg_PasswordChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PasswordChange::IDD, pParent)
	, m_strPwOld(_T(""))
	, m_strPwNew(_T(""))
	, m_strPwConfirm(_T(""))
{

}

CDlg_PasswordChange::~CDlg_PasswordChange()
{
}

void CDlg_PasswordChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PWCHG_OLD, m_strPwOld);
	DDV_MaxChars(pDX, m_strPwOld, 8);
	DDX_Text(pDX, IDC_EDIT_PWCHG_NEW, m_strPwNew);
	DDV_MaxChars(pDX, m_strPwNew, 8);
	DDX_Text(pDX, IDC_EDIT_PWCHG_CONFIRM, m_strPwConfirm);
	DDV_MaxChars(pDX, m_strPwConfirm, 8);
}


BEGIN_MESSAGE_MAP(CDlg_PasswordChange, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlg_PasswordChange::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlg_PasswordChange::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlg_PasswordChange message handlers


BOOL CDlg_PasswordChange::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_hbrBrush.CreateSolidBrush(RGB(237, 235, 235));
	m_staticBrush.CreateSolidBrush(RGB(241, 251, 253));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



HBRUSH CDlg_PasswordChange::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CDlg_PasswordChange::OnDestroy()
{
	CDialog::OnDestroy();
	m_hbrBrush.DeleteObject();
	m_staticBrush.DeleteObject();
	// TODO: Add your message handler code here
}


void CDlg_PasswordChange::OnBnClickedButtonChange()
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	
	CString strPwLoad;
	pTest->m_pReg->f_regiRead_Password ( strPwLoad );

	strPwLoad.MakeLower();

	m_strPwOld.MakeLower ();
	m_strPwNew.MakeLower ();
	m_strPwConfirm.MakeLower (); 

	if(m_strPwOld.IsEmpty())
	{
		AfxMessageBox("Please insert password  \n\n현재 비밀번호를 입력하세요  \n\n");
		//m_strPwOld.SetFocus();
		return;
	}
	
	if(m_strPwNew.IsEmpty())
	{
		AfxMessageBox("Please insert new password  \n\n새로운 비밀번호를 입력하세요  \n\n");
		//m_strPwNew.SetFocus();
		return;
	}
	
	if(m_strPwConfirm.IsEmpty())
	{
		AfxMessageBox("Please confirm new password  \n\n확인 비밀번호를 입력하세요  \n\n");
		//m_strPwNewCheck.SetFocus();
		return;
	}
	


	if(m_strPwOld != strPwLoad )
	{
		AfxMessageBox("Failed..!\nPlease check password.  \n\n현재 비밀번호가 맞지않습니다.  \n\n");
		return;
	}

	if (m_strPwNew.GetLength() > 12 )
	{
		AfxMessageBox("Failed..!\nPlease check new password.  \n\n 비밀번호를 12글자 범위에서 입력하세요.  \n\n");
		return;
	}	

	if (m_strPwNew != m_strPwConfirm)
	{
		AfxMessageBox("Failed..!\nPlease check new password.  \n\n 새로운 비밀번호가 일치하지 않습니다.  \n\n");
		return;
	}	

	
	pTest->m_pReg->f_regiSave_Password (m_strPwNew);


	AfxMessageBox("Password changed!!  \n\n비밀번호가 변경되었습니다.  \n\n");

	OnCancel();
}


void CDlg_PasswordChange::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
