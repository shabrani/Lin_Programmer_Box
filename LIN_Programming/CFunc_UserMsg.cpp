#include "stdafx.h"
#include "CFunc_UserMsg.h"
#include "CTest_Main.h"
#include "CFunc_FilePath.h"

#include "MyListCtrl.h"
#include "LIN_ProgrammingDoc.h"
#include "LIN_ProgrammingView.h"


extern HWND hList;
extern HWND hProgress_Test;
extern HWND hDlgMain;

extern HWND hWnd_Result_Fail;
extern HWND hWnd_Result_Pass;
extern HWND hWnd_Result_Test;
extern HWND hWnd_Result_Wait;

extern CLIN_ProgrammingView	*g_pLinProgView;

extern CTest_Main			*pTest;

CFunc_UserMsg::CFunc_UserMsg(void)
{
}


CFunc_UserMsg::~CFunc_UserMsg(void)
{
}



void CFunc_UserMsg::f_LIN_LView_Insert_QData  (unsigned nPnum, unsigned nStep, unsigned nQIndex)
{
	TU_UINT32 u;
	
	u.U16.s0 = nQIndex;
	u.U16.s1 = nStep;

	SendMessage(g_pLinProgView->m_hWnd, USERMSG_LV_LIN_INSERT_QDATA, (WPARAM)nPnum, (LPARAM)u.uint32);
}

void CFunc_UserMsg::f_disp_tproc_data_msg(unsigned pnum, unsigned idx, double fData, CString sMsg)
{

	if(false == m_cfg.pts->Status.bTestProcessDataView) 
		return;

	this->m_TestProcDataMsg.fData	= fData;
	this->m_TestProcDataMsg.nPnum	= pnum;
	this->m_TestProcDataMsg.nIdx	= idx;
	this->m_TestProcDataMsg.sMsg	= sMsg;

	
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_LV_INSERT_TEST_PROC_DATA, (WPARAM)pnum, (LPARAM)idx);
}



void CFunc_UserMsg::f_LIN_LView_Insert_Msg    (char *s, bool bNextLine)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_LV_LIN_INSERT_MSG, (WPARAM)s, (LPARAM)bNextLine);
}


void CFunc_UserMsg::f_LIN_LView_SendTimer_On (bool bTimerOn, unsigned nTime_MS)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_LIN_SEND_TIMER_ON, (WPARAM)bTimerOn, (LPARAM)nTime_MS);	// $ Delete 2013.11.13 
}



void CFunc_UserMsg::f_ReTest_Start (void)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_MAIN_BTN_RETEST_START, (WPARAM)0, (LPARAM)0);
}

void CFunc_UserMsg::f_Test_Start   (void)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_MAIN_BTN_TEST_START, (WPARAM)0, (LPARAM)0);
}



void f_display_msg_for_LoadingFail_systemInformation()
{

	CString msg;			

	if (pTest->m_cState.SysInfo.isLoading_CompanyName != true)
	{
		msg = "시스템 정보가 부족합니다.";
		msg += "\n";
		msg += "회사명을 등록해주세요";
	}
	else if (pTest->m_cState.SysInfo.isLoading_DivisionName != true)
	{
		msg = "시스템 정보가 부족합니다.";
		msg += "\n";
		msg += "부서명을 등록해주세요";
	}
	else if (pTest->m_cState.SysInfo.isLoading_SystemInformationFile != true)
	{
		msg = "시스템 정보화일을 열지 못했습니다.";
		msg += "\n";
		msg += "시스템 화일을 등록해주세요";
	}
	else
	{
		msg = "시스템 정보가 수정되었습니다.";
		msg += "\n";
		msg += " 프로그램을 다시 시작해 주세요";
	}

	display_msg_for_warning ( msg  );

}

void display_errmsg_and_exit(const char *msg)
{
	MessageBox(NULL, msg, "ERROR MESSAGE", MB_OK);

	SendMessage(hDlgMain, WM_COMMAND, (WPARAM)ID_ALLWAYS_EXIT, (LPARAM)0);
	Sleep (1000);
	exit (-1);
}

void display_errmsg_and_conform(const char *msg)
{	
	UINT result;
	result = MessageBox(NULL, msg, "ERROR MESSAGE", MB_YESNO);
	
	if (result == IDYES)
	{
		SendMessage(hDlgMain, WM_COMMAND, (WPARAM)ID_ALLWAYS_EXIT, (LPARAM)0);
		Sleep (1000);
		exit (-1);
	}
}
			

void display_msg_for_warning( const char *msg )
{
	//MessageBox(NULL, msg, "WARNING", MB_OK);
	MessageBox(NULL, msg, "WARNING", NULL);
}

void display_msg_for_Information ( const char *msg )
{
	MessageBox(NULL, msg, "Information", MB_OK);
}



void display_test_prog_filename(char *name)
{
	//::SetDlgItemText(hDlgMain, IDC_EDIT_PROG_FILENAME, name);			// $ Delete 2014.10.113 sjkim
}
	
void display_test_window_text(char *name)
{
	SetWindowText(hDlgMain, name);
}

void display_test_device_name (char* device_name)
{
	// SetDlgItemText(hDlgMain, IDC_EDIT_TEST_DEVICE, device_name);// $ Delete 2014.10.113 sjkim
}

void display_test_spec_name (char* spec_name)
{
	// SetDlgItemText(hDlgMain, IDC_EDIT_TEST_SPEC,   spec_name); // $ Delete 2014.10.113 sjkim
}

void display_test_spec_revno (char* szRevNo)
{
//	SetDlgItemText(hDlgMain, IDC_EDIT_TEST_SPEC_REV_NO,   szRevNo);	// $ Delete 2014.10.113 sjkim
}


void display_test_spec_revno (int nRevNo)
{
	char buf[10];
	sprintf_s(buf,"%d",nRevNo);
	display_test_spec_revno(buf);
}




		
void display_test_prog_name (char *name)
{
//	SetDlgItemText (hDlgMain, IDC_MAIN_TEST_PROG, name);// $ Delete 2014.10.113 sjkim
}


void display_data_filename(char *filename)
{
	char buf [ MAX_PATH ];

	strcpy_s (buf, filename);
	
	CFunc_FilePath	CPath;
	CPath.f_filename_remove_path ( buf );
	CPath.f_filename_remove_ext  ( buf );
//	SetDlgItemText(hDlgMain, IDC_EDIT_DATA_FILENAME, buf );	// $ Delete 2014.10.113 sjkim
}				

void display_data_filename_nosave ( char *buf )
{
//	SetDlgItemText (hDlgMain, IDC_EDIT_DATA_FILENAME, buf );// $ Delete 2014.10.113 sjkim
}

/*
void display_device_number(unsigned int test_dnum)
{
		char buf[10];

		//test_dnum=999;
		wsprintf ( buf, "%d", test_dnum);
		SetDlgItemText(hDlgMain, IDC_EDIT_DEVICE_NUM, buf );
}
*/
/*
void display_device_pass_fail(long pass, long fail)
{
	long total;
	char szStr[10];

	total = pass + fail;
	double rate;

//	if (total !=0)
	{
		wsprintf(szStr, "%d", total);
		SetDlgItemText (hDlgMain, IDC_EDIT_DEVICE_TOTAL, szStr);
		
		wsprintf(szStr, "%d", pass);
		SetDlgItemText (hDlgMain, IDC_EDIT_DEVICE_PASS, szStr);
		
		wsprintf(szStr, "%d", fail);
		SetDlgItemText (hDlgMain, IDC_EDIT_DEVICE_FAIL, szStr);
		
		if (fail+pass) 
		{
			rate = (double) fail / (fail+pass);
		} else 
			rate = 0;

		sprintf(szStr, "%5.1f %C", rate * 100, '%' );
	    SetDlgItemText (hDlgMain, IDC_EDIT_DEVICE_FAIL_RATIO, szStr);	
	}
}*/

void display_test_time(CTest_State *ts)
{
	LARGE_INTEGER t;		//current time
	double test_time; 

	if (ts->Timer64_Freq.QuadPart != 0)
	{
		::QueryPerformanceCounter(&t);
		test_time =  (double) ( t.QuadPart - ts->Timer64_sTime.QuadPart ) /	(double) ts->Timer64_Freq.QuadPart;
		WndMsgCmd_display_test_time ( UINT(( test_time * 1000.0 ) ));
	}
}



/*
void Display_ListView_HeadLine( void )
{
	LVCOLUMN col;

//LVM_GETITEMSPACING 
    //wParam = (WPARAM) (BOOL) fSmall; 
    //lParam = 0; 
//	SendMessage(hList, LVM_SETITEMSPACING , (BOOL)1,0);

	ListView_SetExtendedListViewStyle(hList, LVS_EX_GRIDLINES);
	
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	col.fmt  = LVCFMT_CENTER;
	
	col.cx = 50;
	col.pszText = "순번";
	col.iSubItem = 0;
	ListView_InsertColumn ( hList, 0, &col );
	//SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&col);
	
	col.cx = 260;
	col.pszText = "항목";
	col.iSubItem = 1;
	ListView_InsertColumn ( hList, 1, &col );

    //wParam = (WPARAM)(INT) iCount;
    //lParam = (LPARAM) MAKELPARAM(cx, cy);

//	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&col);

	col.cx = 100;
	col.pszText = "측정값";
	col.iSubItem = 2;
	ListView_InsertColumn ( hList, 2, &col );
//	SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&col);

	col.cx = 60;
	col.pszText = "단위";
	col.iSubItem = 3;
	ListView_InsertColumn ( hList, 3, &col );
	//	SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&col);
	
	col.cx = 100;
	col.pszText = "하한규격";
	col.iSubItem = 4;
	ListView_InsertColumn ( hList, 4, &col );
	//SendMessage(hList, LVM_INSERTCOLUMN, 4, (LPARAM)&col);

	col.cx = 100;
	col.pszText = "상한규격";
	col.iSubItem = 5;
	ListView_InsertColumn ( hList, 5, &col );
	//SendMessage(hList, LVM_INSERTCOLUMN, 5, (LPARAM)&col);

	col.cx = 60;
	col.pszText = "결과";
	col.iSubItem = 6;
	ListView_InsertColumn ( hList, 7, &col );
	//SendMessage(hList, LVM_INSERTCOLUMN, 7, (LPARAM)&col);
}

void Display_ListView_Spec (CTest_State *ts)
{
	unsigned test_num, pnum;

	char tdesc[STRSIZE_SYMBOL + STRSIZE_DESC + 5] ;

	LVITEM   li;

	li.mask = LVIF_TEXT;
	li.state = 0;
	li.stateMask = 0;

	char szTemp [10];
	
	ListView_DeleteAllItems(hList);		
	SendMessage (hList, LVM_SETTEXTCOLOR, 0, COLOR_BLACK);

	//unsigned tmax = ts->testproc.proc_tmax;


	for(unsigned t=0; t < ts->specInfo.tspec.titem; t++)
	{
		wsprintf(szTemp, "%3d", t+1);
		li.iItem    = t;
		li.iSubItem = 0;
		li.pszText  = szTemp;

		SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&li);
	}


	for(t=0; t < ts->specInfo.tspec.titem; t++)
	{
		pnum = ts->ftest_index [t].nNum;

		if (ts->ftest[pnum].spec.isTest ) 
		{
			test_num = ts->ftest[pnum].spec.test_num;
			
			strcpy (tdesc, ts->ftest[pnum].spec.symbol);
			strcat (tdesc, ".  "             );
			strcat (tdesc, ts->ftest[pnum].spec.desc);

			ListView_SetItemText (hList, test_num - 1 , 1, tdesc);	

			ListView_SetItemText (hList, test_num - 1 , 2, "");
			ListView_SetItemText (hList, test_num - 1,  3, ts->ftest[pnum].spec.unit);
		
			sprintf(szTemp, "%8.3f", ts->ftest[pnum].spec.los);
			ListView_SetItemText (hList, test_num - 1, 4, szTemp);
		
			sprintf(szTemp, "%8.3f", ts->ftest[pnum].spec.his);
			ListView_SetItemText (hList, test_num - 1, 5, szTemp);
		}

	}
}
*/


void WndMsgCmd_Main_BtnTestStart (void)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_MAIN_BTN_TEST_START, (WPARAM)0, (LPARAM)0);
}

void WndMsgCmd_display_test_quantity (void)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_QUANTITY, (WPARAM)0, (LPARAM)0);
}

void WndMsgCmd_Diag_BreakPoint_Test (void)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_COMMAND_DIAG_BREAKPOINT_TEST, (WPARAM)0, (LPARAM)0);
}

void WndMsgCmd_Display_LotNo( void )
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_LOT_NO, NULL, NULL);
}

//void WndMsgCmd_AddTotalAmount (void)



void WndDisplay_TestData( unsigned nJig, unsigned pnum )
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_DATA, (WPARAM)nJig, (LPARAM)pnum);
}

void WndDisplay_TestLinMsg( unsigned pnum, KVR_LIN_STRUCT &linBuf )
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_LIN_MSG, (WPARAM)pnum, (LPARAM)&linBuf);
}

void WndDisplay_SerialMsg(unsigned line, unsigned &addr)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_SERIAL_DATA, (WPARAM)line, (LPARAM)&addr);
}

void WndDisplay_TestStatusMsg (char *s1, char *s2)
{
	SetDlgItemText (hDlgMain, IDC_MAIN_EDIT_TESTSTATUS_MSG1, s1 );	
	SetDlgItemText (hDlgMain, IDC_MAIN_EDIT_TESTSTATUS_MSG2, s2 );
}
	


void WndDisplay_progress_position (unsigned jig, unsigned pos)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_PROGRESS_POS, (WPARAM)jig, (LPARAM)pos);
}	

void WndMsgCmd_display_ChkBtn_Ch(bool bChkBtn_Ch1, bool bChkBtn_Ch2, bool bRetest)
{
	UINT	uData = 0;

	if (bRetest     ) uData += K0;
	if (bChkBtn_Ch1) uData += K1;
	if (bChkBtn_Ch2) uData += K2;


	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_CHKBTN_CH, (WPARAM)uData, (LPARAM)NULL);
}

void WndMsgCmd_display_test_dnum	 (unsigned int dnum)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_DNUM, (WPARAM)dnum, (LPARAM)0);
}
void WndMsgCmd_display_test_time (unsigned int test_time)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_TIME, (WPARAM)test_time, (LPARAM)0);
}

void WndMsgCmd_display_MainScreen_Reset   ()
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_MAINSCREEN_RESET, (WPARAM)0, (LPARAM)0);
}

void WndMsgCmd_display_status_failStopEnable   (bool isFailStopEnable)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_STATUS_FAILSTOP, (WPARAM)isFailStopEnable, (LPARAM)0);
}

void WndMsgCmd_display_status_remoteTestEnable (bool isRemoteTestEnable)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_STATUS_REMOTETEST, (WPARAM)isRemoteTestEnable, (LPARAM)0);
}

void WndMsgCmd_remoteTest_Restore ()
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_REMOTETEST_RESTORE, (WPARAM)0, (LPARAM)0);
}


void WndMsgCmd_display_HoldOffBtn (bool status)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_HOLDOFF_BTN, (WPARAM)status, (LPARAM)0);
}

void WndMsgCmd_set_TestStopEnableBtn(bool status)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_SETBUTTON_STOPENABLE, (WPARAM)status, (LPARAM)0);	
}

void WndDisplay_TestImage (unsigned jig, unsigned img)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_IMAGE, (WPARAM)jig, (LPARAM)img);
}

void WndDisplay_TestResultInit ( unsigned nJig, unsigned nList)
{
	SendMessage(g_pLinProgView->m_hWnd, USERMSG_DISPLAY_TEST_RESULT_INIT, (WPARAM)nJig, (LPARAM)nList);
}


void WndDisplay_ButtonRemoteEnable ( char *text )
{
//	SetDlgItemText (hDlgMain, IDC_BUTTON_REMOTE_ENABLE, text );	// $ Delete 2014.10.113 sjkim
}

void WndDisplay_ButtonFailStop (char *text )
{
//	SetDlgItemText(hDlgMain, IDC_BUTTON_FAIL_STOP, text );// $ Delete 2014.10.113 sjkim
}
