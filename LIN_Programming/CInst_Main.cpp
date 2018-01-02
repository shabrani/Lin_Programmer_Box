#include "stdafx.h"
#include "CInst_Main.h"
#include "CTest_System_Config.h"

#define	SERIAL_VISAINSTR_PS_3645A	"COM3"

CInst_Main::CInst_Main(void)
{
	m_pVsrc = new CInst_PS_3645A;

#ifdef LIN_PROGRAM
	m_pVsrc->f_viOpen (SERIAL_VISAINSTR_PS_3645A, "POWER 3645A");
#endif // LIN_PROGRAM

}


CInst_Main::~CInst_Main(void)
{
	delete m_pVsrc;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CInst_PS_3645A
CInst_PS_3645A::CInst_PS_3645A(void)
{
}


CInst_PS_3645A::~CInst_PS_3645A(void)
{
}


bool CInst_PS_3645A::f_set_volt  (double fVin, double fDlyMs) 
{
	if (m_setVal.fVolt == fVin) return false;
	
	m_setVal.fVolt = fVin;
	f_cmd_dly("VOLT:LEVEL", fVin, fDlyMs);
	
	return true;
}

bool CInst_PS_3645A::f_set_curr  (double fIin, double fDlyMs) 
{
	if (m_setVal.fCurr == fIin) return true;
	
	m_setVal.fCurr = fIin;
	f_cmd_dly("CURR:LEVEL", fIin, fDlyMs);
	
	return true;
}


double CInst_PS_3645A::f_meas_iout  (double fDlyMs)
{
	this->f_cmd_dly("MEAS:CURR?",   fDlyMs);

	return this->f_scan_data();
}

double CInst_PS_3645A::f_meas_vout  (double fDlyMs)
{
	this->f_cmd_dly("MEAS:VOLT?",   fDlyMs);

	return this->f_scan_data();
}