#pragma once


// CDlg_PasswordCheck dialog

class CDlg_PasswordCheck : public CDialog
{
	DECLARE_DYNAMIC(CDlg_PasswordCheck)

public:
	CDlg_PasswordCheck(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_PasswordCheck();

// Dialog Data
	enum { IDD = IDD_DIALOG_PASSWORD_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_hbrBrush;
	CBrush m_staticBrush;

	CString m_strPassword;


	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
};
