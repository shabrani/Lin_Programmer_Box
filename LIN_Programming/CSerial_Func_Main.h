#pragma once

#include <afxmt.h>

//////////////////////////////////////////////////////////////////////
#define	IN_QUE_SIZE				4096
#define	OUT_QUE_SIZE			4096
#define	DEFAULT_SIZE			4096

#define	MINIMUM_TIMEOUT			50	// miliseconds
#define	ONE_BYTE_READ_INTERVAL	100	// miliseconds

//////////////////////////////////////////////////////////////////////

class CSerial_Func_Main
{
public:
	CSerial_Func_Main(void);
	~CSerial_Func_Main(void);

public:
	BOOL			m_bConnected;

private:
	HANDLE			m_hComm;
	char			m_szPortName[10];
	DWORD			m_dwBaudRate;
	OVERLAPPED		m_ovWrite;
	OVERLAPPED		m_ovRead;
	HANDLE			m_hStatEvent;
	HANDLE			m_hStopReading;

	UINT			m_nCheckIntervalValue;

public:
	BOOL			IsOpened();
	void			ErrorMsg(DWORD dwError);
	BOOL			OpenPort(LPSTR szPortName, DWORD dwBaudRate, UINT nDataBit = 8, LPSTR szParity = "None", LPSTR szStopBit =  "2 Bit");
	BOOL			OpenPort(LPSTR szPortName, DCB* pdcb);
	void			ClosePort();
	void			ClearRxBuffer();
	UINT			GetInQueDataSize();
	UINT			WriteData(BYTE *pBuff, UINT nLen, UINT nTimeout);
	UINT			WriteDataMulti(BYTE *pBuff, UINT nLen, UINT nTimeout);
	UINT			WriteDataMulti_J(BYTE *pBuff, UINT nLen, UINT nTimeout) {return WriteBytes(pBuff, nLen, nTimeout);};
	BOOL			ReadSingleByte(BYTE *OneByte, UINT nTimeout);
	UINT			ReadData(BYTE *pBuff, UINT nLen, UINT nTimeout);
	UINT			ReadData2(BYTE *pBuff, UINT nLen, UINT nTimeout);
	UINT			ReadDataMulti(BYTE *pBuff, UINT nLen, UINT nTimeout);
	UINT			ReadDelayData(BYTE *pBuff, UINT nLen, UINT nTimeout, UINT nRetryCnt = 3, UINT nDelayTime = 50);
	void			StopReading();

//	void			SaveLog(char *szDevice, char *szLogData);


private:
	void			InitOverlapped(OVERLAPPED *ov);
	BOOL			CreateOvlapEvent(OVERLAPPED *ov);
	BOOL			InitSerialEvents();
	BOOL			ClearPort();
	void			InitTxPort();
	BOOL			FlushBuffer();
	BOOL			WriteSingleByte(BYTE OneByte, UINT nTimeout);
	UINT			WriteBytes(BYTE *pBytes, UINT nLen, UINT nTimeout);
	void			InitRxPort();
	BOOL			WaitEventThread();
	UINT			ReadBytes(BYTE *pBytes, UINT nLen, UINT nTimeout);

private:
	///////////////////////////////////////////////////////////////////
	// Thread Functions
	static DWORD WINAPI WaitEventFunc(LPVOID pParam);
};

