#include "stdafx.h"
#include "CTest_System_Config.h"


CTest_System_Config::CTest_System_Config(void)
{
		m_EOT.bEOT_Reset_after_TestEnd	= false;
		m_EOT.nEOT_StartDelay_ms		= 100;
		m_EOT.nEOT_PulseWidth_ms		= 100;
}


CTest_System_Config::~CTest_System_Config(void)
{
}
