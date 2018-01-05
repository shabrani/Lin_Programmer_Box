#pragma once

#include "CFunc_Beep.h"

#include "CFunc_Reg.h"

#include "CFunc_File.h"
#include "CFunc_FilePath.h"

#include "CFunc_Spec.h"
#include "CFunc_Spec_File.h"

#include "CTest_State.h"
#include "CTest_System_Config.h"

#include "CFunc_TestData.h"
#include "CFunc_TestData_SaveAccess.h"

#include "CFunc_UserMsg.h"

#include "CInst_Main.h"

#include "CLin_Func_Main.h"




class CTest_Base
{
public:
	CTest_Base(void);
	~CTest_Base(void);

//////////////////////////////////////////////////////////
// CLASS
	CFunc_File			*m_pCFile;
	CFunc_Spec			*m_pCSpec;
	CLin_Func_Main		*m_pLin;
	CFunc_RegMain		*m_pReg;
	CInst_Main			*m_pInst;
	CFunc_Beep			*m_pBeep;

	CFunc_TestData			  *m_pCTestData;
	CFunc_TestData_SaveAccess *m_pCSaveDataAccess;

	CFunc_UserMsg		m_cUserMsg;
	CFunc_DelayTime		m_dtElaspedTime;

	CInst_PS_3645A		*m_pVsrc;

	CFunc_Spec_Item		*m_pTitem;
	CFunc_Spec_Item		*m_pTitemPrev;
	CFunc_Spec_Item		*m_pTitemNext;



	CTest_State			m_cState;
	CTest_System_Config m_Cfg;

//////////////////////////////////////////////////////////
// VARIABLE 
	unsigned			m_nRtn;	

//////////////////////////////////////////////////////////
// FUNCTION 
	void f_ts_Initialize (void);
};

