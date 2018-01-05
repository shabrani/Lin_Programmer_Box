#include "stdafx.h"
#include "procedure_Macro.h"

#include "CTest_Main.h"

#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BOSCH CR665
int CTest_Main::f_kvr_LINREG_CR665_Init_VERIFY_MODE	(unsigned nline)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[9] = {0};
	unsigned int	length = 8;

	msg[0] = 0x90;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = 0xFF;
	msg[4] = 0xFF;
	msg[5] = 0xFF;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);
	f_delay_ms(1);

	// Initial Message ///////////////////////////////////////////
	msg[0] = 0x90;
	msg[1] = 0xA5;
	msg[2] = 0xFF;
	msg[3] = 0xFF;
	msg[4] = 0xFF;
	msg[5] = 0xFF;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);
	WndDisplay_TestLinMsg(nline, linBuf);
	f_delay_ms(1);

	msg[0] = 0x90;
	msg[1] = 0x5A;
	msg[2] = 0x00;
	msg[3] = 0xFF;
	msg[4] = 0xFF;
	msg[5] = 0xFF;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);
	WndDisplay_TestLinMsg(nline+1, linBuf);

	return 0; 
}

int CTest_Main::f_kvr_LINREG_CR665_Finish	(unsigned p, unsigned nline)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[9] = {0};
	unsigned int	length = 8;

	msg[0] = 0x90;
	msg[1] = 0xB6;
	msg[2] = 0x00;
	msg[3] = 0x07;
	msg[4] = 0x00;
	msg[5] = 0x00;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);
	WndDisplay_TestLinMsg(nline, linBuf);

	return 0;
}

int CTest_Main::f_kvr_LINREG_CR665_Addr_Verify (unsigned p, unsigned nline, unsigned char addr, unsigned char exp, unsigned char &data)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[9] = {0};
	unsigned int	length = 8;

	msg[0] = 0x90;
	msg[1] = 0xB6;
	msg[2] = addr;
	msg[3] = 0x05;
	msg[4] = exp;
	msg[5] = 0x00;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);

	f_delay_ms(1);

	this->m_pLin->SendTX_and_Read(0x3D, linBuf, 100);
	WndDisplay_TestLinMsg(nline, linBuf);
	f_delay_ms(1);

	if (linBuf.Data[0] != exp)
	{
		data = linBuf.Data[0];
		return (-1);		// fail
	}

	if (linBuf.Data[1] != 0x5D)
	{
		data = linBuf.Data[1];
		return (-1);		// fail
	}
	data = linBuf.Data[0];

	return 0;
}

int CTest_Main::f_kvr_LINREG_CR665_Addr_Programing (unsigned p, unsigned nline, unsigned char addr, unsigned char data)
{
	KVR_LIN_STRUCT linBuf;
	
	unsigned char	msg[9] = {0};
	unsigned int	length = 8;

	msg[0] = 0x90;
	msg[1] = 0xB6;
	msg[2] = addr;
	msg[3] = 0x06;
	msg[4] = data;
	msg[5] = 0x00;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 10);

	f_delay_ms(1);

	this->m_pLin->SendTX_and_Read(0x3D, linBuf, 10);
//	WndDisplay_TestLinMsg(nline, linBuf);
	f_delay_ms(1);

	if (linBuf.Data[1] != 0x69) return (-1);		// fail

	return 0;
}

int CTest_Main::f_kvr_LINREG_CR665_Verify (unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

//	if (true != m_pTitem->Spec.isTest) return TEST_CONTINUE;

//	for (unsigned idx = 1; idx<9; idx++)
//	{
//		this->m_pCSpec->m_vTitem[idx].Spec.isTest = true;
//		this->m_pCSpec->m_vTitem[idx].Spec.nRefTitem = m_pCSpec->m_stMode.stRefTitem.ID_0000_NC;
//	}

	int iRtn  = 0;
	int nline = 0;

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_CLIN_DATA_UNION_NVM uNVM;

	uNVM.u8.Data10_L = 0;
	uNVM.u8.Data11_H = 0;
	uNVM.u8.Data20_L = 0;
	uNVM.u8.Data21_H = 0;
	uNVM.u8.Data30_L = 0;
	uNVM.u8.Data31_H = 0;
	uNVM.u8.Data40_L = 0;
	uNVM.u8.Data41_H = 0;
	uNVM.u8.Data50_L = 0;


	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	f_kvr_LINREG_CR665_Init_VERIFY_MODE	(nline);

	// Address 0x00
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p, nline+2, 0x00, pNVM->Addr00, uNVM.u8.Data10_L);

		iRtn = f_testdata_judge_uint (0, p,  uNVM.u8.Data10_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}



	// Address 0x10
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 1, nline+3, 0x10, pNVM->Addr01, uNVM.u8.Data11_H);

		iRtn = f_testdata_judge_uint (0, p + 1,  uNVM.u8.Data11_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x30
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 3, nline+4, 0x30, pNVM->Addr03, uNVM.u8.Data20_L);

		iRtn = f_testdata_judge_uint (0, p + 3,  uNVM.u8.Data20_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x40
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 4, nline+5, 0x40, pNVM->Addr04, uNVM.u8.Data21_H);

		iRtn = f_testdata_judge_uint (0, p + 4,  uNVM.u8.Data21_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x50
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 5, nline+6, 0x50, pNVM->Addr05, uNVM.u8.Data30_L);

		iRtn = f_testdata_judge_uint (0, p + 5,  uNVM.u8.Data30_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x60
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 6, nline+7, 0x60, pNVM->Addr06, uNVM.u8.Data31_H);

		iRtn = f_testdata_judge_uint (0, p + 6,  uNVM.u8.Data31_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x70
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 7, nline+8, 0x70, pNVM->Addr07, uNVM.u8.Data40_L);

		iRtn = f_testdata_judge_uint (0, p + 7,  uNVM.u8.Data40_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x80
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 8, nline+9, 0x80, pNVM->Addr08, uNVM.u8.Data41_H);

		iRtn = f_testdata_judge_uint (0, p + 8,  uNVM.u8.Data41_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x20
	{
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 2, nline+10, 0x20, pNVM->Addr02, uNVM.u8.Data50_L);

		iRtn = f_testdata_judge_uint (0, p + 2,  uNVM.u8.Data50_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	
	f_kvr_LINREG_CR665_Finish (p + 9, nline+11);

	return TEST_CONTINUE;
}

int CTest_Main::f_kvr_LINREG_CR665_Program_and_Verify (unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];


	int iRtn  = 0;
	int nline = 0;


	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;


	TU_CLIN_DATA_UNION_NVM uNVM;
	uNVM.u8.Data10_L = 0;
	uNVM.u8.Data11_H = 0;
	uNVM.u8.Data20_L = 0;
	uNVM.u8.Data21_H = 0;
	uNVM.u8.Data30_L = 0;
	uNVM.u8.Data31_H = 0;
	uNVM.u8.Data40_L = 0;
	uNVM.u8.Data41_H = 0;
	uNVM.u8.Data50_L = 0;


	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}
	
	f_kvr_LINREG_CR665_Init_VERIFY_MODE	(nline);

	// Address 0x00
	{
		f_kvr_LINREG_CR665_Addr_Programing (p, nline+2, 0x00, pNVM->Addr00);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p, nline+3, 0x00, pNVM->Addr00, uNVM.u8.Data10_L);

		iRtn = f_testdata_judge_uint (0, p,  uNVM.u8.Data10_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x10
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 1, nline+4, 0x10, pNVM->Addr01);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 1, nline+5, 0x10, pNVM->Addr01, uNVM.u8.Data11_H);

		iRtn = f_testdata_judge_uint (0, p + 1,  uNVM.u8.Data11_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x30
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 3, nline+6, 0x30, pNVM->Addr03);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 3, nline+7, 0x30, pNVM->Addr03, uNVM.u8.Data20_L);

		iRtn = f_testdata_judge_uint (0, p + 3,  uNVM.u8.Data20_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x40
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 4, nline+8, 0x40, pNVM->Addr04);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 4, nline+9, 0x40, pNVM->Addr04, uNVM.u8.Data21_H);

		iRtn = f_testdata_judge_uint (0, p + 4,  uNVM.u8.Data21_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x50
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 5, nline+10, 0x50, pNVM->Addr05);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 5, nline+11, 0x50, pNVM->Addr05, uNVM.u8.Data30_L);

		iRtn = f_testdata_judge_uint (0, p + 5,  uNVM.u8.Data30_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x60
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 6, nline+12, 0x60, pNVM->Addr06);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 6, nline+13, 0x60, pNVM->Addr06, uNVM.u8.Data31_H);

		iRtn = f_testdata_judge_uint (0, p + 6,  uNVM.u8.Data31_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x70
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 7, nline+14, 0x70, pNVM->Addr07);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 7, nline+15, 0x70, pNVM->Addr07, uNVM.u8.Data40_L);

		iRtn = f_testdata_judge_uint (0, p + 7,  uNVM.u8.Data40_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x80
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 8, nline+16,0x80, pNVM->Addr08);
		f_delay_ms(10);
		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 8, nline+17,0x80, pNVM->Addr08, uNVM.u8.Data41_H);

		iRtn = f_testdata_judge_uint (0, p + 8,  uNVM.u8.Data41_H );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	


	// Address 0x20
	{
		f_kvr_LINREG_CR665_Addr_Programing (p + 2, nline+18,0x20, pNVM->Addr02);

		iRtn = f_kvr_LINREG_CR665_Addr_Verify (p + 2, nline+19,0x20, pNVM->Addr02, uNVM.u8.Data50_L);

		iRtn = f_testdata_judge_uint (0, p + 2,  uNVM.u8.Data50_L );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}
	
	f_kvr_LINREG_CR665_Finish (p + 9, nline+21);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TLE8881 Function
/*
int CTest_Main::f_kvr_LINREG_Infenion_Init_PROGRAM_MODE (unsigned p)
{

	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;

//	msg[0] = 0x90;
//	msg[1] = 0xFF;
//	msg[2] = 0xFF;
//	msg[3] = 0xFF;
//	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);

	for (unsigned i=0; i<2; i++)
	{
		f_delay_ms (20);		//restart wait 

		msg[0] = 0x00;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x00;
		this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);
//		f_delay_ms (10);

		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);
		
		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (145);

		msg[0] = 0xC4;
		msg[1] = 0x80;
		msg[2] = 0x01;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);

		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
//		f_delay_ms (10);
		if (linBuf.Data[0] != 0x00) continue;		//다시 시작 
		if (linBuf.Data[1] != 0x85) continue;		//다시 시작
		if (linBuf.Data[2] != 0x06) continue;		//다시 시작 

		msg[0] = 0xF4;
		msg[1] = 0x3F;
		msg[2] = 0x00;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);

		int nLoop = 0;
		
		while (1)
		{
			nLoop++;
			if (nLoop > 10) return false;

			this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
//			f_delay_ms (10);

			if ( 0x00 != (linBuf.Data[2] != 0x40) ) break;
		}

		msg[0] = 0xF4;
		msg[1] = 0xBF;
		msg[2] = 0x80;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		msg[0] = 0xF4;
		msg[1] = 0xBF;
		msg[2] = 0x90;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		return 0;	//문제없이 왔으면 프로그램을 빠져 나간다. 
	}

	return -1;		//다섯번을 돌고 왔다면 문제가 있다는 판단을 해도 됨.
}*/

int CTest_Main::f_kvr_LINREG_Infenion_Init_PROGRAM_MODE (unsigned p)
{

	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[8] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	
	//CTest_Main::f_kvr_LINREG_Infenion_Init_PROGRAM_MODE

	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;

	//msg[0] = 0x90;
	//msg[1] = 0xFF;
	//msg[2] = 0xFF;
	//msg[3] = 0xFF;
	//this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);

	for (unsigned i=0; i<2; i++)
	{
		f_delay_ms (20);		//restart wait 

		msg[0] = 0x00;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x00;
		this->m_pLin->SendRX_and_Read(0x3C, msg, 8, linBuf, 100);
//		f_delay_ms (10);

		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);
		
		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
		//f_delay_ms (145);

		msg[0] = 0xC4;
		msg[1] = 0x80;
		msg[2] = 0x01;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);

		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
//		f_delay_ms (10);
		if (linBuf.Data[0] != 0x00) continue;		//다시 시작 
		if (linBuf.Data[1] != 0x85) continue;		//다시 시작
		if (linBuf.Data[2] != 0x06) continue;		//다시 시작 

		msg[0] = 0xF4;
		msg[1] = 0x3F;
		msg[2] = 0x00;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
//		f_delay_ms (10);

		int nLoop = 0;
		
		while (1)
		{
			nLoop++;
			if (nLoop > 10) return false;

			this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
//			f_delay_ms (10);

			if ( 0x00 != (linBuf.Data[2] != 0x40) ) break;
		}

		msg[0] = 0xF4;
		msg[1] = 0xBF;
		msg[2] = 0x80;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		msg[0] = 0xF4;
		msg[1] = 0xBF;
		msg[2] = 0x90;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		return 0;	//문제없이 왔으면 프로그램을 빠져 나간다. 
	}

	return -1;		//다섯번을 돌고 왔다면 문제가 있다는 판단을 해도 됨.
}

int CTest_Main::f_kvr_LINREG_Infenion_Init_VERIFY_MODE	(unsigned p)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;

	for (unsigned i=0; i<2; i++)
	{
		msg[0] = 0x00;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x00;
		this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);

		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		msg[0] = 0xC1;
		msg[1] = 0x00;
		msg[2] = 0x00;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		msg[0] = 0xC4;
		msg[1] = 0x80;
		msg[2] = 0x01;
		msg[3] = 0x06;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);	
		WndDisplay_TestLinMsg(0, linBuf);
		if (linBuf.Data[0] != 0x00) continue;		//다시 시작 
		if (linBuf.Data[1] != 0x85) continue;		//다시 시작
		if (linBuf.Data[2] != 0x06) continue;		//다시 시작 

		msg[0] = 0xF4;
		msg[1] = 0x3F;
		msg[2] = 0x00;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);


		int nLoop = 0;
		
		while (1)
		{
			nLoop++;
			if (nLoop > 10) return false;

			this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
			WndDisplay_TestLinMsg(1, linBuf);
			if ( 0x00 != (linBuf.Data[2] != 0x40) ) break;
		}

		msg[0] = 0xF4;
		msg[1] = 0xBF;
		msg[2] = 0x80;
		msg[3] = 0x7E;
		this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

		return 0;	//문제없이 왔으면 프로그램을 빠져 나간다. 
	}

	return -1;		//다섯번을 돌고 왔다면 문제가 있다는 판단을 해도 됨.
}

int CTest_Main::f_kvr_LINREG_Infenion_Finish	(unsigned p)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	msg[0] = 0x00;
	msg[1] = 0x00;
	msg[2] = 0x00;
	msg[3] = 0x00;
	this->m_pLin->SendRX_and_Read(0x3C, msg, length, linBuf, 100);	

	return 0;
}


int CTest_Main::f_kvr_LINREG_Infenion_Addr_Program (unsigned p, unsigned addr, unsigned char &D_HI, unsigned char &D_LO)
{
	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;


	msg[0] = 0xD4;
	msg[1] = 0xB2;
	msg[2] = addr;
	msg[3] = 0x7E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xF4;
	msg[1] = 0xB3;
	msg[2] = D_LO;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xC4;
	msg[1] = 0xB4;
	msg[2] = D_HI;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xD4;
	msg[1] = 0xB5;
	msg[2] = 0x00;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xC4;
	msg[1] = 0xB0;
	msg[2] = 0x8C;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xF4;
	msg[1] = 0x3F;
	msg[2] = 0x00;
	msg[3] = 0x7E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	for (unsigned i=0; i<10; i++)
	{
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);

														
		if (0x3F != linBuf.Data[0] ) 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Data[0] not Equal 0x3F", false);		
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Fail", true);	
			return -1;
		}

		if (0x06 != linBuf.Data[2] ) 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Data[2] not Equal 0x06", false);		
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Fail", true);	
			return -1;
		}
		
		if (0x00 == (linBuf.Data[1] & 0x0F) ) 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Success", false);
			return 0;			
		}

		if (0x01 == (linBuf.Data[1] & 0x01) )		//BIT B0
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Wait Program Finish", false);
			continue; 			
		}

		if (K3 == (linBuf.Data[1] & K3) )		//BIT B3-> Voltage To Low 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Voltage to LOW", false);
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program FAIL       ",     true);	
//			m_userMsg.f_LIN_LView_Insert_Msg ("Check POWER Supply ",    true);
			return -1;			
		}

	}

//	m_userMsg.f_LIN_LView_Insert_Msg ("Program Not Finished", false);
//	m_userMsg.f_LIN_LView_Insert_Msg ("Program FAIL       ",     true);	

	return -1;
}

int CTest_Main::f_kvr_LINREG_Infenion_Addr_Verify	(unsigned p, unsigned nline, unsigned addr, unsigned char *Lo, unsigned char *Hi)
{

	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;


	msg[0] = 0xD4;
	msg[1] = 0xB2;
	msg[2] = addr;
	msg[3] = 0x7E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xC4;
	msg[1] = 0xB0;
	msg[2] = 0x81;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	f_delay_ms(1);

	msg[0] = 0xF4;
	msg[1] = 0x33;
	msg[2] = 0x00;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	{	
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
		WndDisplay_TestLinMsg(nline, linBuf);
//***** JUDGE**********************************************************************************************************
		if (0x33 != linBuf.Data[0] )  return -1;
		if (0x06 != linBuf.Data[2] )  return -1;
	
		*Lo = linBuf.Data[1];
		
	}
	

	msg[0] = 0xC4;
	msg[1] = 0x34;
	msg[2] = 0x00;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	{
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
		WndDisplay_TestLinMsg(nline+1, linBuf);
//***** JUDGE**********************************************************************************************************
		if (0x34 != linBuf.Data[0] )  return -1;
		if (0x06 != linBuf.Data[2] )  return -1;
	
		*Hi = linBuf.Data[1];
	}


	msg[0] = 0xD4;
	msg[1] = 0x31;
	msg[2] = 0x00;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	{
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
		WndDisplay_TestLinMsg(nline+2, linBuf);
//***** JUDGE**********************************************************************************************************		
		if (0x31 != linBuf.Data[0] )  return 1;
		if (0x06 != linBuf.Data[2] )  return 1;
	
		if (0x01 == ( linBuf.Data[1] & 0x40) ) return -1;
		if (0x01 == ( linBuf.Data[1] & 0x80) ) return -1;
	}

	return 0;
}

int CTest_Main::f_kvr_LINREG_Infenion_Addr_Program_and_Verify	(unsigned p, unsigned addr, unsigned char W_HI, unsigned char W_LO, unsigned char &R_HI, unsigned char &R_LO)
{

	KVR_LIN_STRUCT linBuf;

	unsigned char	msg[4] = {0};
	unsigned int	length = 4;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;

	msg[0] = 0xD4;
	msg[1] = 0xB2;
	msg[2] = addr;
	msg[3] = 0x7E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xF4;
	msg[1] = 0xB3;
	msg[2] = W_LO;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xC4;
	msg[1] = 0xB4;
	msg[2] = W_HI;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xD4;
	msg[1] = 0xB5;
	msg[2] = 0x00;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xC4;
	msg[1] = 0xB0;
	msg[2] = 0x8C;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);

	msg[0] = 0xF4;
	msg[1] = 0x3F;
	msg[2] = 0x00;
	msg[3] = 0x7E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);


	bool bPRG_bSuccess = false;

	for (unsigned i=0; i<10; i++)
	{
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
															
		if (0x3F != linBuf.Data[0] ) 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Data[0] not Equal 0x3F", false);		
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Fail", true);	
			return -1;
		}

		if (0x06 != linBuf.Data[2] ) 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Data[2] not Equal 0x06", false);		
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Fail", true);	
			return -1;
		}
		
		if (0x00 == (linBuf.Data[1] & 0x0F) ) 
		{
			bPRG_bSuccess = true;
//			m_userMsg.f_LIN_LView_Insert_Msg ("Success", false);
			break;			
		}

		if (0x01 == (linBuf.Data[1] & 0x01) )		//BIT B0
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Wait Program Finish", false);
//			m_userMsg.f_LIN_LView_Insert_Msg ("retry read step", false);
			continue; 			
		}

		if (K3 == (linBuf.Data[1] & K3) )		//BIT B3-> Voltage To Low 
		{
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program Voltage to LOW", false);
//			m_userMsg.f_LIN_LView_Insert_Msg ("Program FAIL       ",     true);	
//			m_userMsg.f_LIN_LView_Insert_Msg ("Check POWER Supply ",    true);
			return -1;			
		}

	}

	if (true != bPRG_bSuccess)
	{
//		m_userMsg.f_LIN_LView_Insert_Msg ("Program Not Finished",    false);
//		m_userMsg.f_LIN_LView_Insert_Msg ("Program FAIL       ",     true );	
		return -1;
	}

	msg[0] = 0xC4;
	msg[1] = 0xB0;
	msg[2] = 0x81;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	f_delay_ms(1);

	msg[0] = 0xF4;
	msg[1] = 0x33;
	msg[2] = 0x00;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	{
		this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
		if (0x33 != linBuf.Data[0] )  return -1;
		if (0x06 != linBuf.Data[2] )  return -1;
	
		R_LO = linBuf.Data[1]; 
	}
	

	msg[0] = 0xC4;
	msg[1] = 0x34;
	msg[2] = 0x00;
	msg[3] = 0x6E;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
	{																		//Judge
		if (0x34 != linBuf.Data[0] )  return -1;
		if (0x06 != linBuf.Data[2] )  return -1;
	
		R_HI = linBuf.Data[1]; 
	}


	msg[0] = 0xD4;
	msg[1] = 0x31;
	msg[2] = 0x00;
	msg[3] = 0x66;
	this->m_pLin->SendRX_and_Read(pLin->Fid.nRx, msg, length, linBuf, 100);
	this->m_pLin->SendTX_and_Read(pLin->Fid.nTx3, linBuf, 100);
	{																		//Judge
		if (0x31 != linBuf.Data[0] )  return -1;
		if (0x06 != linBuf.Data[2] )  return -1;
	
		if (0x01 == ( linBuf.Data[1] & 0x40) ) return -1;
		if (0x01 == ( linBuf.Data[1] & 0x80) ) return -1;
	}

	return 0;
}



int CTest_Main::f_kvr_LINREG_Infenion_Verify	(unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

//	for (unsigned idx = 1; idx<4; idx++)
//	{
//		this->m_pCSpec->m_vTitem[idx].Spec.isTest = true;
//		this->m_pCSpec->m_vTitem[idx].Spec.nRefTitem = m_pCSpec->m_stMode.stRefTitem.ID_0000_NC;
//	}

	int iRtn = 0;

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_CLIN_DATA_UNION_NVM uNVM;

	uNVM.u8.Data10_L = 0;
	uNVM.u8.Data11_H = 0;
	uNVM.u8.Data20_L = 0;
	uNVM.u8.Data21_H = 0;
	uNVM.u8.Data30_L = 0;
	uNVM.u8.Data31_H = 0;
	uNVM.u8.Data40_L = 0;
	uNVM.u8.Data41_H = 0;
	uNVM.u8.Data50_L = 0;


	TU_UINT16	judValue;

	TS_CSPEC_TITEM_SPEC_GROUPITEM *pGR;
	pGR = &m_pTitem->Spec.stGroup;

	unsigned pnum_NVM_R1	= p + pGR->nItem_IdxNo[0];
	unsigned pnum_NVM_R2	= p + pGR->nItem_IdxNo[1];
	unsigned pnum_NVM_R3	= p + pGR->nItem_IdxNo[2];
	unsigned pnum_NVM_R4	= p + pGR->nItem_IdxNo[3];
	unsigned pnum_LOCKBIT	= p + pGR->nItem_IdxNo[4];


	{
/*		double temp;

		this->m_pVsrc->f_set_volt(18, 100);
		this->m_pVsrc->f_set_curr(0.5, 100);
		this->m_pVsrc->f_outp_on(100);

		temp = this->m_pVsrc->f_meas_vout(100);
		if(temp > 18.3)
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
			return TEST_STOP_FAIL;
		}*/
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	iRtn = this->f_kvr_LINREG_Infenion_Init_VERIFY_MODE (p);

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Verify(p, 2, 0x00, &uNVM.u8.Data10_L, &uNVM.u8.Data11_H);
		judValue.byte.b0 = uNVM.u8.Data10_L;
		judValue.byte.b1 = uNVM.u8.Data11_H;

		m_nRtn = f_testdata_judge_uint (0, p,       judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;	
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Verify(p, 5, 0x01, &uNVM.u8.Data20_L, &uNVM.u8.Data21_H);
		judValue.byte.b0 = uNVM.u8.Data20_L;
		judValue.byte.b1 = uNVM.u8.Data21_H;

		m_nRtn = f_testdata_judge_uint (0, p+1,       judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Verify(p, 8, 0x02, &uNVM.u8.Data30_L, &uNVM.u8.Data31_H);
		judValue.byte.b0 = uNVM.u8.Data30_L;
		judValue.byte.b1 = uNVM.u8.Data31_H;

		m_nRtn = f_testdata_judge_uint (0, p+2,       judValue.uint16  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Verify(p, 11, 0x03, &uNVM.u8.Data40_L, &uNVM.u8.Data41_H);
		judValue.byte.b0 = uNVM.u8.Data40_L;
		judValue.byte.b1 = uNVM.u8.Data41_H;

		m_nRtn = f_testdata_judge_uint (0, p+3,       judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	if (1 == pGR->uTestYN.bit.b04)
	{
		m_nRtn = f_testdata_judge_uint (0, pnum_LOCKBIT,  uNVM.u8.Data41_H & 0x80);
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	this->f_kvr_LINREG_Infenion_Finish(p);

	return TEST_CONTINUE;
}

int CTest_Main::f_kvr_LINREG_Infenion_Program_and_Verify (unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

//	if (true != m_pTitem->Spec.isTest) return TEST_CONTINUE;

//	for (unsigned idx = 1; idx<4; idx++)
//	{
//		this->m_pCSpec->m_vTitem[idx].Spec.isTest = true;
//		this->m_pCSpec->m_vTitem[idx].Spec.nRefTitem = m_pCSpec->m_stMode.stRefTitem.ID_0000_NC;
//	}

	int iRtn = 0;

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_CLIN_DATA_UNION_NVM uNVM;

	uNVM.u8.Data10_L = 0;
	uNVM.u8.Data11_H = 0;
	uNVM.u8.Data20_L = 0;
	uNVM.u8.Data21_H = 0;
	uNVM.u8.Data30_L = 0;
	uNVM.u8.Data31_H = 0;
	uNVM.u8.Data40_L = 0;
	uNVM.u8.Data41_H = 0;
	uNVM.u8.Data50_L = 0;


	TU_UINT16	judValue;

	TS_CSPEC_TITEM_SPEC_GROUPITEM *pGR;
	pGR = &m_pTitem->Spec.stGroup;

	unsigned pnum_NVM_R1	= p + pGR->nItem_IdxNo[0];
	unsigned pnum_NVM_R2	= p + pGR->nItem_IdxNo[1];
	unsigned pnum_NVM_R3	= p + pGR->nItem_IdxNo[2];
	unsigned pnum_NVM_R4	= p + pGR->nItem_IdxNo[3];

	unsigned pnum_LOCKBIT	= p + pGR->nItem_IdxNo[4];



	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	iRtn = this->f_kvr_LINREG_Infenion_Init_PROGRAM_MODE ( p );

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Program_and_Verify (p, 0x00, pNVM->Addr01, pNVM->Addr00, uNVM.u8.Data11_H, uNVM.u8.Data10_L);

		judValue.byte.b0 = uNVM.u8.Data10_L;
		judValue.byte.b1 = uNVM.u8.Data11_H;

		m_nRtn = f_testdata_judge_uint (0, p, judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;	
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Program_and_Verify (p+1, 0x01, pNVM->Addr03, pNVM->Addr02, uNVM.u8.Data21_H, uNVM.u8.Data20_L);

		judValue.byte.b0 = uNVM.u8.Data20_L;
		judValue.byte.b1 = uNVM.u8.Data21_H;

		m_nRtn = f_testdata_judge_uint (0, p+1, judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Program_and_Verify (p+2, 0x02, pNVM->Addr05, pNVM->Addr04, uNVM.u8.Data31_H, uNVM.u8.Data30_L);

		judValue.byte.b0 = uNVM.u8.Data30_L;
		judValue.byte.b1 = uNVM.u8.Data31_H;

		m_nRtn = f_testdata_judge_uint (0, p+2, judValue.uint16  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	{
		iRtn = this->f_kvr_LINREG_Infenion_Addr_Program_and_Verify (p+3, 0x03, pNVM->Addr07 & 0x7F, pNVM->Addr06, uNVM.u8.Data41_H, uNVM.u8.Data40_L);

		judValue.byte.b0 = uNVM.u8.Data40_L;
		judValue.byte.b1 = uNVM.u8.Data41_H;

		m_nRtn = f_testdata_judge_uint (0, p+3, judValue.uint16 );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;

		if ( -1 == iRtn) 
		{
			this->m_pCTestData->m_testData.Var.bPass = false;
		} 
	}

	if (1 == pGR->uTestYN.bit.b04)
	{
		m_nRtn = f_testdata_judge_uint (0, pnum_LOCKBIT, uNVM.u8.Data41_H & 0x80);
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	this->f_kvr_LINREG_Infenion_Finish(p);

	return TEST_CONTINUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  L9916 Function
int CTest_Main::f_kvr_LINREG_L9916_Verify (unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

	int iRtn = 0;

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;	
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_UINT8	judValue;

	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	// Write할 데이터 보내기 : #rdata XX XX XX XX XX XX\r
	{
		CString sMessage, temp;
		char	*pCh;
		char	buff[100] = {0, };

		sprintf_s(buff, "%02x %02x %02x %02x %02x %02x", pNVM->Addr00, pNVM->Addr01, pNVM->Addr02, pNVM->Addr03, pNVM->Addr04, pNVM->Addr05);

		sMessage.Format("#rdata %s", buff);

		pCh = LPSTR(LPCTSTR(sMessage));
//		temp = this->m_pFrdm->f_cmd_and_read_cstring (pCh);
	}

	CString sMessage, temp;
	CString Addr00, Addr01, Addr02, Addr03, Addr04, Addr05;

	char	*pCh;
	char	buff[1];
	buff[0] = 0x0D;

	sMessage.Format("#veri");

	pCh = LPSTR(LPCTSTR(sMessage));
//	temp = this->m_pFrdm->f_cmd_and_read_cstring (pCh);


	AfxExtractSubString(Addr00, temp, 0, ',');
	AfxExtractSubString(Addr01, temp, 1, ',');
	AfxExtractSubString(Addr02, temp, 2, ',');
	AfxExtractSubString(Addr03, temp, 3, ',');
	AfxExtractSubString(Addr04, temp, 4, ',');
	AfxExtractSubString(Addr05, temp, 5, ',');
	
	// Addr 00
	{
		judValue.byte = f_hex_conv_to_int(Addr00);
		m_nRtn = f_testdata_judge_uint (0, p, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 01
	{
		judValue.byte = f_hex_conv_to_int(Addr01);
		m_nRtn = f_testdata_judge_uint (0, p+1, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 02
	{
		judValue.byte = f_hex_conv_to_int(Addr02);
		m_nRtn = f_testdata_judge_uint (0, p+2, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 03
	{
		judValue.byte = f_hex_conv_to_int(Addr03);
		m_nRtn = f_testdata_judge_uint (0, p+3, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 04
	{
		judValue.byte = f_hex_conv_to_int(Addr04);
		m_nRtn = f_testdata_judge_uint (0, p+4, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 05
	{
		judValue.byte = f_hex_conv_to_int(Addr05);
		m_nRtn = f_testdata_judge_uint (0, p+5, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	return TEST_CONTINUE;
}

int CTest_Main::f_kvr_LINREG_L9916_Program_and_Verify (unsigned p)
{
	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

	int iRtn = 0;

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;	
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_UINT8	judValue;

	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	// Write할 데이터 보내기 : #rdata XX XX XX XX XX XX\r
	{
		CString sMessage, temp;
		char	*pCh;
		char	buff[100] = {0, };

		sprintf_s(buff, "%02x %02x %02x %02x %02x %02x", pNVM->Addr00, pNVM->Addr01, pNVM->Addr02, pNVM->Addr03, pNVM->Addr04, pNVM->Addr05);

		sMessage.Format("#rdata %s", buff);

		pCh = LPSTR(LPCTSTR(sMessage));
//		temp = this->m_pFrdm->f_cmd_and_read_cstring (pCh);
	}

	// Write : #rburn\r
	CString sMessage, temp;
	CString Addr00, Addr01, Addr02, Addr03, Addr04, Addr05;

	char	*pCh;

	sMessage.Format("#pandv");

	pCh = LPSTR(LPCTSTR(sMessage));
//	temp = this->m_pFrdm->f_cmd_and_read_cstring (pCh);
	temp = temp.Mid(8);

	AfxExtractSubString(Addr00, temp, 0, ',');
	AfxExtractSubString(Addr01, temp, 1, ',');
	AfxExtractSubString(Addr02, temp, 2, ',');
	AfxExtractSubString(Addr03, temp, 3, ',');
	AfxExtractSubString(Addr04, temp, 4, ',');
	AfxExtractSubString(Addr05, temp, 5, ',');
	
	// Addr 00
	{
		judValue.byte = f_hex_conv_to_int(Addr00);
		m_nRtn = f_testdata_judge_uint (0, p, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 01
	{
		judValue.byte = f_hex_conv_to_int(Addr01);
		m_nRtn = f_testdata_judge_uint (0, p+1, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 02
	{
		judValue.byte = f_hex_conv_to_int(Addr02);
		m_nRtn = f_testdata_judge_uint (0, p+2, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 03
	{
		judValue.byte = f_hex_conv_to_int(Addr03);
		m_nRtn = f_testdata_judge_uint (0, p+3, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 04
	{
		judValue.byte = f_hex_conv_to_int(Addr04);
		m_nRtn = f_testdata_judge_uint (0, p+4, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	// Addr 05
	{
		judValue.byte = f_hex_conv_to_int(Addr05);
		m_nRtn = f_testdata_judge_uint (0, p+5, judValue.byte  );
		if (m_nRtn != TEST_CONTINUE) return m_nRtn;
	}

	return TEST_CONTINUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  LIN2112 Function
void CTest_Main::f_kvr_LINREG_LIN2112_TxMessage(unsigned p, unsigned nline, 
												unsigned char rsid, 
												unsigned char data1, 
												unsigned char data2, 
												unsigned char data3, 
												unsigned char data4, 
												unsigned char data5)
{
	unsigned char msg[8] = {0, };
	KVR_LIN_STRUCT linbuf;


	msg[0] = 0xC6;
	msg[1] = 0x06;
	msg[2] = rsid;
	msg[3] = data1;
	msg[4] = data2;
	msg[5] = data3;
	msg[6] = data4;
	msg[7] = data5;
	this->m_pLin->SendRX_and_Read(0x3C, msg, sizeof(msg), linbuf, 100);
	WndDisplay_TestLinMsg(nline, linbuf);

	return ;
}

int CTest_Main::f_kvr_LINREG_LIN2112_Program_and_Verify	(unsigned p)
{
	int iRtn  = 0;
	int nline = 0;
	unsigned char msg[8] = {0, };
	unsigned char key[3] = {0, };

	KVR_LIN_STRUCT linbuf;

	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

//	for (unsigned idx = 1; idx<3; idx++)
//	{
//		this->m_pCSpec->m_vTitem[idx].Spec.isTest = true;
//		this->m_pCSpec->m_vTitem[idx].Spec.nRefTitem = m_pCSpec->m_stMode.stRefTitem.ID_0000_NC;
//	}

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_LIN2112_DATA_UNION_NVM uNVM;

	uNVM.u8.offset0_5 = 0;
	uNVM.u8.offset0_6 = 0;
	uNVM.u8.offset0_7 = 0;
	uNVM.u8.offset0_8 = 0;

	uNVM.u8.offset1_5 = 0;
	uNVM.u8.offset1_6 = 0;
	uNVM.u8.offset1_7 = 0;
	uNVM.u8.offset1_8 = 0;

	uNVM.u8.offset2_5 = 0;
	uNVM.u8.offset2_6 = 0;
	uNVM.u8.offset2_7 = 0;
	uNVM.u8.offset2_8 = 0;

	TU_UINT32 judValue;

	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// Wake-Up LIN2112
	msg[0] = 0x90;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = 0xFF;
	msg[4] = 0xFF;
	msg[5] = 0xFF;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, sizeof(msg), linbuf, 10);
	WndDisplay_TestLinMsg(nline, linbuf);

	////////////////////////////////////////////////////////////////////////////////////
	// seed request 
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+1, 0xA0, 0x53, 0xCA, 0x88, 0x53, 0xCA);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  seed receive  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+2, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE0)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	key[0] = ~linbuf.Data[5];
	key[1] = ~linbuf.Data[4];
	key[2] = ~linbuf.Data[3];

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Enter TM
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+3, 0xA1, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check we are in TM
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+4, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE1)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to check MEM
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+5, 0xA2, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check if MEM locked
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+6, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE2)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	if (linbuf.Data[3] != 0x00)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to write MEM
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+7, 0xA4, key[0], key[1], key[2], 0xFF, 0xFF);
	
	////////////////////////////////////////////////////////////////////////////////////
	// M  :  write MEM data offset 0
	//                                                            byte5,        byte6,        byte7,        byte8
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+8, 0xA4, 0x00, pNVM->Addr00, pNVM->Addr01, pNVM->Addr02, pNVM->Addr03);

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  write MEM data offset 1
	//                                                            byte5,        byte6,        byte7,        byte8
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+9, 0xA4, 0x01, pNVM->Addr04, pNVM->Addr05, pNVM->Addr06, pNVM->Addr07);

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  write MEM data offset 2
	//                                                             byte5,        byte6,        byte7,        byte8
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+10, 0xA4, 0x02, pNVM->Addr08, pNVM->Addr09, pNVM->Addr10,         0x00);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check MEM status
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+11, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE4)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	if (linbuf.Data[3] != 0x03)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Start burning
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+12, 0xA5, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read if BURNING done and status
	nline = nline + 12;

	while(1)
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
		WndDisplay_TestLinMsg(nline+1, linbuf);
		f_delay_ms(100);

		if (linbuf.Data[3] == 0x03)
		{
			break;		// done
		}

		nline = nline + 1;
	} 
	
	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to read burned values	
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+5, 0xA6, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 0
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
		WndDisplay_TestLinMsg(nline+6, linbuf);
//		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x00)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = linbuf.Data[7];

		iRtn = f_testdata_judge_uint (0, p,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 1
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 100);
		WndDisplay_TestLinMsg(nline+7, linbuf);
//		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x01)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = 0x00;

		iRtn = f_testdata_judge_uint (0, p+1,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 2
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 100);
		WndDisplay_TestLinMsg(nline+8, linbuf);
//		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x02)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = 0x00;

		iRtn = f_testdata_judge_uint (0, p+2,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  EXIT BURNING  
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+9, 0xA1, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check we are still in TM  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 100);
	WndDisplay_TestLinMsg(nline+10, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE1)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	if (linbuf.Data[3] != 0x01)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to check MEM again
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+11, 0xA2, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check if MEM locked  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 100);
	WndDisplay_TestLinMsg(nline+12, linbuf);
//	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE2)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	if (linbuf.Data[3] != 0x01)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  EXIT TM 
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+13, 0xAB, key[0], key[1], key[2], 0xFF, 0xFF);

	return TEST_CONTINUE;
}

int CTest_Main::f_kvr_LINREG_LIN2112_Verify (unsigned p)
{
		int iRtn  = 0;
	int nline = 0;
	unsigned char msg[8] = {0, };
	unsigned char key[3] = {0, };

	KVR_LIN_STRUCT linbuf;

	this->m_pTitem = &this->m_pCSpec->m_vTitem[p];

//	for (unsigned idx = 1; idx<3; idx++)
//	{
//		this->m_pCSpec->m_vTitem[idx].Spec.isTest = true;
//		this->m_pCSpec->m_vTitem[idx].Spec.nRefTitem = m_pCSpec->m_stMode.stRefTitem.ID_0000_NC;
//	}

	TS_CSPEC_SPECINFO_LIN_NVM	*pNVM;
	pNVM = &this->m_pCSpec->m_stSpecInfo.Lin.Nvm;

	TU_LIN2112_DATA_UNION_NVM uNVM;

	uNVM.u8.offset0_5 = 0;
	uNVM.u8.offset0_6 = 0;
	uNVM.u8.offset0_7 = 0;
	uNVM.u8.offset0_8 = 0;

	uNVM.u8.offset1_5 = 0;
	uNVM.u8.offset1_6 = 0;
	uNVM.u8.offset1_7 = 0;
	uNVM.u8.offset1_8 = 0;

	uNVM.u8.offset2_5 = 0;
	uNVM.u8.offset2_6 = 0;
	uNVM.u8.offset2_7 = 0;
	uNVM.u8.offset2_8 = 0;

	TU_UINT32 judValue;

	{
		f_delay_ms(this->m_pCSpec->m_stSpecInfo.Lin.nWaitTime);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// Wake-Up LIN2112
	msg[0] = 0x90;
	msg[1] = 0xFF;
	msg[2] = 0xFF;
	msg[3] = 0xFF;
	msg[4] = 0xFF;
	msg[5] = 0xFF;
	msg[6] = 0xFF;
	msg[7] = 0xFF;
	this->m_pLin->SendRX_and_Read(0x3C, msg, sizeof(msg), linbuf, 10);
	WndDisplay_TestLinMsg(nline, linbuf);

	////////////////////////////////////////////////////////////////////////////////////
	// seed request 
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+1, 0xA0, 0x53, 0xCA, 0x88, 0x53, 0xCA);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  seed receive  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+2, linbuf);
	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE0)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	key[0] = ~linbuf.Data[5];
	key[1] = ~linbuf.Data[4];
	key[2] = ~linbuf.Data[3];

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Enter TM
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+3, 0xA1, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check we are in TM
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+4, linbuf);
	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE1)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to check MEM
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+5, 0xA2, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check if MEM locked
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+6, linbuf);
	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE2)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to read burned values	
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+5, 0xA6, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 0
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
		WndDisplay_TestLinMsg(nline+6, linbuf);
		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x00)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = linbuf.Data[7];

		iRtn = f_testdata_judge_uint (0, p,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 1
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
		WndDisplay_TestLinMsg(nline+7, linbuf);
		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x01)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = 0x00;

		iRtn = f_testdata_judge_uint (0, p+1,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  read MEM offset 2
	{
		this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
		WndDisplay_TestLinMsg(nline+8, linbuf);
		f_delay_ms(1);

		if (linbuf.Data[2] != 0xE6)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		if (linbuf.Data[3] != 0x02)
		{
			iRtn = -1;
			this->m_pCTestData->m_testData.Var.bPass = false;
			if (iRtn != TEST_CONTINUE) return iRtn;
		}

		judValue.byte.b0 = linbuf.Data[4];
		judValue.byte.b1 = linbuf.Data[5];
		judValue.byte.b2 = linbuf.Data[6];
		judValue.byte.b3 = 0x00;

		iRtn = f_testdata_judge_uint (0, p+2,  judValue.uint32 );
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  EXIT BURNING  
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+9, 0xA1, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check we are still in TM  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+10, linbuf);
	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE1)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	if (linbuf.Data[3] != 0x01)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  Go to check MEM again
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+11, 0xA2, key[0], key[1], key[2], 0xFF, 0xFF);

	////////////////////////////////////////////////////////////////////////////////////
	// S  :  Check if MEM locked  
	this->m_pLin->SendTX_and_Read(0x3D, linbuf, 10);
	WndDisplay_TestLinMsg(nline+12, linbuf);
	f_delay_ms(1);

	if (linbuf.Data[2] != 0xE2)
	{
		iRtn = -1;
		this->m_pCTestData->m_testData.Var.bPass = false;
		if (iRtn != TEST_CONTINUE) return iRtn;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// M  :  EXIT TM 
	f_kvr_LINREG_LIN2112_TxMessage(0, nline+13, 0xAB, key[0], key[1], key[2], 0xFF, 0xFF);

	return TEST_CONTINUE;
}
