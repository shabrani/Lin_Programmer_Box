#pragma once

#include "CInst_Base.h"
#include "CTest_System_Config.h"


class CInst_PS_3645A : public CInst_VISA
{
public:
	CInst_PS_3645A(void);
	~CInst_PS_3645A(void);

	struct 
	{
		double fVolt;
		double fCurr;
		//bool   bOnOff;		// $ Delete by sjkim - On/Off는 기억하지 말고 실행할수 있도록 수정함
	}m_setVal;



	void	f_outp_on	(double fDlyMs)		{f_cmd_dly("OUTP ON",	fDlyMs);}
	void	f_outp_off	(double fDlyMs)		{f_cmd_dly("OUTP OFF",	fDlyMs);}
	void	f_reset		(double fDlyMs)		{f_cmd_dly("*RST",		fDlyMs);}
	void	f_remote	(double fDlyMs)		{f_cmd_dly("SYST:REM",	fDlyMs);}


	bool	f_set_volt	(double fVin, double fDlyMs); 
	bool	f_set_curr	(double fIin, double fDlyMs);	


	double  f_meas_iout (double fDlyMs);
	double  f_meas_vout (double fDlyMs);
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CInst_Main
class CInst_Main
{
public:
	CInst_Main(void);
	~CInst_Main(void);

	CInst_PS_3645A	*m_pVsrc;

};