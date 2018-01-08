// LIN_ProgrammingView.h : interface of the CLIN_ProgrammingView class
//
#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "KvrLin.h"
#include "MyListCtrl.h"
#include "afxwin.h"

#include <IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib")


class CLIN_ProgrammingView : public CFormView
{
protected: // create from serialization only
	CLIN_ProgrammingView();
	DECLARE_DYNCREATE(CLIN_ProgrammingView)

public:
	enum{ IDD = IDD_LIN_PROGRAMMING_FORM };

// Attributes
public:
	CLIN_ProgrammingDoc* GetDocument() const;
	CBrush				 m_hbrBrush;
	CBrush				 m_staticBrush;
	CFont				 m_Font;
	CBitmap				 m_bmpBack;
	HBITMAP				 hbmp;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLIN_ProgrammingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DWORD_PTR	m_num;

	CNiButton	m_CNB_sDeviceName;
	CNiButton	m_CNB_sSpecName;
	
	CNiButton	m_BTN_bTest;
	CNiButton	m_BTN_bStop;
	CNiButton	m_BTN_bRetest;
	CNiButton	m_BTN_bHdlr;
	CNiButton	m_BTN_bMode;
	CNiButton	m_BTN_bMode2;
	CNiButton	m_CNB_Standby;

	CNiButton	m_CWN_EX;

	CNiNumEdit	m_CNE_fTime;
	CNiNumEdit	m_CNE_nGood;
	CNiNumEdit	m_CNE_nFail;
	CNiNumEdit	m_CNE_fYield;
	CNiNumEdit	m_CNE_nDnum;

	CMyListCtrl m_ListSpec;
	CMyListCtrl m_ListData;
	CMyListCtrl m_ListLinMsg;
//	CMyListCtrl m_ListSerial;

	CString		m_sSpecFileName;

	CProgressCtrl m_progress;
	
	BOOL		m_bRemoteTestEnable;

	CTime CurTime;

	bool		m_bRemoteState_prev;

/////////////////////////////////////////////////////////////////////////////
	void f_Test_Start(void);

	void f_remote_start_stop_and_state_save (void);
	void f_remote_start_state_restore		(void);

	void f_spec_change_param_set_display	(void);

	void f_ListView_Spec_Header_Init (void);
	void f_ListView_Data_Header_Init (void);
	void f_ListView_LinMsg_Header_Init (void);

	void f_ListView_Data_Display_InitTestResult (unsigned nList);
	void f_ListView_Spec_Display				(void);

	CString Decryption(CString strTemp);
	CString	GetMacAddress(void);
	void Extraction();

protected:
// Generated message map functions
	afx_msg void OnAppExit();

	afx_msg void OnUserMsgDisplayTestImage			(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayTestData			(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayLinMessage			(WPARAM wParam, KVR_LIN_STRUCT &linBuf);
	afx_msg void OnUserMsgDisplayTestResultInit		(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayTestQuantity		(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayTestTime			(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayStatusRemoteTest	(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayMainScreenReset	(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayTestDnum			(WPARAM wParam, LPARAM lParam);

	afx_msg void OnUserMsgRemoteTestRestore			(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserCmdMainBtnTestStart			(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgSetButtonStopEnable		(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMsgDisplayProgressPosition	(WPARAM wParam, LPARAM lParam);

	afx_msg void OnMenuSpecOpen	(void);
	afx_msg void OnMenuExit		(void);
	afx_msg void OnMenuSpecEdit (void);
	afx_msg void OnMenuChangePassword();
	afx_msg void OnMenuChangeDataFileSavePath();
	afx_msg void OnMenuDiagMcuComport();
protected:
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

public:
	void ClickCnbSelSpec(void);
	void ClickBtnTest(void);
	void ClickBtnStop(void);
	void ClickBtnRetest(void);
	void ClickBtnExit(void);
	void ClickBtnRemote();
	void ClickBtnHdlr();
	void ClickBtnModeSelect();
	void ClickBtnModeSelect2();

	void ClickCwnEx();
	CString m_edit_ex;
	void ValueChangedCwnEx2(BOOL Value);
};

#ifndef _DEBUG  // debug version in 

View.cpp
inline CLIN_ProgrammingDoc* CLIN_ProgrammingView::GetDocument() const
   { return reinterpret_cast<CLIN_ProgrammingDoc*>(m_pDocument); }
#endif

