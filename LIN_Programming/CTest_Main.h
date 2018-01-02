#pragma once

#include "CTest_Base.h"


class CTest_Main : public CTest_Base
{
public:
	CTest_Main(void);
	~CTest_Main(void);

	unsigned	m_pnum;
	unsigned	m_nar;

	double		m_fMeasData;

	unsigned	m_nTitem;
	bool		m_bTitemExist;
	bool		m_bTitemEqual;

//	int 		m_nFailRetestNum;

	enum {CONTINUE, FAIL_STOP, USER_STOP}m_enResult;

	struct 
	{
		bool   bSet[ CSPEC_MEAS_SETVAR_BUFSIZE ];
		double fVal[ CSPEC_MEAS_SETVAR_BUFSIZE ];
	}m_setvar;

	struct 
	{
		double fSetVal;
		bool	isValid;
	}m_Vset;

	struct 
	{
		double		fFR;
		double		fT;
		bool		isValid;
	}m_op_freq;

	struct _st_ctest_main_retest
	{
		bool		bEnable;
		bool		bPass;
		unsigned	nRetestCount;
	}m_FAIL_Retest;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Main Procedure Function
	int f_test_procedure		(void);

	int f_test_start_process	(void);
	int f_test_main_process		(void);
	int f_test_end_process		(void);

	//////////////////////////////////////////////////////////////////////
	// 테스트 함수 포인터 
	int (CTest_Main::*m_pFunc_titem)(unsigned);
	int f_titem_RefTitemAll			(unsigned nSetRetestNumber, unsigned nRefTitem);
	int f_titem						(unsigned p);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  titem Function
	int f_COMM_Meas_Voltage (unsigned p);
	int f_COMM_Meas_Current (unsigned p);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CR665 Function
	int f_kvr_LINREG_CR665_Init_VERIFY_MODE		(unsigned nline);
	int f_kvr_LINREG_CR665_Finish				(unsigned p, unsigned nline);
	int f_kvr_LINREG_CR665_Addr_Verify			(unsigned p, unsigned nline, unsigned char addr, unsigned char exp, unsigned char &data);
	int f_kvr_LINREG_CR665_Addr_Programing		(unsigned p, unsigned nline, unsigned char addr, unsigned char data);

	int f_kvr_LINREG_CR665_Verify				(unsigned p);
	int f_kvr_LINREG_CR665_Program_and_Verify	(unsigned p);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TLE8881 Function
	int f_kvr_LINREG_Infenion_Init_PROGRAM_MODE	(unsigned p);
	int f_kvr_LINREG_Infenion_Init_VERIFY_MODE	(unsigned p);
	int f_kvr_LINREG_Infenion_Finish				(unsigned p);

	int f_kvr_LINREG_Infenion_Addr_Program			 (unsigned p, unsigned addr, unsigned char &D_HI, unsigned char &D_LO);
	int f_kvr_LINREG_Infenion_Addr_Verify			 (unsigned p, unsigned addr, unsigned nline, unsigned char *Lo, unsigned char *Hi);
	int f_kvr_LINREG_Infenion_Addr_Program_and_Verify (unsigned p, unsigned addr, unsigned char W_HI, unsigned char W_LO, unsigned char &R_HI, unsigned char &R_LO);

	int f_kvr_LINREG_Infenion_Verify				(unsigned p);
	int f_kvr_LINREG_Infenion_Program_and_Verify	(unsigned p);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  L9916 Function
	int f_kvr_LINREG_L9916_Verify				(unsigned p);
	int f_kvr_LINREG_L9916_Program_and_Verify	(unsigned p);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  LIN2112 Function
	void f_kvr_LINREG_LIN2112_TxMessage(unsigned p, unsigned nline, unsigned char rsid, unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4, unsigned char data5);
	
	int f_kvr_LINREG_LIN2112_Verify				(unsigned p);
	int f_kvr_LINREG_LIN2112_Program_and_Verify	(unsigned p);	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Function
	bool f_testdata_check_pass  (unsigned pnum, CFunc_Spec_Item_Main *pSpec, unsigned nData);
	bool f_testdata_check_pass  (unsigned pnum, CFunc_Spec_Item_Main *pSpec, double   fData);
	bool f_check_read_status		(unsigned pnum, unsigned nData);

	int	f_testdata_judge_uint	(unsigned nArray, unsigned pnum, unsigned meas_nData);
	int	f_testdata_judge_dbl	(unsigned nArray, unsigned pnum, double meas_data   );

	void f_testdata_save_variable_from_meas_data (unsigned nId, double meas_data    );
		
	CString	f_testdata_conv_to_Binary	 (unsigned p, unsigned nData, unsigned big_digit);
	CString	f_testdata_conv_to_CString	 (unsigned p, VARIANT varData);
	void f_testdata_conv_spec_to_CString (unsigned p, CString &sHIL, CString &sLOL);
	int f_hex_conv_to_int(CString szHexStr);

	void f_progress_bar (unsigned int pnum);
};

