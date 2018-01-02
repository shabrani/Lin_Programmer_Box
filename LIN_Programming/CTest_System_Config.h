#pragma once

#include "stdafx.h"


//������Ʈ�� �����ϴ� ������ �� 
#define		SYSTEM_MODEL_NO_STRING				"TM01LIN"
#define		SYSTEM_MODEL_NAME_STRING			"LIN PROGRAMER BOX"


//����ȭ�� �����ϴ�  ������ �� 
#define		TPROC_NAME_STRING					"TM01LIN"
#define		TPROC_REV_NO						0
#define		TPROC_REV_DATE_STRING				"2015-11-17"


#define		SYSTEM_PROGRAM_BUILD_NO_STRING		"1.00"
#define		SYSTEM_PROGRAM_BUILD_DATE_STRING	"2015-11-17"

//********************************************************************************************************************************************************
//***
//***	HARDWARE SIMULATION OPTION
//***
//********************************************************************************************************************************************************

#define			TEST_RUN_WITH_NO_HARDWARE
#define			SIM_IO

#define			SIM_VISA
#define			SIM_GPIB
#define			SIM_INST

#define			SIM_DAQ
#define			SIM_LIN
#define			SIM_MARKING


//********************************************************************************************************************************************************
//***
//***	SYSTEM CONFIGULATION SETTING
//***
//********************************************************************************************************************************************************

//#define			LIN_PROGRAM
#define			LIN_PROGRAM_BOX



//********************************************************************************************************************************************************
//***
//***	DATA FILE SAVE OPTION
//***
//********************************************************************************************************************************************************



class CTest_System_Config
{
public:
	CTest_System_Config(void);
	~CTest_System_Config(void);


	struct
	{
		bool     bEOT_Reset_after_TestEnd;		// �ڵ����� EOT��ȣ�� Reset���θ� ����
												// �ڵ����� Rest���� ������ ���� �˻� ���۽� Reset 
		unsigned nEOT_PulseWidth_ms;
		unsigned nEOT_StartDelay_ms;
	}m_EOT;

};
