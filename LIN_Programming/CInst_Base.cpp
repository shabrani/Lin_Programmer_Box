// CInst.cpp: implementation of the CInst class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CTest_System_Config.h"
#include "CInst_Main.h"
#include "CTest_State.h"
#include "CFunc_DelayTime.h"



CInst_VISA::CInst_VISA()
{

}

CInst_VISA::~CInst_VISA()
{
  /* Close session */
	viClose (m_vi);
	viClose (m_defaultRM);
}


void CInst_VISA::f_viOpen(ViString str, CString sInst)
{  
	m_vi	   = 0;
	m_viStatus = 0;
	m_viStatus = viOpenDefaultRM (&m_defaultRM);
   
   
	if (m_viStatus != VI_SUCCESS)
	{
		viStatusDesc (m_defaultRM, m_viStatus, this->m_viStatusDesc);
		CString sBuf;
		sBuf.Format ("%s ( %s ) viOpenDefaultRM Error \n\n (Status # %d) %s ", sInst, str, m_viStatus, m_viStatusDesc);



		AfxMessageBox( sBuf );
		exit (-1);
	}


  
	m_viStatus = viOpen (m_defaultRM, str, VI_NULL, 5000, &m_vi);
	//	m_viStatus = viOpen (m_defaultRM, str, VI_NULL,VI_NULL, &m_vi);

	if (m_viStatus != VI_SUCCESS)
	{
		viStatusDesc (m_defaultRM, m_viStatus, this->m_viStatusDesc);
		CString sBuf;
		sBuf.Format ("%s ( %s ) viOpen Error \n\n (Status # %d) %s ", sInst, str, m_viStatus, m_viStatusDesc);

		AfxMessageBox( sBuf );
		exit (-1);
	}

}



void CInst_VISA::f_cmd_dly (char *cmd, double fDlyMs) 
{

	viPrintf(this->m_vi, "%s\n", cmd);

	f_delay_ms(fDlyMs);
}

void CInst_VISA::f_cmd_dly (char *cmd, double fVar1, double fDlyMs)
{

	viPrintf(this->m_vi, "%s %f\n", cmd,  fVar1); 

	f_delay_ms(fDlyMs);
}

void CInst_VISA::f_cmd_dly (char *cmd, double fVar1, double fVar2, double fDlyMs)
{

	viPrintf(this->m_vi, "%s %f %f\n", cmd, fVar1, fVar2); 

	f_delay_ms(fDlyMs);
}

void CInst_VISA::f_cmd (char *cmd) 
{
	viPrintf(this->m_vi, "%s\n", cmd);
}

//Add sjkim 2012-06-22
void CInst_VISA::f_cmd(char *cmd, double fVar1)
{
	m_viStatus = viPrintf(this->m_vi, "%s %f\n", cmd,  fVar1); 
}


char*	CInst_VISA::f_scan_buf()
{
	viScanf(m_vi, "%s\n", m_buf);

	return m_buf;
}

double  CInst_VISA::f_scan_data()
{
	return atof ( this->f_scan_buf () );
}


