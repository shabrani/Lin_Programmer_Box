// CFunc_DataTable.cpp: implementation of the CFunc_DataTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "CFunc_TestData_SaveAccess.h"
//#include "tproc_header_main.h"
#include "CTest_Main.h"
#include "io.h"
#include "afxdao.h"

#include "CFunc_TestData.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//extern CTest_Main	*pTest;

//DWORD ThreadID_saveData;
//HANDLE hThread_saveData;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4995) 
#pragma warning(disable:4101) 


bool	CFunc_TestData_SaveAccess::f_Create_New_DBFile(unsigned nAr, bool bSave_TextData)
{
//데이타베이스 스펙에 맞게 테이블생성하고 초기화 시작


	this->m_BOOL.DBFile_bExist = false;
	this->m_BOOL.DBFile_bCreate = false;
	this->m_BOOL.Table_DATA_bExist = false;


	this->m_BOOL.bInitDB = false;
	this->m_BOOL.bTestSpec = false;
	this->m_BOOL.bDataTable_Config = false;
	
	//this->m_BOOL.DATA_TEXTNOTE_bSave = false;
	this->m_BOOL.DATA_TEXTNOTE_bSave = bSave_TextData;		// $ 2015.07.02 Change

	m_var.nAr	 = nAr;
	m_var.nTitem = m_cfg.pCSpec->m_stStatus.nTitem;

	m_var.tmCreateTime = CTime::GetCurrentTime() ;
	m_var.strCreateTime  = m_var.tmCreateTime.Format("%Y-%m-%d %H:%M:%S");

	
	//char path [MAX_PATH];	
	CString sBuf;
	CFunc_RegMain Reg;
	Reg.f_regiRead_BasePath_DataFile (sBuf);

	CString strDBFilePath, strDBFileMiddle;//데이타베이스 경로
	strDBFilePath.Format("%s\\", sBuf.GetString() );

	// $ Change by sjkim 2012-06-21 ->회사_컴퓨터이름으로 데이터베이스 이름 변경	


	//strDBFileMiddle.Format("%s_%s_%s", m_cfg.pts->System.sCompanyName.GetString(), m_cfg.pts->System.sComputerName.GetString(), SYSTEM_MODEL_NO_STRING);	
//	CTest_System_Build_History system;
	strDBFileMiddle.Format("%s_%s_%s_%s", m_var.strDBFilname_start.GetString(), m_cfg.pts->SysInfo.sCompanyName.GetString(), m_cfg.pts->SysInfo.sComputerName.GetString(), SYSTEM_MODEL_NO_STRING );

		
	//INIT DB -> 데이타베이스 파일이 없으면 생성하고 기본 TABLE을 생성한다. 그리고 데이터 저장에 필요한 기본 플래그를 설정한다. 
	BOOL bRtn = f_DB_Init(strDBFilePath.GetBuffer(strDBFilePath.GetLength()), strDBFileMiddle.GetBuffer(strDBFileMiddle.GetLength()));

	if(false == bRtn)
	{	
		AfxMessageBox("데이타베이스 파일 초기화오류");
		return false;
	}

	if(FALSE == f_Init_TestMain())//TestSpecHeader입력
	{
		AfxMessageBox("TestSpecHeader 입력오류");
		return false;
	}
	



//데이타베이스 스펙에 맞게 테이블생성하고 초기화 끝
/////////////////////////////////////////////////////////////////

	return true;
}



//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////
// CFunc_TestData_SaveAccess Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunc_TestData_SaveAccess::CFunc_TestData_SaveAccess()
{
	m_var.strDBFilname_start = TESTDATA_DB_FILENAME_HEADER;

	m_var.nAr			= 0;
	m_var.nTitem		= 0;
	m_var.nTestSpec		= 0;
	
	//this->m_pSaveHeader	= new ST_CDATATABLE_TESTSPECHEADER;

	m_var.nPID = 0;								//TESTSPECHEADER의 DB ID
	m_BOOL.bInitDB			= false;
	m_BOOL.bDataTable_Config	= false;
	m_BOOL.bTestSpec		= false;

}

CFunc_TestData_SaveAccess::~CFunc_TestData_SaveAccess()
{
	//this->f_deleteArray_DataAndSpec();
	//delete m_pSaveHeader;
}


BOOL CFunc_TestData_SaveAccess::f_Change_New_LotNumber(CString strNewLotNum)
{
/*	CDatabase database;
	CString sSql;
	CString sDriver;


	TRY
	{
		/////////////////
		database.Open(NULL,false,false,m_var.strDsn);

		
		sSql.Format("UPDATE TEST_MAIN SET LOTNUMBER='%s' where DEVICENAME='%s' and TESTSPEC='%s' and TESTDATE=#%s#", strNewLotNum.GetString(),
			m_cfg.pCSpec->m_stSpecInfo.tspec.strDeviceName.GetString(),
			m_cfg.pCSpec->m_stSpecInfo.tspec.strSpecName.GetString(),
			m_var.strCreateTime.GetString());

		database.ExecuteSQL(sSql);
		database.Close();
			
	}
	CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);

		database.Close();

		return false;
	}
	END_CATCH;

*/
	return true;
}

void CFunc_TestData_SaveAccess::f_saveData()
{
	this->m_var.bSaveComplete = false;

	//데이타베이스 입력 시작

	if(!f_Input_TestData_to_TABLE())
	{
		AfxMessageBox("데이타입력 오류");
		m_var.bSaveComplete = true;

		return;
	}

	if (true != m_BOOL.DATA_TEXTNOTE_bSave)		// $ 2015.07.02 Add
	{
		m_var.bSaveComplete = true;
		return;
	}


	if (true != ( f_Input_TEXTData_to_TABLE() ? true : false) )	// $ 2015.07.02 Add
	{
		AfxMessageBox("SAVE DATA DB ERROR :: f_Input_TEXTData_to_TABLE () ");
		m_var.bSaveComplete = true;
		return;
	}

	m_var.bSaveComplete = true;



	//hThread_saveData = CreateThread(NULL, 0, Thread_saveData, NULL, 0, &ThreadID_saveData);
	//CloseHandle(hThread_saveData);
}




BOOL CFunc_TestData_SaveAccess::f_DB_Init( CString strDBFilePath, CString strFileMiddle)	//DB 파일이 없으면 새로운 DB파일을 판들고 기본 DB Table을 생성한다. 
{
	m_BOOL.bInitDB	= false;
	m_BOOL.bDataTable_Config = false;
	m_BOOL.bTestSpec = false;

	m_var.nTestSpec = 0;


	m_BOOL.DBFile_bExist = false;
	m_BOOL.DBFile_bCreate = false;


	m_var.strDBFilePath = strDBFilePath;


	if(m_var.strDBFilePath.IsEmpty())
	{
		//실행파일 파일경로구하기
		char buf[1024];
		::GetCurrentDirectory(sizeof(buf), buf);

		CString strRootFilePath;
		strRootFilePath = buf;
		m_var.strDBFilePath = strRootFilePath + "\\";
	}
	else
	{
		//DB 폴더 있는지 확인
		CString strDBFilePath = m_var.strDBFilePath + "*.*";
		CFileFind finder;
		if(finder.FindFile(strDBFilePath)!=TRUE)
		{
			//실행파일 파일경로구하기
			char buf[1024];
			::GetCurrentDirectory(sizeof(buf), buf);
			CString strRootFilePath;
			strRootFilePath = buf;
			m_var.strDBFilePath = strRootFilePath + "\\";
		}
	}

	m_BOOL.DBFile_bExist = false;
	m_BOOL.DBFile_bCreate = false;

	//CTime tmCur  = CTime::GetCurrentTime() ;
	
	CString strCurDate, strCurDate_msg, strCurDate_db;

	strCurDate_msg = m_var.tmCreateTime.Format("%Y년%m월");
	strCurDate_db  = m_var.tmCreateTime.Format("_%Y%m.mdb");

	m_var.strDBFileName = m_var.strDBFilePath + strFileMiddle + strCurDate_db;

	CString strFolderMsg;

	if(!m_var.strDBFileName.IsEmpty())
	{
		if(0 == _access(_T(m_var.strDBFileName), 00))//파일 존재 검사
		{
				m_BOOL.DBFile_bExist = true;
		}
		else
		{
			m_BOOL.DBFile_bExist = false;
		}
	}
	else
	{
		strFolderMsg = "DataBase를 저장할 폴더경로가 잘못되었습니다.";
		return false;
	}

	if (false == m_BOOL.DBFile_bExist )
	{

		BOOL bRtn = f_DB_Make();

		if ( false == bRtn )		//DB파일이 없으면 생성하고 기본 데이터 TABLE을 생성한다. 
		{		
			return false;
		}
		
		m_BOOL.DBFile_bExist = true;
		m_BOOL.DBFile_bCreate = true;
	}



///////// Data_Info_Header데이타 읽기
	CDatabase database;
    CString sSql;
    CString sDriver;
	CDBVariant varValue,varValue1;

	sDriver = f_GetDriverStringX("Access");
    if(sDriver.IsEmpty())
    {
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		AfxMessageBox("No Access ODBC driver found");
        return false;
    }    
    m_var.strDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s",sDriver.GetString(),m_var.strDBFileName.GetString());


	if (true == m_BOOL.DBFile_bCreate)	// $ Add 2015.03.03 sjkim DB File이 만들어질 때만 생성한다.
	{
		if (FALSE == f_input_DBInfo_to_TABLE() )
			return false;
	}


	m_BOOL.bInitDB = true;
	
	return true;
}


BOOL CFunc_TestData_SaveAccess::f_Init_TestMain()
{
	if(!m_BOOL.bInitDB)
		return false;

	//if(	FALSE == f_Config_New_TestLot_Table())
	if(	FALSE == this->f_Input_TestMain_to_Table())
	{
		m_BOOL.bDataTable_Config = false;
		return false;
	}
	m_BOOL.bDataTable_Config = true;
	

	if (false == m_BOOL.Table_DATA_bExist)
	{
		if (FALSE == f_Create_DBTable_TestData_Spec())
		{
			m_BOOL.Table_DATA_bExist = false;
			AfxMessageBox("Test Data DB Err: f_Create_DBTable_TestData_Spec");
			return false;
		}

		if(FALSE == f_Input_TestSpec_to_TABLE() )
		{
			m_BOOL.Table_DATA_bExist = false;
			AfxMessageBox("Test Data DB Err: f_Input_TestSpec_to_TABLE");
			return false;
		}


		if (FALSE == f_Create_DBTable_TestData() )				
		{
			m_BOOL.Table_DATA_bExist = false;

			AfxMessageBox("Test Data DB Err: f_Create_DBTable_TestData");
			return false;
		}
		//else
		//	m_BOOL.Table_DATA_bExist = true;					// $ 2015.07.02 수정



		if (false == this->m_BOOL.DATA_TEXTNOTE_bSave)			// $ 2015.07.02 Add
		{
			m_BOOL.Table_DATA_bExist = true;
			return true;
		}


		if (FALSE == f_Create_DBTable_TestData_TEXT())			// $ 2015.07.02 Add
		{
			m_BOOL.Table_DATA_bExist = false;

			AfxMessageBox("Test Data DB Err: f_Create_DBTable_TestData_TEXT");
			return false;
		}
		else
			m_BOOL.Table_DATA_bExist = true;


	}

	return true;
}
	
BOOL CFunc_TestData_SaveAccess::f_input_DBInfo_to_TABLE()  // $ 2015.03.03 Add sjkim 
{
	///////// 데이타베이스에 데이타 저장
	CDatabase database;
	CString sSql;
																					   

	TRY
	{
		database.Open(NULL,false,false,m_var.strDsn);


	//	sSql.Format("insert into DB_INFO (REV_NO_MAIN,REV_NO_SUB,REVDATE,REVNOTE) values (%d,%d,'%s','%s')", DATA_DB_REV_MAIN_NO, DATA_DB_REV_SUB_NO, DATA_DB_REV_DATE, DATA_DB_REV_NOTE ); 
	//	database.ExecuteSQL(sSql);   
		
		sSql.Format("insert into DBFORM_INFO (FIELD,DATA) values ('%s','%s')", "00_DBFORM_TYPE", "TEST_DATA");
		database.ExecuteSQL(sSql);

		sSql.Format("insert into DBFORM_INFO (FIELD,DATA) values ('%s','%s')",	"10_REV_NO", DATA_DB_REV_NO);
		database.ExecuteSQL(sSql);

		sSql.Format("insert into DBFORM_INFO (FIELD,DATA) values ('%s','%s')",	"30_REV_DATE", DATA_DB_REV_DATE);
		database.ExecuteSQL(sSql);


		sSql.Format("insert into DBFORM_INFO (FIELD,DATA) values ('%s','%s')","40_NOTE", DATA_DB_REV_NOTE);
		database.ExecuteSQL(sSql);



		database.Close();




	}
	CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: "+e->m_strError);

		database.Close();
		return false;
	}
	END_CATCH;

	return true;
}


BOOL CFunc_TestData_SaveAccess::f_Input_TestSpec_to_TABLE()
{
	if(!m_BOOL.bInitDB || !m_BOOL.bDataTable_Config)
		return false;
	///////// 데이타베이스에 데이타 저장
	
	CDatabase database;
	CString sSql;
	
	CFunc_Spec_Item_Main	 *pSpec;

	TRY
	{
		database.Open(NULL,false,false,m_var.strDsn);
	
		for (unsigned t=0; t < m_cfg.pCSpec->m_stStatus.nTitem; t++)
		{
			pSpec = &m_cfg.pCSpec->m_vTitem[t].Spec;

			sSql.Format("insert into %s (TNUM,SYMBOL,TESTITEM,UNIT,LSL,HSL,LIMITMODE,DATAFORMAT,TEXTDATA_YN,TEXTSPEC1,TEXTSPEC2) values ('%d','%s','%s','%s','%d','%d','%d','%s','%d','%s','%s')",			// $ 2015.05.05 Add
				m_var.strTableName_DATA_SPEC.GetString(),
				//m_var.nPID,
				pSpec->nPnum + 1,
				pSpec->strTestSymbol.GetString(),
				pSpec->strTestName.GetString(),
				pSpec->strTestUnit.GetString(),

				pSpec->stLimit.LSL_VAR.uintVal,
				pSpec->stLimit.HSL_VAR.uintVal,

				pSpec->stLimit.nMode,
				pSpec->strDataFormat.GetString(),
				0,
				"",
				"");

			database.ExecuteSQL(sSql);
       

		}

	}
	CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: "+e->m_strError);
		m_BOOL.bInitDB = false;
		m_BOOL.bDataTable_Config = false;
		m_BOOL.bTestSpec = false;

	
		database.Close();
		return false;
	}
	END_CATCH;

	database.Close();
	m_BOOL.bTestSpec = true;
	

	return true;
}


BOOL CFunc_TestData_SaveAccess::f_Input_TestData_to_TABLE ( )
{
	if(!m_BOOL.bInitDB || !m_BOOL.bDataTable_Config || !m_BOOL.bTestSpec)
	{


		if (!m_BOOL.bInitDB)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		if (!m_BOOL.bDataTable_Config)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		if (!m_BOOL.bTestSpec)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		::MessageBox(NULL, "if(!m_bInitDB || !m_bCfgDataTable || !m_bTestSpec)", "CFunc_DataTable::InputData 오류", MB_OK);

		return false;
	}


	///////// 데이타베이스에 데이타 저장
	CDatabase database;
	CString sSql;
	///////////////

	int  nResult = 0;
	CString strCHK = " ";
	unsigned p;
	unsigned tnum;
	//unsigned ar;
	
	CString strSqlTemp;
	CString strSqlHeader;
	CString strSqlData;


	TS_CTESTDATA_DEVICEDATA	*pSaveData = &m_cfg.pCData->m_saveData;


	CString strTestStartTime;


	//sprintf_s (szTestTime, "%04d-%02d-%02d %02d:%02d:%02d", stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
	strTestStartTime.Format("%04d-%02d-%02d %02d:%02d:%02d",
		pSaveData->Var.tTime.GetYear(),
		pSaveData->Var.tTime.GetMonth(),
		pSaveData->Var.tTime.GetDay(),
		pSaveData->Var.tTime.GetHour(),
		pSaveData->Var.tTime.GetMinute(),
		pSaveData->Var.tTime.GetSecond()
		);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////						Header 작성
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	strSqlHeader = "DNUM,Array";

	for(p=0; p< m_var.nTitem; p++)						//DB에 데이타삽입
	{
			
		tnum = p+1;

		//if (false == m_BOOL.DATA_TEXTNOTE_bSave)		// $ 2015.07.02 수정
		{
			strSqlTemp = strSqlHeader;
			strSqlHeader.Format("%s,T%03d,T%03d_CHK",strSqlTemp.GetString(),tnum,tnum);
		}
		//else                                         // $ 2015.07.02 수정
		//{                                            // $ 2015.07.02 수정
		//	strSqlTemp = strSqlHeader;                 // $ 2015.07.02 수정
		//	strSqlHeader.Format("%s,T%03d,TXT_%03d,CHK__%03d",strSqlTemp,tnum,tnum,tnum);// $ 2015.07.02 수정
		//}

	}


	strSqlTemp = strSqlHeader;

	strSqlHeader.Format("%s,PassYN,BIN,StartTime,SerialNo,NOTE1,NOTE2",strSqlTemp.GetString());
	//strSqlHeader.Format("%s,PassYN,BIN,StartTime,SerialNo,TestTime,NOTE1,NOTE2",strSqlTemp);
	//strSqlHeader.Format("%s,PassYN,BIN,StartTime,SerialNo,TOOL,TestTime,NOTE1,NOTE2",strSqlTemp);


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		data를 저장하세요
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TRY
	{
		database.Open(NULL,false,false,m_var.strDsn);

		ST_CFUNCDATA_ITEMDATA *pData;

		for (unsigned ar=0; ar<m_var.nAr; ar++)
		{
			strSqlData.Format("%d,%d",
				pSaveData->Var.nDnum,
				ar);

			for(p=0; p< m_var.nTitem; p++)						//DB에 데이타삽입
			{
			
				unsigned tnum = p+1;

				pData = &m_cfg.pCData->m_saveData.vData[ar][p];

				if (true == pData->bTested)
				{
					strCHK = m_cfg.pCData->m_saveData.vData[ar][p].bPass ? "" : "F";
				}
				else
				{
					strCHK  = "X";
				}

				//if (false == m_BOOL.DATA_TEXTNOTE_bSave)// $ 2015.07.02 수정
				{
		
					if ( m_cfg.pCSpec->m_vTitem[p].Spec.stDataFmt.nMode <= ENUM_CSPEC_DATA_MODE::M01_DBL_USER_FORMAT)
					{
						strSqlTemp = strSqlData;
						strSqlData.Format("%s,%f,'%s'",strSqlTemp.GetString(), pData->varData.dblVal, strCHK.GetString());	// $ Change 2015-01-17 sjkim
					}
					else
					{
						strSqlTemp = strSqlData;
						strSqlData.Format("%s,%d,'%s'",strSqlTemp.GetString(), pData->varData.uintVal, strCHK.GetString());	// $ Change 2015-01-17 sjkim
					}

				}
				/*                     // $ 2015.07.02 수정
				else
				{
					if ( m_cfg.pCSpec->m_vTitem[p].Spec.stDataFmt.nMode <= ENUM_CSPEC_DATA_MODE::M01_DBL_USER_FORMAT)
					{
						strSqlTemp = strSqlData;
						strSqlData.Format("%s,%f,'%s','%s'",strSqlTemp, pData->varData.dblVal, pData->strText, strCHK );	// $ Change 2015-01-17 sjkim
					}
					else
					{
						strSqlTemp = strSqlData;
						strSqlData.Format("%s,%d,'%s','%s'",strSqlTemp, pData->varData.uintVal, pData->strText,  strCHK );	// $ Change 2015-01-17 sjkim
					}
				}
				*/

			}

			{
				CString strNote1;
				CString strNote2;

				if ( true == this->m_cfg.pCData->m_saveData.Var.bPass )
				{
				//	CString strNote1 = "";
					CString strNote2 = "";
				}
				else
				{
				//	strNote1.Format("PRE T%03d", this->m_cfg.pCData->m_saveData.Var.st1stFail.nTnum_prev);
					strNote2.Format("FIN T%03d", this->m_cfg.pCData->m_saveData.Var.st1stFail.nTnum);
				}

				strNote1.Format ("%d", 	(unsigned)(1000*pSaveData->Var.fElapsedtime));			// TestTime;

				/*
				strSqlTemp = strSqlData;
				strSqlData.Format("%s,%d,%d,#%s#,'%s',%d,%f,'%s','%s'",
					strSqlTemp,
					pSaveData->Var.bPass,
					pSaveData->Var.nBin,				// BIN
					szTestStartTime,
					pSaveData->Var.sSerialNo,
					pSaveData->Var.nJig, 
					pSaveData->Var.fElapsedtime,			// TestTime
					strNote1, 
					strNote2);
					*/

				/*
				strSqlTemp = strSqlData;
				strSqlData.Format("%s,%d,%d,#%s#,'%s',%f,'%s','%s'",
					strSqlTemp,
					pSaveData->Var.bPass,
					pSaveData->Var.nBin,				// BIN
					szTestStartTime,
					pSaveData->Var.sSerialNo,
					//pSaveData->Var.nJig, 
					pSaveData->Var.fElapsedtime,			// TestTime
					strNote1, 
					strNote2);
					*/

				
				strSqlTemp = strSqlData;
			//	strSqlData.Format("%s,%d,%d,#%s#,'%s',%d,'%s'",
				strSqlData.Format("%s,%d,%d,#%s#,'%s','%s','%s'",
					strSqlTemp.GetString(),
					pSaveData->Var.bPass,
					pSaveData->Var.nBin,				// BIN
					strTestStartTime.GetString(),
					pSaveData->Var.sSerialNo.GetString(),
					//pSaveData->Var.nJig, 
					//(unsigned)(1000*pSaveData->Var.fElapsedtime),			// TestTime
					strNote1.GetString(),
					strNote2.GetString());
					


			}

			sSql.Format("insert into %s (%s) values (%s)", m_var.strTableName_DATA.GetString(), strSqlHeader.GetString(), strSqlData.GetString());

			//AfxMessageBox ("데이터 저장 오류입니다.");

			database.ExecuteSQL(sSql);        
		}

	}
	CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: "+e->m_strError);
		database.Close();
		return false;
	}
	END_CATCH;

	database.Close();

	return true;
}


BOOL CFunc_TestData_SaveAccess::f_Input_TEXTData_to_TABLE()
{
#ifdef TEXTDATA_SAVE_ENABLE

	if (true != this->m_BOOL.DATA_TEXTNOTE_bSave) return TRUE;

	if (!m_BOOL.bInitDB || !m_BOOL.bDataTable_Config || !m_BOOL.bTestSpec)
	{


		if (!m_BOOL.bInitDB)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		if (!m_BOOL.bDataTable_Config)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		if (!m_BOOL.bTestSpec)
			::MessageBox(NULL, "m_bInitDB", "CFunc_DataTable::InputData 오류", MB_OK);

		::MessageBox(NULL, "if(!m_bInitDB || !m_bCfgDataTable || !m_bTestSpec)", "CFunc_DataTable::InputData 오류", MB_OK);

		return false;
	}


	///////// 데이타베이스에 데이타 저장
	CDatabase database;
	CString sSql;
	///////////////

	int  nResult = 0;
	CString strCHK = " ";
	unsigned p;
	unsigned tnum;
	//unsigned ar;

	CString strSqlTemp;
	CString strSqlHeader;
	CString strSqlData;


	TS_CTESTDATA_DEVICEDATA	*pSaveData = &m_cfg.pCData->m_saveData;


	char szTestStartTime[30];
	//sprintf_s (szTestTime, "%04d-%02d-%02d %02d:%02d:%02d", stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
	sprintf_s(szTestStartTime, "%04d-%02d-%02d %02d:%02d:%02d",
		pSaveData->Var.tTime.GetYear(),
		pSaveData->Var.tTime.GetMonth(),
		pSaveData->Var.tTime.GetDay(),
		pSaveData->Var.tTime.GetHour(),
		pSaveData->Var.tTime.GetMinute(),
		pSaveData->Var.tTime.GetSecond()
		);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////						Header 작성
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	strSqlHeader = "DNUM,Array";

	for (p = 0; p< m_var.nTitem; p++)						
	{

		tnum = p + 1;

		strSqlTemp = strSqlHeader;
		strSqlHeader.Format("%s,T%03d_TXT", strSqlTemp.GetString(), tnum);

	}


	strSqlTemp = strSqlHeader;

	strSqlHeader.Format("%s,PassYN,StartTime", strSqlTemp.GetString());



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		data를 저장하세요
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TRY
	{
		database.Open(NULL, false, false, m_var.strDsn);

		ST_CFUNCDATA_ITEMDATA *pData;

		for (unsigned ar = 0; ar < m_var.nAr; ar++)
		{
			strSqlData.Format("%d,%d",
				pSaveData->Var.nDnum, ar);

			for (p = 0; p < m_var.nTitem; p++)						//DB에 데이타삽입
			{

				unsigned tnum = p + 1;

				pData = &m_cfg.pCData->m_saveData.vData[ar][p];

				strSqlTemp = strSqlData;
				strSqlData.Format("%s,'%s'", strSqlTemp.GetString(), pData->strData.GetString());
			}


			{
				strSqlTemp = strSqlData;
				//	strSqlData.Format("%s,%d,%d,#%s#,'%s',%d,'%s'",
				strSqlData.Format("%s,%d,#%s#",
					strSqlTemp.GetString(),
					pSaveData->Var.bPass,
					szTestStartTime
					);
			}

			sSql.Format("insert into %s (%s) values (%s)", m_var.strTableName_DATA_TEXT.GetString(), strSqlHeader.GetString(), strSqlData.GetString());

			//AfxMessageBox ("데이터 저장 오류입니다.");

			database.ExecuteSQL(sSql);
		}
		

	}
		CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);
		database.Close();
		return false;
	}
	END_CATCH;

	database.Close();

#endif
	return true;
}

CString CFunc_TestData_SaveAccess::f_GetDriverStringX(CString drivername) 
{
	//파라메터에 "Access", "dBase" , "Text", "Excel" 이라고 넣어주면
	//각각의 드라이버 이름을 얻어올수 있습니다.

    char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver; // return value
    CString tDriver = drivername ;

	if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
        return "";
    do
    {   
        if( strstr( pszBuf, tDriver ) != 0 )
        {
            // Found !
            sDriver = CString( pszBuf );
            break;// NOT BREAK
        }
        pszBuf = strchr( pszBuf, '\0' ) + 1;
        
    }
    while( pszBuf[1] != '\0' );
    return sDriver;
}

BOOL CFunc_TestData_SaveAccess::f_DB_Make()//데이타베이스 처음 만들때
{


	CString strMsg;

	CDaoDatabase	*pdb;
	pdb = new CDaoDatabase;
	
	try//데이타베이스 생성
	{
		pdb->Create(m_var.strDBFileName,dbLangGeneral);
	}
	catch(CDaoException &ex)
	{
		strMsg.Format("데이타베이스 생성 실패");
		AfxMessageBox(strMsg);
		pdb->Close();
		delete pdb;
		return false;
	}
	catch(CMemoryException &ex)
	{ 
		strMsg = "데이타베이스 메모리 로드 실패";
		AfxMessageBox(strMsg);
		pdb->Close();
		delete pdb;
		return false;
	}

/**************************************************/
	if (FALSE == f_Create_DBTable_TestMain ( pdb ) )
	{
		pdb->Close();
		delete pdb;
		return FALSE;
	}

/************* Test Spec ******************/
	
	/*			// $ 2015.07.02
	if (FALSE == f_Create_DBTable_TestSpec ( pdb ) )
	{
		pdb->Close();
		delete pdb;
		return FALSE;
	}
	*/

/**************************************************/
	if (FALSE == f_Create_DBTable_DBInfo ( pdb ) )
	{
		pdb->Close();
		delete pdb;
		return FALSE;
	}

	pdb->Close();
	delete pdb;




	return true;
}


BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_TestSpec (CDaoDatabase	*pdb)
{
	CString			strMsg;

	CDaoTableDef	*pTableDef;
	pTableDef	= new CDaoTableDef(pdb);

	try//테이블 생성
	{
		pTableDef->Create("TEST_SPEC");
	}
	catch(CDaoException &ex)
	{
		strMsg = "데이타베이스 테이블 생성 실패";
		AfxMessageBox(strMsg);
		delete pdb;
		delete pTableDef;
		return false;
	}
	catch(CMemoryException &ex)
	{ 
		strMsg = "데이타베이스 테이블 메모리 로드 실패";
		AfxMessageBox(strMsg);
		delete pdb;
		delete pTableDef;
		return false;
	}

	CDaoFieldInfo wfInfo;
	CDaoFieldInfo rfInfo;


	CString strFieldName;

	try//필드 생성
	{

		pTableDef->CreateField("ID" ,  dbLong , 4,dbAutoIncrField);
		pTableDef->CreateField("PID" , dbLong , 4 ,0);
		pTableDef->CreateField("TNUM" , dbLong , 4 ,0);

		this->m_daoFunc.f_field_Create_dbText (pTableDef, "SYMBOL",  true, 16);
		pTableDef->CreateField("TESTITEM" , dbText , 75 ,0);

		this->m_daoFunc.f_field_Create_dbText (pTableDef, "UNIT",  true, 16);
	
		pTableDef->CreateField("LSL" , dbText , 12 ,0);
		pTableDef->CreateField("HSL" , dbText , 12 ,0);
		pTableDef->CreateField("LIMITMODE" , dbLong , 4 ,0);
		pTableDef->CreateField("DATAFORMAT" ,    dbText , 8 ,0);	// % 4.2f, %08s, %8.4f, %0x02X

		pTableDef->Append();

		delete pTableDef;

	}
	catch(CDaoException &ex)
	{
		strMsg = "데이터 저장 DB -> TEST_SPEC 테이블 생성 실패";
		AfxMessageBox(strMsg);
		delete pdb;
		delete pTableDef;
		return false;
	}
	catch(CMemoryException &ex)
	{
		strMsg = "데이타베이스 테이블 필드 메모리 로드 실패";
		AfxMessageBox(strMsg);
		delete pdb;
		delete pTableDef;
		return false;
	}


	return	TRUE;
}


BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_TestMain   (CDaoDatabase	*pdb )
{
	CString			strMsg;

/***************** Table Name ******************/
	CDaoTableDef	*pTableDef;
	pTableDef	= new CDaoTableDef(pdb);

	try//테이블 생성
	{
		pTableDef->Create("TEST_MAIN");
	}
	catch(CDaoException &ex)
	{
		strMsg = "데이타베이스 테이블 생성 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}
	catch(CMemoryException &ex)
	{ 
		strMsg = "데이타베이스 테이블 메모리 로드 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}

	CDaoFieldInfo wfInfo;
	CDaoFieldInfo rfInfo;


	CString strFieldName;


	try//필드 생성
	{
		pTableDef->CreateField("ID" ,			dbLong , 4,	dbAutoIncrField);
		pTableDef->CreateField("DEVICENAME" ,	dbText , 25 ,0);
		pTableDef->CreateField("TESTSPEC" ,		dbText , 25 ,0);

		//pTableDef->CreateField("LOTNUMBER" ,	dbText , 75 ,0);						
		if (FALSE ==  m_daoFunc.f_field_Create_dbText(pTableDef, "LOTNUMBER", true, 40, 0) )
		{
			pTableDef->Close();
			delete pTableDef;

			return FALSE;
		} 
		
		
		pTableDef->CreateField("TESTDATE" ,			 dbDate , 8 ,0);	//$Added sjkim 2012-06-05
		pTableDef->CreateField("DATA_TABLENAME",	 dbText, 20, 0);
		pTableDef->CreateField("SPEC_TABLENAME",	 dbText, 20, 0);
		pTableDef->CreateField("TEXT_TABLENAME", dbText, 20, 0);	// $ 2015.07.02
		pTableDef->CreateField("TEXTDATA_YN",		 dbBoolean, 1, 0);	// $ 2015.07.07

		pTableDef->CreateField("ITEM_NUM",			 dbLong , 4,		0);
		pTableDef->CreateField("ARRAY_NUM",			 dbLong , 4,		0);
		pTableDef->CreateField("SAVEFAIL_YN",		 dbBoolean, 1,	0);	// $ 2015.07.02

		pTableDef->CreateField("COUNT_YN",			 dbBoolean , 1,  0);	//DATABASE 프로그램에서 저장한다.LOT변경시에는 항상 FALSE로 설정한다.
		pTableDef->CreateField("COUNT_DATA",		 dbLong , 4,  0);	//DATABASE 프로그램에서 저장한다. AR=0인경우에만 읽어 드린다. 
		pTableDef->CreateField("COUNT_PASS",		 dbLong , 4,  0);	//DATABASE 프로그램에서 저장한다. AR=0인 경우에만 읽어 드린다.
		
		pTableDef->Append();

		delete pTableDef;

	}
	catch(CDaoException &ex)
	{
		strMsg = "데이터 저장 DB -> TEST_MAIN  필드 생성 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}
	catch(CMemoryException &ex)
	{
		strMsg = "데이타베이스 테이블 필드 메모리 로드 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}



	return TRUE;
}


BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_DBInfo(CDaoDatabase	*pdb )
{
	CString			strMsg;

/***************** Table Name ******************/
	CDaoTableDef	*pTableDef = NULL;


/*
	try//테이블 생성
	{
		pTableDef->Create("DB_INFO");
	}
	catch(CDaoException &ex)
	{
		strMsg = "데이타베이스 테이블 생성 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}
	catch(CMemoryException &ex)
	{ 
		strMsg = "데이타베이스 테이블 메모리 로드 실패";
		AfxMessageBox(strMsg);
		delete pTableDef;
		return false;
	}
*/


	try//필드 생성
	{

/*
		pTableDef	= new CDaoTableDef(pdb);
		pTableDef->Create("DB_INFO");

		pTableDef->CreateField("REV_NO_MAIN" ,	dbLong , 4,	0);
		pTableDef->CreateField("REV_NO_SUB" ,	dbLong , 4 ,0);
		pTableDef->CreateField("REVDATE" ,		dbDate , 8 ,0);	//$Added sjkim 2012-06-05
		pTableDef->CreateField("REVNOTE" ,		dbText , 255 ,0);	

		pTableDef->Append();
		pTableDef->Close();
		delete pTableDef;
*/

		pTableDef = new CDaoTableDef(pdb);
		pTableDef->Create("DBFORM_INFO");

		pTableDef->CreateField("FIELD", dbText, 255, 0);
		pTableDef->CreateField("DATA",  dbText, 255, 0);

		pTableDef->Append();
		pTableDef->Close();
		delete pTableDef;

	}
	catch (CDaoException &ex)
	{
		strMsg = "데이타베이스 테이블 필드 생성 실패";
		AfxMessageBox(strMsg);

		if (pTableDef != NULL)
		{
			pTableDef->Close();
			delete pTableDef;
			return false;
		}

	}
	catch(CMemoryException &ex)
	{
		strMsg = "데이타베이스 테이블 필드 메모리 로드 실패";
		AfxMessageBox(strMsg);
		if (pTableDef != NULL)
		{
			pTableDef->Close();
			delete pTableDef;
			return false;
		}
	}



	return TRUE;
}


BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_TestData_Spec()
{
	CDatabase database;
	CString sSql;
	CString sDriver;

	CString strMsg;
	CDaoDatabase	*pdb = NULL;
	CDaoTableDef	*pTableDef = NULL;

	CDaoFieldInfo rfInfo;
	CDaoFieldInfo wfInfo;

	TRY			//테이블 만듦
	{
		pdb = new CDaoDatabase;
		pdb->Open(m_var.strDBFileName);		//DB파일을 OPEN한다. 

		CDaoTableDef	*pTableDef;
		pTableDef = new CDaoTableDef(pdb);

		pTableDef->Create(m_var.strTableName_DATA_SPEC);


		pTableDef->CreateField("ID", dbLong, 4, dbAutoIncrField);
		//pTableDef->CreateField("PID", dbLong, 4, 0);					// $ 2015.07.02
		pTableDef->CreateField("TNUM", dbLong, 4, 0);

		this->m_daoFunc.f_field_Create_dbText(pTableDef, "SYMBOL", true, 16);
		pTableDef->CreateField("TESTITEM", dbText, 75, 0);

		this->m_daoFunc.f_field_Create_dbText(pTableDef, "UNIT", true, 16);

		pTableDef->CreateField("LSL", dbText, 12, 0);
		pTableDef->CreateField("HSL", dbText, 12, 0);
		pTableDef->CreateField("LIMITMODE", dbLong, 4, 0);
		pTableDef->CreateField("DATAFORMAT", dbText, 8, 0);	// % 4.2f, %08s, %8.4f, %0x02X

		pTableDef->CreateField("TEXTDATA_YN", dbBoolean, 1, 0);
		this->m_daoFunc.f_field_Create_dbText(pTableDef, "TEXTSPEC1", true, 32);
		this->m_daoFunc.f_field_Create_dbText(pTableDef, "TEXTSPEC2", true, 32);

		pTableDef->Append();

		pTableDef->Close();
		delete pTableDef;
		pTableDef = NULL;

		pdb->Close();
		delete pdb;
		pdb = NULL;

	}
	CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);

		if (pTableDef != NULL)
		{
			pTableDef->Close();
			delete pTableDef;
			pTableDef = NULL;
		}

		if (pdb != NULL)
		{
			pdb->Close();
			delete pdb;
			pdb = NULL;

		}
		return false;
	}
	END_CATCH;




	return TRUE;

}

BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_TestData_TEXT()
{
#ifndef TEXTDATA_SAVE_ENABLE
	return TRUE;
#endif

	{
		CDatabase database;
		CString sSql;
		CString sDriver;

		CString strMsg;
		CDaoDatabase	*pdb;
		pdb = new CDaoDatabase;

		CDaoFieldInfo rfInfo;
		CDaoFieldInfo wfInfo;

		TRY			//테이블 만듦
		{
			pdb->Open(m_var.strDBFileName);		//DB파일을 OPEN한다. 

			CDaoTableDef	*pTableDef;
			pTableDef = new CDaoTableDef(pdb);


			try//테이블 생성
			{

				pTableDef->Create(m_var.strTableName_DATA_TEXT);
			}
			catch (CDaoException &ex)
			{
				strMsg = "데이타베이스 테이블 생성 실패";
				AfxMessageBox(strMsg);

				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return false;
			}
			catch (CMemoryException &ex)
			{
				strMsg = "데이타베이스 테이블 메모리 로드 실패";
				AfxMessageBox(strMsg);

				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return false;
			}

			try//필드 생성
			{
				pTableDef->CreateField("ID",	dbLong, 4, dbAutoIncrField);
				pTableDef->CreateField("DNUM",	dbLong, 4, 0);
				pTableDef->CreateField("ARRAY", dbLong, 4, 0);

				CString strFieldName;
				unsigned p;

				for (p = 0; p < m_var.nTitem; p++)				// 필드 갯수는 255개임. 검사항목 숫자를 적당하게 조절해야 함.
				{
					strFieldName.Format("T%03d_TXT", p + 1);

					if (FALSE == m_daoFunc.f_field_Create_dbText(pTableDef, strFieldName, true, 32, 0))
					{
						pTableDef->Close();
						delete pTableDef;

						pdb->Close();
						delete pdb;

						return FALSE;
					}
				}

				pTableDef->CreateField("PassYN", dbBoolean, 1, 0);

				pTableDef->CreateField("StartTime", dbDate, 8, 0);
				//pTableDef->CreateField("SerialNo",		dbText ,	20 ,0);			// SERIAL CODE, MARKING 

			}
			catch (CDaoException &ex)
			{
				strMsg = "데이타베이스 테이블 필드 생성 실패";
				AfxMessageBox(strMsg);

				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return false;
			}
			catch (CMemoryException &ex)
			{
				strMsg = "데이타베이스 테이블 필드 메모리 로드 실패";
				AfxMessageBox(strMsg);

				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return false;
			}

			pTableDef->Append();


			pTableDef->Close();
			delete pTableDef;

			pdb->Close();
			delete pdb;

		}
			CATCH(CDBException, e)
		{
			AfxMessageBox("Database error: " + e->m_strError);

			pdb->Close();
			delete pdb;

			return false;
		}
		END_CATCH;

		return TRUE;
	}
}

BOOL CFunc_TestData_SaveAccess::f_Create_DBTable_TestData ()
{

	if (120 < m_var.nTitem)
	{
		AfxMessageBox("Test Data DB Error :: Test Data Table is not created, (Max Item = 122 )");
		return FALSE;
	}


	CDatabase database;
    CString sSql;
    CString sDriver;
		
	CString strMsg;
	CDaoDatabase	*pdb;
	pdb = new CDaoDatabase;
	
	CDaoFieldInfo rfInfo;
	CDaoFieldInfo wfInfo;

    TRY			//테이블 만듦
    {
		pdb->Open(m_var.strDBFileName);		//DB파일을 OPEN한다. 
		
		CDaoTableDef	*pTableDef;
		pTableDef = new CDaoTableDef(pdb);


		try//테이블 생성
		{

			pTableDef->Create(m_var.strTableName_DATA);
		}
		catch(CDaoException &ex)
		{
			strMsg = "데이타베이스 테이블 생성 실패";
			AfxMessageBox(strMsg);
			
			pTableDef->Close();
			delete pTableDef;

			pdb->Close();
			delete pdb;

			return false;
		}
		catch(CMemoryException &ex)
		{ 
			strMsg = "데이타베이스 테이블 메모리 로드 실패";
			AfxMessageBox(strMsg);
			
			pTableDef->Close();
			delete pTableDef;

			pdb->Close();
			delete pdb;

			return false;
		}

		try//필드 생성
		{


			pTableDef->CreateField("ID" ,		dbLong , 4,dbAutoIncrField);
			//pTableDef->CreateField("PID" ,		dbLong , 4, 0);				// $ 2015.07.02
			pTableDef->CreateField("DNUM" ,		dbLong , 4 ,0);
			pTableDef->CreateField("ARRAY" ,	dbLong,  4 ,0);

			CString strFieldName;

			unsigned p;


			for(p=0; p < m_var.nTitem; p++)				// 필드 갯수는 255개임. 검사항목 숫자를 적당하게 조절해야 함.
			//for (p = 0; p < 80; p++)
			{


				strFieldName.Format("T%03d",p+1);

				if ( m_cfg.pCSpec->m_vTitem[p].Spec.stDataFmt.nMode < ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT)
				{
					pTableDef->CreateField(strFieldName , dbDouble , 8 ,0);	// $ 2015-03-05 <-- pTableDef->CreateField(strFieldName , dbDouble , 10 ,0);
				}
				else
				{
					pTableDef->CreateField(strFieldName , dbLong , 4 ,0);	// $ 2015-03-05 <-- pTableDef->CreateField(strFieldName , dbDouble , 10 ,0);
				}
				
				/*															// $ 2015.07.02 수정
				if (m_BOOL.DATA_TEXTNOTE_bSave)								// $ 2015.07.02 수정
				{
					strFieldName.Format("TXT_%03d",p+1);

					if (FALSE ==  m_daoFunc.f_field_Create_dbText (pTableDef, strFieldName, true, 32, 0) )
					{
						pTableDef->Close();
						delete pTableDef;

						pdb->Close();
						delete pdb;

						return FALSE;
					}
				}
				*/

				{
					strFieldName.Format("T%03d_CHK",p+1);

					if (FALSE ==  m_daoFunc.f_field_Create_dbText (pTableDef, strFieldName, true, 2, 0) )
					{
						pTableDef->Close();
						delete pTableDef;

						pdb->Close();
						delete pdb;

						return FALSE;
					}
				}
		
			}

			pTableDef->CreateField("PassYN" ,			dbBoolean , 1  ,0);
			pTableDef->CreateField("BIN",				dbLong, 4, 0);
			pTableDef->CreateField("StartTime" ,		dbDate ,	8  ,0);
			//pTableDef->CreateField("SerialNo",		dbText ,	20 ,0);			// SERIAL CODE, MARKING 
		
			if (FALSE ==  m_daoFunc.f_field_Create_dbText(pTableDef, "SerialNo", true, 255, 0) )
			{
				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return FALSE;
			} 


			//pTableDef->CreateField("TOOL" ,				dbLong,		4  ,0);	
			//pTableDef->CreateField("TestTime" ,			dbDouble,	8  ,0);
			
			//pTableDef->CreateField("NOTE1" ,			dbLong,	4  ,0);

			
			if (FALSE ==  m_daoFunc.f_field_Create_dbText(pTableDef, "NOTE1", true, 50, 0) )
			{
				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return FALSE;
			} 
			

			if (FALSE ==  m_daoFunc.f_field_Create_dbText(pTableDef, "NOTE2", true, 50, 0) )
			{
				pTableDef->Close();
				delete pTableDef;

				pdb->Close();
				delete pdb;

				return FALSE;
			} 
		}
		catch(CDaoException &ex)
		{
			strMsg = "데이타베이스 테이블 필드 생성 실패";
			AfxMessageBox(strMsg);
			
			pTableDef->Close();
			delete pTableDef;

			pdb->Close();
			delete pdb;

			return false;
		}
		catch(CMemoryException &ex)
		{
			strMsg = "데이타베이스 테이블 필드 메모리 로드 실패";
			AfxMessageBox(strMsg);
			
			pTableDef->Close();
			delete pTableDef;

			pdb->Close();
			delete pdb;

			return false;
		}

		pTableDef->Append();

			
			pTableDef->Close();
			delete pTableDef;

		pdb->Close();
		delete pdb;

	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		
		pdb->Close();
		delete pdb;

		return false;
    }
    END_CATCH;

	return TRUE;
}


BOOL CFunc_TestData_SaveAccess::f_Input_TestMain_to_Table ()
{
	CDatabase database;
    CString sSql;
    CString sDriver;
				
	m_var.strTableName_DATA = "";


    try
    {
/////////////////
        database.Open(NULL,false,false,m_var.strDsn);

		//데이타 테이블없으면 새로추가
		CDBVariant varValue;
		CRecordset recset( &database );


		{
			sSql.Format("SELECT COUNT(DATA_TABLENAME) FROM TEST_MAIN where DEVICENAME='%s' and TESTSPEC='%s' and TESTDATE=#%s#", 
				m_cfg.pCSpec->m_stSpecInfo.tspec.strDeviceName.GetString(), 
				m_cfg.pCSpec->m_stSpecInfo.tspec.strSpecName.GetString(), 
				m_var.strCreateTime.GetString());
		}	

		recset.Open(CRecordset::forwardOnly,sSql,CRecordset::readOnly);		// query문을 수행하여 데이터를 읽어 드린다. 

		recset.GetFieldValue((short)0, varValue,SQL_C_SLONG);				// Query 문을 수행한 결과를 CDBVariant varValue로 추출한다. 
		recset.Close();

		if(varValue.m_lVal == 0)//테이블 없슴 새로추가해야함
		{
			m_BOOL.Table_DATA_bExist = false;

			sSql.Format("SELECT COUNT(ID) FROM TEST_MAIN");						// SQL Query 문 작성 
			recset.Open(CRecordset::forwardOnly,sSql,CRecordset::readOnly);			// SQL Query 문 수행 
			recset.GetFieldValue((short)0, varValue,SQL_C_SLONG);                   // SQL 레코드셑으로 부터 결과값 추출 
			long nTotCnt = varValue.m_lVal;//데이타 테이블의 총레코드 갯수 구함		// 결과값 추출함.
			recset.Close();



			//if (0 == nTotCnt)
			//{
			//	m_var.strTableName_DATA.Format("DATA_%05d", nTotCnt);
			//	m_var.strTableName_DATA_SPEC = m_var.strTableName_DATA + "_SPEC";
			//	m_var.strTableName_DATA_TEXT = m_var.strTableName_DATA + "_TEXT";
			//}
			//else
			{
				sSql.Format("SELECT MAX(ID) FROM TEST_MAIN");						// SQL Query 문 작성 
				recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);			// SQL Query 문 수행 
				recset.GetFieldValue((short)0, varValue, SQL_C_SLONG);                   // SQL 레코드셑으로 부터 결과값 추출 
				long nMaxID = varValue.m_lVal;//데이타 테이블의 총레코드 갯수 구함		// 결과값 추출함.
				recset.Close();


				m_var.strTableName_DATA.Format("DATA_%05d", nMaxID+1);
				m_var.strTableName_DATA_SPEC = m_var.strTableName_DATA + "_SPEC";
				m_var.strTableName_DATA_TEXT = m_var.strTableName_DATA + "_TEXT";
			}



	
			if(TRUE)
				sSql.Format("insert into TEST_MAIN (DEVICENAME,TESTSPEC,LOTNUMBER,TESTDATE,DATA_TABLENAME,SPEC_TABLENAME,TEXT_TABLENAME,TEXTDATA_YN,ITEM_NUM,ARRAY_NUM,SAVEFAIL_YN,COUNT_YN,COUNT_DATA,COUNT_PASS) values \
				('%s','%s','%s',#%s#,'%s','%s','%s','%d','%d','%d','%d','%d','%d','%d')", 
				m_cfg.pCSpec->m_stSpecInfo.tspec.strDeviceName.GetString(),					//m_stTestSpecHeader.strDeviceName, 
				m_cfg.pCSpec->m_stSpecInfo.tspec.strSpecName.GetString(),					//m_stTestSpecHeader.strTestSpec, 
				"",																//m_stTestSpecHeader.strLotNumber,
				m_var.strCreateTime.GetString(),								//m_stTestSpecHeader.strTestDate,
				m_var.strTableName_DATA.GetString(),
				m_var.strTableName_DATA_SPEC.GetString(),
				m_var.strTableName_DATA_TEXT.GetString(),
				0,
				m_var.nTitem,
				m_var.nAr,
				0,0,0,0);
			//$End Modify sjkim 2012-0605

			database.ExecuteSQL(sSql);
			Sleep(100);
		}

		
		//생성된 테이블이나 존재하는 값으로부터 table이름을 찾는다. 
		{
			sSql.Format("SELECT ID,DATA_TABLENAME FROM TEST_MAIN where DEVICENAME='%s' and TESTSPEC='%s' and TESTDATE=#%s#", 
					m_cfg.pCSpec->m_stSpecInfo.tspec.strDeviceName.GetString(),
					m_cfg.pCSpec->m_stSpecInfo.tspec.strSpecName.GetString(),
					m_var.strCreateTime.GetString());

			recset.Open(CRecordset::forwardOnly,sSql,CRecordset::readOnly);		// query문을 수행하여 데이터를 읽어 드린다. 
				
			CDBVariant varValue;
			recset.GetFieldValue("ID", varValue,SQL_C_SLONG);				// Query 문을 수행한 결과를 CDBVariant varValue로 추출한다. 
			m_var.nPID = varValue.m_lVal;
			
			CString strTemp;
			recset.GetFieldValue("DATA_TABLENAME", strTemp);				// Query 문을 수행한 결과를 CDBVariant varValue로 추출한다. 
			m_var.strTableName_DATA = strTemp;

			recset.Close();
		}

		database.Close();
    }
    catch(CDBException &ex)
    {
        AfxMessageBox("Database error // BOOL CFunc_TestData_SaveAccess::f_Input_TestMain_to_Table (): " + ex.m_strError);
		
		database.Close();

		return false;
    }
	catch(CException &ex)
	{
		AfxMessageBox("Database error // BOOL CFunc_TestData_SaveAccess::f_Input_TestMain_to_Table () : ");

		database.Close();

		return false;
	}
   // END_CATCH;


	return true;


}
