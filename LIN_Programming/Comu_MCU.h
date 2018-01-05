#pragma once

#include "Comu_CSerial.h"



/*

MCU10.R1-KAI TEST MUX

MCU PORT DEV.H  PD.8~15
MCU PORT DEV.L  PD.0~7

MCU PORT INST.H PE.0~3
MCU PORT INST.L PE.4~7

MCU PORT PLC.OUT PE.12~15
MCU PORT EXT.OUT PE.8~11
MCU PORT PLC.IN  PB.0~1


MCU PORT PLCIN PB.0->START (PB.0)
MCU PORT PLCOUT.P0->JIG ON (PE.12)
MCU PORT PLCOUT.P1->BUZ ON  )PE.13)

*/



class Comu_MCU
{
public:
	Comu_MCU();
	~Comu_MCU();

	Comu_CSerial *m_pCom;




	//-------------------------------------------------------------------------------------
	void f_port_set_MUX(unsigned devL, unsigned devH, unsigned Inst, unsigned ext);
	void f_port_set_devL(unsigned data);
	void f_port_set_devH(unsigned data);
	void f_port_set_Inst(unsigned data);
	void f_port_set_Ext(unsigned data);
	void f_port_set_PLC_OUT(unsigned data);



	//-----------------------------------------------------------------------------------

	bool f_bit_read_JIG_start_sw_press();  // if 0이면 스위치 동작함.
	void f_bit_set_JIG_SOL(bool bSet);					// plc_out.p0
	void f_bit_set_JIG_Buzzer(bool bSet);				// plc_out.p1
														// plc_in.p0


														//-----------------------------------------------------------------------------------
	void f_debug();

	void f_regi_save_com_param();
	void f_regi_read_com_param();
	//=================================================================================

	int   f_cmd(char *pWrite);
	int   f_cmd(char *pWrite, double fVal);
	int   f_cmd_uint(char *pWrite, unsigned nVal);
	int   f_cmd_dbl(char *pWrite, double fVal);

	int   f_cmd(char *pMsg, char *pFmt, double fVal);

	struct
	{
		BYTE byRecv[100];
		int nRecvLen;

		CString sRecv;		//
		CString sErrMsg;	//
	}m_recv;

	struct
	{
		BYTE byCmd[100];
		int nWriteLen;
		int nCmdLen;

		CString sCmd;	//
	}m_send;




	//======================================================================================
private:

	struct
	{
		char szPort[10];

		UINT nBaudRate;
		CString sPort;

		CString sInstrumentName;
	}m_cfg;

	bool  f_Open(LPSTR szPort, UINT nBaudRate);
	bool  f_Open();
	int   f_Communicate(BYTE *pWrite, UINT nCmdLen, BYTE *pRead, UINT nReadTimeout);


};

