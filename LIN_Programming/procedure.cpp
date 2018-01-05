#include "stdafx.h"

#include <vector>

#include "procedure.h"
#include "procedure_Macro.h"
#include "LIN_ProgrammingDoc.h"
#include "LIN_ProgrammingView.h"

#include "CTest_Main.h"
#include "CTest_State.h"


extern CLIN_ProgrammingView	*g_pLinProgView;
extern HWND					hDlgMain;

HINSTANCE	g_hInst;

DWORD ThreadID;
DWORD ThreadID_Test;
DWORD ThreadID_waitTestSignal;
DWORD ThreadID_saveData;

HANDLE hThread_Test;
HANDLE hThread_waitTestSignal;
HANDLE hThread_saveData;

/////////////////////////////////////////////////////////////////////////////

extern CTest_Main			*pTest;
CLIN_ProgrammingView		*pLinProgView;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function
DWORD WINAPI Thread_MainCmd_Test(LPVOID temp)
{	
	unsigned nResult = TEST_CONTINUE;

	if ( pTest->m_pCSpec->m_stStatus.isLoading_spec == false ) return 0;
	if ( pTest->m_cState.Status.isTestRun ) return 0;
	
	pTest->m_cState.Status.isTestRun = true;
	set_test_handler_thread (TEST_HANDLER_THREAD_DISABLE);


	if( pTest->m_cState.Status.isHdlrOn )
	{
		// 보드로 보내는 시리얼 신호
	}

	WndDisplay_TestResultInit    (0, 1);
	WndDisplay_progress_position (0, pTest->m_cState.Status.ProgressBar.pos = 0);
	WndDisplay_TestImage	     (0, TEST_IMAGE_WAIT);



	bool bResult = false;

	{
		nResult = ThreadFunction_MainCmd_Test (temp);

		bResult = pTest->m_pCTestData->m_testData.Var.bPass;
	}
	

	if( pTest->m_cState.Status.isHdlrOn )	
	{
		while( 1 )
		{
			if (false == pTest->m_cState.Status.isHdlrOn) break;

			// 보드로 보내는 시리얼 신호 // START Signal
//			if (0x01 == (temp&0x01)) break;

			WndDisplay_TestStatusMsg("Start Signal Detecting...","");

			Sleep(100);
		}

		if(pTest->m_cState.Status.bStopMode)
		{
			if(true == bResult)
			{
				// 보드로 보내는 시리얼 신호 // OK
			}
			else
			{
				// 보드로 보내는 시리얼 신호 // NG
			}
			Sleep(100);
			// 보드로 보내는 시리얼 신호 // EOT
		}
		else
		{
			if(true == bResult)
			{
				// 보드로 보내는 시리얼 신호 // OK
			}
			else
			{
				// 보드로 보내는 시리얼 신호 // NG
			}
			Sleep(100);
			// 보드로 보내는 시리얼 신호 // EOT
		}

	}


	pTest->m_cState.Status.bRetest = false;
	WndMsgCmd_set_TestStopEnableBtn (false);			// Test Stop Enable 버튼을 초기화합니다. 

	pTest->m_cState.Status.isTestRun		= false;	// TEST_WAIT_STATE;
	pTest->m_cState.Status.bTestStopEnable	= false;

	WndMsgCmd_remoteTest_Restore();


	return 0;
}

DWORD WINAPI Thread_waitTestSignal (LPVOID temp)
{
	char szBuf[64];
	unsigned nCount_10  = 0;
	unsigned nCount_100 = 0;

	

	while (1)
	{
		Sleep(10);

		if ( ++nCount_10 > 10 ) 
		{
			nCount_10 = 0;
			nCount_100++;
			
			if (nCount_100 > 9)
			{
				nCount_100 = 0;
			}

			sprintf_s(szBuf, 128, "Count = %d", nCount_100);
			WndDisplay_TestStatusMsg("Start Signal Waiting...", szBuf);
		}

		// 보드에서 오는 시작신호 체크
		/*
		if (0x01 == (temp&0x01))
		{
			Sleep(10);
			CFunc_UserMsg UserMsg;
			UserMsg.f_Test_Start ();
		}
		*/
	}

	return 0;
}

DWORD WINAPI Thread_saveData (LPVOID temp)
{
	pTest->m_pCSaveDataAccess->f_saveData();
	return 0;
}



int ThreadFunction_MainCmd_Test (LPVOID pView)
{
	unsigned nResult = 0;
	

	pTest->m_cState.Status.tmTestStart = CTime::GetCurrentTime();
	::QueryPerformanceCounter (&pTest->m_cState.Timer64_sTime);
	
	display_test_time(&pTest->m_cState);
	WndDisplay_TestStatusMsg("Start Test !!!!","Waiting...");
	WndDisplay_TestImage (0, TEST_IMAGE_TEST);


	if (true != pTest->m_cState.Status.bRetest)
	{
		pTest->m_cState.Status.nDnum++;
		WndMsgCmd_display_test_dnum	 (pTest->m_cState.Status.nDnum);
	}
	else
	{
		//ts->dnum.nDnum = ts->stTResult.pCh_selected->nDnum;	
	}
	pTest->m_pCTestData->f_reset_CTestData_for_Test_Ready (0, pTest->m_cState.Status.nDnum );

	// Test Start //////////////////////////////////////////////////////////
	nResult = pTest->f_test_procedure ();

	////////////////////////////////////////////////////////////////////////

	if (nResult == TEST_STOP_USER)
	{
		pTest->m_cState.Result.m_Result.bAllPass			= false;
		pTest->m_cState.Result.m_Result.pCh->isTested	= true;
		pTest->m_cState.Result.m_Result.pCh->isStop		= true;	
		pTest->m_cState.Result.m_Result.pCh->isPass		= false;
		pTest->m_pCTestData->m_testData.Var.bPass	= false;

		WndDisplay_TestImage (0, TEST_IMAGE_STOP );
	}
	else if (true == pTest->m_pCTestData->m_testData.Var.bPass)
	{
		pTest->m_cState.Result.m_Result.pCh->isPass		= true;
		pTest->m_cState.Result.m_Result.pCh->isTested	= true;

		pTest->m_cState.Result.m_Result.pCh->nPass_add	= 1;

		pTest->m_cState.Result.m_Qty.Curr.nPass++;
		pTest->m_cState.Result.m_Qty.Acc.nPass++;

		WndDisplay_TestImage (0, TEST_IMAGE_PASS );
	}
	else
	{
		pTest->m_cState.Result.m_Result.bAllPass			= false;
		pTest->m_cState.Result.m_Result.pCh->isPass		= false;
		pTest->m_cState.Result.m_Result.pCh->isTested	= true;

		pTest->m_cState.Result.m_Result.pCh->nFail_add	= 1;

		pTest->m_cState.Result.m_Qty.Curr.nFail++;
		pTest->m_cState.Result.m_Qty.Acc.nFail++;

		WndDisplay_TestImage (0, TEST_IMAGE_FAIL );
	}

	// Test Time Write /////////////////////////////////////////////////////
	pTest->m_cState.Status.tmTestEnd = CTime::GetCurrentTime();
	display_test_time(&pTest->m_cState);

	// Save Data ///////////////////////////////////////////////////////////
	while(1)
	{
		if(pTest->m_pCSaveDataAccess->m_var.bSaveComplete) break;
		Sleep(50);
	}
	pTest->m_pCTestData->m_testData.Var.tTime = pTest->m_cState.Status.tmTestStart;
	pTest->m_pCTestData->f_data_copy (&pTest->m_pCTestData->m_testData, &pTest->m_pCTestData->m_saveData);


	hThread_saveData = CreateThread(NULL, 0, Thread_saveData, NULL, 0, &ThreadID_saveData);
	
	if (0 != hThread_saveData)						// $ 2014.11.08 bug fix from test
		CloseHandle(hThread_saveData);

	// Display Panel ///////////////////////////////////////////////////////
	WndMsgCmd_display_test_quantity ();
	display_test_time(&pTest->m_cState);

	return nResult;
}

int set_test_handler_thread	(unsigned int state)
{
	static unsigned suspend_count;

	if (TEST_HANDLER_THREAD_ENABLE == state)
	{		
		if ( 0 == suspend_count ) return 1;
		
		suspend_count = 0;
		ResumeThread (hThread_waitTestSignal);
	}
	else if (TEST_HANDLER_THREAD_DISABLE == state)
	{
		if (1 == suspend_count) return 1;

		suspend_count = 1;	
		SuspendThread (hThread_waitTestSignal);

		WndDisplay_TestStatusMsg(NULL, "Disable-Wait Test Signal");
	}

	return 0;
}

void system_initialize (CTest_State *ts)
{

	pTest->f_test_start_process ();
	pTest->f_test_end_process   ();

	GetCurrentDirectory(MAX_PATH, ts->file_testprog.szPath);

	QueryPerformanceFrequency(&ts->Timer64_Freq);

	WndMsgCmd_set_TestStopEnableBtn (false);
	WndMsgCmd_display_test_time	(0);
	WndMsgCmd_display_test_quantity ();

	set_test_handler_thread ( TEST_HANDLER_THREAD_DISABLE );

}