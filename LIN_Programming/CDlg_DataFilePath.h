#pragma once


// CDlg_DataFilePath dialog

class CDlg_DataFilePath : public CDialog
{
	DECLARE_DYNAMIC(CDlg_DataFilePath)

public:
	CDlg_DataFilePath(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_DataFilePath();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATAFILEPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPathDataFile;

	afx_msg void OnBnClickedButtonChangePath();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
