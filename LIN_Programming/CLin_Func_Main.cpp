#include "stdafx.h"
#include "stdio.h"
#include <fstream>
#include <iostream>

#include "procedure_Macro.h"
#include "CLin_Func_Main.h"


CLin_Func_Main::CLin_Func_Main(void)
{
	linInitializeLibrary();
}


CLin_Func_Main::~CLin_Func_Main(void)
{
}



LinStatus CLin_Func_Main::f_kvrlinReadMessageWait(unsigned int *fid, void *msg, unsigned int *length, unsigned int *flags, LinMessageInfo *msgInfo)
{
	m_sKVR = linReadMessageWait(m_hKVR, fid, msg, length, flags, msgInfo, 100);
	if(m_sKVR < linOK)
	{
		this->m_sErrMsg = "fail => CLIN_Func_Base::f_kvrlinReadMessageWait()";
		TRACE( m_sErrMsg + '\n');
		f_kvrErrorCheck(m_sKVR);
	}

	return m_sKVR;
}

LinStatus CLin_Func_Main::f_kvrlinRequestMessage(unsigned int fid,  double nTimeOut_ms)
{
	linReadTimer(m_hKVR);

	m_sKVR = linRequestMessage(m_hKVR, fid);
	if(m_sKVR < linOK)
	{
		this->m_sErrMsg = "fail => CLIN_Func_Base::f_kvrlinRequestMessage()";
		TRACE( m_sErrMsg + '\n');
		f_kvrErrorCheck(m_sKVR);
	}

	return m_sKVR;
}

LinStatus CLin_Func_Main::f_kvrlinWriteMessage(unsigned int fid, void *msg, unsigned int length,  double nTimeOut_ms)
{
	linReadTimer(m_hKVR);

	m_sKVR = linWriteMessage(m_sKVR, fid, msg, length);
	if(m_sKVR < linOK)
	{
		this->m_sErrMsg = "fail => CLIN_Func_Base::f_kvrlinRequestMessage()";
		TRACE( m_sErrMsg + '\n');
		f_kvrErrorCheck(m_sKVR);
	}

	return m_sKVR;
}


void CLin_Func_Main::f_kvrErrorCheck(LinStatus m_sKVR)
{
	switch(m_sKVR)
	{
	case linERR_NOMSG:
		this->m_sErrMsg = "No Message Available";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOTRUNNING:
		this->m_sErrMsg = "No Running";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_MASTERONLY :
		this->m_sErrMsg = "Master Only";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_SLAVEONLY:
		this->m_sErrMsg = "Slave Only";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_PARAM:
		this->m_sErrMsg = "Error in Parameter";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOTFOUND:
		this->m_sErrMsg = "Specified hardware not found. This error is reported when the LIN transceiver isn't powered up.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOMEM:
		this->m_sErrMsg = "Out of memory.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOCHANNELS:
		this->m_sErrMsg = "No channels avaliable.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_TIMEOUT:
		this->m_sErrMsg = "Timeout occurred.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOTINITIALIZED:
		this->m_sErrMsg = "Library not initialized.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOHANDLES:
		this->m_sErrMsg = "Can't get handle.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_INVHANDLE:
		this->m_sErrMsg = "Handle is invalid.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_CANERROR :
		this->m_sErrMsg = "Error Can";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_ERRRESP:
		this->m_sErrMsg = "There was an error response from the LIN interface.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_WRONGRESP:
		this->m_sErrMsg = "The LIN interface response wasn't the expected one.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_DRIVER:
		this->m_sErrMsg = "CAN driver type not supported.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_DRIVERFAILED:
		this->m_sErrMsg = "DeviceIOControl failed; use the Win32 GetLastError API to get the real (WIn32) error code.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NOCARD:
		this->m_sErrMsg = "The card was removed or not inserted.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_LICENSE:
		this->m_sErrMsg = "The license is not valid.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_INTERNAL:
		this->m_sErrMsg = "Internal error in the driver.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_NO_ACCESS:
		this->m_sErrMsg = "Access denied.";
		TRACE( m_sErrMsg + '\n');
		break;
	case linERR_VERSION:
		this->m_sErrMsg = "Function not supported in this version.";
		TRACE( m_sErrMsg + '\n');
		break;
	default:
		break;
	}

	
}

bool CLin_Func_Main::f_KVR_Configuration(int linChannel, unsigned int Baudrate, unsigned nChip)
{
	m_sKVR = linGetTransceiverData(linChannel, eanNo, serNo, &ttype);
	if(m_sKVR != linOK)
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	m_hKVR = linOpenChannel(linChannel, LIN_MASTER);
	if(m_hKVR != linOK)
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	m_sKVR = linSetBitrate(m_hKVR, Baudrate);
	if(m_sKVR != linOK)
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	m_sKVR = linBusOn(m_hKVR);
	if (m_sKVR != linOK) 
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	if(SELECT_CR665 == nChip)
	{
		m_sKVR = linSetupLIN(m_hKVR, LIN_ENHANCED_CHECKSUM  | LIN_VARIABLE_DLC,  Baudrate);
		if (m_sKVR != linOK) 
		{
			f_kvrErrorCheck(m_sKVR);
			return false;
		}
	}

	m_tOffset.timeOffset = linReadTimer(m_hKVR);

	return true;
}

bool CLin_Func_Main::f_KVR_Close(void)
{
	m_sKVR = linBusOff(m_hKVR);
	if (m_sKVR != linOK) 
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	m_sKVR = linClose(m_hKVR);
	if (m_sKVR != linOK) 
	{
		f_kvrErrorCheck(m_sKVR);
		return false;
	}

	return true;
}

void CLin_Func_Main::SendTX_and_Read(unsigned int id, KVR_LIN_STRUCT &linBUF, unsigned long delay)
{

	m_sKVR = linRequestMessage(m_hKVR, id);
	if(m_sKVR != linOK)
	{
		this->m_sErrMsg = "fail => linRequestMessage()";
		TRACE( m_sErrMsg + '\n');
	}

	m_sKVR = linReadMessageWait(m_hKVR, &linBUF.ArbitrationId, linBUF.Data, &linBUF.DataLength, &linBUF.Flags, &linBUF.msgInfo, delay);
	linBUF.msgInfo.timestamp -= timeOffset;
	if(m_sKVR != linOK)
	{
		this->m_sErrMsg = "fail => linReadMessageWait()";
		TRACE( m_sErrMsg + '\n');
	}

	return ;
}

void CLin_Func_Main::SendRX_and_Read(unsigned int id, void *msg, unsigned int length, KVR_LIN_STRUCT &linBUF, unsigned long delay)
{
	m_sKVR = linWriteMessage(m_hKVR, id, msg, length);
	if(m_sKVR != linOK)
	{
		this->m_sErrMsg = "fail => linRequestMessage()";
		TRACE( m_sErrMsg + '\n');
	}

	m_sKVR = linReadMessageWait(m_hKVR, &linBUF.ArbitrationId, linBUF.Data, &linBUF.DataLength, &linBUF.Flags, &linBUF.msgInfo, delay);
	linBUF.msgInfo.timestamp -= timeOffset;
	if(m_sKVR != linOK)
	{
		this->m_sErrMsg = "fail => linReadMessageWait()";
		TRACE( m_sErrMsg + '\n');
	}

	return ;
}
