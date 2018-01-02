#pragma once

#include <visa.h>


class CInst_VISA  
{
public:
	CInst_VISA();
	virtual ~CInst_VISA();

	void	f_viOpen (ViString str, CString sInst);


public:
	ViSession	m_defaultRM;
	ViSession	m_vi;

	ViStatus	m_viStatus;

	char		m_viErr [100];
	char		m_viStatusDesc [100];


	char	m_buf[2048];

	void	f_cmd(char *cmd);
	void	f_cmd (char *cmd, double fVar1);				//Add sjkim 2012-06-22
//	void	f_cmd (char *cmd, double fVar1, double fVar2);


	void	f_cmd_dly (char *cmd, double fDlyMs);
	void	f_cmd_dly (char *cmd, double fVar1, double fDlyMs);
	void	f_cmd_dly (char *cmd, double fVar1, double fVar2, double fDlyMs);


	char*	f_scan_buf();
	double  f_scan_data();

	void	f_reset (double fDlyMs)	{f_cmd_dly ("*rst", fDlyMs);}
	void	f_clear (double fDlyMs)	{f_cmd_dly ("*cls", fDlyMs);}
	void	f_err   (double fDlyMs)	{f_cmd_dly ("err?", fDlyMs);}

};

