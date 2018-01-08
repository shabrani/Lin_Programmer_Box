// LIN_ProgrammingView.cpp : implementation of the CLIN_ProgrammingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LIN_Programming.h"
#endif

#include "LIN_ProgrammingDoc.h"
#include "LIN_ProgrammingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Header
#include "procedure.h"
#include "procedure_Macro.h"
#include "MyListCtrl.h"

#include "CDlg_Spec.h"
#include "CFunc_UserMsg.h"
#include "CTest_Main.h"
#include "CDlg_PasswordChange.h"
#include "CDlg_PasswordCheck.h"
#include "CDlg_PasswordChange.h"
#include "CDlg_DataFilePath.h"
#include "CDlg_Diag_MCU_ComPort.h"

#include "Rijndael.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variable
CTest_Main		*pTest;

HWND			hDlgMain;

HANDLE			hEvent;
extern HANDLE	hThread_Test;
extern HANDLE	hThread_waitTestSignal;

extern DWORD	ThreadID_Test;
extern DWORD	ThreadID_waitTestSignal;

void MySetScrollPos(UINT nPos);
void MySetScrollPageDown();
void MySetScrollPageUp();
void MySetScrollLineDown();
void MySetScrollLineUp();
BOOL g_bListCtlIsFun = FALSE;
int g_nListIndex = 1;

CLIN_ProgrammingView	*g_pLinProgView = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLIN_ProgrammingView

IMPLEMENT_DYNCREATE(CLIN_ProgrammingView, CFormView)
	
BEGIN_MESSAGE_MAP(CLIN_ProgrammingView, CFormView)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)

	ON_MESSAGE(USERMSG_DISPLAY_TEST_IMAGE,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestImage)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_DATA,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestData)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_LIN_MSG,			(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayLinMessage)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_RESULT_INIT,		(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestResultInit)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_QUANTITY,			(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestQuantity)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_TIME,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestTime)
	ON_MESSAGE(USERMSG_DISPLAY_STATUS_REMOTETEST,		(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayStatusRemoteTest)
	ON_MESSAGE(USERMSG_DISPLAY_MAINSCREEN_RESET,		(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayMainScreenReset)
	ON_MESSAGE(USERMSG_DISPLAY_TEST_DNUM,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayTestDnum)

	ON_MESSAGE(USERMSG_REMOTETEST_RESTORE,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgRemoteTestRestore)
	ON_MESSAGE(USERMSG_MAIN_BTN_TEST_START,				(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserCmdMainBtnTestStart)
	ON_MESSAGE(USERMSG_DISPLAY_PROGRESS_POS,			(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnUserMsgDisplayProgressPosition)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MENU Bar Message
	ON_COMMAND(ID_MENU_SPECOPEN,	OnMenuSpecOpen)
	ON_COMMAND(ID_MENU_EXIT,		OnMenuExit)
	ON_COMMAND(ID_MENU_SPECEDIT,	OnMenuSpecEdit)
	ON_COMMAND(ID_MENU_CHANGEPASSWORD, OnMenuChangePassword)
	ON_COMMAND(ID_EDIT_DATAFILESAVEPATH, OnMenuChangeDataFileSavePath)
	ON_COMMAND(ID_MENU_DIAG_MCU_COMPORT, OnMenuDiagMcuComport)

END_MESSAGE_MAP()

// CLIN_ProgrammingView construction/destruction

CLIN_ProgrammingView::CLIN_ProgrammingView()
	: CFormView(CLIN_ProgrammingView::IDD)
	, m_edit_ex(_T(""))
{
	// TODO: add construction code here

}

CLIN_ProgrammingView::~CLIN_ProgrammingView()
{
}

void CLIN_ProgrammingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIN_PROGRAMER,		m_CNB_sDeviceName);
	DDX_Control(pDX, IDC_CNB_SPEC_NAME,		m_CNB_sSpecName);

	DDX_Control(pDX, IDC_BTN_TEST,			m_BTN_bTest);
	DDX_Control(pDX, IDC_BTN_STOP,			m_BTN_bStop);
	DDX_Control(pDX, IDC_BTN_RETEST,		m_BTN_bRetest);
	DDX_Control(pDX, IDC_BTN_HDLR,			m_BTN_bHdlr);
	DDX_Control(pDX, IDC_BTN_MODE_SELECT,	m_BTN_bMode);
	DDX_Control(pDX, IDC_BTN_MODE_SELECT2,	m_BTN_bMode2);

	DDX_Control(pDX, IDC_CWN_EX2,	m_CWN_EX);

	DDX_Control(pDX, IDC_LIST_SPEC,			m_ListSpec);
	DDX_Control(pDX, IDC_LIST_DATA,			m_ListData);
	DDX_Control(pDX, IDC_LIST_LINMSG,		m_ListLinMsg);
//	DDX_Control(pDX, IDC_LIST_SERIAL,		m_ListSerial);

	DDX_Control(pDX, IDC_CNB_STAND_BY,		m_CNB_Standby);

	DDX_Control(pDX, IDC_EDIT_TIME,			m_CNE_fTime);
	DDX_Control(pDX, IDC_EDIT_GOOD,			m_CNE_nGood);
	DDX_Control(pDX, IDC_EDIT_FAIL,			m_CNE_nFail);
	DDX_Control(pDX, IDC_EDIT_YIELD,		m_CNE_fYield);
	DDX_Control(pDX, IDC_CNE_DNUM,			m_CNE_nDnum);

	DDX_OCBool(pDX,  IDC_BTN_REMOTE, DISPID(2), m_bRemoteTestEnable);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_EDIT1, m_edit_ex);
}

BEGIN_EVENTSINK_MAP(CLIN_ProgrammingView, CFormView)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_SPEC,	DISPID_CLICK, CLIN_ProgrammingView::ClickCnbSelSpec,	VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_TEST,	DISPID_CLICK, CLIN_ProgrammingView::ClickBtnTest,		VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_STOP,	DISPID_CLICK, CLIN_ProgrammingView::ClickBtnStop,		VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_RETEST,	DISPID_CLICK, CLIN_ProgrammingView::ClickBtnRetest,		VTS_NONE)

	ON_EVENT(CLIN_ProgrammingView, IDC_CWN_EX2,	DISPID_CLICK, CLIN_ProgrammingView::ClickCwnEx,		VTS_NONE)

	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_EXIT,	DISPID_CLICK, CLIN_ProgrammingView::ClickBtnExit,		VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_REMOTE,  DISPID_CLICK, CLIN_ProgrammingView::ClickBtnRemote,		VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_HDLR,	DISPID_CLICK, CLIN_ProgrammingView::ClickBtnHdlr,		VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_MODE_SELECT, DISPID_CLICK, CLIN_ProgrammingView::ClickBtnModeSelect, VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_BTN_MODE_SELECT2, DISPID_CLICK, CLIN_ProgrammingView::ClickBtnModeSelect2, VTS_NONE)
	ON_EVENT(CLIN_ProgrammingView, IDC_CWN_EX2, 1, CLIN_ProgrammingView::ValueChangedCwnEx2, VTS_BOOL)
END_EVENTSINK_MAP()

BOOL CLIN_ProgrammingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLIN_ProgrammingView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	g_pLinProgView = this;
	pTest	= new CTest_Main;

	AfxGetMainWnd()->MoveWindow(0, 0, 1280, 1024);


	// Button Image Init ///////////////////////////////////////////////////////////////////////////
	WndDisplay_TestImage (0, TEST_IMAGE_STOP);

	// ProgressBar Init ////////////////////////////////////////////////////////////////////////////
	m_progress.SetRange (0, 90);
	m_progress.SetPos   (0);

	// Control List Font Init ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Font.CreateFont(15,					// nHeight
					  5,					// nWidth 
					  0,					// nEscapement 
					  0,					// nOrientation 
					  FW_DONTCARE,			// FW_BOLD,	nWeight 
					  FALSE,				// bItalic 
					  FALSE,				// bUnderline 
					  0,					// cStrikeOut
					  DEFAULT_CHARSET,		// nCharSet 
					  OUT_DEFAULT_PRECIS,	// nOutPrecision 
					  CLIP_DEFAULT_PRECIS,	// nClipPrecision
					  DEFAULT_QUALITY,		// nQuality 
					  DEFAULT_PITCH,		// nPitchAndFamily 
					  _T("Arial"));			// lpszFacename

	m_ListSpec.SetFont(&m_Font, TRUE);
	m_ListData.SetFont(&m_Font, TRUE);
	m_ListLinMsg.SetFont(&m_Font, TRUE);
//	m_ListSerial.SetFont(&m_Font, TRUE);

	//	ListCtrl Init ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_ListSpec.SetBkColor(RGB(255, 255, 255));
	m_ListData.SetBkColor(RGB(255, 255, 255));
	m_ListLinMsg.SetBkColor(RGB(255, 255, 255));
//	m_ListSerial.SetBkColor(RGB(255, 255, 255));

	m_ListSpec.m_nListIndex = 1;
	m_ListData.m_nListIndex = 2;

	f_ListView_Spec_Header_Init();
	f_ListView_Data_Header_Init();
	f_ListView_LinMsg_Header_Init();
//	f_ListView_Serial_Header_Init();

	// Hardware and Struct Init //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hDlgMain = this->m_hWnd;	
		
	this->UpdateData(FALSE);

	TRACE("CLIN_ProgrammingView::OnInitialUpdate() : hThread_waitTestSigna->Start_0 \n");
	hThread_waitTestSignal = CreateThread (NULL, 0, Thread_waitTestSignal, this, 0, &ThreadID_waitTestSignal);
	set_test_handler_thread ( TEST_HANDLER_THREAD_DISABLE );
	TRACE("CLIN_ProgrammingView::OnInitialUpdate() : hThread_waitTestSigna->Start_1 \n");

	TRACE("CLIN_ProgrammingView::OnInitialUpdate() : system_initialize->Start_0 \n");
	system_initialize (&pTest->m_cState);
	TRACE("CLIN_ProgrammingView::OnInitialUpdate() : system_initialize->Start_1 \n");

	pTest->m_pReg->f_regiRead_testMode_EndMode	(pTest->m_cState.Status.bEngMode);
	pTest->m_pReg->f_regiRead_testMode_HandlerOn(pTest->m_cState.Status.isHdlrOn);
	pTest->m_pReg->f_RegiLoad_testMode_StopMode	(pTest->m_cState.Status.bStopMode);

	this->m_BTN_bMode.SetValue (pTest->m_cState.Status.bEngMode);
	this->m_BTN_bHdlr.SetValue (pTest->m_cState.Status.isHdlrOn);
	this->m_BTN_bMode2.SetValue(pTest->m_cState.Status.bStopMode);


	this->UpdateData (FALSE);

	WndDisplay_TestStatusMsg ("Set Test Spec.",NULL);
	
	Extraction();
}


// CLIN_ProgrammingView diagnostics

#ifdef _DEBUG
void CLIN_ProgrammingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLIN_ProgrammingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLIN_ProgrammingDoc* CLIN_ProgrammingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLIN_ProgrammingDoc)));
	return (CLIN_ProgrammingDoc*)m_pDocument;
}
#endif //_DEBUG


// CLIN_ProgrammingView message handlers
void CLIN_ProgrammingView::OnAppExit()
{
	this->ClickBtnExit();
}

void CLIN_ProgrammingView::OnUserMsgDisplayTestImage ( WPARAM wParam, LPARAM lParam )
{
	
	unsigned jig = (unsigned)wParam;
	unsigned img = (unsigned)lParam;

	CNiButton	*pTStatus;
	pTStatus =  &this->m_CNB_Standby;

	switch (img)
	{
	
	case TEST_IMAGE_TEST:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_TEST		);
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_TEST );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_TEST		);
		break;
		
	case TEST_IMAGE_PASS:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_PASS		);
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_PASS );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_PASS		);
		break;
	
	case TEST_IMAGE_FAIL:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_FAIL		);
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_FAIL );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_FAIL		);
		break;
	
	case TEST_IMAGE_WAIT:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_WAIT		);
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_WAIT );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_WAIT		);
		break;
		
	case TEST_IMAGE_STOP:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_STOP		);
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_STOP );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_STOP		);
		break;
	
	case TEST_IMAGE_READY:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_READY		 );
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_READY );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_READY        );
		break;

	case TEST_IMAGE_DISABLE:
		pTStatus->SetOffColor		( TRESULT_IMAGE_COLOR_DISABLE	   );
		pTStatus->SetOffTextColor	( TRESULT_IMAGE_COLOR_TEXT_DISABLE );
		pTStatus->SetOffText			( TRESULT_IMAGE_STR_DISABLE        );
		break;

	default: break;
	}

}

void CLIN_ProgrammingView::OnUserMsgDisplayTestData (WPARAM wParam, LPARAM lParam)
{
	unsigned nJig   = (unsigned)wParam;
	unsigned nPnum	= (unsigned)lParam;


	CFunc_Spec_Item_Main *pSpec;
	pSpec = &pTest->m_pCSpec->m_vTitem[nPnum].Spec;

	ST_CFUNCDATA_ITEMDATA	*pData;
	pData = &pTest->m_pCTestData->m_testData.vData[0][nPnum];
	
	
	CMyListCtrl * pList;
	pList = &m_ListData;	
	

	CString strTemp;
	strTemp.Empty();




	strTemp.Format("%02d", nPnum + 1);
	pList->SetItemText	  (nPnum, 1, strTemp.operator LPCTSTR());


	strTemp = pTest->f_testdata_conv_to_CString (nPnum, pData->varData);
	pList->SetItemText	  (nPnum, 2, strTemp.operator LPCTSTR());


	if ( pTest->m_pCTestData->m_testData.vData[0][nPnum].bPass == false)
	{
		pList->SetMyTextColor (RGB(255, 0, 0) );			//
		pList->SetItemText	  (nPnum, 3, "NG");
	}
	else
	{
		pList->SetMyTextColor  (RGB(0, 0, 0) );
	}


	if (pTest->m_pCTestData->m_testData.vData[0][nPnum].nFailCount)
	{
		strTemp.Format("%d", pTest->m_pCTestData->m_testData.vData[0][nPnum].nFailCount);
		pList->SetItemText	  (nPnum, 4, strTemp.operator LPCTSTR());
	}
	

	pList->EnsureVisible(nPnum,true);			//원하는 스크롤을 화면에 보이고 싶을때
	m_ListSpec.EnsureVisible(nPnum,true);		//원하는 스크롤을 화면에 보이고 싶을때

}

void CLIN_ProgrammingView::OnUserMsgDisplayLinMessage (WPARAM wParam, KVR_LIN_STRUCT &linBuf)
{
	unsigned nItem = (unsigned)wParam;

	CMyListCtrl	*pList;
	pList = &m_ListLinMsg;

	CString		strTemp;
	strTemp.Empty();

	LV_ITEM lvItem;
	
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.cchTextMax = 0;
	lvItem.pszText = _T("");
	pList->InsertItem(&lvItem);

	unsigned int msec1 = linBuf.msgInfo.timestamp/1000;
	unsigned int msec2 = linBuf.msgInfo.timestamp%1000;
	strTemp.Format(_T("%5d.%03d"), msec1, msec2);
	pList->SetItemText(nItem, 1, strTemp.operator LPCTSTR());

	strTemp.Format(_T("0x%02X"), linBuf.ArbitrationId);
	pList->SetItemText(nItem, 2, strTemp.operator LPCTSTR());

	strTemp.Format(_T("%02X %02X %02X %02X %02X %02X %02X %02X"), linBuf.Data[0]
																, linBuf.Data[1]
																, linBuf.Data[2]
																, linBuf.Data[3]
																, linBuf.Data[4]
																, linBuf.Data[5]
																, linBuf.Data[6]
																, linBuf.Data[7]);
	pList->SetItemText(nItem, 3, strTemp.operator LPCTSTR());

	pList->EnsureVisible(nItem,true);
	m_ListLinMsg.EnsureVisible(nItem,true);

}

void CLIN_ProgrammingView::OnUserMsgDisplayTestResultInit( WPARAM wParam, LPARAM lParam )
{
	unsigned nJig  = (unsigned)wParam;
	unsigned nList = (unsigned)lParam;

	f_ListView_Data_Display_InitTestResult (nList);
}

void CLIN_ProgrammingView::OnUserMsgDisplayTestQuantity (WPARAM wParam, LPARAM lParam)
{
	double total= pTest->m_cState.Result.m_Qty.Curr.nPass + pTest->m_cState.Result.m_Qty.Curr.nFail;

	if (total != 0) 
		m_CNE_fYield.SetValue ( (double)pTest->m_cState.Result.m_Qty.Curr.nPass/total*100);
	else 
		m_CNE_fYield.SetValue ( 0 ); 

	m_CNE_nFail.SetValue ( pTest->m_cState.Result.m_Qty.Curr.nFail);
	m_CNE_nGood.SetValue ( pTest->m_cState.Result.m_Qty.Curr.nPass);	  
}

void CLIN_ProgrammingView::OnUserMsgDisplayTestTime	(WPARAM wParam, LPARAM lParam)
{
	this->m_CNE_fTime.SetValue ( (double)wParam/1000.0 );
}

void CLIN_ProgrammingView::OnUserMsgDisplayStatusRemoteTest (WPARAM wParam, LPARAM lParam)
{
	//if (pTest->m_ts.Status.isTestRun) return;


	if (wParam == 0) 
	{
		this->m_bRemoteTestEnable = false;
	}
	else 
	{
		this->m_bRemoteTestEnable = true;
	}

	

	if( TRUE == this->m_bRemoteTestEnable)						// $ Add by sjkim 2012-0624 --> Change Remote Test
	{
		set_test_handler_thread(TEST_HANDLER_THREAD_ENABLE);
	}
	else
	{
		set_test_handler_thread(TEST_HANDLER_THREAD_DISABLE);
	}



	this->UpdateData (FALSE);
}

void CLIN_ProgrammingView::OnUserMsgDisplayMainScreenReset (WPARAM wParam, LPARAM lParam)
{
	this->f_ListView_Spec_Display ();
	
	this->f_ListView_Data_Display_InitTestResult (1);
}

void CLIN_ProgrammingView::OnUserMsgDisplayTestDnum	(WPARAM wParam, LPARAM lParam)
{
	this->m_CNE_nDnum.SetValue ((double)wParam);
}


void CLIN_ProgrammingView::OnUserMsgRemoteTestRestore (WPARAM wParam, LPARAM lParam)
{
	this->f_remote_start_state_restore();
}

void CLIN_ProgrammingView::OnUserCmdMainBtnTestStart (WPARAM wParam, LPARAM lParam)
{
	if (pTest->m_cState.Status.isTestRun) return;

	pTest->m_cState.Status.bRetest = false;
	
	WndDisplay_TestResultInit (0, 2);

	this->f_Test_Start ();
}

void CLIN_ProgrammingView::OnUserMsgSetButtonStopEnable    (WPARAM wParam, LPARAM lParam)
{
	pTest->m_cState.Status.bTestStopEnable	= ((unsigned)wParam) ? true:false;

	this->m_BTN_bStop.SetValue ( (pTest->m_cState.Status.bTestStopEnable) ? TRUE:FALSE );

	this->UpdateData (FALSE);
}

void CLIN_ProgrammingView::OnUserMsgDisplayProgressPosition(WPARAM wParam, LPARAM lParam)
{
	unsigned pos = (unsigned)lParam;
	m_progress.SetPos(lParam);
}

void CLIN_ProgrammingView::OnMenuSpecOpen ()
{
	ClickCnbSelSpec();
}

void CLIN_ProgrammingView::OnMenuExit ()
{
	ClickBtnExit();
}

void CLIN_ProgrammingView::OnMenuSpecEdit ()
{
	if (pTest->m_cState.Status.isTestRun) return;
	this->f_remote_start_stop_and_state_save();

	if(true != pTest->m_pCSpec->m_stStatus.isLoading_spec)
	{
		AfxMessageBox("Fail Loading Spec. Please Set Test Spec!");
		return ;
	}

	if (pTest->m_cState.Status.bEngMode == false) 
	{
		AfxMessageBox("This is Work Mode. Please Set ENG Mode!");
		return ;
	}

	// Spec Edit Dialog 생성 /////////////////////////////////////////////////////////////////////////
	CDlg_Spec	dlg;

	dlg.m_var.pTest = pTest;
	dlg.m_var.CSpec_pOrg = pTest->m_pCSpec;
	pTest->m_pCSpec->f_CSpec_Copy_to_class (dlg.m_var.CSpec_Edit);

	dlg.DoModal();
	//////////////////////////////////////////////////////////////////////////////////////////////////

	f_spec_change_param_set_display	();

	this->f_remote_start_state_restore();
	
}

void CLIN_ProgrammingView::OnMenuChangePassword() 
{
	if (pTest->m_cState.Status.isTestRun) return;
	this->f_remote_start_stop_and_state_save();

	if (pTest->m_cState.Status.bEngMode == false) 
	{
		AfxMessageBox("This is Work Mode. Please Set ENG Mode!");
		return ;
	}

	CDlg_PasswordChange dlg;
	dlg.DoModal ();	
}

void CLIN_ProgrammingView::OnMenuChangeDataFileSavePath()
{
	if (pTest->m_cState.Status.isTestRun) return;
	this->f_remote_start_stop_and_state_save();

	if (pTest->m_cState.Status.bEngMode == false) 
	{
		AfxMessageBox("This is Work Mode. Please Set ENG Mode!");
		return ;
	}

	CDlg_DataFilePath dlg;
	dlg.DoModal ();	
}


void CLIN_ProgrammingView::OnMenuDiagMcuComport()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::CDlg_Diag_MCU_ComPort dlg;

	dlg.m_cfg.pTest = pTest;

	dlg.DoModal();
}


void CLIN_ProgrammingView::ClickCnbSelSpec()
{
	if (pTest->m_cState.Status.isTestRun) return ; // 테스트 중이면 실행중지

	this->f_remote_start_stop_and_state_save ();


/*	if (true == pTest->m_cState.SysInfo.isLoadingFail_SystemInformation)
	{
		f_display_msg_for_LoadingFail_systemInformation();
		return ;
	}*/

	{
		CFunc_Spec CSpec_temp;

		pTest->m_pCSpec->f_CSpec_Copy_to_class (CSpec_temp);
	
		CFunc_Spec_File specfile(&CSpec_temp);
		if (false == specfile.f_SpecFile_Load (&pTest->m_cState))
		{
			WndDisplay_TestStatusMsg("ERROR : Fail Loading Test Spec","");
			return ;
		}

		pTest->m_pCSpec->f_CSpec_Copy_from_class (CSpec_temp);
	}


	pTest->m_pReg->f_regiSave_Path_TestSpec (pTest->m_pCSpec->m_stStatus.strFilename);


	this->m_sSpecFileName.Format(" SPEC FILE : %s", pTest->m_pCSpec->m_stStatus.strFilename.GetString() );


	//데이타베이스 스펙에 맞게 테이블생성하고 초기화 시작////////////////////////////////////////////////
	pTest->m_pCTestData->f_create_data_vector (pTest->m_pCSpec->m_stStatus.nTitem, 1);	
	bool bRtn = pTest->m_pCSaveDataAccess->f_Create_New_DBFile (1);			// $ delete 2013-0911

	CString sDataFilename = pTest->m_pCSaveDataAccess->m_var.strDBFileName;


	CFunc_FilePath CPath;
	CPath.f_filename_remove_path (sDataFilename);
	//데이타베이스 스펙에 맞게 테이블생성하고 초기화 끝//////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////
	f_spec_change_param_set_display();

	{
		this->m_CNE_fTime.SetValue(0.0);
		this->m_CNE_nDnum.SetValue(0);

		pTest->m_cState.Result.m_Qty.Curr.nFail = 0;
		pTest->m_cState.Result.m_Qty.Curr.nPass = 0;

		double total = pTest->m_cState.Result.m_Qty.Curr.nPass + pTest->m_cState.Result.m_Qty.Curr.nFail;

		if(total != 0)
			m_CNE_fYield.SetValue((double)pTest->m_cState.Result.m_Qty.Curr.nPass/total*100);
		else
			m_CNE_fYield.SetValue(0);

		m_CNE_nFail.SetValue(pTest->m_cState.Result.m_Qty.Curr.nFail);
		m_CNE_nGood.SetValue(pTest->m_cState.Result.m_Qty.Curr.nPass);
	}



	this->UpdateData (FALSE);	

	this->f_remote_start_state_restore();
	WndDisplay_TestStatusMsg ("Complete Set Test Spec!!","");

}

void CLIN_ProgrammingView::ClickBtnTest()
{
	if (pTest->m_cState.Status.isTestRun) return;

	pTest->m_cState.Status.bRetest = false;

	WndDisplay_TestResultInit (0, 2);

	this->f_Test_Start();
}

void CLIN_ProgrammingView::ClickBtnStop()
{
	if ( true == pTest->m_cState.Status.isTestRun )
	{
		pTest->m_cState.Status.bTestStopEnable = true;
	}
	else
	{
		pTest->m_cState.Status.bTestStopEnable = false;
	}
}

void CLIN_ProgrammingView::ClickBtnRetest()
{
	if (pTest->m_cState.Status.isTestRun) return;

	pTest->m_cState.Status.bRetest = true;

	this->f_Test_Start();
}

void CLIN_ProgrammingView::ClickCwnEx() 
{
	// HDLR 상태 읽기
//	pTest->m_pFrdm->f_Read_Buffer(HDLR_ERR, &m_edit_ex);

	this->UpdateData (FALSE);
}

void CLIN_ProgrammingView::ClickBtnExit()
{
	if ( pTest->m_cState.Status.isTestRun ) return;

	if (IDNO == AfxMessageBox("Do you want to Exit?", MB_YESNO,NULL) )
	{
		WndDisplay_TestStatusMsg("검사프로그램 종료가","취소되었습니다.");
		return;
	}
	
	set_test_handler_thread(TEST_HANDLER_THREAD_DISABLE);
	Sleep(100);

	CloseHandle (hThread_waitTestSignal);

	pTest->m_pInst->m_pVsrc->f_reset (0);

	delete pTest;


	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}



void CLIN_ProgrammingView::f_Test_Start()
{
	if ( true == pTest->m_cState.Status.isTestRun ) return;
	
	if ( false == pTest->m_pCSpec->m_stStatus.isLoading_spec )
	{
		WndDisplay_TestStatusMsg("ERROR : Fail Loading Test Spec","");
		return ;
	}

	// 핸들러 관련 함수 추가

	WndDisplay_TestStatusMsg("Test Start!!!","");

	this->f_remote_start_stop_and_state_save();

	pTest->m_cState.Status.nDnum = (unsigned)this->m_CNE_nDnum.GetValue();


	hThread_Test = CreateThread(NULL, 0, Thread_MainCmd_Test, this, 0, &ThreadID_Test);

	CloseHandle(hThread_Test);

	return ;
}

void CLIN_ProgrammingView::f_remote_start_stop_and_state_save()
{
	this->UpdateData(TRUE);
	
	pTest->m_cState.Status.isRemoteTestEnable		 = this->m_bRemoteTestEnable ? true:false;
	pTest->m_cState.Status.isRemoteTestEnable_Backup = this->m_bRemoteTestEnable ? true:false;


	set_test_handler_thread (TEST_HANDLER_THREAD_DISABLE);

	pTest->m_cState.Status.isRemoteTestEnable = this->m_bRemoteTestEnable ? true : false;

	this->UpdateData(FALSE);	
}

void CLIN_ProgrammingView::f_remote_start_state_restore()
{
	this->UpdateData(TRUE);
	
	if (this->m_bRemoteTestEnable)
	{
		set_test_handler_thread( TEST_HANDLER_THREAD_ENABLE);
	}

}

void CLIN_ProgrammingView::f_spec_change_param_set_display()
{

	this->f_ListView_Spec_Display ();
	this->f_ListView_Data_Display_InitTestResult (1);

	this->m_CNB_sDeviceName.SetOffText (pTest->m_pCSpec->m_stSpecInfo.tspec.strDeviceName);
	this->m_CNB_sSpecName.SetOffText   (pTest->m_pCSpec->m_stSpecInfo.tspec.strSpecName);

	WndDisplay_TestImage (0, TEST_IMAGE_WAIT);


	this->UpdateData(FALSE);

}


void CLIN_ProgrammingView::f_ListView_Spec_Header_Init (void)
{
	CMyListCtrl		*pList;

	pList = &m_ListSpec;

	pList->SetExtendedStyle(LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	CRect rect;
	pList->GetClientRect(&rect);
	
	LVCOLUMN lc;
	lc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lc.fmt = LVCFMT_CENTER;

	int x;
	int nW	= rect.Width() - 360;

	x = 0; lc.iSubItem = x; lc.cx =   0; lc.pszText = "";			lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 1; lc.iSubItem = x; lc.cx =  50; lc.pszText = "TNo";		lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 2; lc.iSubItem = x; lc.cx =  100; lc.pszText = "Symbol";	lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 3; lc.iSubItem = x; lc.cx =  242; lc.pszText = "Item";		lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 4; lc.iSubItem = x; lc.cx =  70; lc.pszText = "Unit";		lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 5; lc.iSubItem = x; lc.cx =  50; lc.pszText = "LOL";		lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);
	x = 6; lc.iSubItem = x; lc.cx =  50; lc.pszText = "HIL";		lc.fmt = LVCFMT_CENTER; pList->InsertColumn( x, &lc);

}

void CLIN_ProgrammingView::f_ListView_Data_Header_Init (void)
{
	CMyListCtrl		*pList;

	pList = &m_ListData;

	pList->SetExtendedStyle(LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;
	pList->GetClientRect(&rect);

	LVCOLUMN lc;
	lc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	
	int x = 0;
	int sum_w = 0;

	x = 0; lc.iSubItem = x;	lc.cx = 0;	lc.fmt = LVCFMT_CENTER;	lc.pszText = "";		pList->InsertColumn(x, &lc);
	x = 1; lc.iSubItem = x;	lc.cx = 40;	lc.fmt = LVCFMT_RIGHT;	lc.pszText = "No";		pList->InsertColumn(x, &lc);
	x = 2; lc.iSubItem = x;	lc.cx = 76;	lc.fmt = LVCFMT_RIGHT;	lc.pszText = "Data";	pList->InsertColumn(x, &lc);
	x = 3; lc.iSubItem = x;	lc.cx = 76;	lc.fmt = LVCFMT_CENTER; lc.pszText = "Judge";	pList->InsertColumn(x, &lc);
	x = 4; lc.iSubItem = x;	lc.cx = 0;	lc.fmt = LVCFMT_CENTER;	lc.pszText = "Ref";		pList->InsertColumn(x, &lc);

}

void CLIN_ProgrammingView::f_ListView_LinMsg_Header_Init (void)
{
	CMyListCtrl		*pList;

	pList = &m_ListLinMsg;

	pList->SetExtendedStyle(LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;
	pList->GetClientRect(&rect);

	LVCOLUMN lc;
	lc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	
	int x = 0;
	int sum_w = 0;

	x = 0; lc.iSubItem = x;	lc.cx = 0;		lc.fmt = LVCFMT_CENTER;	lc.pszText = "";			pList->InsertColumn(x, &lc);
	x = 1; lc.iSubItem = x;	lc.cx = 120;	lc.fmt = LVCFMT_CENTER;	lc.pszText = "Time";		pList->InsertColumn(x, &lc);
	x = 2; lc.iSubItem = x;	lc.cx = 100;	lc.fmt = LVCFMT_CENTER;	lc.pszText = "Identifier";	pList->InsertColumn(x, &lc);
	x = 3; lc.iSubItem = x;	lc.cx = 300;	lc.fmt = LVCFMT_LEFT;	lc.pszText = "Data";		pList->InsertColumn(x, &lc);
	x = 4; lc.iSubItem = x;	lc.cx = 250;	lc.fmt = LVCFMT_LEFT;	lc.pszText = "Ref";			pList->InsertColumn(x, &lc);

}

void CLIN_ProgrammingView::f_ListView_Data_Display_InitTestResult(unsigned nList)
{
	LV_ITEM		lvItem;

	CMyListCtrl	*pList;
	CString		strTemp;

	unsigned	nTnum;
		
	if(nList == 1)
	{
		pList = &m_ListData;
		pList->DeleteAllItems();

		for ( nTnum=0; nTnum < pTest->m_pCSpec->m_stStatus.nTitem; nTnum++)
		{
			int nItemNum = pList->GetItemCount();

			lvItem.iItem	  = nItemNum;
			lvItem.iSubItem   = 0;
			lvItem.mask		  = LVIF_PARAM | LVIF_TEXT;
			lvItem.cchTextMax = 0;
			lvItem.pszText	  = "";

			pList->InsertItem(&lvItem);
			pList->SetMyTextColor( RGB(0, 0, 0) );

			strTemp.Empty();
			pList->SetItemText (nTnum, 1, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 2, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 3, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 4, strTemp.operator LPCTSTR());
		}
	}
	else if(nList == 2)
	{
		pList = &m_ListLinMsg;
		pList->DeleteAllItems();

		for ( nTnum=0; nTnum < pTest->m_pCSpec->m_stStatus.nTitem; nTnum++)
		{
			int nItemNum = pList->GetItemCount();

			lvItem.iItem	  = nItemNum;
			lvItem.iSubItem   = 0;
			lvItem.mask		  = LVIF_PARAM | LVIF_TEXT;
			lvItem.cchTextMax = 0;
			lvItem.pszText	  = "";

			pList->InsertItem(&lvItem);
			pList->SetMyTextColor( RGB(0, 0, 0) );

			strTemp.Empty();
			pList->SetItemText (nTnum, 1, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 2, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 3, strTemp.operator LPCTSTR());
			pList->SetItemText (nTnum, 4, strTemp.operator LPCTSTR());
		}
	}
	

	
}

void CLIN_ProgrammingView::f_ListView_Spec_Display (void)
{
	CMyListCtrl *pList;
	pList	= &m_ListSpec;
		
	CString strTemp;
	CFunc_Spec_Item_Main *pSpec;
	CString sHIL,sLOL;

	m_ListSpec.LockWindowUpdate();

	m_ListSpec.DeleteAllItems();

	
	LV_ITEM lv;

	int nLow = 0;
	int nItemNum = m_ListSpec.GetItemCount();
	lv.iItem = nLow;
	lv.iSubItem = 0;
	lv.mask = LVIF_PARAM | LVIF_TEXT;
	lv.cchTextMax = 0;
	lv.pszText = "";
		


	for (unsigned pnum=0;pnum < pTest->m_pCSpec->m_stStatus.nTitem; pnum++)
	{
					
		pSpec =  &pTest->m_pCSpec->m_vTitem[pnum].Spec;

		{
			pList = &m_ListSpec;

			nLow = pnum*2 +0;

			lv.iItem = nLow;
			pList->InsertItem(&lv);		
		}


		{
			pList = &m_ListSpec;
			nLow = pnum ;
			pList->InsertItem(&lv);

			
			strTemp.Format("%02d", pnum+1);		
			pList->SetItemText(nLow, 1, strTemp.operator LPCTSTR());

			strTemp.Format("%s", pSpec->strTestSymbol.GetString());
			pList->SetItemText(nLow, 2, strTemp.operator LPCTSTR());

			strTemp.Format("%s", pSpec->strTestName.GetString());
			pList->SetItemText(nLow, 3, strTemp.operator LPCTSTR());

			pList->SetItemText(nLow, 4, pSpec->strTestUnit);
	
			pTest->f_testdata_conv_spec_to_CString(pnum, sHIL, sLOL);

			pList->SetItemText(nLow, 5, sLOL.operator LPCTSTR());
			pList->SetItemText(nLow, 6, sHIL.operator LPCTSTR());
		}

	}

	m_ListSpec.UnlockWindowUpdate();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scroll Function
void MySetScrollPos(UINT nPos)
{
	int x, nDirection, nCount, nOldPos;
	
	if(g_nListIndex == 1)
		nOldPos = g_pLinProgView->m_ListData.GetScrollPos(SB_VERT);
	else
		nOldPos = g_pLinProgView->m_ListSpec.GetScrollPos(SB_VERT);



	if(int(nPos) > nOldPos)
	{
		nDirection = SB_LINEDOWN;
		nCount = nPos - nOldPos;
	}
	else
	{
		nDirection = SB_LINEUP;
		nCount = nOldPos - nPos;
	}
	
	g_bListCtlIsFun = TRUE;
	for(x = 0;x < nCount;x++)
	{
		g_pLinProgView->m_ListSpec.SendMessage(WM_VSCROLL, nDirection);
		g_pLinProgView->m_ListData.SendMessage(WM_VSCROLL, nDirection);
	}
	g_bListCtlIsFun = FALSE;
}

void MySetScrollLineDown()
{
	g_bListCtlIsFun = TRUE;
	g_pLinProgView->m_ListSpec.SendMessage(WM_VSCROLL, SB_LINEDOWN);
	g_pLinProgView->m_ListData.SendMessage(WM_VSCROLL, SB_LINEDOWN);
	g_bListCtlIsFun = FALSE;
}

void MySetScrollLineUp()
{
	g_bListCtlIsFun = TRUE;
	g_pLinProgView->m_ListSpec.SendMessage(WM_VSCROLL, SB_LINEUP);
	g_pLinProgView->m_ListData.SendMessage(WM_VSCROLL, SB_LINEUP);
	g_bListCtlIsFun = FALSE;
}

void MySetScrollPageDown()
{
	int nScrollnum = 5, x;
	g_bListCtlIsFun = TRUE;
	for(x = 0;x < nScrollnum;x++)
	{
		g_pLinProgView->m_ListSpec.SendMessage(WM_VSCROLL, SB_LINEDOWN);
		g_pLinProgView->m_ListData.SendMessage(WM_VSCROLL, SB_LINEDOWN);
	}
	g_bListCtlIsFun = FALSE;
}

void MySetScrollPageUp()
{
	int nScrollnum = 5, x;
	g_bListCtlIsFun = TRUE;
	for(x = 0;x < nScrollnum;x++)
	{
		g_pLinProgView->m_ListSpec.SendMessage(WM_VSCROLL, SB_LINEUP);
		g_pLinProgView->m_ListData.SendMessage(WM_VSCROLL, SB_LINEUP);
	}
	g_bListCtlIsFun = FALSE;
}

void CLIN_ProgrammingView::ClickBtnRemote()
{
	// TODO: Add your message handler code here
	if (this->m_bRemoteTestEnable) 
	{
		this->m_bRemoteTestEnable = false;
	}
	else 
	{
		this->m_bRemoteTestEnable = true;
	}
	
	this->UpdateData (FALSE);


	if (pTest->m_cState.Status.isTestRun) return;	// 검사도중에 HANDLER INTERFACE 신호를 DISABLE할수 있도록 하기 위하여
	

	if( TRUE == this->m_bRemoteTestEnable)						// $ Change by sjkim 2012-0624 --> Change Remote Test
	{
		set_test_handler_thread(TEST_HANDLER_THREAD_ENABLE);
	}
	else
	{
		set_test_handler_thread(TEST_HANDLER_THREAD_DISABLE);
	}

}

void CLIN_ProgrammingView::ClickBtnHdlr()
{
	// TODO: Add your message handler code here
//	pTest->m_cState.Status.isHdlrOn = this->m_BTN_bHdlr.GetValue();

//	pTest->m_pReg->f_RegiSave_testMode_HandlerOn (pTest->m_cState.Status.isHdlrOn);

//	this->UpdateData (FALSE);
}


void CLIN_ProgrammingView::ClickBtnModeSelect()
{
	// TODO: Add your message handler code here
	if (true == pTest->m_cState.Status.isTestRun) return;
	this->f_remote_start_stop_and_state_save ();

	bool b = this->m_BTN_bMode.GetValue();

	if ( b == true )
	{									
		CDlg_PasswordCheck dlg;					

		if ( IDOK != dlg.DoModal() )
		{
			this->m_BTN_bMode.SetValue (false);
		}
		else 
		{
			pTest->m_cState.Status.bEngMode = true;
		}
	}
	else 
	{
		pTest->m_cState.Status.bEngMode = false;		
	}
	
	pTest->m_pReg->f_regiSave_testMode_EngMode (pTest->m_cState.Status.bEngMode);

	this->f_remote_start_state_restore();

}

void CLIN_ProgrammingView::ClickBtnModeSelect2()
{
	// TODO: Add your message handler code here
	if (true == pTest->m_cState.Status.isTestRun) return;
	this->f_remote_start_stop_and_state_save ();

	bool b = this->m_BTN_bMode2.GetValue();

	if ( b == true )
	{									
		CDlg_PasswordCheck dlg;					

		if ( IDOK != dlg.DoModal() )
		{
			this->m_BTN_bMode2.SetValue (false);
		}
		else 
		{
			pTest->m_cState.Status.bStopMode = true;
		}
	}
	else 
	{
		pTest->m_cState.Status.bStopMode = false;		
	}
	
	pTest->m_pReg->f_RegiSave_testMode_StopMode (pTest->m_cState.Status.bStopMode);

	this->f_remote_start_state_restore();

}

void CLIN_ProgrammingView::ValueChangedCwnEx2(BOOL Value)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


CString CLIN_ProgrammingView::Decryption(CString strTemp)
{
	CString		Password;
	char		szDataIn[33]  = { 0, };
	char		szDataOut[33] = { 0, };

	for (int i = 0; i < 33; i++)
	{
		CString temp = strTemp.Left(2);

		char* pData = LPSTR(LPCTSTR(temp));

		szDataIn[i] = (char)strtol(pData, NULL, 16);

		strTemp.Delete(0, 2);
	}


	CRijndael	oRijndael;

	oRijndael.MakeKey("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "11111111111111111111111111111111", 32, 32);

	oRijndael.DecryptBlock(szDataIn, szDataOut);

	for (int i = 0; i < 33; i++)
	{
		CString temp;
		temp.Format(_T("%c"), (unsigned char)szDataOut[i]);
		Password += temp;
	}

	return Password;
}


CString CLIN_ProgrammingView::GetMacAddress()
{
	CString Temp;

	DWORD Size = sizeof(PIP_ADAPTER_INFO);

	PIP_ADAPTER_INFO Info;

	ZeroMemory(&Info, Size);

	int Result = GetAdaptersInfo(Info, &Size);
	if (Result == ERROR_BUFFER_OVERFLOW)
	{
		Info = (PIP_ADAPTER_INFO)malloc(Size);
		GetAdaptersInfo(Info, &Size);
	}

	if (!Info)
	{
		Temp.Format("MAC Address를 불러오는데 실패하였습니다.");
		return Temp;
	}

	Temp.Format("%02X-%02X-%02X-%02X-%02X-%02X", Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);


	return Temp;
}


void CLIN_ProgrammingView::Extraction()
{
	CString		strTemp, strFileName;
	CString		DecryptFileName, DecryptMacAddr, DecryptCreationDate, DecryptPriodOfUse;
	CString		FileName, MacAddr, CurTimeText;
	char		buffer[1000];


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 라이센스 데이터 추출 및 저장
	MacAddr = GetMacAddress();
	MacAddr.Remove('-');

	CurTime = CTime::GetCurrentTime();
	CurTimeText.Format(_T("%04d-%02d-%02d"), CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());
	CurTimeText.Remove('-');
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	CFileFind finder;
	BOOL bWorking = finder.FindFile("LinE.lic");
	if(bWorking == 0)
	{
		AfxMessageBox("라이센스를 찾을 수 없습니다.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}

	while(bWorking)
	{
		bWorking = finder.FindNextFile();

         if(!finder.IsDirectory())
			 strFileName = finder.GetFileName();
	}


	
	CFile file;
	file.Open((LPCTSTR)strFileName, CFile::modeRead);
	file.Read(buffer, 132);
	file.Close();


	CString	CheckKey((LPCTSTR)buffer);


	strTemp = Decryption(CheckKey);

	int len = 0;
	len = strTemp.GetLength();

	TCHAR a;
	unsigned idx_1 = 0;
	for (int i=0; i<len; i++)
	{
		a = strTemp.GetAt(i);
		if (a == ' ')
		{
			idx_1 = i;
			break;
		}
	}


	DecryptMacAddr = strTemp.Mid(4, 12);
	if (MacAddr.CompareNoCase(DecryptMacAddr) != NULL)
	{
		//		AfxMessageBox("라이센스 키와 불일치 합니다.\n프로그램을 종료합니다.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}

	DecryptCreationDate = strTemp.Mid(16, 8);
	if (CurTimeText.CompareNoCase(DecryptCreationDate) < NULL)
	{
		//		AfxMessageBox("라이센스 키와 불일치 합니다.\n프로그램을 종료합니다.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}

	DecryptPriodOfUse = strTemp.Mid(24, 8);
	if (CurTimeText.CompareNoCase(DecryptPriodOfUse) > NULL)
	{
		if (DecryptPriodOfUse.Left(2) == "00")
			return;

		//		AfxMessageBox("라이센스 키와 불일치 합니다.\n프로그램을 종료합니다.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}

}