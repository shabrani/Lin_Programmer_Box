#include "stdafx.h"
#include "procedure_Macro.h"

#include "CTest_Main.h"


CTest_Main::CTest_Main(void)
{
}


CTest_Main::~CTest_Main(void)
{
}


int CTest_Main::f_test_procedure (void)
{
	int iRtn;


	iRtn = this->f_test_start_process ();


	if (iRtn == TEST_CONTINUE)
	{
		iRtn = this->f_test_main_process ();
	}
	else
	{
		m_cState.Result.m_Result.pCh->isPass   = false;
		m_cState.Result.m_Result.pCh->isTested = false;
		m_cState.Result.m_Result.pCh->isStop   = true;
	}


	this->f_test_end_process ();

	return iRtn;
}

int CTest_Main::f_test_start_process ()
{
	CString temp;
	char	buff[10] = {0, };
	bool	bRtn = false;


	////////////////////////////////////////////////////////////////////
	//	LIN Module Open
	TS_CSPEC_SPECINFO_LIN	*pInfo;
	pInfo = &this->m_pCSpec->m_stSpecInfo.Lin;

	bRtn = this->m_pLin->f_KVR_Configuration (0, pInfo->nBaudrate, pInfo->nChip);
	if (false == bRtn)
	{
		AfxMessageBox("Fail LIN Initialize! Test Stop");

		return TEST_STOP_USER;
	}

	this->m_cUserMsg.f_LIN_LView_SendTimer_On (false, 0);

	return TEST_CONTINUE;
}

int CTest_Main::f_test_main_process	()
{
	unsigned nRtn;


	
	m_nTitem = m_pCSpec->m_vTitem.size();


	for (unsigned p=0; p < this->m_nTitem; p++)
	{
		m_pnum = p;
		m_pTitem = &this->m_pCSpec->m_vTitem[p];
	
		// Check TestStopEnable ////////////////////////////////////////////////////////////////////////////////
		if (true == this->m_cState.Status.bTestStopEnable) return TEST_STOP_USER;

		// Check isTest ////////////////////////////////////////////////////////////////////////////////////////
//		if (false == m_pTitem->Spec.isTest) continue;									

		if( m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.ID_0000_NC) continue;

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nCOMM_Meas_Voltage)
		{
			nRtn = this->f_COMM_Meas_Voltage (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_CR665_Program_and_Verify)
		{
			nRtn = this->f_kvr_LINREG_CR665_Program_and_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_CR665_Verify)
		{
			nRtn = this->f_kvr_LINREG_CR665_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_TLE8880_Program_and_Verify)
		{
			nRtn = this->f_kvr_LINREG_Infenion_Program_and_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_TLE8880_Verify)
		{
			nRtn = this->f_kvr_LINREG_Infenion_Verify	(p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_TLE8881_Program_and_Verify)
		{
			nRtn = this->f_kvr_LINREG_Infenion_Program_and_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_TLE8881_Verify)
		{
			nRtn = this->f_kvr_LINREG_Infenion_Verify	(p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_L9916_Program_and_Verify)
		{
			nRtn = this->f_kvr_LINREG_L9916_Program_and_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_L9916_Verify)
		{
			nRtn = this->f_kvr_LINREG_L9916_Verify	(p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_LIN2112_Program_and_Verify)
		{
			nRtn = this->f_kvr_LINREG_LIN2112_Program_and_Verify (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

		if (m_pTitem->Spec.nRefTitem == m_pCSpec->m_stMode.stRefTitem.nLINREG_LIN2112_Verify)
		{
			nRtn = this->f_kvr_LINREG_LIN2112_Verify	 (p);

			if (nRtn != TEST_CONTINUE) return nRtn;		
			continue;
		}

	}

	return TEST_CONTINUE;
}

int CTest_Main::f_test_end_process ()
{
	bool bRtn;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	LIN Module Close
	bRtn = this->m_pLin->f_KVR_Close();
	if (false == bRtn)
	{
		AfxMessageBox("Fail : LIN Close");
	}

	return TEST_CONTINUE;
}

int CTest_Main::f_titem_RefTitemAll (unsigned nSetRetestNumber, unsigned nRefTitem)
{
	int nResult;

	for(unsigned nP =0; nP < m_nTitem;	nP++)
	{
		m_pnum = nP;
		m_pTitem = &this->m_pCSpec->m_vTitem[ nP ];
		
		if (true == m_cState.Status.bTestStopEnable) return TEST_STOP_USER;		// $ Add by sjkim 2012-06-21 -> Move this Function

		if ( (m_pCSpec->m_vTitem[nP].Spec.nRefTitem  == nRefTitem) && m_pCSpec->m_vTitem[nP].Spec.Option.isTest)
		{
			nResult = f_titem (nP);
			if(TEST_CONTINUE != nResult ) return nResult;
		}
	}

	return TEST_CONTINUE;
}

int CTest_Main::f_titem   (unsigned p)
{
	int nResult = 0;
	
	m_pnum = p;
	
	if (false == m_pCSpec->m_vTitem[p].Spec.Option.isTest) return 0;

	//Retest Control Module
	this->m_FAIL_Retest.bEnable = false;
	
	this->m_FAIL_Retest.nRetestCount = 2;


	do
	{
		this->m_FAIL_Retest.nRetestCount--;


		nResult = (this->*m_pFunc_titem)(p);	
		

		if (nResult != TEST_STOP_FAIL_RETEST) break;


	} while (this->m_FAIL_Retest.nRetestCount);


	if(TEST_CONTINUE != nResult ) return nResult;


	return TEST_CONTINUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  titem Function
int CTest_Main::f_COMM_Meas_Voltage (unsigned p)
{
	double meas_data = 0;

#ifdef LIN_PROGRAM

	
	this->m_pVsrc->f_set_volt(this->m_pCSpec->m_stSpecInfo.Lin.fVoltage, 100);
	this->m_pVsrc->f_set_curr(this->m_pCSpec->m_stSpecInfo.Lin.fCurrent, 100);
	this->m_pVsrc->f_outp_on(100);

	meas_data = this->m_pVsrc->f_meas_vout(100);
	m_nRtn = f_testdata_judge_dbl(0, p, meas_data);
	if (m_nRtn != TEST_CONTINUE) return m_nRtn;
#endif // LIN_PROGRAM

	return 0;
}

int CTest_Main::f_COMM_Meas_Current (unsigned p)
{
	double meas_data = 0;

#ifdef LIN_PROGRAM
	meas_data = this->m_pVsrc->f_meas_iout(100);
	m_nRtn = f_testdata_judge_dbl(0, p, meas_data);
	if (m_nRtn != TEST_CONTINUE) return m_nRtn;
#endif // LIN_PROGRAM

#ifdef LIN_PROGRAM_BOX
#endif // LIN_PROGRAM_BOX

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Function
bool CTest_Main::f_testdata_check_pass (unsigned pnum, CFunc_Spec_Item_Main *pSpec, unsigned nData)
{

	switch(pSpec->stLimit.nMode)
	{

	case ENUM_CSPEC_LIMIT_MODE::M1_UPPER_LIMIT	:
		if (nData > (unsigned)pSpec->stLimit.HSL_VAR.ulVal) return false;
		return true;
		
	case ENUM_CSPEC_LIMIT_MODE::M2_LOWER_LIMIT	:
		if (nData < (unsigned)pSpec->stLimit.LSL_VAR.ulVal) return false;
		return true;

	case ENUM_CSPEC_LIMIT_MODE::M3_EQUAL		:
		if (nData != (unsigned)pSpec->stLimit.LSL_VAR.ulVal) return false;
		return true;

	case ENUM_CSPEC_LIMIT_MODE::M4_NOT_EQUAL	:
		if (nData == (unsigned)pSpec->stLimit.LSL_VAR.ulVal) return false;
		return true;

	default:
		if (nData > (unsigned)pSpec->stLimit.HSL_VAR.ulVal) return false;
		if (nData < (unsigned)pSpec->stLimit.LSL_VAR.ulVal) return false;
		return true;
	}

	return false;
}

bool CTest_Main::f_testdata_check_pass (unsigned pnum, CFunc_Spec_Item_Main *pSpec, double   fData)
{

	switch(m_pTitem->Spec.stLimit.nMode)
	{

	case ENUM_CSPEC_LIMIT_MODE::M1_UPPER_LIMIT	:
		if (fData > pSpec->stLimit.HSL_VAR.dblVal) return false;
		return true;
		
	case ENUM_CSPEC_LIMIT_MODE::M2_LOWER_LIMIT	:
		if (fData < pSpec->stLimit.LSL_VAR.dblVal) return false;
		return true;

	case ENUM_CSPEC_LIMIT_MODE::M3_EQUAL		:
		if (fData != pSpec->stLimit.LSL_VAR.dblVal) return false;
		return true;

	case ENUM_CSPEC_LIMIT_MODE::M4_NOT_EQUAL	:
		if (fData == pSpec->stLimit.LSL_VAR.dblVal) return false;
		return true;

	default:
		if (fData > pSpec->stLimit.HSL_VAR.dblVal) return false;
		if (fData < pSpec->stLimit.LSL_VAR.dblVal) return false;
		return true;
	}


	return false;
}

bool CTest_Main::f_check_read_status (unsigned pnum, unsigned nData)
{
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_pCSpec->m_stSpecInfo.Lin;

	if(SELECT_CR665 == pLin->nChip)
	{
		if (nData != 0x5D) return false;
	}

	return true;
}

int CTest_Main::f_testdata_judge_uint(unsigned nArray, unsigned pnum, unsigned meas_data )
{
	this->m_pCTestData->m_testData.vData[nArray][pnum].varData.uintVal = 0;

	CFunc_Spec_Item	*pTitem;

	pTitem = &this->m_pCSpec->m_vTitem[pnum]; 

	try
	{

		if (true == this->m_cState.Status.isHdlrOn)					// handler skip이 아니면 stop 신호를 체크
		{
//			if (this->m_pBd->m_pBdHdr->f_check_hsignal_testStop())	// 시리얼로 신호 확인 /*양수*/
//			{
//				return TEST_STOP_USER;
//			}
		}


		this->m_FAIL_Retest.bPass = f_testdata_check_pass (pnum, &pTitem->Spec, meas_data);	// 테스트 데이터를 양품과 불량으로 판정합니다.
	
		this->m_pCTestData->m_testData.vData[nArray][pnum].varData.uintVal = meas_data;

		if (  (true == this->m_FAIL_Retest.bEnable) && (false == this->m_FAIL_Retest.bPass) )			//Modify 2005.11.10 by sjkim
		{
			if(this->m_FAIL_Retest.nRetestCount != 0) 	
				return TEST_STOP_FAIL_RETEST;
		}

		this->m_pCTestData->m_testData.vData[nArray][pnum].bTested = true;		// $ 2013-0911 Add

		if (this->m_FAIL_Retest.bPass == true)
		{
			this->m_pCTestData->m_testData.vData[nArray][pnum].bPass	= true;		// $ 2013-0911 Add
		}
		else
		{
			this->m_pCTestData->m_testData.vData[nArray][pnum].bPass = false;	// $ 2013-0911 Add

			this->m_pCTestData->m_testData.Var.bPass = false;
		}

		WndDisplay_TestData(0, pnum);

		return TEST_CONTINUE;
	

	}
	catch (CMemoryException *e)
	{
		::MessageBox(NULL, "TEST_JUDGE_UINT", "경고", MB_OK);
		e->ReportError();
		e->Delete();
	}
	catch (CException *e)
	{
		::MessageBox(NULL, "TEST_JUDGE_UINT", "경고", MB_OK);
		e->Delete();
	}
	catch(...)
	{
		::MessageBox(NULL, "TEST_JUDGE_UINT", "경고", MB_OK);
	}

	return TEST_CONTINUE;
}

int CTest_Main::f_testdata_judge_dbl(unsigned nArray,  unsigned pnum,  double meas_data)
{

	this->m_pCTestData->m_testData.vData[nArray][pnum].varData.dblVal = 0;

	//debug
	if(pnum>12)
	{
		unsigned  x= 0;
	}



	CFunc_Spec_Item	*pTitem;

	pTitem = &this->m_pCSpec->m_vTitem[pnum]; 


	try
	{

		if (true == this->m_cState.Status.isHdlrOn)					// handler skip이 아니면 stop 신호를 체크
		{
//			if (this->m_pBd->m_pBdHdr->f_check_hsignal_testStop())	// 시리얼로 신호 확인 /*양수*/
//			{
//				return TEST_STOP_USER;
//			}
		}

		
		if (true == m_cState.Status.bTestStopEnable) return TEST_STOP_USER;

		
		//2005.11.10 by sjkim Modify Retest 
		//불량 판정 부분과 처리 부분을 분명하게 구분하고 
		//Retest 옵션이 설정된 경우 불량이 발생하면 불량 처리를 잠시 보류한다. 
		//이때 Retest Count 잔여 수는 함수를 부르는 부분에서 처리한다. 
		this->m_pCTestData->m_testData.vData[nArray][pnum].varData.dblVal = meas_data;

		this->m_FAIL_Retest.bPass = f_testdata_check_pass (pnum, &pTitem->Spec, meas_data);		//테스트 데이터를 양품과 불량으로 판정합니다. 

		if (  (true == this->m_FAIL_Retest.bEnable) && (false == this->m_FAIL_Retest.bPass) )
		{
			if(this->m_FAIL_Retest.nRetestCount != 0) 	
				return TEST_STOP_FAIL_RETEST;
		}


		this->m_pCTestData->m_testData.vData[nArray][pnum].bTested = true;		// $ 2013-0911 Add


		if (this->m_FAIL_Retest.bPass == true)
		{	
			this->m_pCTestData->m_testData.vData[nArray][pnum].bPass	= true;		// $ 2013-0911 Add
		}
		else
		{
			this->m_pCTestData->m_testData.vData[nArray][pnum].bPass = false;	// $ 2013-0911 Add

			this->m_pCTestData->m_testData.Var.bPass		= false;
		}

		WndDisplay_TestData(0, pnum);

		return TEST_CONTINUE;

	}
	catch (CMemoryException *e)
	{
		::MessageBox(NULL, "TEST_JUDGE", "경고", MB_OK);
		e->ReportError();
		e->Delete();
	}
	catch (CException *e)
	{
		::MessageBox(NULL, "TEST_JUDGE", "경고", MB_OK);
		e->Delete();
	}
	catch(...)
	{
		::MessageBox(NULL, "TEST_JUDGE", "경고", MB_OK);
	}


	return TEST_CONTINUE;
}

CString CTest_Main::f_testdata_conv_to_Binary  (unsigned pnum, unsigned dec, unsigned bin_digit)		// $ 2013.11.19 Add
{
	CString sBuf;
	
	unsigned digit = 0;


	while( dec > 0 )
	{
		if (dec % 2)
		{
			sBuf = '1' + sBuf;
		}
		else 
		{
			sBuf = '0' + sBuf;
		}
	
		dec = dec / 2;
		
		if (3 == (digit % 4) )
		{
			//sBuf = ' ' + sBuf;
		}

		digit ++;


	}

	while (bin_digit > digit)
	{
		sBuf = '0' + sBuf;

		if ( 3 == (digit % 4) ) 
		{
			//sBuf = ' ' + sBuf;
		}

		digit++;
	}

	sBuf = "b" + sBuf;

	return sBuf;
}

CString CTest_Main::f_testdata_conv_to_CString (unsigned pnum, VARIANT varData)
{
	CFunc_Spec_Item_Main		*pItemSpec;
	ST_CFUNCDATA_ITEMDATA       *pItemData;

	pItemSpec = &this->m_pCSpec->m_vTitem[pnum].Spec;
	pItemData = &this->m_pCTestData->m_testData.vData[0][pnum];

	unsigned nDispMode = pItemSpec->stDataDisp.nMode;
	unsigned nFmtMode  = pItemSpec->stDataFmt.nMode;
	CString  sFmt      = pItemSpec->stDataFmt.sFormat;


	CString strTemp;
		

	switch(nFmtMode)
	{
		case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:			strTemp.Format("%8.3f", varData.dblVal); break;
		case ENUM_CSPEC_DATA_MODE::M01_DBL_USER_FORMAT:		strTemp.Format(sFmt,    varData.dblVal); break;

		case ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT:			strTemp.Format("%d", varData.uintVal); break;
		//case ENUM_CSPEC_DATA_MODE::M11_UINT_USER_FORMAT:		strTemp.Format(sFmt,	nUINT); break;

		case ENUM_CSPEC_DATA_MODE::M21_UINT_HEX_2:			strTemp.Format("0x%02x", varData.uintVal); break;	
		case ENUM_CSPEC_DATA_MODE::M22_UINT_HEX_4:			strTemp.Format("0x%04x", varData.uintVal); break;		
		case ENUM_CSPEC_DATA_MODE::M23_UINT_HEX_6:			strTemp.Format("0x%06x", varData.uintVal); break;	
		case ENUM_CSPEC_DATA_MODE::M24_UINT_HEX_8:			strTemp.Format("0x%08x", varData.uintVal); break;		

		case ENUM_CSPEC_DATA_MODE::M31_UINT_BIN_1:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 1); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M32_UINT_BIN_2:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 2); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M33_UINT_BIN_3:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 3); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M34_UINT_BIN_4:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 4); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M35_UINT_BIN_5:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 5); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M36_UINT_BIN_6:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 6); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M37_UINT_BIM_7:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 7); break;		// $ 2013.11.19 Add
		case ENUM_CSPEC_DATA_MODE::M38_UINT_BIN_8:			strTemp = f_testdata_conv_to_Binary  (pnum, varData.uintVal, 8); break;		// $ 2013.11.19 Add

		//case ENUM_CSPEC_DATA_MODE::M40_UINT_BOOL_PF:			strTemp = nUINT ? "PASS" : "FAIL"; break;

		default:
			break;
	}	

	return strTemp;
}

void CTest_Main::f_testdata_conv_spec_to_CString (unsigned pnum, CString &sHIL, CString &sLOL)
{

	CFunc_Spec_Item_Main *pSpec;
	pSpec = &this->m_pCSpec->m_vTitem[pnum].Spec;

	switch (pSpec->stLimit.nMode)
	{
	case ENUM_CSPEC_LIMIT_MODE::M1_UPPER_LIMIT:
		sLOL = "";
		sHIL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.HSL_VAR);
		break;

	case ENUM_CSPEC_LIMIT_MODE::M2_LOWER_LIMIT:
		sHIL = "";
		sLOL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.LSL_VAR);
		break;

	case ENUM_CSPEC_LIMIT_MODE::M3_EQUAL:

		pSpec->stLimit.HSL_VAR	= pSpec->stLimit.LSL_VAR;

		sLOL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.LSL_VAR);
		sHIL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.HSL_VAR);
		break;

	case ENUM_CSPEC_LIMIT_MODE::M4_NOT_EQUAL:
		pSpec->stLimit.HSL_VAR	= pSpec->stLimit.LSL_VAR;

		sLOL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.LSL_VAR);
		sHIL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.HSL_VAR);
		break;

	default:
		sLOL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.LSL_VAR);
		sHIL = this->f_testdata_conv_to_CString (pnum, pSpec->stLimit.HSL_VAR);
		break;
	}

	return ;
}

int CTest_Main::f_hex_conv_to_int(CString szHexStr)
{
	int nLen = szHexStr.GetLength();
	TCHAR * tchHex = (TCHAR *)(LPCTSTR)szHexStr;
	INT	nResult = 0;

	for(int i=0;i<nLen;i++)
	{
		TCHAR tchCh = 0;
		if(tchHex[i] >= L'0' && tchHex[i] <= L'9')
			tchCh = (tchHex[i] - 0x0030) & 0x000F;
		else if(tchHex [i] >= L'A' && tchHex[i] <= L'F')
			tchCh = (tchHex[i] - 0x0037) & 0x000F;
		else
			return 0;		// 정상 Character가 아닌경우 0 리턴
		 
		nResult |= (tchCh << ((nLen-1) - i) * 4);
	}
	return nResult;
}


void CTest_Main::f_progress_bar (unsigned int pnum)
{
//	unsigned int nRefTitem = m_pTitem->Spec.nRefTitem;
//	WndDisplay_TestData(0, pnum);

//	if(pnum == 2)
//	{
//		pnum=9;
//		WndDisplay_progress_position (0, pnum*10);
//	}
//	else
//	{
//		WndDisplay_progress_position (0, pnum*10);
//	}
}
