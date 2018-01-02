// CDlg_DataFilePath.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_DataFilePath.h"
#include "afxdialogex.h"


// CDlg_DataFilePath dialog

#include "tmenu_file.h"
#include "CTest_Main.h"
#include "CDlg_PasswordCheck.h"
#include "CFunc_FilePath.h"


extern CTest_Main	*pTest;

IMPLEMENT_DYNAMIC(CDlg_DataFilePath, CDialog)

CDlg_DataFilePath::CDlg_DataFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_DataFilePath::IDD, pParent)
	, m_strPathDataFile(_T(""))
{

}

CDlg_DataFilePath::~CDlg_DataFilePath()
{
}

void CDlg_DataFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SETPATH_DATAFILE, m_strPathDataFile);
}


BEGIN_MESSAGE_MAP(CDlg_DataFilePath, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_PATH, &CDlg_DataFilePath::OnBnClickedButtonChangePath)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlg_DataFilePath::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlg_DataFilePath::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDlg_DataFilePath message handlers
BOOL CDlg_DataFilePath::OnInitDialog()
{
	CDialog::OnInitDialog();

	pTest->m_pReg->f_regiRead_BasePath_DataFile (m_strPathDataFile);

	this->UpdateData (FALSE); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_DataFilePath::OnBnClickedButtonChangePath()
{
	// TODO: Add your control notification handler code here
		char path [MAX_PATH];

	UpdateData(TRUE);

	CFunc_FilePath	CPath;
	CPath.f_filename_remove_filename (path, this->m_strPathDataFile );
	::SetCurrentDirectory (path);  


	BROWSEINFO bi;

    LPITEMIDLIST pidl;

    TCHAR szBuff[MAX_PATH] = {0}, szDisp[MAX_PATH] = {0}, szPath[MAX_PATH] = {0};

    lstrcpy(szBuff, "Select Data File Path...");

    ZeroMemory( &bi, sizeof(BROWSEINFO) );
 

    bi.hwndOwner = this->GetSafeHwnd();

    bi.pidlRoot = NULL;

    bi.lpszTitle = static_cast<LPSTR>(szBuff);

    bi.pszDisplayName = static_cast<LPSTR>(szDisp);

 	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX  ;    // BIF_USENEWUI 는 '새 폴더 만들기' 기능을 위한 플래그. 없는 것보단 있는게 낫겠죠?

    bi.lParam = (LPARAM)this;

	if( !(pidl=SHBrowseForFolder(&bi)) ) return;
            
    ZeroMemory(szPath, MAX_PATH);
    SHGetPathFromIDList(pidl, szPath);	

	this->m_strPathDataFile = szPath;
	
	UpdateData(FALSE);	
}


void CDlg_DataFilePath::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	CDlg_PasswordCheck dlg;
	if (IDOK != dlg.DoModal()) return;



	UpdateData(TRUE);

	char path [MAX_PATH];	

	strcpy_s (path, this->m_strPathDataFile );
	pTest->m_pReg->f_regiSave_BasePath_DataFile ( path );

	CDialog::OnOK();
}


void CDlg_DataFilePath::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
