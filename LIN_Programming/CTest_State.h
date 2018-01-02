#pragma once

#include <iterator>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>
#include <conio.h>
#include <math.h>
#include <vector>

#include "procedure_Macro.h"
#include "procedure_Number.h"

#include "CTest_Status_Test_Result.h"

using namespace std;

typedef struct
{
	char szBase_path[MAX_PATH];	//사용자가 지정한 path
	char szPath[MAX_PATH];		//실제 데이터가 위치할 곳으로 시스템에서 재구성한 path  
	char szName[MAX_PATH];		//filename with Full Path
}TS_FILENAME;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _st_meas_data_with_time		TS_DATA_TIME;

typedef struct _st_windows_parameter		TS_WINPARAM;

typedef struct _st_datasave					TS_DATASAVE;

typedef struct st_listcntl_header			TS_LISTCTRL_HEADER;

typedef struct _st_progress_bar_status		TS_PROGRASS_BAR_STATUS;

struct _st_progress_bar_status
{
	unsigned max;
	unsigned pos;
};

struct _st_meas_data_with_time
{
	double dTime;
	double dData;
};

struct _st_windows_parameter
{
	HWND	hWnd;
	UINT	iMsg;
	WPARAM	wParam;
	LPARAM	lParam;
};

struct _st_datasave
{
	TS_FILENAME file;
};

struct st_listcntl_header
{
	CString		sName;
	int			nWidth;
	int			nFmt;
};

typedef struct _st_lot_number_information
{
	CString			sLotNo;		 
	CString			sLotRemark;  
	CString			sOperator;	 

	bool			bFlagLotNoChanged;
	bool			isLotRemakrSeted;
	bool			isLotNameSeted;
}TS_LOT_NO_INFO;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{

	unsigned  nDnum_next;	//Add-2006.10.24	sjkim

	unsigned	nPnum;	// current Process Num
	unsigned	nAnum;	// Current array Num
	unsigned    nDnum;	// current test device num

	unsigned	nPass_total;
	unsigned	nFail_total;
	unsigned	nPass;			
	unsigned	nFail;

}TS_CTEST_BASE_STATUS_DNUM;

typedef struct
{
	bool		bTestStopEnable;

	bool		bRetest;

	unsigned    nDnum;
	bool		isLampOn;
	bool		isSoundOn;
	bool		isBuzzerOn;
	bool		isBtnSet_AutoTest;

	bool		isDispOn_Progress;
	bool		isDispOn_TestData;
	bool		isTestRun;


	bool		isRemoteTestEnable;
	bool		isRemoteTestEnable_Backup;
	bool		isFailStopEnable;
	bool		bEngMode;
	bool		bStopMode;
	bool		isHdlrOn;					

	bool		isHoldOffButton;

	TS_PROGRASS_BAR_STATUS	ProgressBar;

	CTime		tmTestStart;			//time
	CTime		tmTestEnd;				//time

	bool		isDisplayOrder_AutoAuto;

	bool		bTestProcessDataView;

}TS_SYSTEM_STATUS;

typedef struct
{

	CString 	sProcName;
	CString 	sProcRevData;
	unsigned 		nProcRevNo;

	CString		sCompanyName;
	CString		sDivisionName;
	
	CString		sSystemName;
	CString		sSystemModelNo;
	CString		sSystemSerialNo;

	bool			isLoading_CompanyName;
	bool			isLoading_DivisionName;
	bool			isLoading_ProcessInformationFile;
	bool			isLoading_SystemInformationFile;


	bool			isLoadingFail_SystemInformation;

	CString		sComputerName;		// $ Add by sjkim 2012-06-21 ---> 데이터베이스 이름 변경


}TS_CTESTBASE_SYSTEM_STATE;

class CTest_State
{
public:
	CTest_State(void);
	~CTest_State(void);

	TS_DATASAVE							datasave;		// Data Save Information
	TS_DATASAVE							datasave_auto;	// Data Save Information 
	TS_FILENAME							file_testprog;

	LARGE_INTEGER						Timer64_Freq;
	LARGE_INTEGER						Timer64_sTime;	// test start time


	TS_LOT_NO_INFO						Lot;
	
	TS_SYSTEM_STATUS					Status;
	TS_CTESTBASE_SYSTEM_STATE			SysInfo;
	

	CTest_Status_Test_Result            Result;

};
