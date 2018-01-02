#include "stdafx.h"
#include "procedure_Macro.h"
#include "CSerial_Func_FRDM.h"

#include "CTest_Main.h"

CCriticalSection *m_pCriticalSection;

CSerial_Func_FRDM::CSerial_Func_FRDM(void)
{
	this->f_Open("COM5", 19200);
}


CSerial_Func_FRDM::~CSerial_Func_FRDM(void)
{
}


bool CSerial_Func_FRDM::f_Open(LPSTR szPort, UINT nBaudRate)
{
	sprintf_s(m_szPort, 10, "%s", szPort);
	m_nBaudRate = nBaudRate;

	if ( !OpenPort(m_szPort, m_nBaudRate) )
		return false;

	return true;
}

int CSerial_Func_FRDM::f_Check_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Send_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Send_Message (void *msg)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s$", msg);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

char CSerial_Func_FRDM::f_Read_Message (void *msg)
{
	CString	sMessage;
	char	*pCh;
	char	nValue = 0;


	sMessage.Format("#%s$", msg);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_char (pCh);

	return nValue;
}

void  CSerial_Func_FRDM::f_Read_Buffer (void *msg, CString *sBuf)
{
	CString	sMessage;
	char	*pCh;



	sMessage.Format("#%s$", msg);
	pCh = LPSTR(LPCTSTR(sMessage));
	f_cmd_and_read_buf(pCh, sBuf);
}

int CSerial_Func_FRDM::f_Check_Start_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Send_OK_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Send_NG_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Send_RUN_Signal (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Voltage_Set (void *cmd, void *vol)
{
	CString	sMessage;
	char	*pCh;
	int		nValue = 0;


	sMessage.Format("#%s%s$", cmd, vol);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

float CSerial_Func_FRDM::f_Voltage_Read (void)
{
	float fValue = 0;


	fValue = this->f_cmd_and_read_float ("#read$");

	return fValue;
}

int CSerial_Func_FRDM::f_Bit_Clear (void *cmd, void *port, void *regi)
{
	CString	sMessage;
	char	*pCh;
	int		nValue;


	sMessage.Format("#%s%s%s$", cmd, port, regi);

	pCh = LPSTR(LPCTSTR(sMessage));
	nValue = this->f_cmd_and_read_int (pCh);

	return nValue;
}

int CSerial_Func_FRDM::f_Clear_Output (void)
{
	int nValue;

	nValue = f_Bit_Clear(BIT_CLR, PORTC, BIT_0);
	nValue = f_Bit_Clear(BIT_CLR, PORTC, BIT_1);
	nValue = f_Bit_Clear(BIT_CLR, PORTC, BIT_2);
	nValue = f_Bit_Clear(BIT_CLR, PORTC, BIT_3);
	nValue = f_Bit_Clear(BIT_CLR, PORTF, BIT_6);
	nValue = f_Bit_Clear(BIT_CLR, PORTF, BIT_7);

	return nValue;
}

bool CSerial_Func_FRDM::f_cmd_and_read_buf		(void *msg, CString *sRead)
{
	CString sBuf;
	sBuf.Format("%s", msg);

	m_send.nCmdLen = sBuf.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));
	
	for (int i=0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = sBuf[i];

	m_send.byCmd[m_send.nCmdLen] = 13;
	m_send.nCmdLen++;


	m_send.nWriteLen = WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 1000);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 1000);

	sRead->Format("%s%c",m_recv.byRecv, 0x00);

	return true;
}

int CSerial_Func_FRDM::f_cmd_and_read_int (char *pWrite)
{
	CString sBuf;
	sBuf.Format("%s", pWrite);

	m_send.nCmdLen = sBuf.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));
	
	for (int i=0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = sBuf[i];

	m_send.byCmd[m_send.nCmdLen] = 13;
	m_send.nCmdLen++;


	m_send.nWriteLen = WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 1000);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 1000);

	CString sAns;
	sAns.Format("%s", m_recv.byRecv);
	
	if (0 == sAns.Compare("OK") )
	{
		//Illegal Parameter 오류 
		// return true;

	}
	else if ('C' == sAns[0] )
	{

		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}
	else if ('E' == sAns[0])
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}


	int value = strtol((const char *)this->m_recv.byRecv, NULL, 16);

	return value;
}

float CSerial_Func_FRDM::f_cmd_and_read_float		 (char *pWrite)
{
	CString sBuf;
	sBuf.Format("%s", pWrite);

	m_send.nCmdLen = sBuf.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));
	
	for (int i=0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = sBuf[i];

	m_send.byCmd[m_send.nCmdLen] = 13;
	m_send.nCmdLen++;


	m_send.nWriteLen = WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 100);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 100);


	CString sAns;
	sAns.Format("%s", m_recv.byRecv);
	
	if (0 == sAns.Compare("OK") )
	{
		//Illegal Parameter 오류 
		// return true;

	}
	else if ('C' == sAns[0] )
	{

		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}
	else if ('E' == sAns[0])
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}
	float value;
	sscanf_s((const char *)this->m_recv.byRecv, "%f", &value);

	return value;
}

char CSerial_Func_FRDM::f_cmd_and_read_char (char *pWrite)
{
	CString sBuf;
	sBuf.Format("%s", pWrite);

	m_send.nCmdLen = sBuf.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));
	
	for (int i=0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = sBuf[i];

	m_send.byCmd[m_send.nCmdLen] = 13;
	m_send.nCmdLen++;


	m_send.nWriteLen = WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 1000);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 1000);

	CString sAns;
	sAns.Format("%s", m_recv.byRecv);
	
	if (0 == sAns.Compare("OK") )
	{
		//Illegal Parameter 오류 
		// return true;
	}
	else if ('C' == sAns[0] )
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}
	else if ('E' == sAns[0])
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}

	char value = this->m_recv.byRecv[0];

	return value;
}

CString  CSerial_Func_FRDM::f_cmd_and_read_cstring	(char *pWrite)
{
	CString sBuf;
	sBuf.Format("%s", pWrite);

	m_send.nCmdLen = sBuf.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));
	
	for (int i=0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = sBuf[i];

	m_send.byCmd[m_send.nCmdLen] = 13;
	m_send.nCmdLen++;


	m_send.nWriteLen = WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 1000);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 1000);

	CString sAns;
	sAns.Format("%s", m_recv.byRecv);
	
	if (0 == sAns.Compare("OK") )
	{
		//Illegal Parameter 오류 
		// return true;
	}
	else if ('C' == sAns[0] )
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}
	else if ('E' == sAns[0])
	{
		sBuf += " : PS 통신오류";
		::MessageBox(NULL, sBuf, "오류", MB_OK);
	}

	return sAns;
}