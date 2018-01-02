#pragma once

#include "stdafx.h"
#include "KvrLin.h"

#include <stdio.h>      // Include file for printf
#include <stdlib.h>     // Include file for strtol
#include <windows.h>    // Include file for Win32 time functions
#include <conio.h>      // Include file for _getch/kbhit 
#include <string.h>

#include "CLin_Data.h"
#include "CFunc_DelayTime.h"

class CLin_Func_Main
{
public:
	CLin_Func_Main(void);
	~CLin_Func_Main(void);

	KVR_LIN_STRUCT		*m_pBuf;

	CString				m_sErrMsg;

	LinHandle			m_hKVR;
	LinStatus			m_sKVR;

	KVR_LIN_STRUCT		m_kvrReadBuf;
	KVRTYPE_LIN_FRAME	m_kvrSendBuf;
	KVR_LIN_TIME		m_tOffset;

	unsigned char		serNo[8];
	unsigned char		eanNo[8];
	int					ttype;
	int					linChannel;
	unsigned long		timeOffset;
	unsigned long		tLastPoll;
	unsigned long		tNow;


	LinStatus		f_kvrlinReadMessageWait (unsigned int *id, void   *msg, unsigned int *length, unsigned int *flags, LinMessageInfo *msgInfo);
	LinStatus		f_kvrlinRequestMessage  (unsigned int  id, double nTimeOut_ms);
	LinStatus		f_kvrlinWriteMessage    (unsigned int  id, void   *msg, unsigned int  length, double nTimeOut_ms);

	void			f_kvrErrorCheck		(LinStatus m_sKVR);
	bool			f_KVR_Configuration	(int linChannel, unsigned int Baudrate, unsigned nChip);
	bool			f_KVR_Close			(void);

	void			SendTX_and_Read		(unsigned int id, KVR_LIN_STRUCT &linBUF, unsigned long delay);
	void			SendRX_and_Read		(unsigned int id, void *msg, unsigned int length, KVR_LIN_STRUCT &linBUF, unsigned long delay);
};

