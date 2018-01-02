#include "stdafx.h"
#include <process.h>
#include "CSerial_Func_Main.h"


CSerial_Func_Main::CSerial_Func_Main(void)
{
	m_hComm = NULL;
	m_hStatEvent = NULL;
	m_hStopReading = NULL;
	m_bConnected = FALSE;
	m_nCheckIntervalValue = MINIMUM_TIMEOUT;
}


CSerial_Func_Main::~CSerial_Func_Main(void)
{
	ClosePort();
}


BOOL CSerial_Func_Main::IsOpened()
{
	if ( !m_bConnected || m_hComm == NULL ) 
		return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////
//	Error Message Function -- For Debug
void CSerial_Func_Main::ErrorMsg(DWORD dwError)
{
	char msg[512];
	LPTSTR lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL 
	);

	sprintf_s(msg, 512,"Errno:[%d]\n%s", dwError, lpMsgBuf);
	MessageBox(NULL, msg, "Comu_CSerial Message", MB_OK);
	LocalFree(lpMsgBuf);
}

BOOL CSerial_Func_Main::InitSerialEvents()
{
	InitOverlapped(&m_ovWrite);
	if ( !CreateOvlapEvent(&m_ovWrite) )
		return FALSE;

	InitOverlapped(&m_ovRead);
	if ( !CreateOvlapEvent(&m_ovRead) )
		return FALSE;

	return TRUE;
}

BOOL CSerial_Func_Main::CreateOvlapEvent(OVERLAPPED *pov)
{
	if (pov->hEvent != NULL)
		CloseHandle(pov->hEvent);

	pov->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( pov->hEvent == NULL )
		return FALSE;

	return TRUE;
}

void CSerial_Func_Main::InitOverlapped(OVERLAPPED *pov)
{
	pov->hEvent			= NULL;
	pov->Internal		= 0;
	pov->InternalHigh	= 0;
	pov->Offset			= 0;
	pov->OffsetHigh		= 0;
}

BOOL CSerial_Func_Main::ClearPort()
{
	if ( !PurgeComm(m_hComm, PURGE_TXCLEAR|PURGE_TXABORT|PURGE_RXCLEAR|PURGE_RXABORT) )
		return FALSE; 

	return TRUE;
}

///////////////////////////////////////////////////////////
//	Main Internal Functions
//
BOOL CSerial_Func_Main::OpenPort(LPSTR szPortName, DWORD dwBaudRate, UINT nDataBit, LPSTR szParity, LPSTR szStopBit)
{
	if ( IsOpened() )
		return TRUE;

	if ( strlen(szPortName) > 4 )	// Greater than COM9 (ex: COM10)
		sprintf_s(m_szPortName, 10, "\\\\.\\%s", szPortName);
	else
		sprintf_s(m_szPortName, 10, "%s", szPortName);

	m_dwBaudRate = dwBaudRate;

	COMMTIMEOUTS	timeouts;
	DCB				dcb;

	if ( !InitSerialEvents() )
		return FALSE;

	m_hComm = CreateFile(m_szPortName, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE)
		return FALSE;

	ZeroMemory(&timeouts, sizeof(COMMTIMEOUTS));
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;

	if ( !SetCommTimeouts(m_hComm, &timeouts) ) 
	{
		CloseHandle(m_hComm);
		return FALSE; 
	}

	ZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);
	if ( !GetCommState(m_hComm, &dcb) ) 
	{
		CloseHandle(m_hComm);
		return FALSE; 
	}
//	ZeroMemory(&dcb, sizeof(DCB));

	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;

	dcb.BaudRate = m_dwBaudRate;
	dcb.ByteSize = nDataBit;

	if ( !strcmp(szParity, "Odd") )
		dcb.Parity = ODDPARITY;
	else if ( !strcmp(szParity, "Even") )
		dcb.Parity = EVENPARITY;
	else if ( !strcmp(szParity, "Mark") )
		dcb.Parity = MARKPARITY;
	else if ( !strcmp(szParity, "Space") )
		dcb.Parity = SPACEPARITY;
	else if ( !strcmp(szParity, "Coin") )
	{
		dcb.Parity = EVENPARITY;
		dcb.fParity = FALSE;
	}
	else //if ( !strcmp(szParity, "None") )
		dcb.Parity = NOPARITY;

	if ( !strcmp(szStopBit, "1.5 Bit") )
		dcb.StopBits = ONE5STOPBITS;
	else if ( !strcmp(szStopBit, "2 Bit") )
		dcb.StopBits = TWOSTOPBITS;
	else //if ( !strcmp(szStopBit, "1 Bit") )
		dcb.StopBits = ONESTOPBIT;


	if ( !SetCommState(m_hComm, &dcb) )
	{
		CloseHandle(m_hComm);
		return FALSE;
	}

	if ( !SetupComm(m_hComm, IN_QUE_SIZE, OUT_QUE_SIZE) )
	{
		CloseHandle(m_hComm);
		return FALSE;
	}

	m_hStatEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_hStatEvent == NULL )
		return FALSE;

	m_hStopReading = CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_hStopReading == NULL )
		return FALSE;

	if ( !ClearPort() )
		return FALSE;

	m_bConnected = TRUE;

	return TRUE;
}

BOOL CSerial_Func_Main::OpenPort(LPSTR szPortName, DCB* pdcb)
{
	if ( IsOpened() )
		return TRUE;

	if ( strlen(szPortName) > 4 )	// Greater than COM9 (ex: COM10)
		sprintf_s(m_szPortName, 10, "\\\\.\\%s", szPortName);
	else
		sprintf_s(m_szPortName, 10, "%s", szPortName);

	m_dwBaudRate = pdcb->BaudRate;

	COMMTIMEOUTS	timeouts;
	DCB				dcb;

	if ( !InitSerialEvents() )
		return FALSE;

	m_hComm = CreateFile(m_szPortName, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE)
		return FALSE;

	ZeroMemory(&timeouts, sizeof(COMMTIMEOUTS));
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;

	if ( !SetCommTimeouts(m_hComm, &timeouts) ) 
	{
		CloseHandle(m_hComm);
		return FALSE; 
	}

	ZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);
	if ( !GetCommState(m_hComm, &dcb) ) 
	{
		CloseHandle(m_hComm);
		return FALSE; 
	}
	ZeroMemory(&dcb, sizeof(DCB));

	dcb.BaudRate = pdcb->BaudRate;
	dcb.fBinary = pdcb->fBinary;
	dcb.fParity = pdcb->fParity;
	dcb.ByteSize = pdcb->ByteSize;
	dcb.Parity = pdcb->Parity;
	dcb.StopBits = pdcb->StopBits;
	dcb.fInX = pdcb->fInX;
	dcb.fOutX = pdcb->fOutX;		// Xon, Xoff 사용.
	dcb.XonChar = pdcb->XonChar;
	dcb.XoffChar = pdcb->XoffChar;
	dcb.XonLim = pdcb->XonLim;
	dcb.XoffLim = pdcb->XoffLim;

	if ( !SetCommState(m_hComm, &dcb) )
	{
		CloseHandle(m_hComm);
		return FALSE;
	}

	if ( !SetupComm(m_hComm, IN_QUE_SIZE, OUT_QUE_SIZE) )
	{
		CloseHandle(m_hComm);
		return FALSE;
	}

	m_hStatEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_hStatEvent == NULL )
		return FALSE;

	m_hStopReading = CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_hStopReading == NULL )
		return FALSE;

	if ( !ClearPort() )
		return FALSE;

	m_bConnected = TRUE;

	return TRUE;
}

void CSerial_Func_Main::ClosePort()
{
	if ( IsOpened() )
	{
		PurgeComm(m_hComm, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR);
		if ( m_hComm != NULL )
			CloseHandle(m_hComm);
		if ( m_ovWrite.hEvent != NULL )
			CloseHandle(m_ovWrite.hEvent);
		if ( m_ovRead.hEvent != NULL )
			CloseHandle(m_ovRead.hEvent);

		m_hComm = NULL;
		InitOverlapped(&m_ovWrite);
		InitOverlapped(&m_ovRead);
	}

	if ( m_hStatEvent != NULL )
	{
		CloseHandle(m_hStatEvent);
		m_hStatEvent = NULL;
	}
	if ( m_hStopReading != NULL )
	{
		CloseHandle(m_hStopReading);
		m_hStopReading = NULL;
	}

	m_bConnected = FALSE;
}

void CSerial_Func_Main::InitTxPort()
{
	PurgeComm(m_hComm, PURGE_TXCLEAR|PURGE_TXABORT);
}

void CSerial_Func_Main::InitRxPort()
{
	PurgeComm(m_hComm, PURGE_RXCLEAR|PURGE_RXABORT);
}

// All buffered data to be written
BOOL CSerial_Func_Main::FlushBuffer()
{
	return FlushFileBuffers(m_hComm);
}

// 현재 Queue에 쌓여있는 data를 Clear 한다.
void CSerial_Func_Main::ClearRxBuffer()
{
	BYTE	btTemp[DEFAULT_SIZE];
	UINT	nClearBufferInterval = 100;
	UINT	nRet = 0;

	for (;;)
	{
		ZeroMemory(btTemp, sizeof(btTemp));
		nRet = ReadBytes(btTemp, sizeof(btTemp), nClearBufferInterval);
		if (nRet == 0) { break; }
	}
	InitRxPort();
}

///////////////////////////////////////////////////////////////////////////
// 1 byte를 Write 한다.
BOOL CSerial_Func_Main::WriteSingleByte(BYTE OneByte, UINT nTimeout)
{
	DWORD	dwWritten = 0;
	BOOL	bWrittenDone = FALSE;

	bWrittenDone = WriteFile(m_hComm, &OneByte, 1, &dwWritten, &m_ovWrite);
	if ( !bWrittenDone && GetLastError() == ERROR_IO_PENDING )
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_ovWrite.hEvent, nTimeout))
		{
			if (GetOverlappedResult(m_hComm, &m_ovWrite, &dwWritten, FALSE))
				bWrittenDone = TRUE;
			else
				bWrittenDone = FALSE;
		}
		else
			bWrittenDone = FALSE;
	}

	return bWrittenDone;
}

///////////////////////////////////////////////////////////////////////////
// nLen bytes를 Write 한다.
UINT CSerial_Func_Main::WriteBytes(BYTE *pBytes, UINT nLen, UINT nTimeout)
{
	DWORD	dwWritten = 0;
	BOOL	bWrittenDone = FALSE;

	bWrittenDone = WriteFile(m_hComm, pBytes, nLen, &dwWritten, &m_ovWrite);
	if ( !bWrittenDone && GetLastError() == ERROR_IO_PENDING )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject(m_ovWrite.hEvent, nTimeout) )
		{
			if ( GetOverlappedResult(m_hComm, &m_ovWrite, &dwWritten, FALSE) )
				bWrittenDone = TRUE;
			else
				bWrittenDone = FALSE;
		}
		else
			bWrittenDone = FALSE;
	}

	if ( !bWrittenDone )
		return 0;

	return dwWritten;
}

UINT CSerial_Func_Main::WriteData(BYTE *pBuff, UINT nLen, UINT nTimeout)
{
	DWORD	dwTotalWritten = 0;
	BOOL	bWrittenDone = FALSE;
	UINT	i = 0;

	if ( !IsOpened() )
		return 0;
	if ( nLen <= 0 )
		return 0;

	InitTxPort();

	for (i = 0; i < nLen; i++)
	{
		if ( !WriteSingleByte((BYTE)pBuff[i], nTimeout) )
		{
			return dwTotalWritten;
		}
		dwTotalWritten++;
	}

	if ( !FlushBuffer() )
		return 0;

	return dwTotalWritten;
}

UINT CSerial_Func_Main::WriteDataMulti(BYTE *pBuff, UINT nLen, UINT nTimeout)
{
	DWORD	dwTotalWritten = 0;
	BOOL	bWrittenDone = FALSE;
	UINT	i = 0;
	UINT	nWrite;

	if ( !IsOpened() )
		return 0;
	if ( nLen <= 0 )
		return 0;

	InitTxPort();

	while ( nLen > 0 )
	{
		nWrite = WriteBytes(pBuff, nLen, nTimeout);
		if ( nWrite == 0 )
		{
			return dwTotalWritten;
		}
		dwTotalWritten += nWrite;
		nLen -= nWrite;

		if ( nLen == 0 )
			break;
	}

	if ( !FlushBuffer() )
		return 0;

	return dwTotalWritten;
}

UINT CSerial_Func_Main::GetInQueDataSize()
{
	DWORD	dwInQue;
	DWORD	dwError;
	COMSTAT	comstat;

	ClearCommError(m_hComm, &dwError, &comstat);
	dwInQue = comstat.cbInQue;

	return dwInQue;
}
/*
	dwRes = WaitForMultipleObjects(2, hEvents, FALSE, nTimeout);
	if ( WAIT_OBJECT_0 == dwRes )
	{
		if ( GetOverlappedResult(m_hComm, &m_ovRead, &dwReaded, FALSE) )
			bReadDone = TRUE;
		else
			bReadDone = FALSE;
	}
	else if ( WAIT_OBJECT_0+1 == dwRes )
	{
		// For StopReading by user
		ResetEvent(m_hStopReading);
		bReadDone = FALSE;
	}
	else
	{
		// Timeout or Error
		bReadDone = FALSE;
	}
*/
/*
	if ( WAIT_OBJECT_0 == WaitForSingleObject(m_ovRead.hEvent, nTimeout) )
	{
		if ( GetOverlappedResult(m_hComm, &m_ovRead, &dwReaded, FALSE) )
			bReadDone = TRUE;
		else
			bReadDone = FALSE;
	}
	else
		bReadDone = FALSE;
*/

///////////////////////////////////////////////////////////////////////////
// 1 byte를 Read 한다.
BOOL CSerial_Func_Main::ReadSingleByte(BYTE *OneByte, UINT nTimeout)
{
	DWORD	dwReaded = 0;
	BOOL	bReadDone = FALSE;
	//DWORD	dwRes;
	//HANDLE	hEvents[2];

	if ( !GetInQueDataSize() )
		return FALSE;

	//hEvents[0] = m_ovRead.hEvent;
	//hEvents[1] = m_hStopReading;

	*OneByte  = 0x00;
	bReadDone = ReadFile(m_hComm, OneByte, 1, &dwReaded, &m_ovRead);
	if ( !bReadDone && GetLastError() == ERROR_IO_PENDING )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject(m_ovRead.hEvent, nTimeout) )
		{
			if ( GetOverlappedResult(m_hComm, &m_ovRead, &dwReaded, FALSE) )
				bReadDone = TRUE;
			else
				bReadDone = FALSE;
		}
		else
			bReadDone = FALSE;
	}

	return bReadDone;
}

///////////////////////////////////////////////////////////////////////////
// nLen bytes를 Read 한다.
UINT CSerial_Func_Main::ReadBytes(BYTE *pBytes, UINT nLen, UINT nTimeout)
{
	DWORD	dwReaded = 0;
	BOOL	bReadDone = FALSE;
	//DWORD	dwRes;
	//HANDLE	hEvents[2];

	if ( !GetInQueDataSize() )
		return 0;

	//hEvents[0] = m_ovRead.hEvent;
	//hEvents[1] = m_hStopReading;

	ZeroMemory(pBytes, nLen);
	bReadDone = ReadFile(m_hComm, pBytes, nLen, &dwReaded, &m_ovRead);
	if ( !bReadDone && GetLastError() == ERROR_IO_PENDING )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject(m_ovRead.hEvent, nTimeout) )
		{
			if ( GetOverlappedResult(m_hComm, &m_ovRead, &dwReaded, FALSE) )
				bReadDone = TRUE;
			else
				bReadDone = FALSE;
		}
		else
			bReadDone = FALSE;
	}

	if ( !bReadDone )
		return 0;

	return dwReaded;
}

void CSerial_Func_Main::StopReading()
{
	SetEvent(m_hStopReading);
}

UINT CSerial_Func_Main::ReadData(BYTE *pBuff, UINT nLen, UINT nTimeout)
{
	BYTE	btTemp[DEFAULT_SIZE];
	DWORD	dwReaded = 0;
	UINT	nTotalReaded = 0;
	UINT	nOneByteReadInterval = ONE_BYTE_READ_INTERVAL;
	UINT	nRet;

	if ( !IsOpened() )
		return 0;

	if ( nLen <= 0 )
		return 0;

	if ( nTimeout != INFINITE )
	{
		if ( nTimeout < MINIMUM_TIMEOUT )
			nTimeout = MINIMUM_TIMEOUT;
	}

	InitRxPort();

	if ( !WaitEventThread() )
		return nTotalReaded;

	HANDLE	hEvents[2];

	hEvents[0] = m_hStatEvent;
	hEvents[1] = m_hStopReading;

	//DWORD dwRes = WaitForSingleObject(m_hStatEvent, nTimeout);
	DWORD dwRes = WaitForMultipleObjects(2, hEvents, FALSE, nTimeout);
	if ( dwRes == WAIT_OBJECT_0 )
	{
		ResetEvent(m_hStatEvent);
		for (;;)
		{
			ZeroMemory(btTemp, sizeof(btTemp));
			//nRet = ReadBytes(btTemp, nLen, nOneByteReadInterval);
			nRet = ReadSingleByte(btTemp, nOneByteReadInterval);
			if ( nRet == 0 )
				break;
			memcpy(&pBuff[nTotalReaded], &btTemp[0], nRet);
			nTotalReaded += nRet;
			if ( nTotalReaded == nLen )
				break;
		}
	}
	else if ( dwRes == WAIT_OBJECT_0+1 )
	{
		ResetEvent(m_hStopReading);
	}
	else if ( dwRes == WAIT_TIMEOUT )
	{
		// CommEvent Timeout --> No CommEvent Occurred.
		SetEvent(m_hStatEvent);
		return 0;
	}
	else
	{
		// Error Case
		SetEvent(m_hStatEvent);
		return 0;
	}

	return nTotalReaded;
}

UINT CSerial_Func_Main::ReadData2(BYTE *pBuff, UINT nLen, UINT nTimeout)
{
	BYTE	btTemp[DEFAULT_SIZE];
	DWORD	dwReaded = 0;
	UINT	nTotalReaded = 0;
	UINT	nOneByteReadInterval = ONE_BYTE_READ_INTERVAL;
	UINT	nRet;

	if ( !IsOpened() )
		return 0;

	if ( nLen <= 0 )
		return 0;

	if ( nTimeout != INFINITE )
	{
		if ( nTimeout < MINIMUM_TIMEOUT )
			nTimeout = MINIMUM_TIMEOUT;
	}

	if ( !WaitEventThread() )
		return nTotalReaded;

	HANDLE	hEvents[2];

	hEvents[0] = m_hStatEvent;
	hEvents[1] = m_hStopReading;

	DWORD dwRes = WaitForMultipleObjects(2, hEvents, FALSE, nTimeout);
	if ( dwRes == WAIT_OBJECT_0 )
	{
		ResetEvent(m_hStatEvent);
		for (;;)
		{
			ZeroMemory(btTemp, sizeof(btTemp));
			//nRet = ReadBytes(btTemp, nLen, nOneByteReadInterval);
			nRet = ReadSingleByte(btTemp, nOneByteReadInterval);
			if ( nRet == 0 )
				break;
			memcpy(&pBuff[nTotalReaded], &btTemp[0], nRet);
			nTotalReaded += nRet;
			if ( nTotalReaded == nLen )
				break;
		}
	}
	else if ( dwRes == WAIT_OBJECT_0+1 )
	{
		ResetEvent(m_hStopReading);
	}
	else if ( dwRes == WAIT_TIMEOUT )
	{
		// CommEvent Timeout --> No CommEvent Occurred.
		SetEvent(m_hStatEvent);
		return 0;
	}
	else
	{
		// Error Case
		SetEvent(m_hStatEvent);
		return 0;
	}

	return nTotalReaded;
}

UINT CSerial_Func_Main::ReadDataMulti(BYTE *pBuff, UINT nLen, UINT nTimeout)
{
	BYTE	btTemp[DEFAULT_SIZE];
	DWORD	dwReaded = 0;
	UINT	nTotalReaded = 0;
	UINT	nOneByteReadInterval = ONE_BYTE_READ_INTERVAL;
	UINT	nRet;

	if ( !IsOpened() )
		return 0;

	if ( nLen <= 0 )
		return 0;

	if ( nTimeout != INFINITE )
	{
		if ( nTimeout < MINIMUM_TIMEOUT )
			nTimeout = MINIMUM_TIMEOUT;
	}

	InitRxPort();

	if ( !WaitEventThread() )
		return nTotalReaded;

	HANDLE	hEvents[2];

	hEvents[0] = m_hStatEvent;
	hEvents[1] = m_hStopReading;

	//DWORD dwRes = WaitForSingleObject(m_hStatEvent, nTimeout);
	DWORD dwRes = WaitForMultipleObjects(2, hEvents, FALSE, nTimeout);
	if ( dwRes == WAIT_OBJECT_0 )
	{
		ResetEvent(m_hStatEvent);
		for (;;)
		{
			ZeroMemory(btTemp, sizeof(btTemp));
			nRet = ReadBytes(btTemp, nLen, nOneByteReadInterval);
			//nRet = ReadSingleByte(btTemp, nOneByteReadInterval);
			if ( nRet == 0 )
				break;
			memcpy(&pBuff[nTotalReaded], &btTemp[0], nRet);
			nTotalReaded += nRet;
			if ( nTotalReaded == nLen )
				break;
		}
	}
	else if ( dwRes == WAIT_OBJECT_0+1 )
	{
		ResetEvent(m_hStopReading);
	}
	else if ( dwRes == WAIT_TIMEOUT )
	{
		// CommEvent Timeout --> No CommEvent Occurred.
		SetEvent(m_hStatEvent);
		return 0;
	}
	else
	{
		// Error Case
		SetEvent(m_hStatEvent);
		return 0;
	}

	return nTotalReaded;
}

UINT CSerial_Func_Main::ReadDelayData(BYTE *pBuff, UINT nLen, UINT nTimeout, UINT nRetryCnt, UINT nDelayTime)
{
	BYTE	btTemp[DEFAULT_SIZE];
	DWORD	dwReaded = 0;
	UINT	nTotalReaded = 0;
	UINT	nOneByteReadInterval = ONE_BYTE_READ_INTERVAL;
	UINT	nRet;
	UINT	nCnt = 0;

	if ( !IsOpened() )
		return 0;

	if ( nLen <= 0 )
		return 0;

	if ( nTimeout != INFINITE )
	{
		if ( nTimeout < MINIMUM_TIMEOUT )
			nTimeout = MINIMUM_TIMEOUT;
	}

	InitRxPort();

	if ( !WaitEventThread() )
		return nTotalReaded;

		HANDLE	hEvents[2];

	hEvents[0] = m_hStatEvent;
	hEvents[1] = m_hStopReading;

	//DWORD dwRes = WaitForSingleObject(m_hStatEvent, nTimeout);
	DWORD dwRes = WaitForMultipleObjects(2, hEvents, FALSE, nTimeout);
	if ( dwRes == WAIT_OBJECT_0 )
	{
		ResetEvent(m_hStatEvent);
		for (;;)
		{
			ZeroMemory(btTemp, sizeof(btTemp));
			nRet = ReadBytes(btTemp, nLen, nOneByteReadInterval);
			if ( nRet == 0 )
			{
				if ( nCnt++ < nRetryCnt )
				{
					Sleep(nDelayTime);
					continue;
				}
				else
					break;
			}
			memcpy(&pBuff[nTotalReaded], &btTemp[0], nRet);
			nTotalReaded += nRet;
			if ( nTotalReaded == nLen )
				break;
		}
	}
	else if ( dwRes == WAIT_OBJECT_0+1 )
	{
		ResetEvent(m_hStopReading);
	}
	else if ( dwRes == WAIT_TIMEOUT )
	{
		// CommEvent Timeout --> No CommEvent Occurred.
		SetEvent(m_hStatEvent);
		return 0;
	}
	else
	{
		// Error Case
		SetEvent(m_hStatEvent);
		return 0;
	}

	return nTotalReaded;
}

BOOL CSerial_Func_Main::WaitEventThread()
{
	HANDLE		hThread = NULL;
	DWORD		dwThreadId;

	hThread =  (HANDLE)_beginthreadex(
					NULL,
					0,
					(unsigned int (WINAPI *)(void *))WaitEventFunc,
					(LPVOID)this,
					0,
					(unsigned int*)&dwThreadId
				);

	if ( hThread == NULL )
		return FALSE;

	CloseHandle(hThread);
	hThread = NULL;
	return TRUE;
}

///////////////////////////////////////////////////////////////////
// Thread Functions
DWORD WINAPI CSerial_Func_Main::WaitEventFunc(LPVOID pParam)
{
	CSerial_Func_Main *p = (CSerial_Func_Main *)pParam;

	for (;;)
	{
		DWORD dwRes = WaitForSingleObject(p->m_hStatEvent, p->m_nCheckIntervalValue);
		if ( dwRes == WAIT_TIMEOUT )
		{
			if ( p->GetInQueDataSize() )
			{
				SetEvent(p->m_hStatEvent);
				break;
			}
			else
			{
				continue;
			}
		}
		else if ( dwRes == WAIT_OBJECT_0 )
		{
			// CommEvent Timeout --> No CommEvent Occurred.
			ResetEvent(p->m_hStatEvent);
			break;
		}
		else
		{
			// Error Case
			ResetEvent(p->m_hStatEvent);
			break;
		}
	}

	return FALSE;
}

/*
void CSerial_Func_Main::SaveLog(char *szDevice, char *szLogData)
{
	return;

	char szTime[21];
	char szDate[20];
	char szFilename[100];

	memset(szTime, 0x00, sizeof(szTime));
	memset(szDate, 0x00, sizeof(szDate));

	time_t ltime;
	struct tm *today;
	time( &ltime );
	today = localtime( &ltime );
	sprintf(szTime, "%4d/%02d/%02d %02d:%02d:%02d", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec);
	sprintf(szDate, "%4d%02d%02d", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);

	memset(szFilename, 0x00, sizeof(szFilename));
	//sprintf(szFilename, "%s\\Serial_%s%s.log", LOG_DIRECTORY, szDevice, szDate);
	sprintf(szFilename, "%s\\Serial_%s%s.log", ".", szDevice, szDate);

	FILE *fp = NULL;
	fp = fopen(szFilename, "a");

	fprintf(fp, "[%s]\r\n%s\r\n\r\n", szTime, szLogData);


	fclose(fp);


}*/
