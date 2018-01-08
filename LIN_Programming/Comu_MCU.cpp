#include "stdafx.h"
#include "Comu_MCU.h"
#include "CFunc_Reg.h"

#define CH_TERM 13   //CR 

Comu_MCU::Comu_MCU()
{

	m_cfg.nBaudRate = 115200;
	m_cfg.sPort = "COM8";

	this->f_regi_read_com_param();


	m_pCom = new Comu_CSerial;

#ifndef	SIM_MCU_MUX

	bool bRtn = this->f_Open();

	if (bRtn != true)
	{
		AfxMessageBox("MCU 통신포트를 열수가 없습니다.");
		AfxMessageBox("프로그램을 열수가 없습니다.");
		exit(-1);
	}


	this->f_debug();

#endif

}


Comu_MCU::~Comu_MCU()
{
	delete m_pCom;
}


void Comu_MCU::f_debug()
{
	this->f_cmd("*idn?");

	this->f_cmd("*idn?");

	//	this->f_cmd("PIN PD 32 OM");
	//	this->f_cmd("PIN PD 16 1");

	//	this->f_cmd("PIN PD 16 OFF");

	//	this->f_cmd("BIT PD 1 ON");
	//	this->f_cmd("BIT PD 1 OFF");

	//	this->f_cmd("PORT DEVH",  (unsigned)8); 

	this->f_cmd("*rst");

}


void Comu_MCU::f_port_set_MUX(unsigned devH, unsigned devL, unsigned Inst, unsigned Ext)
{
	CString strBuf;
	strBuf.Format("PORT MUX %d, %d, %d, %d", devH, devL, Inst, Ext);
	f_cmd((char *)(LPCTSTR)strBuf);

}


void Comu_MCU::f_port_set_devL(unsigned data)
{
	f_cmd_uint("PORT DEVL", data & 0x00ff);
}


void Comu_MCU::f_port_set_devH(unsigned data)
{
	f_cmd_uint("PORT DEVH", data & 0x00ff);
}


void Comu_MCU::f_port_set_Inst(unsigned data)
{
	f_cmd_uint("PORT INST", data & 0x00ff);
}


void Comu_MCU::f_port_set_Ext(unsigned data)
{
	f_cmd_uint("PORT EXT", data & 0x00ff);
}


void Comu_MCU::f_port_set_PLC_OUT(unsigned data)
{
	f_cmd_uint("PORT PLC", data & 0x000f);
}

bool Comu_MCU::f_bit_read_JIG_start_sw_press()  // if 0이면 스위치 동작함.
{
#ifdef SIM_MCU_MUX
	return false;
#endif

	f_cmd("PIN PB 1 ?");

	unsigned nChk = atoi(m_recv.sRecv);

	return (0 == nChk) ? true : false;   // Sw가 눌려지면 0값이 된다, PC뢰로 때문임

}

void Comu_MCU::f_bit_set_JIG_SOL(bool bSet)					// plc_out.p0
{
	CString sBuf;

	sBuf.Format("PIN PE %d %d", K12, bSet ? 1 : 0);
	f_cmd((char*)(LPCTSTR)sBuf);
}


void Comu_MCU::f_bit_set_JIG_Buzzer(bool bSet)
{
	CString sBuf;

	sBuf.Format("PIN PE %d %d", K13, bSet ? 1 : 0);
	f_cmd((char*)(LPCTSTR)sBuf);
}






////////////////////////////////////////////////////////////////////////////////////////////////
#define REG_SUBKEY_MCU_COMPORT				"mcu_port"

void Comu_MCU::f_regi_save_com_param()
{
	CFunc_RegUser Regi(REG_SUBKEY_MCU_COMPORT);
	Regi.save_CString("mcu_com_port", m_cfg.sPort);
	Regi.save_uint("mcu_com_baudrate", m_cfg.nBaudRate);
}


void Comu_MCU::f_regi_read_com_param()
{
	CFunc_RegUser Regi(REG_SUBKEY_MCU_COMPORT);
	Regi.read_CString("mcu_com_port", m_cfg.sPort, "COM8");
	Regi.read_uint("mcu_com_baudrate", m_cfg.nBaudRate, 115200);
}


bool Comu_MCU::f_Open(LPSTR szPort, UINT nBaudRate)
{
	m_cfg.sPort = szPort;
	m_cfg.nBaudRate = nBaudRate;

	return f_Open();
}



bool Comu_MCU::f_Open()
{
	if (!m_pCom->OpenPort((LPSTR)(LPCSTR)m_cfg.sPort, m_cfg.nBaudRate))				//2013.12.09 sjkim
		return false;

	f_regi_save_com_param();

	return true;

}


int Comu_MCU::f_Communicate(BYTE *pWrite, UINT nCmdLen, BYTE *pRead, UINT nReadTimeout)
{
	BYTE byCmd[100];
	BYTE byRes[100];
	int nRead, nWrite;

	memset(byCmd, 0, sizeof(byCmd));
	memcpy(byCmd, pWrite, nCmdLen);

	nWrite = m_pCom->WriteDataMulti(byCmd, nCmdLen, 3000);
	if (nWrite == 0) { return 0; }

	memset(byRes, 0, sizeof(byRes));
	nRead = m_pCom->ReadDelayData(byRes, sizeof(byRes), nReadTimeout);
	if (nRead >0)
	{
		memcpy(pRead, byRes, nRead);
	}
	else
		return 0;

	return nRead;
}

int Comu_MCU::f_cmd(char *pWrite)
{
	m_recv.sRecv = "";
	m_recv.sErrMsg = "";

	m_send.sCmd.Format("%s", pWrite);

	m_send.nCmdLen = m_send.sCmd.GetLength();

	memset(m_send.byCmd, 0, sizeof(m_send.byCmd));

	for (int i = 0; i<m_send.nCmdLen; i++)
		m_send.byCmd[i] = m_send.sCmd[i];

	m_send.byCmd[m_send.nCmdLen] = CH_TERM;
	m_send.nCmdLen++;


	m_send.nWriteLen = m_pCom->WriteDataMulti(m_send.byCmd, m_send.nCmdLen, 1000);
	if (m_send.nWriteLen == 0) { return 0; }


	memset(m_recv.byRecv, 0, sizeof(m_recv.byRecv));
	m_recv.nRecvLen = m_pCom->ReadDelayData(m_recv.byRecv, sizeof(m_recv.byRecv), 1000);


	m_recv.sRecv.Format("%s", m_recv.byRecv);

	//-----------------------------------------------------------------------------------


	if (0 == m_recv.sRecv.Compare("OK"))
	{
		//Illegal Parameter 오류 
		return true;

	}
	else if ('C' == m_recv.sRecv[0])
	{
		//	m_recv.sErrMsg += " : PS 통신오류";
		//	::MessageBox(NULL, m_recv.sErrMsg, "오류", MB_OK);
	}
	else if ('E' == m_recv.sRecv[0])
	{
		//	m_recv.sErrMsg += " : PS 통신오류";
		//	::MessageBox(NULL, m_recv.sErrMsg, "오류", MB_OK);
	}




	if (m_recv.nRecvLen >0)
	{
		return m_recv.nRecvLen;
	}
	else
		return 0;


	return 0;
}


int  Comu_MCU::f_cmd_uint(char *pMsg, unsigned nVal)
{
#ifndef	SIM_MCU_MUX
	CString sMsg;

	sMsg.Format("%s %d", pMsg, nVal);

	return f_cmd((LPSTR)(LPCTSTR)sMsg);
#endif

	return 0;
}


int  Comu_MCU::f_cmd_dbl(char *pMsg, double fVal)
{
#ifndef	SIM_MCU_MUX
	CString sMsg;

	sMsg.Format("%s %f", pMsg, fVal);

	return f_cmd((LPSTR)(LPCTSTR)sMsg);
#endif

	return 0;

}

int  Comu_MCU::f_cmd(char *pMsg, double fVal)
{
#ifndef	SIM_MCU_MUX

	CString sMsg;

	sMsg.Format("%s %f", pMsg, fVal);

	return f_cmd((LPSTR)(LPCTSTR)sMsg);

#endif

	return 0;

}


int  Comu_MCU::f_cmd(char *pMsg, char *pFmt, double fVal)
{
#ifndef	SIM_MCU_MUX
	CString sMsg, sFmt, sBuf;

	sFmt.Format("%c%c %s", '%', '%s', pFmt);
	sMsg.Format(sFmt, pMsg, fVal);

	return f_cmd((LPSTR)(LPCTSTR)sMsg);
#endif

	return 0;
}