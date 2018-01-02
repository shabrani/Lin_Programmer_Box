#include "stdafx.h"
#include "CTest_Status_Test_Result.h"
#include "CTest_System_Config.h"


CTest_Status_Test_Result::CTest_Status_Test_Result(void)
{
	m_nChannelCount = 1;

	this->f_clear_Qty_Acc();
	this->f_clear_Qty_Curr();
	this->f_Result_Reset_for_Test ();
}


CTest_Status_Test_Result::~CTest_Status_Test_Result(void)
{
}



void CTest_Status_Test_Result::f_clear_Qty_Acc  ()
{
	this->m_Qty.Acc.nPass = 0;
	this->m_Qty.Acc.nFail = 0;
}

void CTest_Status_Test_Result::f_clear_Qty_Curr ()
{
	this->m_Qty.Curr.nPass = 0;
	this->m_Qty.Curr.nFail = 0;
}

void CTest_Status_Test_Result::f_Result_Reset_for_Test ()
{
	this->m_Result.pCh				= &this->m_Result.CH;

	this->m_Result.pCh->nDnum		= 0;
	this->m_Result.pCh->isTested		= false;		
	this->m_Result.pCh->isPass		= true;		//합격이라고 가정한다.
	this->m_Result.pCh->isStop		= false;	
	this->m_Result.pCh->nJig			= 0;

	this->m_Result.pCh->nFail_add	= 0;
	this->m_Result.pCh->nPass_add	= 0;	

}

bool CTest_Status_Test_Result::f_check_All_CH_Pass ()
{
	//업체별로 판단하는 기준이 달라야 한다.

	//if (this->m_nChannelCount != 2)
	//{
	//	this->m_Result.bAllPass = this->m_Result.CH[0].isPass;
	//	return m_Result.bAllPass;
	//}

	this->m_Result.bAllPass = false;

	if (this->m_Result.CH.isTested)
	{
		if (true == this->m_Result.CH.isPass) 
		{
			this->m_Result.bAllPass = true;
			return true;
		}
		else
			return false;
	}
	
	return false;
}

void CTest_Status_Test_Result::f_adjust_retest_qty (unsigned nCh, unsigned &nDnum_Prev)
{
	this->m_Qty.Acc.nFail -= this->m_Prev.CH.nFail_add;

	this->m_Qty.Curr.nPass -= this->m_Prev.CH.nPass_add;

	nDnum_Prev = this->m_Prev.CH.nDnum;
}
