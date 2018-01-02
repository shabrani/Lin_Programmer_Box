#pragma once

#include "CSerial_Func_Main.h"

class CSerial_Func_FRDM : public CSerial_Func_Main
{
public:
	CSerial_Func_FRDM(void);
	~CSerial_Func_FRDM(void);

	struct{
		BYTE byRecv[128];
		int nRecvLen;
	}m_recv;

	struct{
		BYTE byCmd[128];
		int nWriteLen;
		int nCmdLen;
	}m_send;


	struct{
		double fSetVolt;
		double fSetCurr;

		bool	bOutOn;
	}m_var;

public:
	bool f_Open(LPSTR szPort, UINT nBaudRate);

	int   f_Check_Signal	(void *cmd, void *port, void *regi);
	int   f_Send_Signal		(void *cmd, void *port, void *regi);
	int	  f_Send_Message	(void *msg);
	char  f_Read_Message	(void *msg);
	void  f_Read_Buffer     (void *msg, CString *sBuf);

	int   f_Voltage_Set		(void *cmd, void *vol);
	float f_Voltage_Read	(void);
	int   f_Bit_Clear		(void *cmd, void *port, void *regi);
	int   f_Clear_Output	(void);


	int f_Check_Start_Signal (void *cmd, void *port, void *regi);
	int f_Send_OK_Signal	 (void *cmd, void *port, void *regi);
	int f_Send_NG_Signal	 (void *cmd, void *port, void *regi);
	int f_Send_RUN_Signal	 (void *cmd, void *port, void *regi);


	bool  f_cmd_and_read_buf		(void *msg, CString *sRead);
	int   f_cmd_and_read_int		(char *pWrite);
	float f_cmd_and_read_float		(char *pWrite);
	char  f_cmd_and_read_char		(char *pWrite);
	CString  f_cmd_and_read_cstring	(char *pWrite);

	//bool  f_cmd_and_read_string		(char *pWrite, CString *sRead);


private:
	CCriticalSection m_CritSec;

	char m_szPort[10];
	UINT m_nBaudRate;
};

