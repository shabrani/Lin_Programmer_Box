#pragma once

#include "KvrLin.h"
#include "CTest_State.h"

typedef struct
{
	unsigned nPnum;
	unsigned nIdx;
	CString  sMsg;
	double	 fData;

}TS_MSG_TEST_PROC_DATA_DISPLAY;

class CFunc_UserMsg
{
public:
	CFunc_UserMsg(void);
	~CFunc_UserMsg(void);

	struct{
		CTest_State	*pts;
	}m_cfg;

	TS_MSG_TEST_PROC_DATA_DISPLAY	m_TestProcDataMsg;

public:
	void f_disp_tproc_data_msg (unsigned p, unsigned idx, double fData, CString sMsg);

	void f_LIN_LView_Insert_QData (unsigned nPnum, unsigned nStep, unsigned nQIndex);
	void f_LIN_LView_Insert_Msg   (char *s, bool bNextLine);
	void f_LIN_LView_SendTimer_On (bool bTimerOn, unsigned nTime_MS = 0);

	void f_ReTest_Start (void);
	void f_Test_Start   (void);
};




void display_errmsg_and_conform  ( const char msg[] );
void display_errmsg_and_exit     ( const char msg[] );
void display_msg_for_warning     ( const char *msg  );
void display_msg_for_Information ( const char *msg  );

void f_display_msg_for_LoadingFail_systemInformation();


void window_set_progress_bar_max ( unsigned max );
void display_test_prog_filename  ( char *name );	
void display_test_window_text    ( char *name );

//void display_data_filename_nosave ( char *buf );
//void display_data_filename (char *filename);

void display_spec_filename ( char *filename );
//void display_device_number(unsigned int test_dnum);
//void display_device_pass_fail(long pass, long fail);

void display_test_main_state ( unsigned state );
void display_progress_bar    ( unsigned pos );

//void display_test_device_name (char* device_name);
//void display_test_spec_name   (char* spec_name);
//void display_test_spec_revno  (int   nRevNo   );
//void display_test_spec_revno  (char  *szRevNo  );
//void display_test_prog_name	  (char *name      );


//void Display_ListView_HeadLine(void);
//void Display_ListView_Spec(CTest_State *ts);

//void Display_Test_Data(unsigned t, CTest_State *ts);
void display_test_time(CTest_State *ts);

void WndDisplay_ButtonRemoteEnable (char *text );
void WndDisplay_ButtonFailStop     (char *text );

//BOOL display_autotest_log(CString strLog);

void WndDisplay_progress_position (unsigned nJig, unsigned pos);
void WndDisplay_TestImage		  (unsigned nJig, unsigned img);
void WndDisplay_TestResultInit	  (unsigned nJig, unsigned nList);
void WndDisplay_TestData		  (unsigned nJig, unsigned pnum);
void WndDisplay_TestLinMsg		  (unsigned pnum, KVR_LIN_STRUCT &linBuf);
void WndDisplay_SerialMsg		  (unsigned line, unsigned &addr);
void WndDisplay_TestStatusMsg	  (char *s1, char *s2);

void WndMsgCmd_Diag_BreakPoint_Test (void);
void WndMsgCmd_Main_BtnTestStart (void);
//void WndMsgCmd_AddTotalAmount (void);
void WndMsgCmd_display_test_quantity (void);
void WndMsgCmd_display_test_dnum	 (unsigned int dnum);
void WndMsgCmd_display_test_time (unsigned int test_time);
void WndMsgCmd_Display_LotNo ( void );

void WndMsgCmd_display_status_failStopEnable   (bool isFailStopEnable);
void WndMsgCmd_display_status_remoteTestEnable (bool isRemoteTestEnable);
void WndMsgCmd_remoteTest_Restore ();
void WndMsgCmd_display_HoldOffBtn (bool btn_status);

void WndMsgCmd_display_ChkBtn_Ch(bool bChkBtn_Ch1, bool bChkBtn_Ch2, bool bRetest);
void WndMsgCmd_display_MainScreen_Reset ();

void WndMsgCmd_set_TestStopEnableBtn(bool status);