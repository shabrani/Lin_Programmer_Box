#pragma once


// CDlg_PasswordChange dialog

class CDlg_PasswordChange : public CDialog
{
	DECLARE_DYNAMIC(CDlg_PasswordChange)

public:
	CDlg_PasswordChange(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_PasswordChange();

// Dialog Data
	enum { IDD = IDD_DIALOG_PASSWORD_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_hbrBrush;
	CBrush m_staticBrush;

	CString m_strPwOld;
	CString m_strPwNew;
	CString m_strPwConfirm;


	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonCancel();
};
