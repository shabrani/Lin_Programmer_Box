#include "stdafx.h"
#include "CFunc_TestData.h"


CFunc_TestData::CFunc_TestData(void)
{
	this->m_const.nArray = 0;
	this->m_const.nTitem  = 0;
}


CFunc_TestData::~CFunc_TestData(void)
{
}


void CFunc_TestData::f_create_data_vector ( unsigned nTitem, unsigned nAr)
{
	int DBG_nSize = 0;

	if ( (nAr == 0) || (0 == nTitem ) )
	{
		return;
	}

	m_const.nArray = nAr;
	m_const.nTitem = nTitem;
		
	this->m_testData.vData.clear();							// this->m_testData.vData.empty() -> vData.clear() 
	this->m_saveData.vData.clear();
	

	vector <ST_CFUNCDATA_ITEMDATA>	vBuf;
	vBuf.resize(nTitem);

	for (unsigned t=0; t<nAr; ++t)
	{
		this->m_testData.vData.push_back(vBuf);
		this->m_saveData.vData.push_back(vBuf);
	}


	f_clear_CTestData_FailCount ();

}

void CFunc_TestData::f_copy_CTestData_to_Class (CFunc_TestData *pCTestData)
{
	//if (this->m_const.nArray == 0 ) return;	//data가 없음
	if ( (0 == m_const.nArray) || (0 == m_const.nTitem) )
	{
		//warning message
		return;
	}

	if ( (m_const.nArray != pCTestData->m_const.nArray) || (m_const.nTitem != pCTestData->m_const.nTitem))
	{
		pCTestData->f_create_data_vector( this->m_const.nTitem, this->m_const.nArray);
	}

	{
		pCTestData->m_testData.Var.nDnum		= this->m_testData.Var.nDnum;
		pCTestData->m_testData.Var.bPass		= this->m_testData.Var.bPass;			// $ 2014.05.11 DEL for .for Critial Bug Fix

		pCTestData->m_testData.Var.bTested		= this->m_testData.Var.bTested;
		pCTestData->m_testData.Var.sSerialNo	= this->m_testData.Var.sSerialNo;
		pCTestData->m_testData.Var.nJig			= this->m_testData.Var.nJig;			// $ Add 2013-0911

		pCTestData->m_testData.Var.nBin			= this->m_testData.Var.nBin;
		pCTestData->m_testData.Var.nFailFirst	= this->m_testData.Var.nFailFirst;

		pCTestData->m_testData.Var.st1stFail.nPnum			= this->m_testData.Var.st1stFail.nPnum;				// $ Add 2015-03-05 sjkim
		pCTestData->m_testData.Var.st1stFail.nTnum			= this->m_testData.Var.st1stFail.nTnum;				// $ Add 2015-03-05 sjkim
		pCTestData->m_testData.Var.st1stFail.nPnum_prev		= this->m_testData.Var.st1stFail.nPnum_prev;		// $ Add 2015-03-05 sjkim
		pCTestData->m_testData.Var.st1stFail.nTnum_prev		= this->m_testData.Var.st1stFail.nTnum_prev;		// $ Add 2015-03-05 sjkim

		pCTestData->m_testData.Var.fElapsedtime				= this->m_testData.Var.fElapsedtime;				// $ Add 2015-03-05 sjkim
		pCTestData->m_testData.Var.nRetestCount				= this->m_testData.Var.nRetestCount;				// $ Add 2015-03-05 sjkim
	}



	for (unsigned t=0;t<m_const.nTitem; t++)
	{
		for (unsigned ar=0; ar<m_const.nArray; ar++)
		{
			pCTestData->m_testData.vData[ar][t].varData		= this->m_testData.vData[ar][t].varData;

			pCTestData->m_testData.vData[ar][t].bPass		= this->m_testData.vData[ar][t].bPass;
			pCTestData->m_testData.vData[ar][t].bTested		= this->m_testData.vData[ar][t].bTested;

			pCTestData->m_testData.vData[ar][t].strData		= this->m_testData.vData[ar][t].strData;
		}
	}
}



void CFunc_TestData::f_reset_CTestData_for_Test_Ready (unsigned nTestCh, unsigned nDnum)
{
	////////////// data가 없음 //////////////////
	if ( (0 == m_const.nArray) || (0 == m_const.nTitem) )
	{
		//warning message
		return;
	}

	this->m_testData.Var.bPass		= true;
	this->m_testData.Var.bTested	= false;

	this->m_testData.Var.nBin		= 0;
	this->m_testData.Var.nFailFirst	= 0;

	this->m_testData.Var.st1stFail.nPnum		= 0;	// Add $ 2015-03-03 sjkim
	this->m_testData.Var.st1stFail.nTnum		= 0;	// Add $ 2015-03-03 sjkim
	this->m_testData.Var.st1stFail.nPnum_prev	= 0;	// Add $ 2015-03-03 sjkim
	this->m_testData.Var.st1stFail.nTnum_prev	= 0;	// Add $ 2015-03-03 sjkim
	this->m_testData.Var.fElapsedtime           = 0;	// Add $ 2015-03-03 sjkim
	this->m_testData.Var.nRetestCount           = 0;	// Add $ 2015-03-03 sjkim

	this->m_testData.Var.nDnum		= nDnum;
//	this->m_testData.Var.nJig		= nTestCh;


	for (unsigned t=0;t<m_const.nTitem; t++)
	{
		for (unsigned ar=0; ar<m_const.nArray; ar++)
		{
			this->m_testData.vData[ar][t].varData.ulVal	= 0;			// Add 2013.11.10
			this->m_testData.vData[ar][t].varData.dblVal= 0;			// Add 2013.11.10
			this->m_testData.vData[ar][t].bPass			= false;
			this->m_testData.vData[ar][t].bTested		= false;
			this->m_testData.vData[ar][t].strData		= "";
		}
	}

}

void CFunc_TestData::f_data_clear (TS_CTESTDATA_DEVICEDATA *pData)
{
	pData->Var.bPass		= 0;
	pData->Var.bTested		= 0;
	pData->Var.nBin			= 0;
	pData->Var.nDnum		= 0;
	pData->Var.nFailFirst	= 0;

	pData->Var.st1stFail.nPnum		= 0;	// $ Add 2015-03-05 
	pData->Var.st1stFail.nTnum		= 0;	// $ Add 2015-03-05 
	pData->Var.st1stFail.nPnum_prev	= 0;	// $ Add 2015-03-05 
	pData->Var.st1stFail.nTnum_prev	= 0;	// $ Add 2015-03-05 
	pData->Var.nRetestCount			= 0;	// $ Add 2015-03-05 
	pData->Var.fElapsedtime			= 0;	// $ Add 2015-03-05 

	pData->Var.nJig			= 0;
	pData->Var.sSerialNo	= "";

	for (unsigned t=0; t<m_const.nTitem; t++)
	{
		for (unsigned ar=0; ar<m_const.nArray; ar++)
		{
				pData->vData[ar][t].nFailCount = 0;
		}
	}

}

void CFunc_TestData::f_data_copy  (TS_CTESTDATA_DEVICEDATA *pSrc, TS_CTESTDATA_DEVICEDATA *pDest)
{
	*pDest = *pSrc;
}



void CFunc_TestData::f_clear_CTestData_FailCount ()
{
	//data가 없음
	if (0 == m_const.nTitem )
	{
		return;
	}

	for (unsigned t=0; t<m_const.nTitem; t++)
	{
		for (unsigned ar=0; ar<m_const.nArray; ar++)
		{
				this->m_testData.vData[ar][t].nFailCount = 0;
		}
	}
}

