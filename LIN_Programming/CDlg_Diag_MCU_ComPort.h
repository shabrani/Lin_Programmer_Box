#pragma once
#include "CTest_Main.h"
#include "afxwin.h"


// CDlg_Diag_MCU_ComPort dialog

class CDlg_Diag_MCU_ComPort : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Diag_MCU_ComPort)

public:
	CDlg_Diag_MCU_ComPort(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_Diag_MCU_ComPort();

// Dialog Data
	enum { IDD = IDD_DLG_DIAG_MCU_COMTEST };

	struct
	{
		CTest_Main *pTest;
	}m_cfg;

	Comu_MCU	 *pMCU;


	void f_PrintStr(CString &String);
	void f_PrintStr(char *szString);

public:
	CNiButton m_nib_Connected;

	CNiButton m_nib_Plc_Out1;
	CNiButton m_nib_Plc_Out2;
	CNiButton m_nib_Plc_Out3;
	CNiButton m_nib_Plc_Out4;

	CNiButton m_nib_Plc_In1;
	CNiButton m_nib_Plc_In2;

	CListBox m_list;
	CButton m_btn_Connect;
	CEdit m_edit_Send;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClearList();
	afx_msg void OnBnClickedBtnIdn();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnSend();
	virtual BOOL OnInitDialog();

	void ClickCwbPlcOut1();
	void ClickCwbPlcOut2();
	void ClickCwbPlcOut3();
	void ClickCwbPlcOut4();
	void ClickCwbPlcIn1();
	void ClickCwbPlcIn2();
	
	DECLARE_EVENTSINK_MAP()
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
};
