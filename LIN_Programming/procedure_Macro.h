#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST STATE Define

////////////////////////////////////////////////////////////////////////
#define			TEST_IMAGE_TEST					1
#define			TEST_IMAGE_PASS					2
#define			TEST_IMAGE_FAIL					3
#define			TEST_IMAGE_WAIT					4	
#define			TEST_IMAGE_STOP					5
#define			TEST_IMAGE_READY				6
#define			TEST_IMAGE_DISABLE				7
////////////////////////////////////////////////////////////////////////
#define			TEST_SPEC_LOADING_YES			1
#define			TEST_SPEC_LOADING_NO			2
#define			TEST_SPEC_LOADING_FAIL			3
#define			TEST_SPEC_LOADING_SUCCESS		4
////////////////////////////////////////////////////////////////////////
#define			TEST_RESULT_PASS				1
#define			TEST_RESULT_FAIL				2
#define			TEST_RESULT_BIN_OK				1
#define			TEST_RESULT_BIN_FAIL			10
////////////////////////////////////////////////////////////////////////
#define			TEST_MESSAGE_PASS				1
#define			TEST_MESSAGE_FAIL				2
#define			TEST_MESSAGE_TESTING			3
#define			TEST_MESSAGE_WAIT				4
////////////////////////////////////////////////////////////////////////
#define			TEST_PROCESS_END				0
#define			TEST_PROCESS_STOP				1
////////////////////////////////////////////////////////////////////////
#define			TEST_RUN_STATE					1
#define			TEST_WAIT_STATE					0
////////////////////////////////////////////////////////////////////////
#define			TEST_HANDLER_MODE_AUTO			1
#define			TEST_HANDLER_MODE_MANU			2
#define			TEST_HANDLER_THREAD_ENABLE		1
#define			TEST_HANDLER_THREAD_DISABLE		2
////////////////////////////////////////////////////////////////////////
#define			TEST_CONTINUE					0
#define			TEST_STOP_FAIL					5
#define			TEST_STOP_USER					6	
#define			TEST_STOP_FAIL_RETEST			7

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST MODE Define 
#define			ROOM_TEMP						1
#define			HOT_TEMP						2

#define			TEST_MODE_SET_ON				1
#define			TEST_MODE_SET_OFF				2 

#define			DISPLAY_ON						1
#define			DISPLAY_OFF						2

#define			SOUND_ON						1
#define			SOUND_OFF						2

#define			YES								1		//TEST YES
#define			NO								2		//TEST NO

#define			TEST_FC_F						1		//TEST FUNCTION
#define			TEST_FC_C						2		//TEST CHECK

#define			BIN_NUMBER_PASS					1
#define			BIN_NUMBER_FAIL					10

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COLOR Define
#define			COLOR_WHITE						RGB( 255, 255, 255)
#define			COLOR_RED						RGB( 255,   0,   0)
#define			COLOR_YELLOW					RGB( 255, 255,   0)
#define			COLOR_YELLOW_LIGHT				RGB( 255, 255, 192)
#define			COLOR_BLUE						RGB(   0,   0, 255)
#define			COLOR_BLUE_LIGHT				RGB( 128, 128, 255)
#define			COLOR_GREEN_DARK				RGB(   0, 255, 128)
#define			COLOR_GREEN						RGB(   0, 255,   0)
#define			COLOR_BLACK						RGB(   0,   0,   0)
#define			RGBCOLOR_BD_DLG					RGB( 217, 230, 230) 
#define			COLOR_SRC_EDIT_SET				RGB( 255, 255, 150)
#define			COLOR_SRC_EDIT_PASS				RGB( 255, 255, 255) 

#define			COLOR_MUX_GRAY					RGB( 255, 255, 255)
#define			COLOR_MUX_GREEN					RGB( 100, 255,   0)
#define			COLOR_MUX_YELLOW				RGB( 255, 255, 120)

#define			COLOR_BACK_RLY_MUX_AUX		     COLOR_MUX_YELLOW
#define			COLOR_BACK_RLY_MUX_DEV		     COLOR_MUX_GREEN	
#define			COLOR_BACK_RLY_DUT				 COLOR_MUX_YELLOW
#define			COLOR_BACK_RLY_PWSEL			 COLOR_MUX_GREEN

#define			COLOR_TEXT_RLY_CHG				RGB( 255,   0,   0)
#define			COLOR_TEXT_RLY_NOCHG			RGB(   0,   0,   0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST RESULT Define
#define		TRESULT_IMAGE_COLOR_TEXT_PASS		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_FAIL		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_TEST		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_WAIT		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_STOP		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_READY		COLOR_WHITE
#define		TRESULT_IMAGE_COLOR_TEXT_DISABLE	COLOR_WHITE	

#define		TRESULT_IMAGE_COLOR_PASS			COLOR_GREEN
#define		TRESULT_IMAGE_COLOR_FAIL			COLOR_RED
#define		TRESULT_IMAGE_COLOR_TEST			COLOR_BLUE
#define		TRESULT_IMAGE_COLOR_WAIT			COLOR_GREEN
#define		TRESULT_IMAGE_COLOR_STOP			COLOR_GREEN
#define		TRESULT_IMAGE_COLOR_READY			COLOR_GREEN
#define		TRESULT_IMAGE_COLOR_DISABLE			COLOR_GREEN

#define		TRESULT_IMAGE_STR_PASS				"P A S S"
#define		TRESULT_IMAGE_STR_FAIL				"F A I L"
#define		TRESULT_IMAGE_STR_TEST				"T E S T"
#define		TRESULT_IMAGE_STR_WAIT				"W A I T"
#define		TRESULT_IMAGE_STR_STOP				"S T O P"
#define		TRESULT_IMAGE_STR_READY				"READY"
#define		TRESULT_IMAGE_STR_DISABLE			"DISABLE"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User Message Define
#define			ID_ALLWAYS_EXIT							WM_APP+1
#define			ID_EDIT_TEST_RESULT						WM_APP+2
#define			ID_EDIT_TEST_DNUM						WM_APP+3
#define			ID_SCROLLBAR_TESTPROGRESS				WM_APP+4

#define         BITMAP_WAITON      						WM_USER+1
#define         BITMAP_WAITOFF      					WM_USER+2

#define			USERMSG_DISPLAY_TEST_IMAGE				WM_USER+11		
#define			USERMSG_DISPLAY_TEST_RESULT_INIT		WM_USER+12
#define			USERMSG_DISPLAY_TEST_DATA				WM_USER+13
#define			USERMSG_DISPLAY_TEST_LIN_MSG			WM_USER+14
#define			USERMSG_DISPLAY_PROGRESS_POS			WM_USER+15
#define			USERMSG_DISPLAY_SERIAL_DATA				WM_USER+16

#define			USERMSG_DISPLAY_TEST_QUANTITY			WM_USER+20
#define			USERMSG_DISPLAY_TEST_DNUM				WM_USER+21
#define			USERMSG_DISPLAY_TEST_TIME				WM_USER+22
#define			USERMSG_DISPLAY_STATUS_REMOTETEST		WM_USER+23
#define			USERMSG_REMOTETEST_RESTORE				WM_USER+24
#define			USERMSG_DISPLAY_STATUS_FAILSTOP			WM_USER+25
#define			USERMSG_DISPLAY_LOT_NO					WM_USER+26
#define			USERMSG_DISPLAY_HOLDOFF_BTN				WM_USER+27
#define         USERMSG_DISPLAY_TESTSTATUS_INFORM		WM_USER+28
#define			USERMSG_DISPLAY_MAINSCREEN_RESET		WM_USER+29



#define			USERMSG_COMMAND_DIAG_BREAKPOINT_TEST	WM_USER+40
#define			USERMSG_MAIN_BTN_TEST_START				WM_USER+41
#define			USERMSG_MAIN_BTN_RETEST_START			WM_USER+42
//#define		USERMSG_COMMAND_ADD_TOTAL_AMOUNT		WM_USER+43
#define			USERMSG_SETBUTTON_STOPENABLE			WM_USER+44
#define			USERMSG_DISPLAY_CHKBTN_CH				WM_USER+45
#define			USERMSG_DISPLAY_MARKING_SN				WM_USER+46

#define			USERMSG_LV_LIN_RESET					WM_USER+50
#define			USERMSG_LV_LIN_INSERT_QDATA				WM_USER+51
#define			USERMSG_LV_LIN_INSERT_MSG				WM_USER+52
#define			USERMSG_LIN_SEND_TIMER_ON				WM_USER+53
#define			USERMSG_LV_INSERT_TEST_PROC_DATA		WM_USER+54

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String Size Define
#define			STRSIZE_LOT_NO							32
#define			STRSIZE_LOT_REMARK						64

#define			STRSIZE_COMPANY_NAME					32
#define			STRSIZE_DIVISION_NAME					32
#define			STRSIZE_SYSTEM_NAME						32
#define			STRSIZE_SYSTEM_MODEL_NO					32
#define			STRSIZE_SYSTEM_SERIAL_NO				32
#define			STRSIZE_OPERATOR						32

#define			STRSIZE_DEVICENAME						100
#define			STRSIZE_WINDOWNAME						20

#define			STRSIZE_PROCNAME						21
#define			STRSIZE_SPECNAME						100
#define			STRSIZE_INFORMNAME						20
#define			STRSIZE_REVDATE							20
#define			STRSIZE_REVNO							10

#define			CHAR_NUM_BLANK							32
#define			CHAR_NUM_COMMA							44
#define			CHAR_NUM_TAB							9
#define			CHAR_NUM_BRACKET_LEFT					123
#define			CHAR_NUM_BRACKET_RIGHT					125
#define			CHAR_NUM_CR								13
#define			CHAR_NUM_LF								10
#define			CHAR_NUM_PATH							92


#define			CH_BLANK								CHAR_NUM_BLANK
#define			CH_COMMA								CHAR_NUM_COMMA
#define			CH_TAB									CHAR_NUM_TAB
#define			CH_BRACKET_LEFT							CHAR_NUM_BRACKET_LEFT
#define			CH_BRACKET_RIGHT						CHAR_NUM_BRACKET_RIGHT
#define			CH_CR									CHAR_NUM_CR
#define			CH_LF									CHAR_NUM_LF
#define			CH_PATH									CHAR_NUM_PATH


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Serial Message Define
#define			PORT_SET								"pset"
#define			BIT_SET									"bset"
#define			BIT_CLR									"bclr"
#define			INPUT_PORT_READ							"ireq"
#define			OUTPUT_PORT_READ						"oreq"
#define			DDR_PORT_READ							"dreq"

#define			PORTA									" pa"
#define			PORTB									" pb"
#define			PORTC									" pc"
#define			PORTD									" pd"
#define			PORTE									" pe"
#define			PORTF									" pf"
#define			PORTG									" pg"
#define			PORTH									" ph"

#define			BIT_0									" 01"
#define			BIT_1									" 02"
#define			BIT_2									" 04"
#define			BIT_3									" 08"
#define			BIT_4									" 10"
#define			BIT_5									" 20"
#define			BIT_6									" 40"
#define			BIT_7									" 80"

#define			VOLTAGE_SET								"setv "
#define			VOLTAGE_READ							"read"

#define			START									"start"
#define			RUN										"run"
#define			READY									"ready"
#define			OKs										"ok"
#define			NG										"ng"
#define			HDLR_ERR								"err?"
#define			JIG_ERR									"jig?"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// etc...
#define			SELECT_CR665							0
#define			SELECT_TLE8880							1
#define			SELECT_TLE8881							2
#define			SELECT_L9916							3
#define			SELECT_LIN2112							4

#define			ENABLE_START							0x00
#define			DISABLE_START							0x01


namespace RETURN
{
	enum Enum
	{
		OK                      =   0,
		FAIL					=  -1,			//fData = 0;
		PASS					=   1,
	};
};

namespace ret_yesno
{
	enum Enum
	{
		yes                     =   1,
		no						=   0,			//fData = 0;
		fail					=   0xff
	};
};


namespace ret_okno
{
	enum Enum
	{
		ok                      =   1,
		no						=   0,			//fData = 0;
		fail					=   0xff
	};
};



namespace enum_test_run_state
{
	enum Enum
	{
		POWER_ON_TEST,
		POWER_OFF_TEST,
		TEST_START_PROC,
		TEST_END_PROC,
		TEST_READY
	};
};