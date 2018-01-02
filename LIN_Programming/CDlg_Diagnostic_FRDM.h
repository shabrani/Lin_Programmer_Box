#pragma once
#include "afxwin.h"


// CDlg_Diagnostic_FRDM dialog

class CDlg_Diagnostic_FRDM : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Diagnostic_FRDM)

public:
	CDlg_Diagnostic_FRDM(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_Diagnostic_FRDM();

// Dialog Data
	enum { IDD = IDD_DIALOG_DIAGNOSTIC_FRDM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	BOOL  m_cwn_bInput1;
	BOOL  m_cwn_bInput2;
	BOOL  m_cwn_bOutput1;
	BOOL  m_cwn_bOutput2;
	BOOL  m_cwn_bOutput3;
	BOOL  m_cwn_bOutput4;
	BOOL  m_cwn_bOutput5;
	BOOL  m_cwn_bOutput6;

	CEdit m_editbox_set_vol;
	CEdit m_editbox_meas_vol;

	void f_Initialize_FRDM(void);

	afx_msg void OnBnClickedButtonSetVol();
	afx_msg void OnBnClickedButtonMeasVol();
	afx_msg void OnBnClickedButtonExit();

	afx_msg void OnBnClickedButtonReadInput1();
	afx_msg void OnBnClickedButtonReadInput2();

	afx_msg void OnBnClickedButtonSetOutput1();
	afx_msg void OnBnClickedButtonClrOutput1();
	afx_msg void OnBnClickedButtonSetOutput2();
	afx_msg void OnBnClickedButtonClrOutput2();
	afx_msg void OnBnClickedButtonSetOutput3();
	afx_msg void OnBnClickedButtonClrOutput3();
	afx_msg void OnBnClickedButtonSetOutput4();
	afx_msg void OnBnClickedButtonClrOutput4();
	afx_msg void OnBnClickedButtonSetOutput5();
	afx_msg void OnBnClickedButtonClrOutput5();
	afx_msg void OnBnClickedButtonSetOutput6();
	afx_msg void OnBnClickedButtonClrOutput6();
};
